#pragma once
#include <Windows.h>
#include <iostream>
#include <stdint.h>
#pragma comment(lib, "HKDrv_Lib.lib")

bool install_drv();

bool unload_drv();

void cr3_read(UINT32 pid, PVOID address, PVOID buffer, DWORD size);

void cr3_write(UINT32 pid, PVOID address, PVOID buffer, DWORD size);

void protect_process(UINT32 pid);

void get_module_address(UINT32 pid, const wchar_t dllName[MAX_PATH], PVOID Buffer);

void force_file(const wchar_t FilePath[MAX_PATH]);

void force_flush();