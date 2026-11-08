#include <std_include.hpp>

#include "loader/component_loader.hpp"

#include "mods.hpp"
#include "console.hpp"
#include "scheduler.hpp"
#include "filesystem.hpp"
#include "scripting.hpp"

#include <utils/hook.hpp>
#include <utils/string.hpp>
#include <utils/io.hpp>

namespace mods
{
    vars::var_ptr var_fs_mod_path;
    vars::var_ptr var_sv_base_url;

    namespace
    {
        utils::hook::detour fs_module_init_hook;

        enum mod_flag_t
        {
            MOD_FLAG_NONE = (0 << 0),
            MOD_FLAG_NEEDS_RESTART = (1 << 0),
        };

        struct mod_pack_file_t
        {
            std::string name;
            std::uint64_t type;
            std::uint32_t flags;
            game::fox::fs::MountPoint* handle;
        };

        struct mod_info_t
        {
            bool has_info;
            std::uint32_t flags;
            std::string name;
            std::string author;
            std::string version;
            std::optional<std::string> path;
            std::vector<mod_pack_file_t> pack_files;
        };

        mod_info_t current_mod{};

        constexpr const auto mount_point_type_mod = 0x535ED39C638Dull; // "mod"
        constexpr const auto mount_point_flags = 0x20 | 0x1;

        void parse_mod_info(const std::string& data, mod_info_t& info)
        {
            auto mod_info_j = nlohmann::json::parse(data, nullptr, false);
            if (mod_info_j.is_discarded())
            {
                return;
            }

            info.has_info = true;

            auto& flags_j = mod_info_j["flags"];
            if (flags_j.is_number_unsigned())
            {
                info.flags = flags_j.get<std::uint32_t>();
            }

            mod_info_j["name"].get_to(info.name);
            mod_info_j["author"].get_to(info.author);
            mod_info_j["version"].get_to(info.version);

            auto& files = mod_info_j["pack_files"];

            if (!files.is_array())
            {
                return;
            }

            for (auto i = 0u; i < files.size(); i++)
            {
                mod_pack_file_t file{};

                auto& name_j = files[i]["name"];
                auto& type_j = files[i]["type"];
                auto& file_flags_j = files[i]["flags"];

                if (!name_j.is_string())
                {
                    continue;
                }

                file.name = files[i]["name"].get<std::string>();

                if (type_j.is_string())
                {
                    const auto type = type_j.get<std::string>();
                    const auto type_hash = game::fox::FoxStrHash32(type.data(), type.size());
                    file.type = type_hash.id;
                }
                else if (type_j.is_number_unsigned())
                {
                    file.type = type_j.get<std::uint64_t>();
                }
                else
                {
                    file.type = mount_point_type_mod;
                }

                if (file_flags_j.is_number_unsigned())
                {
                    file.flags = file_flags_j.get<std::uint32_t>();
                }
                else
                {
                    file.flags = mount_point_flags;
                }

                info.pack_files.emplace_back(file);
            }
        }

        void register_mod_search_paths(const std::string& path, const bool add)
        {
            if (add)
            {
                filesystem::register_path(path);
            }
            else
            {
                filesystem::unregister_path(path);
            }
        }

        void clear_mod(bool& needs_restart)
        {
            if (current_mod.path.has_value())
            {
                const auto& path = current_mod.path.value();
                console::info("[Mods] Unloading mod: %s\n", path.data());
                register_mod_search_paths(path, false);
            }

            needs_restart |= (current_mod.flags & MOD_FLAG_NEEDS_RESTART) != 0;

            for (auto& file : current_mod.pack_files)
            {
                if (file.handle != nullptr)
                {
                    game::fox::fs::MountPoint_::Destroy(file.handle);
                }
            }

            current_mod = {};
        }

        void autload_mods(const std::string& path, bool pre_load)
        {
            if (!utils::io::directory_exists(path))
            {
                return;
            }

            if (pre_load)
            {
                filesystem::register_path(path);
            }
            else
            {
                const auto files = utils::io::list_files(path);
                for (const auto& file : files)
                {
                    if (!file.ends_with(".dat"))
                    {
                        continue;
                    }

                    add_packfile(file, mount_point_type_mod, mount_point_flags);
                }
            }
        }

        bool set_mod(const std::string& path, bool& needs_restart)
        {
            const auto fs_path = std::filesystem::path(path);
            const auto normal_path = fs_path.lexically_normal().generic_string();

            if (!utils::io::directory_exists(normal_path) || !normal_path.starts_with("mods"))
            {
                console::error("[Mods] Invalid mod path \"%s\"\n", path.data());
                return false;
            }

            if (current_mod.path.has_value() && current_mod.path.value() == normal_path)
            {
                return false;
            }

            clear_mod(needs_restart);

            console::info("[Mods] Loading mod \"%s\"\n", normal_path.data());

            current_mod = {};
            current_mod.path.emplace(normal_path);

            register_mod_search_paths(normal_path, true);

            const auto info_path = std::format("{}\\mod.json", normal_path);

            std::string info_data;
            if (utils::io::read_file(info_path, &info_data))
            {
                parse_mod_info(info_data, current_mod);
            }

            needs_restart |= (current_mod.flags & MOD_FLAG_NEEDS_RESTART) != 0;

            for (auto& file : current_mod.pack_files)
            {
                if (!file.name.ends_with(".dat"))
                {
                    continue;
                }

                const auto pack_path = std::format("{}\\{}", normal_path, file.name);
                file.handle = add_packfile(pack_path, file.type, file.flags);
            }

            return true;
        }

        void fs_module_init_stub()
        {
            console::info("[FS module] Init\n");

            autload_mods("mods/autoload", false);

            const auto& mod_path = var_fs_mod_path->current.get_string();
            if (!mod_path.empty())
            {
                auto needs_restart = false;
                set_mod(mod_path, needs_restart);
            }

            fs_module_init_hook.invoke<void>();
        }

        bool can_load_mod()
        {
            const auto inst = game::tpp::ui::hud::CommonDataManager_::GetInstance();
            const auto ui_inst = game::tpp::ui::menu::UiCommonDataManager_::GetInstance();
            if (inst == nullptr || ui_inst == nullptr)
            {
                return false;
            }

            const auto mission_code = game::tpp::ui::utility::GetCurrentLocationId();
            const auto location_code = game::tpp::ui::utility::GetCurrentMissionId();

            if (mission_code == 0xFFFF || mission_code == 1 || location_code == 0xFFFF || location_code == 1)
            {
                return false;
            }

            return true;
        }

        utils::hook::detour create_pack_mountpoint_hook;
        game::fox::fs::MountPoint* create_pack_mountpoint_stub(const char* type, const char* name, __int64 a3, unsigned int flags)
        {
            const auto res = create_pack_mountpoint_hook.invoke<game::fox::fs::MountPoint*>(type, name, a3, flags);
            if (res != nullptr)
            {
                console::debug("[FS Module] create mount point: %s %s %lli %i\n", type, name, a3, flags);
            }

            return res;
        }

        void reload_assets()
        {
            scripting::script_exec("Mission.LoadLocation({force=true});Mission.LoadMission({force=true})");
        }

        void search_mount_point_stub(utils::hook::assembler& a)
        {
            const auto match = a.new_label();
            
            a.mov(rax, qword_ptr(rsp, 0x90));

            a.test(rsi, rsi);
            a.jz(match);

            a.mov(rax, qword_ptr(rbx));
            a.mov(rax, qword_ptr(rax, 0x18));
            a.mov(rdi, mount_point_type_mod);

            a.cmp(rax, rdi);
            a.jz(match);

            a.cmp(rax, rsi);
            a.jz(match);

            a.jmp(0x14004C0CF_r);

            a.bind(match);
            a.jmp(0x14004C05E_r);
        }

        utils::hook::detour compare_mount_points_hook;
        bool compare_mount_points_stub(game::fox::fs::MountPoint* a, game::fox::fs::MountPoint* b)
        {
            if (a->type == mount_point_type_mod && b->type != mount_point_type_mod)
            {
                return true;
            }

            if (a->type != mount_point_type_mod && b->type == mount_point_type_mod)
            {
                return false;
            }

            return compare_mount_points_hook.invoke<bool>(a, b);
        }

        const char* kernel_string_str(game::fox::KernelString* string)
        {
            if (string->unk3 >= 0x10)
            {
                return string->buffer;
            }
            
            return reinterpret_cast<const char*>(string);
        }

        struct mount_points_map_t
        {
            struct pair_t
            {
                game::fox::StringId key;
                game::fox::fs::MountPoint* value;
            };

            struct node_t;

            struct node_t
            {
                node_t* left;
                node_t* parent;
                node_t* right;
                unsigned char color;
                bool is_nil;
                char __pad0[30];
                pair_t pair;
            };

            node_t* head;
            unsigned __int64 size;
        };

        void print_mount_points_vector(game::fox::fs::MountPoint** iter, game::fox::fs::MountPoint** end, std::size_t& priority)
        {
            while (iter != end)
            {
                const auto mount_point = (*iter);
                const auto name = kernel_string_str(&mount_point->fioMountPoint->name);
                console::info("%i: %s\n", priority++, name);
                iter++;
            }
        }

        void print_mount_points_map(mount_points_map_t* map, std::size_t& priority)
        {
            auto iter = map->head->left;
            while (iter != map->head)
            {
                const auto mount_point = iter->pair.value;
                if (mount_point != nullptr)
                {
                    const auto name = kernel_string_str(&mount_point->fioMountPoint->name);
                    console::info("%i: %s\n", priority++, name);
                }

                if (!iter->is_nil)
                {
                    auto right = iter->right;
                    if (right->is_nil)
                    {
                        mount_points_map_t::node_t* i = nullptr;
                        for (i = iter->parent; !i->is_nil; i = i->parent)
                        {
                            if (iter != i->right)
                            {
                                break;
                            }

                            iter = i;
                        }
                        iter = i;
                    }
                    else
                    {
                        iter = iter->right;
                        for (auto j = right->left; !j->is_nil; j = j->left)
                        {
                            iter = j;
                        }
                    }
                }
            }
        }

        void print_mount_points()
        {
            std::size_t priority{};

            const auto pre_patch_mount_points_beg = *reinterpret_cast<game::fox::fs::MountPoint***>(0x142AE1F70_r);
            const auto pre_patch_mount_points_end = *reinterpret_cast<game::fox::fs::MountPoint***>(0x142AE1F78_r);
            const auto patch_mount_points = reinterpret_cast<mount_points_map_t*>(0x142AE1F60_r);
            const auto mount_points = reinterpret_cast<mount_points_map_t*>(0x142AE1F50_r);

            console::info("[FS] Current mount points:\n");
            print_mount_points_vector(
                pre_patch_mount_points_beg,
                pre_patch_mount_points_end,
                priority);
            print_mount_points_map(patch_mount_points, priority);
            print_mount_points_map(mount_points, priority);
            console::info("--------------------------\n");
        }

        void* sub_14003E400_stub(void* a1, void* a2, void* a3)
        {
            return a3;
        }
    }

    game::fox::fs::MountPoint* add_packfile(const std::string& path, const std::uint64_t type, const std::uint32_t flags)
    {
        console::info("[mods] adding mount point: %s\n", path.data());

        const auto abs_path = std::filesystem::absolute(path);
        const auto path_str = abs_path.generic_string();

        const auto handle = game::fox::fs::MountPoint_::CreateWithPackFile(path.data(), path_str.data(), type, flags);
        if (handle)
        {
            game::fox::fs::FileLocationManager_::SetIoHandleCount(handle, 0x10);
        }
        else
        {
            console::error("[fs] failed to create pack file %s\n", path.data());
        }

        return handle;
    }

    game::fox::fs::MountPoint* add_packfile(const std::string& path, const std::string& type, const std::uint32_t flags)
    {
        const auto type_hash = game::fox::FoxStrHash32(type.data(), type.size());
        return add_packfile(path, type_hash.id, flags);
    }

    void load(const std::string& path, const std::optional<std::string>& arg)
    {
        auto needs_restart = false;
        if (!set_mod(path, needs_restart))
        {
            return;
        }

        vars::set_var(var_fs_mod_path, path, vars::var_source_internal);

        if (needs_restart)
        {
            auto cmd = std::format("+fs_mod \"{}\" {}", path, arg.value_or(""));
            utils::nt::relaunch_self(cmd, true);
            utils::nt::terminate();
            return;
        }

        reload_assets();
    }

    void unload(const std::optional<std::string>& arg)
    {
        auto needs_restart = false;

        clear_mod(needs_restart);
        vars::set_var(var_fs_mod_path, "", vars::var_source_internal);

        if (needs_restart)
        {
            auto cmd = std::format("{}", arg.value_or(""));
            utils::nt::relaunch_self("", true);
            utils::nt::terminate();
            return;
        }

        reload_assets();
    }

    class component final : public component_interface
    {
    public:
        void pre_load() override
        {
            var_fs_mod_path = vars::register_string("fs_mod", "", vars::var_flag_readonly, "mod folder path");
            fs_module_init_hook.create(0x14003BC00_r, fs_module_init_stub);
            create_pack_mountpoint_hook.create(game::fox::fs::MountPoint_::CreateWithPackFile, create_pack_mountpoint_stub);
            
            utils::hook::jump(0x14004C050_r, utils::hook::assemble(search_mount_point_stub), true);
            compare_mount_points_hook.create(0x14004BD20_r, compare_mount_points_stub);

            // return correct hash instead of patch manifest thing
            utils::hook::jump(0x14003E400_r, sub_14003E400_stub, true);
        }

        void post_load() override
        {
            autload_mods("mods/autoload", true);

            const auto& fs_mod = var_fs_mod_path->current.get_string();
            if (!fs_mod.empty())
            {
                register_mod_search_paths(fs_mod, true);
            }
        }

        void start() override
        {
            scheduler::once(print_mount_points, scheduler::main);

            command::add("unloadmod", []()
            {
                if (var_fs_mod_path->current.get_string().empty())
                {
                    console::warn("no mod loaded\n");
                    return;
                }

                if (!can_load_mod())
                {
                    console::warn("cannot load mods right now");
                    return;
                }

                unload();
            });

            command::add("loadmod", [](const command::params& params)
            {
                if (params.size() < 2)
                {
                    return;
                }

                const auto path = params.get(1);
                if (!utils::io::directory_exists(path))
                {
                    console::warn("mod path %s not found!\n", path.data());
                    return;
                }

                if (!can_load_mod())
                {
                    return;
                }

                load(path);
            });
        }
    };
}

REGISTER_COMPONENT(mods::component)
