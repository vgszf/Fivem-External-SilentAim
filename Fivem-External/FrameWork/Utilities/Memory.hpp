#pragma once

#include <FrameWork/FrameWork.hpp>

namespace FrameWork
{
	namespace Memory
	{
		HWND GetWindowHandleByPID(int Pid);
		HWND GetWindowHandleByName(std::wstring WindowName);
		DWORD GetProcessPidByName(std::wstring ProcessName);
		uint64_t GetModuleBaseByName(DWORD Pid, std::wstring ModuleName);

		void AttachProces(DWORD Pid);
		void DetachProcess();

		void ReadProcessMemoryImpl(uint64_t ReadAddress, LPVOID Read, SIZE_T Size);
		bool WriteProcessMemoryImpl(uint64_t WriteAddress, LPVOID Write, SIZE_T Size);

		std::string ReadProcessMemoryString(uint64_t ReadAddress, SIZE_T StringSize = 256);

		template <typename T, typename B>
		T ReadMemory(B ReadAddress)
		{
			T Read;
			ReadProcessMemoryImpl((uint64_t)ReadAddress, &Read, sizeof(T));
			return Read;
		}

		template <typename T, typename B>
		bool WriteMemory(B WriteAddress, T Value)
		{
			return WriteProcessMemoryImpl((uint64_t)WriteAddress, &Value, sizeof(T));
		}
	}
}