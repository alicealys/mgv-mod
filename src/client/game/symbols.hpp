#pragma once

#define WEAK __declspec(selectany)

namespace game
{
	namespace fox
	{
		WEAK symbol<impl::TimeSystemImpl()> GetTimeSystem{0x1400FC6D0};

		WEAK symbol<bool(RawKeyboardData*, RAWKEYBOARD*)> GetRawKeyboardData{0x141964970};

		WEAK symbol<void*(unsigned __int64, unsigned int)> KernelAllocAligned{0x1400167D0};
		WEAK symbol<void(void*, unsigned int)> FreeAnnotated{0x140016830};

		WEAK symbol<QuarkSystemTable*()> GetQuarkSystemTable{0x141989050};

		WEAK symbol<StringId(const char*, size_t)> FoxStrHash32{0x140023A40};

		WEAK symbol<unsigned int(unsigned __int8**)> Utf8ToUtf32{0x140023E80};

		namespace AssetConfiguration_
		{
			WEAK symbol<SharedString*()> GetLanguage{0x14017BC80};
		}

		namespace Color_
		{
			WEAK symbol<unsigned int(Color*)> EncodeUInt32RGBA{0x1401CBB30};
		}

		namespace KeyboardListener_
		{
			WEAK symbol<void(fox::RawKeyboardData*)> SetRawKeyData{0x140031790};
		}

		namespace MouseListener_
		{
			WEAK symbol<void(fox::RawMouseData*)> SetRawData{0x1400327F0};
		}

		namespace fs
		{
			namespace PathCodeImpl_
			{
				WEAK symbol<__int64(const char*)> FromString{0x140042150};
			}
		}

		namespace gr
		{
			WEAK symbol<void*(dg::StringFontMetricsCache*, const char*, int, int)> InitMetrics{0x1402BF370};

			WEAK symbol<void(_fp16*, Vectormath::Aos::Vector4*)> ConvertFloat4toHalf4{0x140314AB0};
			WEAK symbol<void(Vectormath::Aos::Vector4*, _fp16*)> ConvertHalf4toFloat4{0x140314CB0};

			WEAK symbol<unsigned char> g_packetSize{0x1428D91F0};

			WEAK symbol<RenderWork*> g_renderWork{0x0};

			namespace Draw2D_
			{
				WEAK symbol<void(Draw2D*, unsigned int, unsigned int)> Draw2D_{0x1401CB450};
			}

			namespace Material_
			{
				WEAK symbol<Material**(Material**, StringId*)> Create{0x0};
				WEAK symbol<void(Material*, StringId*)> BindShaderTechnique{0x0};
				WEAK symbol<void(Material*, unsigned int, Texture*)> BindTexture{0x0};
				WEAK symbol<void(Material*, unsigned int, Vectormath::Aos::Vector4*)> BindParameter{0x0};
				WEAK symbol<void(Material*, StringId*)> Material_{0x0};
			}

			namespace Scene_
			{
				WEAK symbol<Scene*()> GetDefaultScene{0x1401C0870};
				WEAK symbol<void(Scene*, Draw2D*)> Queue{0x1401C0A20};
			}

			namespace Texture_
			{
				WEAK symbol<Texture**(Texture**, StringId*)> Create{0x0};
			}

			namespace Font_
			{
				WEAK symbol<int(const char*, float*, bool, unsigned int)> GetStringWidth{0x0};
			}

			namespace dg
			{
				WEAK symbol<DgDx11*()> GetDgInstance{0x0};

				namespace CommandBuffer_
				{
					WEAK symbol<void(CommandBuffer*, int, unsigned int)> SetTexture{0x1402E96B0};
					WEAK symbol<void(CommandBuffer*, int, void*, int)> SetVector{0x1402E9780};
				}

				namespace DynamicVertexBuffer_
				{
					WEAK symbol<char*(DynamicVertexBuffer*, gn::Buffer**, unsigned int*, int)> GetBuffer{0x1402C9F60};
				}

				namespace ImageGlyphManager_
				{
					WEAK symbol<_TextureGlyphData*(ImageGlyphManager*, unsigned int)> SearchGlyphData{0x140233880};
					WEAK symbol<_TextureGlyphData*(ImageGlyphManager*, FontData*, _TextureAreaInfo*, unsigned int)> RegisterGlyphData{0x140232CD0};
				}

				namespace ImageAreaManager_
				{
					WEAK symbol<_TextureAreaInfo*(ImageAreaManager*, unsigned char, unsigned char, unsigned int)> AllocateAreaInfo{0x1402317A0};
				}

				namespace FontSystem_
				{
					WEAK symbol<FontSystem*> m_instance{0x142B12290};

					WEAK symbol<void*(FontSystem*, const char*, int)> RegisterString{0x140232EC0};
					WEAK symbol<void(FontSystem*, float*, float*)> GetHalfPixelWH{0x140232370};
					WEAK symbol<unsigned int(FontSystem*)> GetFontTextureHandle{0x140232210};
					WEAK symbol<_TextureGlyphData*(FontSystem*)> GetFontTextureGlyphDataTop{0x140232160};
					WEAK symbol<void(FontTextureMetrics*, _TextureGlyphData*, float, float, float)> CalculateMetrics{0x140231A10};
				}

				namespace FontData_
				{
					WEAK symbol<char(FontData*, const char*, const char*)> LoadFontData{0x1402325F0};
				}

				namespace FontTextureRender_
				{
					WEAK symbol<void(FontTextureRender*, unsigned int, unsigned int)> FontTextureRender_{0x140230C10};
					WEAK symbol<void(FontTextureRender*)> UpdateRenderGlyphTexture{0x1402341F0};
					WEAK symbol<void(FontTextureRender*, FontData*, FontData_Glyph*, _TextureGlyphData*)> AddTextureRenderOrder{0x1402316B0};
				}

				namespace TextureManager_
				{
					WEAK symbol<ResourceId(Path*)> CreateResourceFromFile{0x0};
				}

				namespace DgTextureStreamer_
				{
					WEAK symbol<DgTextureStreamer*()> Instance{0x0};
					WEAK symbol<bool(DgTextureStreamer*)> IsEnable{0x0};
					WEAK symbol<bool(DgTextureStreamer*, ResourceId, char)> RequestTextureDetailByDgTexture{0x0};
					WEAK symbol<bool(DgTextureStreamer*, ResourceId, char)> UnRequestTextureDetailByDgTexture{0x0};
				}

				namespace ResourceManagerBase_
				{
					namespace TextureResource_
					{
						WEAK symbol<void(ResourceId)> DeleteResource{0x0};
					}
				}

				namespace plugins
				{
					namespace Draw2DRenderer_
					{
						WEAK symbol<void(Draw2DRenderer*)> InitRenderingState{0x1402F83C0};
						WEAK symbol<void(Draw2DRenderer*)> InitPerObject{0x1402F8280};

						WEAK symbol<void(Draw2DRenderer*)> UpdateViewMapping{0x1402F9F40};

						WEAK symbol<void(Draw2DRenderer*, int, int, int)> DrawVertices{0x1402F7AA0};

						/* 01 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DLine*)> Execute_Packet2DLine{0x1402F3040};
						/* 02 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DTriangle*)> Execute_Packet2DTriangle{0x1402F51C0};
						/* 03 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DQuad*)> Execute_Packet2DQuad{0x1402F3A60};
						/* 04 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DBox*)> Execute_Packet2DBox{0x1402F0D40};
						/* 05 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DSprite*)> Execute_Packet2DSprite{0x1402F49E0};
						/* 06 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DSprite2D*)> Execute_Packet2DSprite2D{0x1402F45C0};
						/* 07 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DRSprite*)> Execute_Packet2DRSprite{0x1402F3DA0};
						/* 08 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DString*)> ExecuteOnly_Packet2DString{0x1402F5B20};
						/* 09 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DString2D*)> Execute_Packet2DString2D{0x1402F4F20};
						/* 10 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DCube*)> Execute_Packet2DCube{0x1402F1310};
						/* 11 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DLineStrip*)> Execute_Packet2DLineStrip{0x1402F3230};
						/* 12 */ template<size_t Count> symbol<void*(Draw2DRenderer*, Packet2DTriangleStrip<Count>*)> Execute_Packet2DTriangleStrip{0x1402F5450};
						/* 13 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DViewport*)> Execute_Packet2DViewport{0x1402F57A0};
						/* 14 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DViewmap*)> Execute_Packet2DViewmap{0x1402F5740};
						/* 15 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DWorldCoords*)> Execute_Packet2DWorldCoords{0x1402F5940};
						/* 16 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DScreenCoords*)> Execute_Packet2DScreenCoords{0x1402F44A0};
						/* 17 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DMatrix*)> Execute_Packet2DMatrix{0x1402F3500};
						/* 18 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DRotation*)> Execute_Packet2DRotation{0x1402F43A0};
						/* 19 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DTranslation*)> Execute_Packet2DTranslation{0x1402F5140};
						/* 20 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DScale*)> Execute_Packet2DScale{0x1402F4420};
						/* 21 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DBillboard*)> Execute_Packet2DBillboard{0x1402F0180};
						/* 22 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DPerspective*)> Execute_Packet2DPerspective{0x1402F35B0};
						/* 23 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DFlat*)> Execute_Packet2DFlat{0x1402F2FF0};
						/* 24 */ WEAK symbol<void*(Draw2DRenderer*, char)> SetDepthMode{0x1402F8BB0};
						/* 25 */ WEAK symbol<void*(Draw2DRenderer*, char)> SetCullMode{0x1402F8AB0};
						/* 26 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DTexture*)> Execute_Packet2DTexture{0x1402F5090};
						/* 27 */ WEAK symbol<void*(Draw2DRenderer*, char)> SetAlpha{0x1402F8790};
						/* 28 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DColor*)> Execute_Packet2DColor{0x1402F1180};
						/* 29 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DStencil*)> SetStencil{0x1402F8C60};
						/* 30 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DClearStencil*)> Execute_Packet2DClearStencil{0x1402F1130};
						/* 32 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DMaterial*)> Execute_Packet2DMaterial{0x1402F33E0};
						/* 33 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DMaterialWork*)> Execute_Packet2DMaterialWork{0x1402F34B0};
						/* 34 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DUserMatrix*)> Execute_Packet2DUserMatrix{0x1402F55C0};
						/* 38 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DPush*)> Execute_Packet2DPush{0x1402F39D0};
						/* 39 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DPop*)> Execute_Packet2DPop{0x1402F3900};
						/* 40 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DResolve*)> Execute_Packet2DResolve{0x1402F4340};
						/* 41 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DCopyRenderTarget*)> Execute_Packet2DCopyRenderTarget{0x1402F1280};
						/* 45 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DDrawIndices*)> Execute_Packet2DDrawIndices{0x1402F2C50};
						/* 46 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DUserVertexBuffer*)> Execute_Packet2DUserVertexBuffer{0x1402F5630};
						/* 47 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DBeginRenderToTemporary*)> Execute_Packet2DBeginRenderToTemporary{0x1402F0020};
						/* 48 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DEndRenderToTemporary*)> Execute_Packet2DEndRenderToTemporary{0x1402F2DE0};
						/* 49 */ WEAK symbol<void*(Draw2DRenderer*, Packet2DSetTemporaryTexture*)> Execute_Packet2DSetTemporaryTexture{0x1402F4520};
					}
				}
			}
		}
	}

	WEAK symbol<fox::RawKeyboardData> g_rawMouseData{0x1430B9C98};

	WEAK symbol<steam_interfaces_t> g_steamInterfaces{0x142AD71F0};

	namespace fox
	{
		WEAK symbol<int> g_vkKeyTable{0x1430B9890};
	}
}
