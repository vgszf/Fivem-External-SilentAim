#pragma once

#include "Offsets.hpp"
#include "GTADefines.hpp"

#include <FrameWork/FrameWork.hpp>

namespace Cheat
{
	class CVehicle
	{
	public:
		uint64_t GetModelInfo()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<uint64_t>(this + 0x20);
		}

		uint64_t GetDriver()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<uint64_t>(this + Driver);
		}

		uint64_t GetNavigation()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<uint64_t>(this + 0x30);
		}

		Vector3D GetCoordinate()
		{
			if (!this)
				return Vector3D{ 0,0,0 };

			return FrameWork::Memory::ReadMemory<Vector3D>(this + 0x90);
		}

		void SetDoorLock(int Lock)
		{
			if (!this)
				return;

			FrameWork::Memory::WriteMemory(this + DoorLock, Lock);
		}

		float GetHealth()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<float>(this + 0x280);
		}

		void SetHealth(float Health)
		{
			if (!this)
				return;

			FrameWork::Memory::WriteMemory(this + 0x280, Health);
		}

		float GetMaxHealth()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<float>(this + MaxHealth);
		}
	};

	class CPlayerInfo
	{
	public:
		int GetPlayerID()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<int>(this + PlayerNetID);
		}

		void SetStamina(float Stamina)
		{
			if (!this)
				return;

			FrameWork::Memory::WriteMemory(this + 0xCF0, Stamina);
		}

		void SetSpeed(float Speed)
		{
			if (!this)
				return;

			FrameWork::Memory::WriteMemory(this + 0xCF0, Speed);
		}
	};

	class CWeaponInfo
	{
	public:
		std::string GetWeaponName()
		{
			if (!this)
				return NULL;

			return FrameWork::Memory::ReadProcessMemoryString(FrameWork::Memory::ReadMemory<uint64_t>(this + 0x05F0));
		}
	};

	class CWeaponManager
	{
	public:
		CWeaponInfo* GetWeaponInfo()
		{
			if (!this)
				return 0;

			return (CWeaponInfo*)FrameWork::Memory::ReadMemory<uint64_t>(this + 0x20);
		}

	};

	class CPed
	{
	public:
		CPlayerInfo* GetPlayerInfo()
		{
			if (!this)
				return 0;

			return (CPlayerInfo*)FrameWork::Memory::ReadMemory<uint64_t>(this + PlayerInfo);
		}

		CWeaponManager* GetWeaponManager()
		{
			if (!this)
				return 0;

			return (CWeaponManager*)FrameWork::Memory::ReadMemory<uint64_t>(this + WeaponManager);
		}

		CVehicle* GetLastVehicle()
		{
			if (!this)
				return 0;

			return (CVehicle*)FrameWork::Memory::ReadMemory<uint64_t>(this + LastVehicle);
		}

		uint64_t GetModelInfo()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<uint64_t>(this + 0x20);
		}

		void godmode_on(bool Toggle)
		{
			FrameWork::Memory::WriteMemory(this + 0x189, true);
		}
		void godmode_off(bool Toggle)
		{
			FrameWork::Memory::WriteMemory(this + 0x189, false);
		}

		void SetInvencible(bool Toggle)
		{
			if (!this)
				return;

			uint64_t OldFlag = FrameWork::Memory::ReadMemory<uint64_t>(this + 0x188);
			FrameWork::Memory::WriteMemory(this + 0x188, Toggle ? (OldFlag | (1 << 8)) : (OldFlag & ~(1 << 8)));
		}

		uint64_t GetNavigation()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<uint64_t>(this + 0x30);
		}

		Vector3D GetCoordinate()
		{
			if (!this)
				return Vector3D{ 0,0,0 };
		
			return FrameWork::Memory::ReadMemory<Vector3D>(this + 0x90);
		}

		bool IsGodMode()
		{
			if (!this)
				return false;

			return FrameWork::Memory::ReadMemory<bool>(this + 0x189);
		}

		float GetHealth()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<float>(this + 0x280);
		}

		void SetHealth(float NewHealth)
		{
			if (!this)
				return;

			FrameWork::Memory::WriteMemory(this + 0x280, NewHealth);
		}

		float GetMaxHealth()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<float>(this + MaxHealth);
		}

		float GetArmor()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<float>(this + Armor);
		}

		uint32_t GetPedType()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<uint32_t>(this + EntityType);
		}

		bool IsVisible()
		{
			if (!this)
				return false;

			BYTE VisibilityFlag = FrameWork::Memory::ReadMemory<BYTE>(this + VisibleFlag);

			if (VisibilityFlag == 36 || VisibilityFlag == 0 || VisibilityFlag == 4)
				return false;

			return true;
		}

		bool IsNPC()
		{
			uint32_t PedType = GetPedType();

			if (!PedType)
				return false;

			PedType = PedType << 11 >> 25;

			if (PedType != 2)
				return true;

			return false;
		}

		bool IsAnimal()
		{
			uint32_t PedType = GetPedType();

			if (!PedType)
				return false;

			PedType = PedType << 11 >> 25;

			if (PedType > 27)
				return true;

			return false;
		}

		void SetConfigFlag(ePedConfigFlags Flag, bool Value)
		{
			int v1 = (int)Flag;
			if (!this || v1 >= 0x1CA)
				return;

			auto v2 = 1 << (v1 & 0x1F);
			auto v3 = v1 >> 5;
			auto v4 = (uint64_t)this + 4 * v3 + ConfigFlags;
			auto v5 = FrameWork::Memory::ReadMemory<long>(v4);

			if (Value != ((v2 & v5) != 0))
			{
				auto v6 = v2 & (v5 ^ -(uint8_t)(Value ? 1 : 0));
				v5 ^= v6;

				FrameWork::Memory::WriteMemory(v4, v5);
			}
		}

		bool HasConfigFlag(ePedConfigFlags Flag)
		{
			int v1 = (int)Flag;
			if (!this || v1 >= 0x1CA) 
				return false;

			auto v2 = 1 << (v1 & 0x1F);
			auto v3 = v1 >> 5;
			auto v4 = (uint64_t)this + 4 * v3 + ConfigFlags;
			auto v5 = FrameWork::Memory::ReadMemory<long>(v4);

			return (v2 & v5) != 0;
		}
	};

	class CPedList
	{
	public:
		CPed* Ped(int Index)
		{
			if (!this) 
				return 0;

			return (CPed*)FrameWork::Memory::ReadMemory<uint64_t>(this + (Index * 0x10));
		}
	};

	class CPedInterface
	{
	public:
		CPedList* PedList()
		{
			if (!this) 
				return 0;

			return (CPedList*)FrameWork::Memory::ReadMemory<uint64_t>(this + 0x100);
		}

		uint64_t PedMaximum()
		{
			if (!this) 
				return 0;

			return FrameWork::Memory::ReadMemory<uint64_t>(this + 0x108);
		}
	};

	class CVehicleList
	{
	public:
		CVehicle* Vehicle(int Index)
		{
			if (!this)
				return 0;

			return (CVehicle*)FrameWork::Memory::ReadMemory<uint64_t>(this + (Index * 0x10));
		}
	};

	class CVehicleInterface
	{
	public:
		CVehicleList* VehicleList()	
		{
			if (!this)
				return 0;

			return (CVehicleList*)FrameWork::Memory::ReadMemory<uint64_t>(this + 0x180);
		}

		uint64_t VehicleMaximum()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<uint64_t>(this + 0x188);
		}

		uint64_t VehiclesAtList()
		{
			if (!this)
				return 0;

			return FrameWork::Memory::ReadMemory<uint64_t>(this + 0x190);
		}
	};

	class CReplayInterface
	{
	public:
		CVehicleInterface* VehicleInterface()
		{
			if (!this)
				return 0;

			return (CVehicleInterface*)FrameWork::Memory::ReadMemory<uint64_t>(this + 0x10);
		}

		CPedInterface* PedInterface()
		{
			if (!this) 
				return 0;

			return (CPedInterface*)FrameWork::Memory::ReadMemory<uint64_t>(this + 0x18);
		}
	};

	class CCamFollowPedCamera
	{
	public:
		Vector3D GetViewAngles()
		{
			if (!this)
				return Vector3D(0, 0, 0);

			return FrameWork::Memory::ReadMemory<Vector3D>(this + 0x40);
		}

		void SetViewAngles(Vector3D Angles)
		{
			if (!this)
				return;

			FrameWork::Memory::WriteMemory(this + 0x40, Angles);
		}

		Vector3D GetCrosshairPosition()
		{
			if (!this)
				return Vector3D(0, 0, 0);

			return FrameWork::Memory::ReadMemory<Vector3D>(this + 0x60);
		}

		void SetCrosshairPosition(Vector3D Position)
		{
			if (!this)
				return;

			FrameWork::Memory::WriteMemory(this + 0x60, Position);
		}

		Vector3D GetThirdpersonViewAngles()
		{
			if (!this)
				return Vector3D(0, 0, 0);

			return FrameWork::Memory::ReadMemory<Vector3D>(this + 0x3d0);
		}

		void SetThirdpersonViewAngles(Vector3D ViewAngles)
		{
			if (!this)
				return;

			FrameWork::Memory::WriteMemory(this + 0x3d0, ViewAngles);
		}


		Vector3D GetCameraPosition()
		{
			if (!this)
				return Vector3D(0, 0, 0);

			return FrameWork::Memory::ReadMemory<Vector3D>(this + 0x3F0);
		}
	};

	class CCamGameplayDirector
	{
	public:
		CCamFollowPedCamera* GetFollowPedCamera()
		{
			if (!this)
				return 0;

			return (CCamFollowPedCamera*)FrameWork::Memory::ReadMemory<uint64_t>(this + 0x3C0);
		}
	};

	class CWorld
	{
	public:
		CPed* LocalPlayer()
		{
			if (!this)
				return 0;

			return (CPed*)FrameWork::Memory::ReadMemory<uint64_t>(this + 0x8);
		}
	};
}