#pragma once

namespace backend_server
{
	bool is_using_custom_server();

	std::optional<nlohmann::json> send_command(const std::string& endpoint, const char* cmd, bool use_session);
	std::optional<nlohmann::json> send_command(const std::string& endpoint, const nlohmann::json& data, bool use_session);
	std::string get_gate_url();
	std::string get_user_storage_path();
	std::string get_url_hash();
}
