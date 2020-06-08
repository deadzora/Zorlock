#pragma once

namespace Zorlock {

	static const char* skins[] = { "Twilight", "Night", "Dark", "Light" };
	static const char* skin_current = skins[0];

	class ImGuiSkin
	{
	public:
		static std::string GetTypeIcon(std::string type);
		static void MapTypes();
		static void Night();
		static void Dark();
		static void Light();
		static void Twilight();		
		static void SetAlpha(float a);
		static void SetFont();
		static void PushFont();
		static void PushIconFont();
		static void SetSkin(size_t i)
		{
			switch (i)
			{
			case 0:
			{
				Twilight();
				break;
			}
			case 1:
			{
				Night();
				break;
			}
			case 2:
			{
				Dark();
				break;
			}
			case 3:
			{
				Light();
				break;
			}
			}
		}
	};

}
#define ZLSETFONT Zorlock::ImGuiSkin::SetFont(); Zorlock::ImGuiSkin::MapTypes();
#define ZLIMGUIALPHA(a) Zorlock::ImGuiSkin::SetAlpha(a);
#define ZLIMGUILIGHT Zorlock::ImGuiSkin::Light();
#define ZLIMGUINIGHT Zorlock::ImGuiSkin::Night();
#define ZLIMGUIDARK Zorlock::ImGuiSkin::Dark();
#define ZLIMGUITWILIGHT Zorlock::ImGuiSkin::Twilight();