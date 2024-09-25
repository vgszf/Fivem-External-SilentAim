#include "SilentAim.hpp"

#include "../../Options.hpp"

namespace Cheat
{
	void RestoreSilent()
	{
		std::vector<uint8_t> ReWriteTable = 
		{
			0xF3, 0x41, 0x0F, 0x10, 0x19,
			0xF3, 0x41, 0x0F, 0x10, 0x41, 0x04,
			0xF3, 0x41, 0x0F, 0x10, 0x51, 0x08
		};

		FrameWork::Memory::WriteProcessMemoryImpl(g_Fivem.GetHandleBulletAddress(), &ReWriteTable[0], ReWriteTable.size());


		std::vector<uint8_t> AngleReWriteTable =
		{
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00
		};

		FrameWork::Memory::WriteProcessMemoryImpl(g_Fivem.GetModuleBase() + 0x34E, &AngleReWriteTable[0], AngleReWriteTable.size());
	}

	void ApplySilent(Vector3D EndBulletPos)
	{
		static uint64_t HandleBulletAddress = g_Fivem.GetHandleBulletAddress();
		static uint64_t AllocPtr = g_Fivem.GetModuleBase() + 0x34E;

		auto CalculateRelativeOffset = [](uint64_t CurrentAddress, uint64_t TargetAddress, int Offset = 5)
		{
			intptr_t RelativeOffset = static_cast<intptr_t>(TargetAddress - (CurrentAddress + Offset));

			return static_cast<uint32_t>(RelativeOffset);
		};

		union
		{
			float f;
			uint32_t i;
		} EndPosX, EndPosY, EndPosZ;

		EndPosX.f = EndBulletPos.x;
		EndPosY.f = EndBulletPos.y;
		EndPosZ.f = EndBulletPos.z;

		{
			std::vector<uint8_t> ReWriteTable =
			{
				0xE9, 0x00, 0x00, 0x00, 0x00
			};

			uint32_t JmpOffset = CalculateRelativeOffset(HandleBulletAddress, AllocPtr);
			ReWriteTable[1] = static_cast<uint8_t>(JmpOffset & 0xFF);
			ReWriteTable[2] = static_cast<uint8_t>((JmpOffset >> 8) & 0xFF);
			ReWriteTable[3] = static_cast<uint8_t>((JmpOffset >> 16) & 0xFF);
			ReWriteTable[4] = static_cast<uint8_t>((JmpOffset >> 24) & 0xFF);

			FrameWork::Memory::WriteProcessMemoryImpl(HandleBulletAddress, &ReWriteTable[0], ReWriteTable.size());
		}

		{
			uintptr_t currentAddress = (uintptr_t)AllocPtr;

			uintptr_t targetAddress = (uintptr_t)(HandleBulletAddress);

			intptr_t relativeOffset = static_cast<intptr_t>(targetAddress - (currentAddress + 28));

			uint32_t jmpOffset = static_cast<uint32_t>(relativeOffset);

			// Modified instructions
			std::vector<uint8_t> ReWriteTable =
			{
				0x41, 0xC7, 0x01, static_cast<uint8_t>(EndPosX.i), static_cast<uint8_t>(EndPosX.i >> 8), static_cast<uint8_t>(EndPosX.i >> 16), static_cast<uint8_t>(EndPosX.i >> 24),
				0x41, 0xC7, 0x41, 0x04, static_cast<uint8_t>(EndPosY.i), static_cast<uint8_t>(EndPosY.i >> 8), static_cast<uint8_t>(EndPosY.i >> 16), static_cast<uint8_t>(EndPosY.i >> 24),
				0x41, 0xC7, 0x41, 0x08, static_cast<uint8_t>(EndPosZ.i), static_cast<uint8_t>(EndPosZ.i >> 8), static_cast<uint8_t>(EndPosZ.i >> 16), static_cast<uint8_t>(EndPosZ.i >> 24),
				0xF3, 0x41, 0x0F, 0x10, 0x19,
				0xE9, 0x00, 0x00, 0x00, 0x00
			};

			// Replace the last 4 bytes in the vector with the new offset
			ReWriteTable[29] = static_cast<uint8_t>(jmpOffset & 0xFF);
			ReWriteTable[30] = static_cast<uint8_t>((jmpOffset >> 8) & 0xFF);
			ReWriteTable[31] = static_cast<uint8_t>((jmpOffset >> 16) & 0xFF);
			ReWriteTable[32] = static_cast<uint8_t>((jmpOffset >> 24) & 0xFF);

			FrameWork::Memory::WriteProcessMemoryImpl(AllocPtr, &ReWriteTable[0], ReWriteTable.size());
		}
	}

	void SilentAim::RunThread()
	{
		while (!g_Options.General.ShutDown)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1 + g_Options.General.ThreadDelay));

			if (!g_Options.LegitBot.SilentAim.Enabled)
				continue;

			if (!g_Fivem.GetLocalPlayerInfo().Ped)
				continue;

			static bool SilentAplied = false;
			bool CanSilent = false;

			Entity ClosestEntity;

			if (g_Fivem.FindClosestEntity(g_Options.LegitBot.SilentAim.Fov, g_Options.LegitBot.SilentAim.MaxDistance, g_Options.LegitBot.SilentAim.ShotNPC, &ClosestEntity))
			{
				if (ClosestEntity.StaticInfo.IsFriend)
				{
					if (SilentAplied)
					{
						RestoreSilent();
						SilentAplied = false;
					}
					continue;
				}

				if (g_Options.LegitBot.AimBot.VisibleCheck && !ClosestEntity.Visible)
				{
					if (SilentAplied)
					{
						RestoreSilent();
						SilentAplied = false;
					}
					continue;
				}

				if (!GetAsyncKeyState(g_Options.LegitBot.SilentAim.KeyBind))
				{
					if (SilentAplied)
					{
						RestoreSilent();
						SilentAplied = false;
					}
					continue;
				}

				Vector3D BonePos;

				switch (g_Options.LegitBot.SilentAim.HitBox)
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

				ApplySilent(BonePos);
				SilentAplied = true;
			}
			else
			{
				if (SilentAplied)
				{
					RestoreSilent();
					SilentAplied = false;
				}
			}
		}
	}
}