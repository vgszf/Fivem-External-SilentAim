#include "Interface.hpp"

#include <Cheat/Options.hpp>
#include <Cheat/Cheat.hpp>
#include <Cheat/ConfigSystem.hpp>
#include "Cheat/FivemSDK/Fivem.hpp"

inline Cheat::ConfigManager Condif;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace FrameWork
{
	void Interface::Initialize(HWND Window, HWND TargetWindow, ID3D11Device* Device, ID3D11DeviceContext* DeviceContext)
	{
		hWindow = Window;
		IDevice = Device;

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(hWindow);
		ImGui_ImplDX11_Init(Device, DeviceContext);
	}

	void Interface::UpdateStyle()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGuiStyle* Style = &ImGui::GetStyle();
		Style->WindowRounding = 7;
		Style->WindowBorderSize = 1;
		Style->WindowPadding = ImVec2(0, 0);
		Style->WindowShadowSize = 0;
		Style->ScrollbarSize = 3;
		Style->ScrollbarRounding = 0;
		Style->PopupRounding = 5;


		Style->Colors[ImGuiCol_Separator] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_SeparatorActive] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_SeparatorHovered] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_ResizeGrip] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_ResizeGripActive] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_ResizeGripHovered] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_PopupBg] = ImColor(14, 14, 14);

		Style->Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
		Style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(232, 63, 212);
		Style->Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(232, 63, 212);
		Style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(232, 63, 212);

		Style->Colors[ImGuiCol_WindowBg] = ImColor(14, 14, 14);
		Style->Colors[ImGuiCol_Border] = ImColor(24, 23, 25);

		Assets::Initialize(IDevice);

		Condif.Setup();
	}

	void Interface::AimbotTab()
	{
		ImGui::SetCursorPos(ImVec2(20, 20));
		ImGui::CustomChild(XorStr("Silent"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 220));
		{
			ImGui::Checkbox(XorStr("Enabled"), &g_Options.LegitBot.SilentAim.Enabled);
			ImGui::KeyBind(XorStr("Key"), &g_Options.LegitBot.SilentAim.KeyBind);
			ImGui::Checkbox(XorStr("Show Fov"), &g_Options.Misc.Screen.ShowSilentAimFov);
			ImGui::Checkbox(XorStr("Shot NPC"), &g_Options.LegitBot.SilentAim.ShotNPC);
			ImGui::Checkbox(XorStr("Visible Check"), &g_Options.LegitBot.SilentAim.VisibleCheck);
			ImGui::Combo(XorStr("HitBox"), &g_Options.LegitBot.SilentAim.HitBox, XorStr("Head\0Neck\0Chest\0"));
			ImGui::SliderInt(XorStr("Fov"), &g_Options.LegitBot.SilentAim.Fov, 0, 180, XorStr("%dpx"));
			ImGui::SliderInt(XorStr("Max Distance"), &g_Options.LegitBot.SilentAim.MaxDistance, 0, 600, XorStr("%dm"));
		}
		ImGui::EndCustomChild();

		ImGui::SetCursorPos(ImVec2(20, 20 + 220 + 20));
		ImGui::CustomChild(XorStr("Trigger"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 130));
		{
			ImGui::Checkbox(XorStr("Enabled"), &g_Options.LegitBot.Trigger.Enabled);
			ImGui::KeyBind(XorStr("Key"), &g_Options.LegitBot.Trigger.KeyBind);
			ImGui::Checkbox(XorStr("Shot NPC"), &g_Options.LegitBot.Trigger.ShotNPC);
			ImGui::Checkbox(XorStr("Visible Check"), &g_Options.LegitBot.Trigger.VisibleCheck);
			ImGui::SliderInt(XorStr("Max Distance"), &g_Options.LegitBot.Trigger.MaxDistance, 0, 600, XorStr("%dm"));
			ImGui::SliderInt(XorStr("Reaction Time"), &g_Options.LegitBot.Trigger.ReactionTime, 0, 300, XorStr("%dms"));
		}
		ImGui::EndCustomChild();


		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + 10, 20));
		ImGui::CustomChild(XorStr("Aimbot"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 370));
		{
			ImGui::Checkbox(XorStr("Enabled"), &g_Options.LegitBot.AimBot.Enabled);
			ImGui::KeyBind(XorStr("Key"), &g_Options.LegitBot.AimBot.KeyBind);
			ImGui::Checkbox(XorStr("Show Fov"), &g_Options.Misc.Screen.ShowAimbotFov);
			ImGui::Checkbox(XorStr("Target NPC"), &g_Options.LegitBot.AimBot.TargetNPC);
			ImGui::Checkbox(XorStr("Visible Check"), &g_Options.LegitBot.AimBot.VisibleCheck);
			ImGui::Combo(XorStr("HitBox"), &g_Options.LegitBot.AimBot.HitBox, XorStr("Head\0Neck\0Chest\0"));
			ImGui::SliderInt(XorStr("Fov"), &g_Options.LegitBot.AimBot.FOV, 0, 180, XorStr("%dpx"));
			ImGui::SliderInt(XorStr("Max Distance"), &g_Options.LegitBot.AimBot.MaxDistance, 0, 600, XorStr("%dm"));
			ImGui::SliderInt(XorStr("Smooth X"), &g_Options.LegitBot.AimBot.SmoothHorizontal, 0, 100, XorStr("%d%"));
			ImGui::SliderInt(XorStr("Smooth Y"), &g_Options.LegitBot.AimBot.SmoothVertical, 0, 100, XorStr("%d%"));
		}
		ImGui::EndCustomChild();
	}

	void Interface::VisualsTab()
	{
		ImGui::SetCursorPos(ImVec2(20, 20));
		ImGui::CustomChild(XorStr("General"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 200));
		{
			ImGui::Checkbox(XorStr("Enabled"), &g_Options.Visuals.ESP.Players.Enabled);
			ImGui::SliderInt(XorStr("Render Distance"), &g_Options.Visuals.ESP.Players.RenderDistance, 0, 600, XorStr("%dm"));
			ImGui::Checkbox(XorStr("Filter LocalPlayer"), &g_Options.Visuals.ESP.Players.ShowLocalPlayer);
			ImGui::Checkbox(XorStr("Filter NPC"), &g_Options.Visuals.ESP.Players.ShowNPCs);
			ImGui::Checkbox(XorStr("Visible Only"), &g_Options.Visuals.ESP.Players.VisibleOnly);
		}
		ImGui::EndCustomChild();

		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + 10, 20));
		ImGui::CustomChild(XorStr("Options"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 370));
		{
			ImGui::Checkbox(XorStr("Box"), &g_Options.Visuals.ESP.Players.Box);
			ImGui::Checkbox(XorStr("Skeleton"), &g_Options.Visuals.ESP.Players.Skeleton);
			ImGui::Checkbox(XorStr("Name"), &g_Options.Visuals.ESP.Players.Name);
			ImGui::Checkbox(XorStr("Health Bar"), &g_Options.Visuals.ESP.Players.HealthBar);
			ImGui::Checkbox(XorStr("Armor Bar"), &g_Options.Visuals.ESP.Players.ArmorBar);
			ImGui::Checkbox(XorStr("Weapon Name"), &g_Options.Visuals.ESP.Players.WeaponName);
			ImGui::Checkbox(XorStr("Distance"), &g_Options.Visuals.ESP.Players.Distance);
			ImGui::Checkbox(XorStr("SnapLines"), &g_Options.Visuals.ESP.Players.SnapLines);
			ImGui::ColorEdit4(XorStr("Skeleton Color"), g_Options.Visuals.ESP.Players.SkeletonColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(XorStr("Name Color"), g_Options.Visuals.ESP.Players.NameColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(XorStr("Weapon Name Color"), g_Options.Visuals.ESP.Players.WeaponNameColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(XorStr("Distance Color"), g_Options.Visuals.ESP.Players.DistanceColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4(XorStr("Snaplines Color"), g_Options.Visuals.ESP.Players.SnaplinesColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
		}
		ImGui::EndCustomChild();
	}

	void Interface::MiscellaneousTab()
	{
		ImGui::SetCursorPos(ImVec2(20, 20));
		ImGui::CustomChild(XorStr("Noclip"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 150));
		{
			ImGui::Checkbox(XorStr("Enabled"), &g_Options.Misc.Exploits.LocalPlayer.Noclip);
			ImGui::KeyBind(XorStr("Key"), &g_Options.Misc.Exploits.LocalPlayer.NoclipBind);
			ImGui::SliderInt(XorStr("Speed"), &g_Options.Misc.Exploits.LocalPlayer.NoclipSpeed, 0, 100, XorStr("%dm/s"));
		}
		ImGui::EndCustomChild();

		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + 10, 20));
		ImGui::CustomChild(XorStr("LocalPlayer"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 300));
		{
			ImGui::Checkbox(XorStr("God"), &g_Options.Misc.Exploits.LocalPlayer.God);
			ImGui::Checkbox(XorStr("SemiGod"), &g_Options.Misc.Exploits.LocalPlayer.SemiGod);

			//a
			ImGui::Checkbox(XorStr("No Recoil"), &g_Options.Misc.Exploits.LocalPlayer.norecoil);
			ImGui::Checkbox(XorStr("No Spread"), &g_Options.Misc.Exploits.LocalPlayer.nospread);
			ImGui::Checkbox(XorStr("No Reload"), &g_Options.Misc.Exploits.LocalPlayer.noreload);
			//
			if (ImGui::Button(XorStr("Teleport To Waypoiny")))
			{
				Cheat::Exploits::TeleportToWaypoint();
			}
			ImGui::SliderInt(XorStr("Health Ammout"), &g_Options.Misc.Exploits.LocalPlayer.health_ammount, 0, 400, XorStr("%dm/s"));

			if (ImGui::Button(XorStr("Set Health")))
			{
				g_Options.Misc.Exploits.LocalPlayer.Start_Health = true;
			}
		}
		ImGui::EndCustomChild();
	}

	void Interface::VehiclesTab()
	{
		static ImGuiTextFilter mFilter;
		static Cheat::VehicleInfo SelectedVehicle = Cheat::VehicleInfo();

		if (SelectedVehicle.Vehicle->GetCoordinate().DistTo(Cheat::g_Fivem.GetLocalPlayerInfo().WorldPos) > 600)
			SelectedVehicle = Cheat::VehicleInfo();

		ImGui::SetCursorPos(ImVec2(20, 20));
		ImGui::CustomChild(XorStr("Vehicle List"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 370));
		{
			mFilter.Draw(XorStr("Search"));
			if (ImGui::BeginListBox(XorStr("##VehList"), ImVec2(ImGui::GetWindowSize().x - 20, 270)))
			{
				if (Cheat::g_Fivem.GetLocalPlayerInfo().Ped)
				{
					for (Cheat::VehicleInfo Current : Cheat::g_Fivem.GetVehicleList())
					{
						if (mFilter.PassFilter(Current.Name.c_str()))
						{
							std::string Text = Current.Name + XorStr(" (") + std::to_string((int)(Current.Vehicle->GetCoordinate().DistTo(Cheat::g_Fivem.GetLocalPlayerInfo().WorldPos))) + XorStr("m)");

							bool Selected = (Current.Vehicle == SelectedVehicle.Vehicle);

							if (ImGui::Selectable(Text.c_str(), &Selected))
							{
								SelectedVehicle = Current;
							}
						}
					}
				}
				ImGui::EndListBox();
			}
		}
		ImGui::EndCustomChild();

		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + 10, 20));
		ImGui::CustomChild(XorStr("Actions"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 120));
		{
			if (SelectedVehicle.iIndex != -1)
			{
				if (ImGui::Button(XorStr("Teleport to")))
				{
					Cheat::g_Fivem.TeleportObject((uintptr_t)Cheat::g_Fivem.GetLocalPlayerInfo().Ped,
						Cheat::g_Fivem.GetLocalPlayerInfo().Ped->GetNavigation(),
						Cheat::g_Fivem.GetLocalPlayerInfo().Ped->GetModelInfo(),
						SelectedVehicle.Vehicle->GetCoordinate(),
						SelectedVehicle.Vehicle->GetCoordinate(),
						true);
				}
				if (ImGui::Button(XorStr("Unlock door")))
				{
					SelectedVehicle.Vehicle->SetDoorLock(1);
				}
				if (ImGui::Button(XorStr("Lock door")))
				{
					SelectedVehicle.Vehicle->SetDoorLock(2);
				}
			}
			else
			{
				ImGui::Text(XorStr("Select a vehicle first!"));
			}
		}
		ImGui::EndCustomChild();

		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + 10, 20 + 120 + 20));
		ImGui::CustomChild(XorStr("Visuals"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 210));
		{
			ImGui::Checkbox(XorStr("Enabled"), &g_Options.Visuals.ESP.Vehicles.Enabled);
			ImGui::Checkbox(XorStr("Ignore Occupied"), &g_Options.Visuals.ESP.Vehicles.IgnoreOccupiedVehicles);
			ImGui::Checkbox(XorStr("Marker"), &g_Options.Visuals.ESP.Vehicles.Marker);
			ImGui::Checkbox(XorStr("Name"), &g_Options.Visuals.ESP.Vehicles.Name);
			ImGui::Checkbox(XorStr("Distance"), &g_Options.Visuals.ESP.Vehicles.Distance);
			ImGui::ColorEdit4(XorStr("Color"), g_Options.Visuals.ESP.Vehicles.Color, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
		}
		ImGui::EndCustomChild();
	}

	void Interface::PlayersTab()
	{
		static ImGuiTextFilter mFilter;
		static Cheat::Entity SelectedEntity = Cheat::Entity();

		if (SelectedEntity.Cordinates.DistTo(Cheat::g_Fivem.GetLocalPlayerInfo().WorldPos) > 600)
			SelectedEntity = Cheat::Entity();

		ImGui::SetCursorPos(ImVec2(20, 20));
		ImGui::CustomChild(XorStr("Player List"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 370));
		{
			mFilter.Draw(XorStr("Search"));
			if (ImGui::BeginListBox(XorStr("##PlayerList"), ImVec2(ImGui::GetWindowSize().x - 20, 270)))
			{
				if (Cheat::g_Fivem.GetLocalPlayerInfo().Ped)
				{
					for (Cheat::Entity Current : Cheat::g_Fivem.GetEntitiyList())
					{
						if (Current.StaticInfo.bIsNPC || !Current.StaticInfo.Ped || Current.StaticInfo.bIsLocalPlayer)
							continue;

						if (mFilter.PassFilter(Current.StaticInfo.Name.c_str()))
						{
							ImGui::PushID(Current.StaticInfo.iIndex);
							{
								std::string Text = Current.StaticInfo.Name + XorStr(" (") + std::to_string((int)(Current.Cordinates.DistTo(Cheat::g_Fivem.GetLocalPlayerInfo().WorldPos))) + XorStr("m)");

								if (Current.StaticInfo.IsFriend)
									Text += XorStr(" (friend)");

								bool Selected = (Current.StaticInfo.Ped == SelectedEntity.StaticInfo.Ped);

								if (ImGui::Selectable(Text.c_str(), &Selected))
								{
									SelectedEntity = Current;
								}
							}
							ImGui::PopID();
						}
					}
				}

				ImGui::EndListBox();
			}
		}
		ImGui::EndCustomChild();

		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + 10, 20));
		ImGui::CustomChild(XorStr("Selected Player Information"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 145));
		{
			if (SelectedEntity.StaticInfo.iIndex > 0)
			{
				ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.8f), XorStr("Name: ")); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.6f), SelectedEntity.StaticInfo.Name.c_str());
				ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.8f), XorStr("Friend: ")); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.6f), SelectedEntity.StaticInfo.IsFriend ? XorStr("True") : XorStr("False"));
				ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.8f), XorStr("Net ID: ")); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.6f), std::to_string(SelectedEntity.StaticInfo.NetId).c_str());
				ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.8f), XorStr("Distance: ")); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.6f), (std::to_string((int)(SelectedEntity.Cordinates.DistTo(Cheat::g_Fivem.GetLocalPlayerInfo().WorldPos))) + XorStr("m")).c_str());

				Cheat::CWeaponManager* WeaponManager = SelectedEntity.StaticInfo.Ped->GetWeaponManager();
				if (WeaponManager)
				{
					Cheat::CWeaponInfo* WeaponInfo = WeaponManager->GetWeaponInfo();
					if (WeaponInfo)
					{
						ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.8f), XorStr("Weapon: ")); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.6f), WeaponInfo->GetWeaponName().c_str());
					}
				}
			}
			else
			{
				ImGui::Text(XorStr("Select a player first!"));
			}
		}
		ImGui::EndCustomChild();

		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + 10, 20 + 145 + 20));
		ImGui::CustomChild(XorStr("Actions"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 120));
		{
			if (SelectedEntity.StaticInfo.iIndex > 0)
			{
				if (ImGui::Button(XorStr("Teleport to")))
				{
					Cheat::g_Fivem.TeleportObject((uintptr_t)Cheat::g_Fivem.GetLocalPlayerInfo().Ped,
						Cheat::g_Fivem.GetLocalPlayerInfo().Ped->GetNavigation(),
						Cheat::g_Fivem.GetLocalPlayerInfo().Ped->GetModelInfo(),
						SelectedEntity.Cordinates,
						SelectedEntity.Cordinates,
						true);
				}

				if (!SelectedEntity.StaticInfo.IsFriend)
				{
					if (ImGui::Button(XorStr("Add Friend")))
					{
						if (!Cheat::g_Fivem.AllEntitesList[SelectedEntity.StaticInfo.Ped].IsFriend || !SelectedEntity.StaticInfo.IsFriend)
							Cheat::g_Fivem.FriendList[SelectedEntity.StaticInfo.Ped] = SelectedEntity.StaticInfo;

						Cheat::g_Fivem.AllEntitesList[SelectedEntity.StaticInfo.Ped].IsFriend = true;
						SelectedEntity.StaticInfo.IsFriend = true;
					}
				}
				else
				{
					if (ImGui::Button(XorStr("Remove Friend")))
					{
						if (Cheat::g_Fivem.AllEntitesList[SelectedEntity.StaticInfo.Ped].IsFriend || SelectedEntity.StaticInfo.IsFriend)
							Cheat::g_Fivem.FriendList.erase(SelectedEntity.StaticInfo.Ped);

						Cheat::g_Fivem.AllEntitesList[SelectedEntity.StaticInfo.Ped].IsFriend = false;
						SelectedEntity.StaticInfo.IsFriend = false;
					}
				}
			}
			else
			{
				ImGui::Text(XorStr("Select a player first!"));
			}
		}
		ImGui::EndCustomChild();
	}

	void Interface::SettingsTab()
	{
		ImGui::SetCursorPos(ImVec2(20, 20));
		ImGui::CustomChild(XorStr("Config System"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 180));
		{
			if (ImGui::Button(XorStr("Load Config")))
			{
				Condif.SaveConfig();
			}

			if (ImGui::Button(XorStr("Save Config")))
			{
				Condif.LoadConfig();
			}

			if (ImGui::Button(XorStr("Export Config")))
			{
				Condif.ExportToClipboard();
			}

			if (ImGui::Button(XorStr("Import Config")))
			{
				Condif.ImportFromClipboard();
			}
		}
		ImGui::EndCustomChild();

		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 + 10, 20));
		ImGui::CustomChild(XorStr("Extra"), ImVec2(ImGui::GetWindowSize().x / 2 - 30, 200));
		{
			ImGui::KeyBind(XorStr("Menu Bind"), &g_Options.General.MenuKey);

			ImGui::Checkbox(XorStr("Stream Mode"), &g_Options.General.CaptureBypass);

			ImGui::SliderInt(XorStr("Update Delay"), &g_Options.General.ThreadDelay, 0, 100, XorStr("%dms"));

			ImGui::ColorEdit4(XorStr("Friend Color"), g_Options.Misc.FriendColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);

			if (ImGui::Button(XorStr("Unload")))
			{
				g_Options.General.ShutDown = true;
			}
		}
		ImGui::EndCustomChild();
	}

	void Interface::RenderGui()
	{
		if (!bIsMenuOpen)
			return;

		ImGui::SetNextWindowSize(ImVec2(560, 410));
		ImGui::Begin(XorStr("Menu"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		{
			ImDrawList* DrawList = ImGui::GetWindowDrawList();
			ImVec2 Pos = ImGui::GetWindowPos();
			ImVec2 Size = ImGui::GetWindowSize();

			DrawList->AddRectFilled(Pos, Pos + ImVec2(80, Size.y), ImColor(16, 16, 16), ImGui::GetStyle().WindowRounding, ImDrawFlags_RoundCornersLeft);
			DrawList->AddLine(Pos + ImVec2(80, 0), Pos + ImVec2(80, Size.y), ImGui::GetColorU32(ImGuiCol_Border));

			DrawList->AddImage(Assets::Logo, Pos + ImVec2(10, 15), Pos + ImVec2(80 - 10, 80 - 10));

			ImGui::BeginChild(XorStr("LeftChild"), ImVec2(80, Size.y));
			{
				ImGui::SetCursorPos(ImVec2(20, 80));
				ImGui::BeginGroup();
				{
					if (ImGui::Tab(XorStr("Aimbot"), ICON_FA_MOUSE, CurrentTab == 0))
					{
						CurrentTab = 0;
					}
					if (ImGui::Tab(XorStr("Visuals"), ICON_FA_EYE, CurrentTab == 1))
					{
						CurrentTab = 1;
					}
					if (ImGui::Tab(XorStr("Misc"), ICON_FA_TH, CurrentTab == 2))
					{
						CurrentTab = 2;
					}
					if (ImGui::Tab(XorStr("Vehicles"), ICON_FA_CAR, CurrentTab == 3))
					{
						CurrentTab = 3;
					}
					if (ImGui::Tab(XorStr("Players"), ICON_FA_USERS, CurrentTab == 4))
					{
						CurrentTab = 4;
					}
					if (ImGui::Tab(XorStr("Settings"), ICON_FA_FILE, CurrentTab == 5))
					{
						CurrentTab = 5;
					}
				}
				ImGui::EndGroup();
			}
			ImGui::EndChild();

			static float AimBotChildAnim = 0;
			static float VisualsChildAnim = 0;
			static float MiscChildAnim = 0;
			static float VehiclesChildAnim = 0;
			static float PlayersChildAnim = 0;
			static float SettingsChildAnim = 0;

			AimBotChildAnim = ImLerp(AimBotChildAnim, CurrentTab == 0 ? 0.f : Size.y, ImGui::GetIO().DeltaTime * 10.f);
			VisualsChildAnim = ImLerp(VisualsChildAnim, CurrentTab == 1 ? 0.f : Size.y, ImGui::GetIO().DeltaTime * 10.f);
			MiscChildAnim = ImLerp(MiscChildAnim, CurrentTab == 2 ? 0.f : Size.y, ImGui::GetIO().DeltaTime * 10.f);
			VehiclesChildAnim = ImLerp(VehiclesChildAnim, CurrentTab == 3 ? 0.f : Size.y, ImGui::GetIO().DeltaTime * 10.f);
			PlayersChildAnim = ImLerp(PlayersChildAnim, CurrentTab == 4 ? 0.f : Size.y, ImGui::GetIO().DeltaTime * 10.f);
			SettingsChildAnim = ImLerp(SettingsChildAnim, CurrentTab == 5 ? 0.f : Size.y, ImGui::GetIO().DeltaTime * 10.f);

			ImGui::SetCursorPos(ImVec2(80, AimBotChildAnim));
			ImGui::BeginChild(XorStr("AimBotMainChild"), ImVec2(Size.x - 80, Size.y));
			{
				AimbotTab();
			}
			ImGui::EndChild();

			ImGui::SetCursorPos(ImVec2(80, VisualsChildAnim));
			ImGui::BeginChild(XorStr("VisualsMainChild"), ImVec2(Size.x - 80, Size.y));
			{
				VisualsTab();
			}
			ImGui::EndChild();

			ImGui::SetCursorPos(ImVec2(80, MiscChildAnim));
			ImGui::BeginChild(XorStr("MiscMainChild"), ImVec2(Size.x - 80, Size.y));
			{
				MiscellaneousTab();
			}
			ImGui::EndChild();

			ImGui::SetCursorPos(ImVec2(80, VehiclesChildAnim));
			ImGui::BeginChild(XorStr("VehiclesMainChild"), ImVec2(Size.x - 80, Size.y));
			{
				VehiclesTab();
			}
			ImGui::EndChild();

			ImGui::SetCursorPos(ImVec2(80, PlayersChildAnim));
			ImGui::BeginChild(XorStr("PlayersMainChild"), ImVec2(Size.x - 80, Size.y));
			{
				PlayersTab();
			}
			ImGui::EndChild();

			ImGui::SetCursorPos(ImVec2(80, SettingsChildAnim));
			ImGui::BeginChild(XorStr("SettingsMainChild"), ImVec2(Size.x - 80, Size.y));
			{
				SettingsTab();
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}

	void Interface::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_SIZE:
			if (wParam != SIZE_MINIMIZED)
			{
				ResizeWidht = (UINT)LOWORD(lParam);
				ResizeHeight = (UINT)HIWORD(lParam);
			}
			break;
		}

		if (bIsMenuOpen)
		{
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		}
	}

	void Interface::HandleMenuKey()
	{
		static bool MenuKeyDown = false;
		if (GetAsyncKeyState(g_Options.General.MenuKey) & 0x8000)
		{
			if (!MenuKeyDown)
			{
				MenuKeyDown = true;
				bIsMenuOpen = !bIsMenuOpen;

				if (bIsMenuOpen)
				{
					SetWindowLong(hWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE);
					SetForegroundWindow(hWindow);
				}
				else
				{
					SetWindowLong(hWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_NOACTIVATE);
					SetForegroundWindow(hTargetWindow);
				}
			}
		}
		else
		{
			MenuKeyDown = false;
		}
	}

	void Interface::ShutDown()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
}