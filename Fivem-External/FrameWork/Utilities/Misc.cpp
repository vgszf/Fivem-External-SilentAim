#include "Misc.hpp"

#include <FrameWork/FrameWork.hpp>
#include <algorithm>
#include <winhttp.h>
#include <sstream>

namespace FrameWork
{
	int Misc::RandomInt(int Lower, int Max)
	{
		return (rand() % (Max - Lower + 1)) + Lower;
	}

	std::wstring Misc::RandomString(size_t Length)
	{
		auto Randchar = []() -> char
			{
				const char* Charset = XorStr("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
				const size_t MaxIndex = (sizeof(Charset) - 1);
				return Charset[rand() % MaxIndex];
			};

		std::wstring Str(Length, 0);
		std::generate_n(Str.begin(), Length, Randchar);
		return Str;
	}

	std::string Misc::Wstring2String(std::wstring Input)
	{
		return std::string(Input.begin(), Input.end());
	}

	std::wstring Misc::String2WString(std::string Input)
	{
		return std::wstring(Input.begin(), Input.end());
	}

	void Misc::InitializeConsole()
	{
		SafeCall(AllocConsole)();
		freopen(XorStr("CONIN$"), XorStr("r"), stdin);
		freopen(XorStr("CONOUT$"), XorStr("w"), stdout);
		SafeCall(SetConsoleTitleA)(XorStr("Debug Console"));
	}

	void Misc::ShutDownConsole()
	{
		SafeCall(FreeConsole)();
	}

	std::string Misc::DownloadServerInfo(std::wstring IP, int PORT)
	{
		HINTERNET hSession = WinHttpOpen(XorStr(L"A WinHTTP FiveM Request Program/1.0"), WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

		if (hSession)
		{
			HINTERNET hConnect = WinHttpConnect(hSession, IP.c_str(), PORT, 0);

			if (hConnect)
			{
				HINTERNET hRequest = WinHttpOpenRequest(hConnect, XorStr(L"GET"), XorStr(L"/players.json"), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);

				if (hRequest)
				{
					if (WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0))
					{
						if (WinHttpReceiveResponse(hRequest, NULL)) 
						{
							DWORD dwSize = 0;
							DWORD dwDownloaded = 0;
							LPSTR pszOutBuffer;
							BOOL  bResults = FALSE;
							std::string Response;

							do 
							{
								dwSize = 0;
								if (WinHttpQueryDataAvailable(hRequest, &dwSize))
								{
									pszOutBuffer = new char[dwSize + 1];
									if (!pszOutBuffer)
									{
										dwSize = 0;
									}
									else
									{
										ZeroMemory(pszOutBuffer, dwSize + 1);

										if (WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
											Response.append(pszOutBuffer, dwDownloaded);
									}

									delete[] pszOutBuffer;
								}

							} while (dwSize > 0);

							return Response;
						}
					}

					WinHttpCloseHandle(hRequest);
				}

				WinHttpCloseHandle(hConnect);
			}

			WinHttpCloseHandle(hSession);
		}

		return NULL;
	}

	RTL_OSVERSIONINFOW Misc::GetRealOSVersion()
	{
		HMODULE hMod = SafeCall(GetModuleHandleW)(XorStr(L"ntdll.dll"));
		if (hMod)
		{
			RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)SafeCall(GetProcAddress)(hMod, XorStr("RtlGetVersion"));
			if (fxPtr != nullptr)
			{
				RTL_OSVERSIONINFOW rovi = { 0 };
				rovi.dwOSVersionInfoSize = sizeof(rovi);
				if (fxPtr(&rovi) == 0x00000000)
				{
					return rovi;
				}
			}
		}
		RTL_OSVERSIONINFOW rovi = { 0 };
		return rovi;
	}

	std::string Misc::GetWindowsFullBuildNumber()
	{
		DWORD Dummy;
		DWORD VersionSize = SafeCall(GetFileVersionInfoSizeA)(XorStr("kernel32.dll"), &Dummy);
		if (VersionSize == 0)
			return NULL;

		std::unique_ptr<BYTE[]> pBuffer(new BYTE[VersionSize]);
		if (!SafeCall(GetFileVersionInfoA)(XorStr("kernel32.dll"), 0, VersionSize, pBuffer.get()))
			return NULL;

		VS_FIXEDFILEINFO* pFileInfo;
		UINT VersionLength;
		if (!SafeCall(VerQueryValueA)(pBuffer.get(), XorStr("\\"), reinterpret_cast<void**>(&pFileInfo), &VersionLength))
			return NULL;

		std::stringstream aa;

		aa << HIWORD(pFileInfo->dwProductVersionMS) << XorStr(".") << LOWORD(pFileInfo->dwProductVersionMS) << XorStr(".") << HIWORD(pFileInfo->dwProductVersionLS) << XorStr(".") << LOWORD(pFileInfo->dwProductVersionLS);

		return aa.str();
	}
}