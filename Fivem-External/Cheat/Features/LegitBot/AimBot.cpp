#include "AimBot.hpp"

#include "../../Options.hpp"

namespace Cheat
{
	void AimBot::RunThread()
	{
		while (!g_Options.General.ShutDown)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1 + g_Options.General.ThreadDelay));

			if (!g_Options.LegitBot.AimBot.Enabled)
				continue;

			if (!g_Fivem.GetLocalPlayerInfo().Ped)
				continue;

			Entity ClosestEntity;

			if (g_Fivem.FindClosestEntity(g_Options.LegitBot.AimBot.FOV, g_Options.LegitBot.AimBot.MaxDistance, g_Options.LegitBot.AimBot.TargetNPC, &ClosestEntity))
			{
				if (!GetAsyncKeyState(g_Options.LegitBot.AimBot.KeyBind))
				{
					continue;
				}

				if (ClosestEntity.StaticInfo.IsFriend)
					continue;

				if (g_Options.LegitBot.AimBot.VisibleCheck && !ClosestEntity.Visible)
					continue;
				
				Vector3D BonePos;
				
				switch (g_Options.LegitBot.AimBot.HitBox)
				{
				case 0: // Head
					BonePos = g_Fivem.GetBonePosVec3(ClosestEntity, SKEL_Head);
					break;
				case 1: // Neck
					BonePos = g_Fivem.GetBonePosVec3(ClosestEntity, SKEL_Neck_1);
					break;
				case 2: // Chest
					BonePos = g_Fivem.GetBonePosVec3(ClosestEntity, SKEL_Spine3);
					break;
				default:
					break;
				}
				
				g_Fivem.ProcessCameraMovement(BonePos, g_Options.LegitBot.AimBot.SmoothHorizontal, g_Options.LegitBot.AimBot.SmoothVertical);
			}
		}
	}
}