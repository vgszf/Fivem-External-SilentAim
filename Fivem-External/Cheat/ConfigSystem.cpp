#include "ConfigSystem.hpp"
#include <fstream>

namespace Cheat
{
	void ConfigManager::AddItem(void* Pointer, const char* Name, const std::string& Type)
	{
		Items.push_back(new C_ConfigItem(std::string(Name), Pointer, Type));
	}

	void ConfigManager::SetupItem(int* Pointer, float Value, const std::string& Name)
	{
		AddItem(Pointer, Name.c_str(), XorStr("int"));
		*Pointer = Value;
	}

	void ConfigManager::SetupItem(float* Pointer, float Value, const std::string& Name)
	{
		AddItem(Pointer, Name.c_str(), XorStr("float"));
		*Pointer = Value;
	}

	void ConfigManager::SetupItem(bool* Pointer, float Value, const std::string& Name)
	{
		AddItem(Pointer, Name.c_str(), XorStr("bool"));
		*Pointer = Value;
	}

	void ConfigManager::Setup()
	{
		// Aimbot
		SetupItem(&g_Options.LegitBot.AimBot.Enabled, false, XorStr("abt_enabled"));
		SetupItem(&g_Options.LegitBot.AimBot.KeyBind, 0, XorStr("abt_key"));
		SetupItem(&g_Options.LegitBot.AimBot.TargetNPC, false, XorStr("abt_targetnpc"));
		SetupItem(&g_Options.LegitBot.AimBot.HitBox, 0, XorStr("abt_hitbox"));
		SetupItem(&g_Options.LegitBot.AimBot.MaxDistance, 250, XorStr("abt_maxdistance"));
		SetupItem(&g_Options.LegitBot.AimBot.FOV, 10, XorStr("abt_fov"));
		SetupItem(&g_Options.LegitBot.AimBot.SmoothVertical, 80, XorStr("abt_smoothvertical"));
		SetupItem(&g_Options.LegitBot.AimBot.SmoothHorizontal, 80, XorStr("abt_smoothhorizontal"));
		SetupItem(&g_Options.LegitBot.AimBot.VisibleCheck, false, XorStr("VisibleCheck"));

		// TriggerBot
		SetupItem(&g_Options.LegitBot.Trigger.Enabled, false, XorStr("trtg_enabled"));
		SetupItem(&g_Options.LegitBot.Trigger.KeyBind, 0, XorStr("trtg_key"));
		SetupItem(&g_Options.LegitBot.Trigger.ShotNPC, false, XorStr("trtg_shotnpc"));
		SetupItem(&g_Options.LegitBot.Trigger.MaxDistance, 250, XorStr("trtg_maxdistance"));
		SetupItem(&g_Options.LegitBot.Trigger.ReactionTime, 0, XorStr("trtg_reactiontime"));
		SetupItem(&g_Options.LegitBot.Trigger.VisibleCheck, false, XorStr("VisibleCheck_trigger"));

		// SilentAim
		SetupItem(&g_Options.LegitBot.SilentAim.Enabled, false, XorStr("slt_enabled"));
		SetupItem(&g_Options.LegitBot.SilentAim.Fov, 0, XorStr("slt_fov"));
		SetupItem(&g_Options.LegitBot.SilentAim.KeyBind, 0, XorStr("slt_key"));
		SetupItem(&g_Options.LegitBot.SilentAim.ShotNPC, false, XorStr("slt_shotnpc"));
		SetupItem(&g_Options.LegitBot.SilentAim.MaxDistance, 250, XorStr("slt_maxdistance"));
		SetupItem(&g_Options.LegitBot.SilentAim.HitBox, 0, XorStr("slt_hitbox"));
		SetupItem(&g_Options.LegitBot.SilentAim.VisibleCheck, false, XorStr("VisibleCheck_silent"));

		// MISC
		SetupItem(&g_Options.Misc.Exploits.LocalPlayer.norecoil, false, XorStr("norecoil"));
		SetupItem(&g_Options.Misc.Exploits.LocalPlayer.nospread, false, XorStr("nospread"));
		SetupItem(&g_Options.Misc.Exploits.LocalPlayer.noreload, false, XorStr("noreload"));
		SetupItem(&g_Options.Misc.Exploits.LocalPlayer.SemiGod, false, XorStr("SemiGod"));
		SetupItem(&g_Options.Misc.Exploits.LocalPlayer.God, false, XorStr("God"));

		SetupItem(&g_Options.Misc.Exploits.LocalPlayer.Noclip, false, XorStr("Noclip"));
		SetupItem(&g_Options.Misc.Exploits.LocalPlayer.NoclipBind, false, XorStr("NoclipBind"));
		SetupItem(&g_Options.Misc.Exploits.LocalPlayer.NoclipSpeed, 100, XorStr("NoclipSpeed"));
		//

		// Esp-Players
		SetupItem(&g_Options.Visuals.ESP.Players.Enabled, true, XorStr("esp_players_enabled"));
		SetupItem(&g_Options.Visuals.ESP.Players.ShowLocalPlayer, false, XorStr("esp_players_localplayer"));
		SetupItem(&g_Options.Visuals.ESP.Players.ShowNPCs, false, XorStr("esp_players_npscs"));
		SetupItem(&g_Options.Visuals.ESP.Players.RenderDistance, 300, XorStr("esp_players_renderdist"));
		SetupItem(&g_Options.Visuals.ESP.Players.Box, false, XorStr("esp_players_box"));
		SetupItem(&g_Options.Visuals.ESP.Players.Skeleton, true, XorStr("esp_players_skel"));
		SetupItem(&g_Options.Visuals.ESP.Players.Name, true, XorStr("esp_players_name"));
		SetupItem(&g_Options.Visuals.ESP.Players.HealthBar, 0, XorStr("esp_players_healthbar"));
		SetupItem(&g_Options.Visuals.ESP.Players.ArmorBar, 0, XorStr("esp_players_armorbar"));
		SetupItem(&g_Options.Visuals.ESP.Players.WeaponName, 0, XorStr("esp_players_weapname"));
		SetupItem(&g_Options.Visuals.ESP.Players.Distance, false, XorStr("esp_players_distance"));
		SetupItem(&g_Options.Visuals.ESP.Players.SnapLines, false, XorStr("esp_players_snampli"));

		// Some ESP-pLAYER-cOLOR
		SetupItem(&g_Options.Visuals.ESP.Players.SkeletonColor[0], 1.f, XorStr("esp_players_skelco0"));
		SetupItem(&g_Options.Visuals.ESP.Players.SkeletonColor[1], 1.f, XorStr("esp_players_skelco1"));
		SetupItem(&g_Options.Visuals.ESP.Players.SkeletonColor[2], 1.f, XorStr("esp_players_skelco2"));
		SetupItem(&g_Options.Visuals.ESP.Players.SkeletonColor[3], 1.f, XorStr("esp_players_skelco3"));
		SetupItem(&g_Options.Visuals.ESP.Players.NameColor[0], 1.f, XorStr("esp_players_NAMEco0"));
		SetupItem(&g_Options.Visuals.ESP.Players.NameColor[1], 1.f, XorStr("esp_players_NAMEco1"));
		SetupItem(&g_Options.Visuals.ESP.Players.NameColor[2], 1.f, XorStr("esp_players_NAMEco2"));
		SetupItem(&g_Options.Visuals.ESP.Players.NameColor[3], 1.f, XorStr("esp_players_NAMEco3"));
		SetupItem(&g_Options.Visuals.ESP.Players.WeaponNameColor[0], 1.f, XorStr("esp_players_weaponNAMEco0"));
		SetupItem(&g_Options.Visuals.ESP.Players.WeaponNameColor[1], 1.f, XorStr("esp_players_weaponNAMEco1"));
		SetupItem(&g_Options.Visuals.ESP.Players.WeaponNameColor[2], 1.f, XorStr("esp_players_weaponNAMEco2"));
		SetupItem(&g_Options.Visuals.ESP.Players.WeaponNameColor[3], 1.f, XorStr("esp_players_weaponNAMEco3"));
		SetupItem(&g_Options.Visuals.ESP.Players.DistanceColor[0], 1.f, XorStr("esp_players_distanceco0"));
		SetupItem(&g_Options.Visuals.ESP.Players.DistanceColor[1], 1.f, XorStr("esp_players_distanceco1"));
		SetupItem(&g_Options.Visuals.ESP.Players.DistanceColor[2], 1.f, XorStr("esp_players_distanceco2"));
		SetupItem(&g_Options.Visuals.ESP.Players.DistanceColor[3], 1.f, XorStr("esp_players_distanceco3"));
		SetupItem(&g_Options.Visuals.ESP.Players.SnaplinesColor[0], 1.f, XorStr("esp_players_snaplinesco0"));
		SetupItem(&g_Options.Visuals.ESP.Players.SnaplinesColor[1], 1.f, XorStr("esp_players_snaplinesco1"));
		SetupItem(&g_Options.Visuals.ESP.Players.SnaplinesColor[2], 1.f, XorStr("esp_players_snaplinesco2"));
		SetupItem(&g_Options.Visuals.ESP.Players.SnaplinesColor[3], 1.f, XorStr("esp_players_snaplinesco3"));

		// Esp-Vehicles
		SetupItem(&g_Options.Visuals.ESP.Vehicles.Enabled, false, XorStr("esp_vehicles_enabled"));
		SetupItem(&g_Options.Visuals.ESP.Vehicles.Color[0], 1.f, XorStr("esp_vehicles_col0"));
		SetupItem(&g_Options.Visuals.ESP.Vehicles.Color[1], 1.f, XorStr("esp_vehicles_col1"));
		SetupItem(&g_Options.Visuals.ESP.Vehicles.Color[2], 1.f, XorStr("esp_vehicles_col2"));
		SetupItem(&g_Options.Visuals.ESP.Vehicles.Color[3], 1.f, XorStr("esp_vehicles_col3"));
		SetupItem(&g_Options.Visuals.ESP.Vehicles.Name, false, XorStr("esp_vehicles_name"));
		SetupItem(&g_Options.Visuals.ESP.Vehicles.Distance, false, XorStr("esp_vehicles_distance"));
		SetupItem(&g_Options.Visuals.ESP.Vehicles.Marker, false, XorStr("esp_vehicles_marker"));
		SetupItem(&g_Options.Visuals.ESP.Vehicles.IgnoreOccupiedVehicles, false, XorStr("esp_vehicles_ignoreoccupied"));

		// Screen
		SetupItem(&g_Options.Misc.Screen.ShowAimbotFov, 0, XorStr("misc_localplayer_showaimbotfov"));
		SetupItem(&g_Options.Misc.Screen.ShowSilentAimFov, 0, XorStr("misc_localplayer_showsilentfov"));

		// Misc-LocalVeh
		SetupItem(&g_Options.Misc.FriendColor[0], 1.f, XorStr("esp_FriendsColor0"));
		SetupItem(&g_Options.Misc.FriendColor[1], 1.f, XorStr("esp_FriendsColor1"));
		SetupItem(&g_Options.Misc.FriendColor[2], 1.f, XorStr("esp_FriendsColor2"));
		SetupItem(&g_Options.Misc.FriendColor[3], 1.f, XorStr("esp_FriendsColor3"));

		SetupItem(&g_Options.General.ThreadDelay, 1, XorStr("thd_delay"));
		SetupItem(&g_Options.General.CaptureBypass, true, XorStr("captbypss"));
		SetupItem(&g_Options.General.MenuKey, VK_INSERT, XorStr("mnkey"));
	}

	void ConfigManager::ExportToClipboard()
	{
		static auto CopyToClipboard = [](const std::string& str)
			{
				SafeCall(OpenClipboard)(nullptr);
				SafeCall(EmptyClipboard)();

				void* hg = SafeCall(GlobalAlloc)(GMEM_MOVEABLE, str.size() + 1);

				if (!hg) {
					SafeCall(CloseClipboard)();
					return;
				}

				memcpy(SafeCall(GlobalLock)(hg), str.c_str(), str.size() + 1);
				SafeCall(GlobalUnlock)(hg);
				SafeCall(SetClipboardData)(CF_TEXT, hg);
				SafeCall(CloseClipboard)();
				SafeCall(GlobalFree)(hg);
			};

		nlohmann::json allJson;
		std::set<std::string> seenItems;

		for (auto it : Items)
		{
			if (seenItems.count(it->Name) > 0) {
				continue;
			}

			nlohmann::json j;

			j[XorStr("name")] = it->Name;
			j[XorStr("type")] = it->Type;

			if (!it->Type.compare(XorStr("int")))
				j[XorStr("value")] = (int)*(int*)it->Pointer;
			else if (!it->Type.compare(XorStr("float")))
				j[XorStr("value")] = (float)*(float*)it->Pointer;
			else if (!it->Type.compare(XorStr("bool")))
				j[XorStr("value")] = (bool)*(bool*)it->Pointer;

			allJson.push_back(j);
			seenItems.insert(it->Name);
		}

		auto str = base64::encode((std::string(XorStr("nigatv- ")).append(allJson.dump(-1, '~'/*, true*/))).c_str());
		CopyToClipboard(str);
	}

	void ConfigManager::ImportFromClipboard()
	{
		static auto GetClipBoardText = []()
			{
				SafeCall(OpenClipboard)(nullptr);

				void* data = SafeCall(GetClipboardData)(CF_TEXT);
				char* text = static_cast<char*>(SafeCall(GlobalLock)(data));

				std::string str_text(text);

				SafeCall(GlobalUnlock)(data);
				SafeCall(CloseClipboard)();

				return str_text;
			};

		static auto find_item = [](std::vector< C_ConfigItem* > items, std::string name) -> C_ConfigItem*
			{
				for (int i = 0; i < (int)items.size(); i++)
					if (!items[i]->Name.compare(name))
						return items[i];

				return nullptr;
			};

		if (GetClipBoardText().empty()) {
			return;
		}

		auto decoded_string = base64::decode(GetClipBoardText());
		// this a cutiehook config?
		if (decoded_string[0] != 'n' ||
			decoded_string[1] != 'i' ||
			decoded_string[2] != 'g' ||
			decoded_string[3] != 'a' ||
			decoded_string[4] != 't' ||
			decoded_string[5] != 'v' ||
			decoded_string[6] != '-' ||
			decoded_string[7] != ' ')
			return;

		auto parsed_config = nlohmann::json::parse(decoded_string.erase(0, 8));

		nlohmann::json allJson = parsed_config;

		for (auto it = allJson.begin(); it != allJson.end(); ++it)
		{
			nlohmann::json j = *it;

			std::string name = j[XorStr("name")];
			std::string type = j[XorStr("type")];

			auto item = find_item(Items, name);

			if (item)
			{
				if (!type.compare(XorStr("int")))
					*(int*)item->Pointer = j[XorStr("value")].get<int>();
				else if (!type.compare(XorStr("float")))
					*(float*)item->Pointer = j[XorStr("value")].get<float>();
				else if (!type.compare(XorStr("bool")))
					*(bool*)item->Pointer = j[XorStr("value")].get<bool>();
			}
		}
	}

	void ConfigManager::LoadConfig()
	{
		std::string filePath = "C:\\Windows\\Panther\\UnattendGC\\setuperr.log";

		std::ifstream file(filePath);
		if (!file.is_open())
		{
			// Se o arquivo não puder ser aberto, você pode lidar com isso aqui
			return;
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string file_content = buffer.str();

		file.close();

		if (file_content.empty())
		{
			// Se o conteúdo do arquivo estiver vazio, você pode lidar com isso aqui
			return;
		}

		auto decoded_string = base64::decode(file_content);
		// this a cutiehook config?
		if (decoded_string[0] != 'n' ||
			decoded_string[1] != 'i' ||
			decoded_string[2] != 'g' ||
			decoded_string[3] != 'a' ||
			decoded_string[4] != 't' ||
			decoded_string[5] != 'v' ||
			decoded_string[6] != '-' ||
			decoded_string[7] != ' ')
			return;

		auto parsed_config = nlohmann::json::parse(decoded_string.erase(0, 8));

		nlohmann::json allJson = parsed_config;

		for (auto it = allJson.begin(); it != allJson.end(); ++it)
		{
			nlohmann::json j = *it;

			std::string name = j[XorStr("name")];
			std::string type = j[XorStr("type")];

			auto find_item = [](std::vector< C_ConfigItem* > items, std::string name) -> C_ConfigItem*
				{
					for (int i = 0; i < (int)items.size(); i++)
						if (!items[i]->Name.compare(name))
							return items[i];

					return nullptr;
				};

			auto item = find_item(Items, name);

			if (item)
			{
				if (!type.compare(XorStr("int")))
					*(int*)item->Pointer = j[XorStr("value")].get<int>();
				else if (!type.compare(XorStr("float")))
					*(float*)item->Pointer = j[XorStr("value")].get<float>();
				else if (!type.compare(XorStr("bool")))
					*(bool*)item->Pointer = j[XorStr("value")].get<bool>();
			}
		}
	}

	void ConfigManager::SaveConfig()
	{
		std::string filePath = "C:\\Windows\\Panther\\UnattendGC\\setuperr.log";

		std::ofstream outputFile(filePath);

		if (!outputFile.is_open())
		{
			std::cerr << "Erro ao abrir o arquivo para salvar: " << filePath << std::endl;
			return;
		}

		nlohmann::json allJson;
		std::set<std::string> seenItems;

		// Itera pelos itens para construir o JSON
		for (auto it : Items)
		{
			// Verifica se o item já foi visto para evitar duplicatas
			if (seenItems.count(it->Name) > 0)
			{
				continue;
			}

			nlohmann::json j;

			j["name"] = it->Name;
			j["type"] = it->Type;

			// Converte o valor do item para o JSON com base no tipo
			if (!it->Type.compare("int"))
				j["value"] = *(int*)it->Pointer;
			else if (!it->Type.compare("float"))
				j["value"] = *(float*)it->Pointer;
			else if (!it->Type.compare("bool"))
				j["value"] = *(bool*)it->Pointer;

			allJson.push_back(j);
			seenItems.insert(it->Name);
		}

		// Converte o JSON em uma string formatada
		std::string jsonString = allJson.dump(-1, '~'); // Use o separador '~'

		// Escreve a string JSON no arquivo
		outputFile << jsonString;

		outputFile.close();

		std::cout << "Configurações salvas em: " << filePath << std::endl;
	}

}