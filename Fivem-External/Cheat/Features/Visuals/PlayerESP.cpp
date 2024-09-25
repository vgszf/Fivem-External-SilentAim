#include "PlayerESP.hpp"

#include <cmath>

#include "../../FivemSDK/Fivem.hpp"
#include "../../Options.hpp"

struct Position
{
	ImVec2 Pos;
};

namespace Cheat
{
	void ESP::Players()
	{
		if (!g_Fivem.GetLocalPlayerInfo().Ped)
			return;

		for (Entity Current : g_Fivem.GetEntitiyList())
		{
			if (Current.StaticInfo.bIsLocalPlayer && !g_Options.Visuals.ESP.Players.ShowLocalPlayer)
				continue;

			if (Current.StaticInfo.bIsNPC && !g_Options.Visuals.ESP.Players.ShowNPCs)
				continue;

			if (g_Options.Visuals.ESP.Players.VisibleOnly && !Current.Visible)
				continue;

			Vector3D PedCoordinates = Current.Cordinates;

			float Distance = PedCoordinates.DistTo(g_Fivem.GetLocalPlayerInfo().WorldPos);

			if (Distance > g_Options.Visuals.ESP.Players.RenderDistance)
				continue;

			ImVec2 PedLocation = g_Fivem.WorldToScreen(PedCoordinates);

			ImVec2 Head = Current.HeadPos;
			if (!g_Fivem.IsOnScreen(Head))
				continue;

			ImVec2 LeftFoot = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_L_Foot));
			if (!g_Fivem.IsOnScreen(LeftFoot))
				continue;

			ImVec2 RightFoot = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_R_Foot));
			if (!g_Fivem.IsOnScreen(RightFoot))
				continue;

			float Height = -Head.y;

			if (LeftFoot.y > RightFoot.y)
				Height += LeftFoot.y;
			else
				Height += RightFoot.y;

			float Width = Height / 1.8f;
			float PedCenterY = Head.y + Height / 2.f;
			Height *= 1.2f;

				//{ ImVec2(PedLocation.x, PedCenterY - Height / 2) }, // Top
				//{ ImVec2(PedLocation.x + Width / 2, PedCenterY - Height / 2) }, // Right
				//{ ImVec2(PedLocation.x, PedCenterY + Height / 2) }, // Bottom
				//{ ImVec2(PedLocation.x - Width / 2, PedCenterY - Height / 2) } // Left

			ImVec2 Padding[4] = { ImVec2(0, 0), ImVec2(0, 0), ImVec2(0, 0), ImVec2(0, 0) };

			if (g_Options.Visuals.ESP.Players.Box)
			{
				ImGui::GetBackgroundDrawList()->AddRect(ImVec2(PedLocation.x - Width / 2, PedCenterY - Height / 2.f), ImVec2(PedLocation.x + Width / 2, PedCenterY + Height / 2.f), ImColor(0, 0, 0, 255), 0, ImDrawFlags_None, 3);
				ImGui::GetBackgroundDrawList()->AddRect(ImVec2(PedLocation.x - Width / 2, PedCenterY - Height / 2.f), ImVec2(PedLocation.x + Width / 2, PedCenterY + Height / 2.f), ImColor(255, 255, 255, 255), 0, ImDrawFlags_None, 2);

				Padding[0].y += 3;
				Padding[1].x += 3;
				Padding[2].y += 3;
				Padding[3].x += 3;
			}
			if (g_Options.Visuals.ESP.Players.Skeleton)
			{
				do
				{
					ImVec2 Pelvis = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_Pelvis));
					if (!g_Fivem.IsOnScreen(Pelvis))
						continue;

					ImVec2 Neck = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_Neck_1));
					if (!g_Fivem.IsOnScreen(Neck))
						continue;

					ImVec2 LeftClavicle = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_L_Clavicle));
					if (!g_Fivem.IsOnScreen(LeftClavicle))
						continue;

					ImVec2 RightClavicle = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_R_Clavicle));
					if (!g_Fivem.IsOnScreen(RightClavicle))
						continue;

					ImVec2 LeftUperarm = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_L_UpperArm));
					if (!g_Fivem.IsOnScreen(LeftUperarm))
						continue;

					ImVec2 RightUperarm = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_R_UpperArm));
					if (!g_Fivem.IsOnScreen(RightUperarm))
						continue;

					ImVec2 RightFormArm = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_R_Forearm));
					if (!g_Fivem.IsOnScreen(RightFormArm))
						continue;

					ImVec2 LeftFormArm = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_L_Forearm));
					if (!g_Fivem.IsOnScreen(LeftFormArm))
						continue;

					ImVec2 RightHand = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_R_Hand));
					if (!g_Fivem.IsOnScreen(RightHand))
						continue;

					ImVec2 LeftHand = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_L_Hand));
					if (!g_Fivem.IsOnScreen(LeftHand))
						continue;

					ImVec2 LeftThigh = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_L_Thigh));
					if (!g_Fivem.IsOnScreen(LeftThigh))
						continue;

					ImVec2 LeftCalf = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_L_Calf));
					if (!g_Fivem.IsOnScreen(LeftCalf))
						continue;

					ImVec2 RightThigh = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_R_Thigh));
					if (!g_Fivem.IsOnScreen(RightThigh))
						continue;

					ImVec2 RightCalf = g_Fivem.WorldToScreen(g_Fivem.GetBonePosVec3(Current, SKEL_R_Calf));
					if (!g_Fivem.IsOnScreen(RightCalf))
						continue;

					ImColor Color = ImColor(g_Options.Visuals.ESP.Players.SkeletonColor[0], g_Options.Visuals.ESP.Players.SkeletonColor[1], g_Options.Visuals.ESP.Players.SkeletonColor[2], g_Options.Visuals.ESP.Players.SkeletonColor[3]);
					if (Current.StaticInfo.IsFriend)
						Color = ImColor(g_Options.Misc.FriendColor[0], g_Options.Misc.FriendColor[1], g_Options.Misc.FriendColor[2], g_Options.Misc.FriendColor[3]);

					ImGui::GetBackgroundDrawList()->AddLine(Neck, RightClavicle, Color, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Neck, LeftClavicle, Color, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(RightClavicle, RightUperarm, Color, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(LeftClavicle, LeftUperarm, Color, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(RightUperarm, RightFormArm, Color, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(LeftUperarm, LeftFormArm, Color, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(RightFormArm, RightHand, Color, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(LeftFormArm, LeftHand, Color, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(Neck, Pelvis, Color, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(Pelvis, LeftThigh, Color, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Pelvis, RightThigh, Color, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(LeftThigh, LeftCalf, Color, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(RightThigh, RightCalf, Color, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(LeftCalf, LeftFoot, Color, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(RightCalf, RightFoot, Color, 1.f);
				} while (false);
			}
			if (g_Options.Visuals.ESP.Players.HealthBar)
			{
				float Health = Current.StaticInfo.Ped->GetHealth();
				float MaxHealth = Current.StaticInfo.Ped->GetMaxHealth();

				ImVec2 DrawPos = ImVec2(PedLocation.x - Width / 2, PedCenterY - Height / 2) - Padding[3] - ImVec2(2, 0);
				ImVec2 Size = ImVec2(0, Height);
				ImVec2 DrawSize = ImVec2(-2, (Height / MaxHealth) * Health);

				ImGui::GetBackgroundDrawList()->AddRectFilled(DrawPos - ImVec2(1, 1), DrawPos + Size + ImVec2(1, 1), ImColor(0, 0, 0));
				ImGui::GetBackgroundDrawList()->AddRectFilled(DrawPos, DrawPos + Size + ImVec2(3, 0), ImColor(0, 0, 0));
				ImGui::GetBackgroundDrawList()->AddRectFilled(DrawPos + Size, DrawPos + Size - DrawSize, ImColor(0, 255, 12));

				Padding[3].x += 4;
			}
			if (g_Options.Visuals.ESP.Players.ArmorBar)
			{
				float Armor = Current.StaticInfo.Ped->GetArmor();
				float MaxArmor = 100;

				if (Armor > 0)
				{
					ImVec2 DrawPos = ImVec2(PedLocation.x, PedCenterY + Height / 2);

					DrawPos = ImVec2(DrawPos.x - Width / 2, DrawPos.y + Padding[2].y);
					ImVec2 Size = ImVec2(Width, 2);
					ImVec2 DrawSize = ImVec2((Width / MaxArmor) * Armor, 2);

					ImGui::GetBackgroundDrawList()->AddRectFilled(DrawPos - ImVec2(1, 1), DrawPos + Size + ImVec2(1, 1), ImColor(0, 0, 0));
					ImGui::GetBackgroundDrawList()->AddRectFilled(DrawPos, DrawPos + Size, ImColor(0, 0, 0));
					ImGui::GetBackgroundDrawList()->AddRectFilled(DrawPos, DrawPos + DrawSize, ImColor(25, 120, 245));

					Padding[2].y += 3;
				}
			}
			if (g_Options.Visuals.ESP.Players.Name)
			{
				std::string Name = Current.StaticInfo.Name;
				if (Name.empty())
					Name = XorStr("NPC");

				ImVec2 TextSize = ImGui::CalcTextSize(Name.c_str());

				ImVec2 DrawPos = ImVec2(PedLocation.x, PedCenterY + Height / 2);
				DrawPos = ImVec2(DrawPos.x - TextSize.x / 2, DrawPos.y + Padding[2].y);
				Padding[2].y += TextSize.y;

				ImGui::PushFont(FrameWork::Assets::InterBold12);

				ImColor Color = ImColor(g_Options.Visuals.ESP.Players.NameColor[0], g_Options.Visuals.ESP.Players.NameColor[1], g_Options.Visuals.ESP.Players.NameColor[2], g_Options.Visuals.ESP.Players.NameColor[3]);

				ImGui::GetBackgroundDrawList()->AddText(DrawPos + ImVec2(1, 1), ImColor(0.f, 0.f, 0.f, g_Options.Visuals.ESP.Players.NameColor[3]), Name.c_str());
				ImGui::GetBackgroundDrawList()->AddText(DrawPos, Color, Name.c_str());

				ImGui::PopFont();
			}
			if (g_Options.Visuals.ESP.Players.WeaponName)
			{
				CWeaponManager* WeaponManager = Current.StaticInfo.Ped->GetWeaponManager();
				if (WeaponManager)
				{
					CWeaponInfo* WeaponInfo = WeaponManager->GetWeaponInfo();
					if (WeaponInfo)
					{
						std::string WeaponName = WeaponInfo->GetWeaponName();
						if (WeaponName.size() > 0)
						{
							ImVec2 TextSize = ImGui::CalcTextSize(WeaponName.c_str());

							ImVec2 DrawPos = ImVec2(PedLocation.x, PedCenterY + Height / 2);
							DrawPos = ImVec2(DrawPos.x - TextSize.x / 2, DrawPos.y + Padding[2].y - 3);
							Padding[2].y += TextSize.y;

							ImColor Color = ImColor(g_Options.Visuals.ESP.Players.WeaponNameColor[0], g_Options.Visuals.ESP.Players.WeaponNameColor[1], g_Options.Visuals.ESP.Players.WeaponNameColor[2], g_Options.Visuals.ESP.Players.WeaponNameColor[3]);

							ImGui::PushFont(FrameWork::Assets::InterBold12);

							ImGui::GetBackgroundDrawList()->AddText(DrawPos + ImVec2(1, 1), ImColor(0.f, 0.f, 0.f, g_Options.Visuals.ESP.Players.WeaponNameColor[3]), WeaponName.c_str());
							ImGui::GetBackgroundDrawList()->AddText(DrawPos, Color, WeaponName.c_str());

							ImGui::PopFont();
						}
					}
					//
					if (g_Options.Misc.Exploits.LocalPlayer.norecoil)
					{
						if (WeaponManager)
						{
							auto weaponinfo = WeaponManager->GetWeaponInfo();

							FrameWork::Memory::WriteMemory<float>((uintptr_t)weaponinfo + 0x2F4, 0.f);
						}
					}
					if (g_Options.Misc.Exploits.LocalPlayer.noreload)
					{
						if (WeaponManager)
						{
							auto weaponinfo = WeaponManager->GetWeaponInfo();

							FrameWork::Memory::WriteMemory<float>((uintptr_t)weaponinfo + 0x134, 1000);
						}
					}
					if (g_Options.Misc.Exploits.LocalPlayer.nospread)
					{
						if (WeaponManager)
						{
							auto weaponinfo = WeaponManager->GetWeaponInfo();

							FrameWork::Memory::WriteMemory<float>((uintptr_t)weaponinfo + 0x84, 0.f);
						}
					}
					//
				}
			}
			if (g_Options.Visuals.ESP.Players.Distance)
			{
				if (!Current.StaticInfo.bIsLocalPlayer)
				{
					std::string PlayerDistance = std::to_string((int)Distance) + XorStr("m");
					ImVec2 TextSize = ImGui::CalcTextSize(PlayerDistance.c_str());

					ImVec2 DrawPos = ImVec2(PedLocation.x, PedCenterY + Height / 2);

					DrawPos = ImVec2(DrawPos.x - TextSize.x / 2, DrawPos.y + Padding[2].y - 3);
					Padding[2].y += TextSize.y;

					ImColor Color = ImColor(g_Options.Visuals.ESP.Players.DistanceColor[0], g_Options.Visuals.ESP.Players.DistanceColor[1], g_Options.Visuals.ESP.Players.DistanceColor[2], g_Options.Visuals.ESP.Players.DistanceColor[3]);

					ImGui::PushFont(FrameWork::Assets::InterBold12);

					ImGui::GetBackgroundDrawList()->AddText(DrawPos + ImVec2(1, 1), ImColor(0.f, 0.f, 0.f, g_Options.Visuals.ESP.Players.DistanceColor[3]), PlayerDistance.c_str());
					ImGui::GetBackgroundDrawList()->AddText(DrawPos, Color, PlayerDistance.c_str());

					ImGui::PopFont();
				}
			}
			if (g_Options.Visuals.ESP.Players.SnapLines)
			{
				if (!Current.StaticInfo.bIsLocalPlayer)
				{
					ImColor Color = ImColor(g_Options.Visuals.ESP.Players.SnaplinesColor[0], g_Options.Visuals.ESP.Players.SnaplinesColor[1], g_Options.Visuals.ESP.Players.SnaplinesColor[2], g_Options.Visuals.ESP.Players.SnaplinesColor[3]);

					ImGui::GetBackgroundDrawList()->AddLine(g_Fivem.GetLocalPlayerInfo().ScreenPos, PedLocation, ImColor(255, 255, 255));
				}
			}

			if (g_Options.Visuals.ESP.Players.Weapon_Misc)
			{
				CWeaponManager* WeaponManager = Current.StaticInfo.Ped->GetWeaponManager();
				if (WeaponManager)
				{
					CWeaponInfo* WeaponInfo = WeaponManager->GetWeaponInfo();
					if (WeaponInfo)
					{
						if (g_Options.Misc.Exploits.LocalPlayer.norecoil)
						{
							if (WeaponManager)
							{
								auto weaponinfo = WeaponManager->GetWeaponInfo();

								FrameWork::Memory::WriteMemory<float>((uintptr_t)weaponinfo + 0x2F4, 0.f);
							}
						}
						if (g_Options.Misc.Exploits.LocalPlayer.noreload)
						{
							if (WeaponManager)
							{
								auto weaponinfo = WeaponManager->GetWeaponInfo();

								FrameWork::Memory::WriteMemory<float>((uintptr_t)weaponinfo + 0x134, 1000);
							}
						}
						if (g_Options.Misc.Exploits.LocalPlayer.nospread)
						{
							if (WeaponManager)
							{
								auto weaponinfo = WeaponManager->GetWeaponInfo();

								FrameWork::Memory::WriteMemory<float>((uintptr_t)weaponinfo + 0x84, 0.f);
							}
						}
					}
					
					//
				}
			}
		}
	}
}