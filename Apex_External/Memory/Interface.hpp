#pragma once
#include "driver.h"
#include <tlhelp32.h>

namespace I
{
	template <class T>
	T Read(DWORD64 address, ULONG Mode = 0)
	{
		T buffer = { 0 };
		ReadMemory(address, (PBYTE)&buffer, sizeof(T), Mode);
		return buffer;
	}

	template <class T>
	BOOL Write(DWORD64 address, T buffer, ULONG Mode = 1)
	{
		return WriteMemory(address, (PBYTE)&buffer, sizeof(T), Mode);
	}

	BOOL installDriver(const char* key)
	{
		return Loaddriver1(key);
	}

	BOOL isInstall()
	{
		return IsInstall();
	}

	void ReadBytesLen(uintptr_t address, OUT unsigned char* oudata, ULONG length, ULONG Mode = 1)
	{
		ReadMemory(address, (PBYTE)&oudata, length, Mode);
	}

	DWORD64 GetModuleBase(const char* Module)
	{
		return GetModule(Module);
	}

	BOOL SetProcess(ULONG pid)
	{
		return ESetProcess(pid);
	}

	DWORD GetProcessIdByName(const WCHAR* szProcessName)
	{
		HANDLE hProcessSnapShot = NULL;
		PROCESSENTRY32 pe32 = { 0 };

		hProcessSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (hProcessSnapShot == (HANDLE)-1) return NULL;

		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hProcessSnapShot, &pe32))
		{
			do {
				if (!wcscmp(szProcessName, pe32.szExeFile)) return pe32.th32ProcessID;
			} while (Process32Next(hProcessSnapShot, &pe32));
		}
		else
		{
			CloseHandle(hProcessSnapShot);
		}
		return NULL;
	}
}