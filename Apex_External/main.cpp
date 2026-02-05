#include <iostream>
#include <thread>
#include <chrono>
#include "OS-ImGui/OS-ImGui.h"
#include "Entity.hpp"

using namespace std;
DWORD64 GameBase = 0;
HWND hwnd = 0;
Vector2 ScreenSize = { GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN) };

void fun()
{
	this_thread::sleep_for(chrono::milliseconds(1));

	uint64_t viewRender = I::Read<uint64_t>(GameBase + OFF_VIEW_RENDER);
	uint64_t viewMatrix = I::Read<uint64_t>(viewRender + OFF_VIEW_MATRIX);
	Matrix m = I::Read<Matrix>(viewMatrix);

	for (int i = 0; i <= 100; i++) {
		DWORD64 Entity = GetEntityById(i, GameBase);
		if (Entity == 0)
			continue;

		Vector3 Position = I::Read<Vector3>(Entity + OFF_VecAbsOrigin);
		Vector3 ScreenPosition = _WorldToScreen(Position, m, ScreenSize);
		if (ScreenPosition.z <= 0.f)
			continue;

		// Color based on health
		int MaxHealth = I::Read<int>(Entity + OFF_iMaxHealth);
		float TargetHealth = I::Read<float>(Entity + OFF_iHealth) / (float)MaxHealth * 255.f;
		float r = 255.f - TargetHealth;
		float g = TargetHealth;
		float b = 0.f;

		ImDrawList* dL = ImGui::GetBackgroundDrawList();
		dL->AddCircle({ ScreenPosition.x,ScreenPosition.y }, 3, ImColor(0, 255, 0, 255), 0, 1.5f);
	}
}

void main()
{
	if (!(I::installDriver("AXP4ER6S677APV6A77I09C")))
	{
		cout << "[!] Failed to install driver!" << endl;
		system("pause");
		exit(0);
	}

	if (!(I::isInstall()))
	{
		cout << "[!] Failed to connect driver!" << endl;
		system("pause");
		exit(0);
	}

	DWORD PID = 0;
	while (!PID)
	{
		cout << "[!] Waiting game process..." << endl;
		Sleep(2000);
		PID = I::GetProcessIdByName(L"r5apex_dx12.exe");
	}

	system("cls");
	cout << "[+] PID: " << PID << endl;

	I::SetProcess(PID);
	GameBase = I::GetModuleBase("r5apex_dx12.exe");
	if (!GameBase)
	{
		cout << "[!] Failed to get region!" << endl;
		system("pause");
		exit(0);
	}

	cout << "[+] Base: " << hex << GameBase << endl;

	while (!hwnd)
	{
		hwnd = FindWindowA("Respawn001", "Apex Legends");
		Sleep(2000);
	}
	cout << "[+] Game HWND: " << hwnd << endl;
		
	try
	{
		Gui.AttachAnotherWindow("Apex Legends", "Respawn001", fun);
	}
	catch (OSImGui::OSException& e)
	{
		cout << e.what() << endl;
	}
	return;
}