#pragma once
#include <Windows.h>
#include <iostream>
#include <stdint.h>
#include <TlHelp32.h>
#pragma comment(lib, "HKDrv_Lib.lib")

namespace drv
{
	bool installDrv();

	bool UnloadDrv();

	void RPM(UINT32 pid, PVOID address, PVOID buffer, DWORD size);

	void WPM(UINT32 pid, PVOID address, PVOID buffer, DWORD size);

	void SHIT(UINT32 pid);

	void GetModule(UINT32 pid, const wchar_t dllName[MAX_PATH], PVOID Buffer);

	void DelFile(const wchar_t FilePath[MAX_PATH]);

	template <typename T>
	T Read(int pid, unsigned long long Addr);

	template <typename T>
	T Read(int pid, unsigned long long Addr, unsigned long size);

	template<typename T>
	bool Write(int pid, unsigned long long Addr, T value);

	uint64_t GetProcessIdByName(const char* processName);
};

template<typename T> inline T drv::Read(int pid, unsigned long long Addr)
{
	T readBuffer{};
	uint64_t lpNumberOfBytesRead;
	RPM(pid, (PVOID)Addr, &readBuffer, sizeof(T));
	return (T)readBuffer;
}

template<typename T> inline T drv::Read(int pid, unsigned long long Addr, unsigned long size)
{
	T readBuffer{};
	uint64_t lpNumberOfBytesRead;
	RPM(pid, (PVOID)Addr, &readBuffer, size);
	return (T)readBuffer;
}

template<typename T> inline bool drv::Write(int pid, unsigned long long Addr, T value)
{
	uint64_t lpNumberOfBytesRead;
	WPM(pid, (PVOID)Addr, &value, sizeof(T));
	return true;
}

inline uint64_t drv::GetProcessIdByName(const char* processName)
{
	size_t len = strlen(processName) + 1;
	wchar_t* wProcessName = new wchar_t[len];
	mbstowcs(wProcessName, processName, len);

	HANDLE hProcessSnapShot = NULL;
	PROCESSENTRY32 pe32 = { 0 };

	hProcessSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (hProcessSnapShot == INVALID_HANDLE_VALUE)
	{
		delete[] wProcessName;
		return 0;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessSnapShot, &pe32))
	{
		do
		{
			if (!_wcsicmp(wProcessName, pe32.szExeFile))
			{
				delete[] wProcessName;
				CloseHandle(hProcessSnapShot);
				return pe32.th32ProcessID;
			}
		} while (Process32Next(hProcessSnapShot, &pe32));
	}

	delete[] wProcessName;
	CloseHandle(hProcessSnapShot);

	return 0;
}