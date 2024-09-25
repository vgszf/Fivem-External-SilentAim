#pragma once
#include "VehicleESP.hpp"

#include "../../FivemSDK/Fivem.hpp"
#include "../../Options.hpp"

namespace Cheat
{
	void ESP::Vehicles()
	{
		if (!g_Fivem.GetLocalPlayerInfo().Ped)
			return;

		for (VehicleInfo Current : g_Fivem.GetVehicleList())
		{
			if (g_Options.Visuals.ESP.Vehicles.IgnoreOccupiedVehicles && Current.Vehicle->GetDriver())
				continue;

			ImVec2 Position = g_Fivem.WorldToScreen(Current.Vehicle->GetCoordinate());
			if (!g_Fivem.IsOnScreen(Position))
				continue;

			float OffsetY = 0;

			if (g_Options.Visuals.ESP.Vehicles.Marker)
			{
				ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(Position.x, Position.y + OffsetY), 4, ImColor(0.f, 0.f, 0.f, g_Options.Visuals.ESP.Vehicles.Color[3]));
				ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(Position.x, Position.y + OffsetY), 3, ImColor(g_Options.Visuals.ESP.Vehicles.Color[0], g_Options.Visuals.ESP.Vehicles.Color[1], g_Options.Visuals.ESP.Vehicles.Color[2], g_Options.Visuals.ESP.Vehicles.Color[3]));

				OffsetY += 12;
			}

			ImGui::PushFont(FrameWork::Assets::InterBold12);

			if (g_Options.Visuals.ESP.Vehicles.Name)
			{
				ImVec2 TextSize = ImGui::CalcTextSize(Current.Name.c_str());

				ImGui::GetBackgroundDrawList()->AddText(ImVec2(Position.x + 1 - TextSize.x / 2, Position.y + OffsetY + 1), ImColor(0.f, 0.f, 0.f, g_Options.Visuals.ESP.Vehicles.Color[3]), Current.Name.c_str());
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(Position.x - TextSize.x / 2, Position.y + OffsetY), ImColor(1.f, 1.f, 1.f, g_Options.Visuals.ESP.Vehicles.Color[3]), Current.Name.c_str());

				OffsetY += 12;
			}

			if (g_Options.Visuals.ESP.Vehicles.Distance)
			{
				char bfr[24];
				sprintf(bfr, XorStr("%dm"), (int)Current.Vehicle->GetCoordinate().DistTo(g_Fivem.GetLocalPlayerInfo().WorldPos));

				ImVec2 TextSize = ImGui::CalcTextSize(bfr);

				ImGui::GetBackgroundDrawList()->AddText(ImVec2(Position.x + 1 - TextSize.x / 2, Position.y + OffsetY + 1), ImColor(0.f, 0.f, 0.f, g_Options.Visuals.ESP.Vehicles.Color[3]), bfr);
				ImGui::GetBackgroundDrawList()->AddText(ImVec2(Position.x - TextSize.x / 2, Position.y + OffsetY), ImColor(1.f, 1.f, 1.f, g_Options.Visuals.ESP.Vehicles.Color[3]), bfr);
				OffsetY += 12;
			}

			ImGui::PopFont();
		}
	}
}