#include <iostream>
#include <thread>
#include <chrono>
#include "Draw.hpp"
#include "Entity.hpp"

using namespace std;
HWND hwnd = 0;
Vector2 ScreenSize = { GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN) };
Vector2 SightCenter = { ScreenSize.x / 2.f,ScreenSize.y / 2.f };

void fun()
{
	// this_thread::sleep_for(chrono::milliseconds(1));

	uint64_t viewRender = drv.RPM<uint64_t>(Global::GameBase + OFF_VIEW_RENDER);
	uint64_t viewMatrix = drv.RPM<uint64_t>(viewRender + OFF_VIEW_MATRIX);
	Matrix m = drv.RPM<Matrix>(viewMatrix);

	for (int i = 0; i <= 128; i++) {
		DWORD64 Entity = GetEntityById(i, Global::GameBase);
		if (Entity == 0)
			continue;

		Vector3 Position = drv.RPM<Vector3>(Entity + OFF_VecAbsOrigin);

		// Color based on health
		int MaxHealth = drv.RPM<int>(Entity + OFF_iMaxHealth);
		float TargetHealth = drv.RPM<float>(Entity + OFF_iHealth) / (float)MaxHealth * 255.f;
		float r = 255.f - TargetHealth;
		float g = TargetHealth;
		float b = 0.f;

		Vector3 bs ,hs;
		Vector3 HeadPosition = NewHitbox(Entity, 0);
		HeadPosition.z += 12.f;
		world_to_screen(Position, m, ScreenSize.x, ScreenSize.y, bs);
		world_to_screen(HeadPosition, m, ScreenSize.x, ScreenSize.y, hs);

		float height = fabsf(fabsf(hs.y) - fabsf(bs.y));
		float width = height / 2.f;
		float boxLeft = bs.x - (width / 2);
		float boxRight = bs.x + (width / 2);
		int widthC = (int)boxRight - (int)boxLeft;
		int x1, y1, x2, y2;
		x1 = (int)boxLeft; y1 = (int)hs.y; x2 = (int)boxRight; y2 = (int)bs.y;

		DrawBox((int)boxLeft, (int)hs.y, (int)boxRight, (int)bs.y, ImColor((int)r, (int)g, (int)b, 255), 1.5f);
	}
}

void main()
{
	if (!(drv.Loaddriver("AXP4ER6S677APV6A77I09C")))
	{
		cout << "[!] Failed to install driver!" << endl;
		system("pause");
		exit(0);
	}

	if (!(drv.IsInstall()))
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
		PID = drv.GetProcessIdByName("r5apex_dx12.exe");
	}

	system("cls");
	cout << "[+] PID: " << PID << endl;

	drv.proceint(PID);
	Global::GameBase = drv.GetMoudleBase();
	if (!Global::GameBase)
	{
		cout << "[!] Failed to get region!" << endl;
		system("pause");
		exit(0);
	}

	cout << "[+] Base: " << hex << Global::GameBase << endl;

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