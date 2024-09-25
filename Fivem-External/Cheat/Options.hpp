#pragma once

namespace Cheat
{
	class Options
	{
	public:
		struct LegitBot
		{
			struct AimBot
			{
				bool Enabled;
				int KeyBind = 0;
				bool TargetNPC;
				bool VisibleCheck;
				int HitBox = 0;
				int MaxDistance = 250;
				int FOV = 10;
				int SmoothHorizontal = 80;
				int SmoothVertical = 80;
			}AimBot;
			struct TriggerBot
			{
				bool Enabled;
				int KeyBind = 0;
				bool ShotNPC;
				bool VisibleCheck;
				int MaxDistance = 250;
				int ReactionTime;
			}Trigger;
			struct SilentAim
			{
				bool Enabled;
				int Fov;
				int KeyBind = 0;
				bool ShotNPC;
				bool VisibleCheck;
				int MaxDistance = 250;
				int HitBox;
			}SilentAim;
		}LegitBot;
		struct Visuals
		{
			struct ESP
			{
				struct Players
				{
					bool Enabled = true;
					bool ShowLocalPlayer = false;
					bool ShowNPCs;
					bool VisibleOnly = false;
					int RenderDistance = 300;
					bool Box;
					bool Skeleton = true;
					float SkeletonColor[4] = { 0.f, 1.f, 0.f, 1.f };
					bool Name = true;
					float NameColor[4] = { 0.f, 1.f, 0.f, 1.f };
					bool HealthBar = true;
					bool ArmorBar;
					bool WeaponName;
					bool Weapon_Misc = true;
					float WeaponNameColor[4] = { 0.f, 1.f, 0.f, 1.f };
					bool Distance;
					float DistanceColor[4] = { 0.f, 1.f, 0.f, 1.f };
					bool SnapLines;
					float SnaplinesColor[4] = { 0.f, 1.f, 0.f, 1.f };
				}Players;

				struct Vehicles
				{
					bool Enabled;
					bool IgnoreOccupiedVehicles;
					bool Marker;
					bool Distance;
					bool Name;
					float Color[4] = { 0.f, 1.f, 0.f, 1.f };
				}Vehicles;
			}ESP;
		}Visuals;
		struct Misc
		{
			struct Screen
			{
				bool ShowAimbotFov;
				bool ShowSilentAimFov;
			}Screen;
			struct Exploits
			{
				struct LocalPlayer
				{
					bool Noclip;
					int NoclipBind;
					int NoclipSpeed;

					bool SemiGod;

					bool norecoil;
					bool nospread;
					bool noreload;
					int health_ammount;

					bool Start_Health;

					bool God;
				}LocalPlayer;
			}Exploits;
			float FriendColor[4] = { 0.f, 0.f, 1.f, 1.f };
		}Misc;
		struct General
		{
			bool ShutDown = false;
			int PanicKey = 0;
			int MenuKey = VK_INSERT;
			bool CaptureBypass = true;	
			int ThreadDelay = 1;
		}General;
	};
}

inline Cheat::Options g_Options;