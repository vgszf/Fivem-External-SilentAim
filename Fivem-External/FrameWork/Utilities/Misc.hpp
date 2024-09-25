#pragma once
#include <Windows.h>
#include <string>

typedef LONG NTSTATUS, * PNTSTATUS;
typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

namespace FrameWork
{
	namespace Misc
	{
		int RandomInt(int Lower = -100, int Max = 100);
		std::wstring RandomString(size_t Length = 12);
		std::string Wstring2String(std::wstring Input);
		std::wstring String2WString(std::string Input);
		void InitializeConsole();
		void ShutDownConsole();
		std::string DownloadServerInfo(std::wstring IP, int PORT);
		RTL_OSVERSIONINFOW GetRealOSVersion();
		std::string GetWindowsFullBuildNumber();
	}
}