#include "Memory.hpp"

struct TGetWindowHandleData
{
	DWORD Pid;
	std::wstring WindowName;
	HWND hWnd;
};

HANDLE AttachedProcessHandle;
DWORD AttachedProcessPid;

BOOL CALLBACK EnumWindowsCallback(HWND Handle, LPARAM lParam)
{
	TGetWindowHandleData& Data = *(TGetWindowHandleData*)lParam;

	// Searching For Name
	if (Data.Pid == 0)
	{
		int Length = SafeCall(GetWindowTextLength)(Handle);
		if (Length == 0)
			return true;

		std::wstring Buffer(Length + 1, L'\0');

		SafeCall(GetWindowText)(Handle, &Buffer[0], Length + 1);

		if (Data.WindowName != Buffer)
			return true;

		Data.hWnd = Handle;
		return false;
	}
	else // Searching for Pid
	{
		DWORD Pid;
		SafeCall(GetWindowThreadProcessId)(Handle, &Pid);

		if (Data.Pid != Pid)
			return true;

		Data.hWnd = Handle;
		return false;
	}

	return true;
}

namespace FrameWork
{
	HWND Memory::GetWindowHandleByPID(int Pid)
	{
		TGetWindowHandleData HandleData;
		HandleData.Pid = Pid;
		HandleData.WindowName = XorStr(L"");
		HandleData.hWnd = NULL;

		SafeCall(EnumWindows)(EnumWindowsCallback, (LPARAM)&HandleData);
		return HandleData.hWnd;
	}

	HWND Memory::GetWindowHandleByName(std::wstring WindowName)
	{
		TGetWindowHandleData HandleData;
		HandleData.Pid = 0;
		HandleData.WindowName = WindowName;
		HandleData.hWnd = NULL;

		SafeCall(EnumWindows)(EnumWindowsCallback, (LPARAM)&HandleData);
		return HandleData.hWnd;
	}

	DWORD Memory::GetProcessPidByName(std::wstring ProcessName)
	{
		HANDLE hSnapshot = SafeCall(CreateToolhelp32Snapshot)(TH32CS_SNAPPROCESS, 0);
		if (!hSnapshot || hSnapshot == INVALID_HANDLE_VALUE || hSnapshot == ((HANDLE)(LONG_PTR)ERROR_BAD_LENGTH))
		{
#ifdef _DEBUG
			std::cout << XorStr("[ERROR : FrameWork::Memory::GetProcessPidByName::CreateToolhelp32Snapshot] Error:") << SafeCall(GetLastError)() <<  std::endl;
#endif // _DEBUG
			return 0;
		}

		DWORD Pid;
		PROCESSENTRY32 ProcessEntry;
		ProcessEntry.dwSize = sizeof(ProcessEntry);
		if (SafeCall(Process32First)(hSnapshot, &ProcessEntry))
		{
			while (_wcsicmp(ProcessEntry.szExeFile, ProcessName.c_str()))
			{
				if (!SafeCall(Process32Next)(hSnapshot, &ProcessEntry)) // Copy The Next Process of the Snapshot and Paste at PROCESSENTRY32 Struct And Check if The Function Worked
				{
					SafeCall(CloseHandle)(hSnapshot);
					return 0;
				}
			}

			Pid = ProcessEntry.th32ProcessID; // Found
		}
		else
		{
#ifdef _DEBUG
			std::cout << XorStr("[ERROR : FrameWork::Memory::GetProcessPidByName::Process32First] Error:") << SafeCall(GetLastError)() << std::endl;
#endif // _DEBUG
			SafeCall(CloseHandle)(hSnapshot);
			return 0;
		}

		SafeCall(CloseHandle)(hSnapshot);
		return Pid;
	}

	uint64_t Memory::GetModuleBaseByName(DWORD Pid, std::wstring ModuleName)
	{
		HANDLE hSnapshot = SafeCall(CreateToolhelp32Snapshot)(TH32CS_SNAPMODULE, Pid);
		if (!hSnapshot || hSnapshot == INVALID_HANDLE_VALUE || hSnapshot == ((HANDLE)(LONG_PTR)ERROR_BAD_LENGTH))
		{
#ifdef _DEBUG
			std::cout << XorStr("[ERROR : FrameWork::Memory::GetModuleBaseByName::CreateToolhelp32Snapshot] Error:") << SafeCall(GetLastError)() << std::endl;
#endif // _DEBUG
			return 0;
		}

		uint64_t ModuleBase;
		MODULEENTRY32 ModuleEntry;
		ModuleEntry.dwSize = sizeof(ModuleEntry);
		if (SafeCall(Module32First)(hSnapshot, &ModuleEntry))
		{
			while (_wcsicmp(ModuleEntry.szModule, ModuleName.c_str()))
			{
				if (!SafeCall(Module32Next)(hSnapshot, &ModuleEntry)) // Copy The Next Process of the Snapshot and Paste at PROCESSENTRY32 Struct And Check if The Function Worked
				{
					SafeCall(CloseHandle)(hSnapshot);
					return 0;
				}
			}

			ModuleBase = (uint64_t)ModuleEntry.modBaseAddr;
		}
		else
		{
			SafeCall(CloseHandle)(hSnapshot);
			return 0;
		}

		SafeCall(CloseHandle)(hSnapshot);
		return ModuleBase;
	}

	void Memory::AttachProces(DWORD Pid)
	{
		AttachedProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, Pid);
		AttachedProcessPid = Pid;
	}

	void Memory::DetachProcess()
	{
		CloseHandle(AttachedProcessHandle);
		AttachedProcessHandle = nullptr;
		AttachedProcessPid = 0x0;
	}

	void Memory::ReadProcessMemoryImpl(uint64_t ReadAddress, LPVOID Read, SIZE_T Size)
	{
		if (AttachedProcessHandle && AttachedProcessPid)
		{
			if (ReadProcessMemory(AttachedProcessHandle, (LPVOID)ReadAddress, Read, Size, NULL))
			{
				return;
			}
		}
	}

	bool Memory::WriteProcessMemoryImpl(uint64_t WriteAddress, LPVOID Value, SIZE_T Size)
	{
		if (AttachedProcessHandle && AttachedProcessPid)
		{
			if (WriteProcessMemory(AttachedProcessHandle, (LPVOID)WriteAddress, Value, Size, NULL))
			{
				return true;
			}
		}

		return false;
	}

	std::string Memory::ReadProcessMemoryString(uint64_t ReadAddress, SIZE_T StringSize)
	{
		const int BufferSize = 256;

		char Buffer[BufferSize];

		int BytesRead = 0;

		while (BytesRead < BufferSize && BytesRead < StringSize)
		{
			char Character;
			ReadProcessMemoryImpl((uint64_t)ReadAddress + BytesRead, &Character, sizeof(char));
			Buffer[BytesRead] = Character;

			if (Character == '\0')
				break;

			BytesRead++;
		}

		return std::string(Buffer);
	}
}