#include "TriggerBot.hpp"

#include <thread>

#include "../../Options.hpp"

namespace Cheat
{
	void TriggerBot::RunThread()
	{
		while (!g_Options.General.ShutDown)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1 + g_Options.General.ThreadDelay));

			if (!g_Options.LegitBot.Trigger.Enabled)
				continue;

			if (!g_Fivem.GetLocalPlayerInfo().Ped)
				continue;

			static bool Shooting = false;

			bool CanShoot = false;

			if (!GetAsyncKeyState(g_Options.LegitBot.Trigger.KeyBind))
			{
				if (Shooting)
				{
					INPUT input = { 0 };
					input.type = INPUT_MOUSE;
					input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SafeCall(SendInput)(1, &input, sizeof(INPUT));

					Shooting = false;
				}

				continue;
			}

			CPed* AimingEnity = g_Fivem.GetAimingEntity();

			if (AimingEnity)
			{
				if (g_Fivem.GetLocalPlayerInfo().WorldPos.DistTo(AimingEnity->GetCoordinate()) > g_Options.LegitBot.Trigger.MaxDistance)
					CanShoot = false;
				else
					CanShoot = true;

				if (AimingEnity->IsNPC() && !g_Options.LegitBot.Trigger.ShotNPC)
					CanShoot = false;

				if (g_Options.LegitBot.AimBot.VisibleCheck && !AimingEnity->IsVisible())
					CanShoot = false;

				if (!g_Fivem.IsPlayerAiming())
					CanShoot = false;

				if (g_Fivem.AllEntitesList[AimingEnity].IsFriend)
					CanShoot = false;
			}
			else
				CanShoot = false;

			if (CanShoot && !Shooting)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(g_Options.LegitBot.Trigger.ReactionTime));

				INPUT input = { 0 };
				input.type = INPUT_MOUSE;
				input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
				SafeCall(SendInput)(1, &input, sizeof(INPUT));

				Shooting = true;
			}
			else if (Shooting && !CanShoot)
			{
				INPUT input = { 0 };
				input.type = INPUT_MOUSE;
				input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
				SafeCall(SendInput)(1, &input, sizeof(INPUT));

				Shooting = false;
			}
		}
	}
}