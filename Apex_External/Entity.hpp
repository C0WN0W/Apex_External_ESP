#pragma once
#include "Functions.hpp"

std::string GetLevelName()
{
	char tmpstr;
	tmpstr = drv.RPM<char>(Global::GameBase + OFF_LEVELNAME, 32);
	return std::string(&tmpstr);
}

uint64_t GetEntityPtr(int i)
{
	return drv.RPM<uint64_t>(Global::GameBase + OFF_ENTITYLIST + ((uint64_t)i << 5));
}

uint64_t GetLocalPlayerPtr()
{
	int i = drv.RPM<int>(Global::GameBase + OFF_LOCAL_ENTITY_HANDLE);
	return drv.RPM<uint64_t>(Global::GameBase + OFF_ENTITYLIST + ((uint64_t)i << 5));
}

std::string GetSignifier(uint64_t Addr)
{
	uint64_t SignifierPtr = drv.RPM<uint64_t>(Addr + OFF_SignifierName);
	return ReadStr32(SignifierPtr);
}

int get_script_name(uint64_t EntityAddr)
{
	return drv.RPM<int>(EntityAddr + OFF_scriptNameIndex);
}

bool isValid(uint64_t EntityAddr)
{
	if (!EntityAddr)
		return false;
	if (get_script_name(EntityAddr) < -1000 || get_script_name(EntityAddr) > 100000)
		return false;
	return true;
}

bool isOnGround(uint64_t player)
{
	uint32_t flags = drv.RPM<uint32_t>(player + OFF_fFlags);
	return (flags & 1) != 0;
}

int GetTeamID(uint64_t Addr)
{
	return drv.RPM<int>(Addr + OFF_iTeamNum);
}

int GetHealth(uint64_t Addr)
{
	return drv.RPM<int>(Addr + OFF_iHealth);
}

int GetMaxHealth(uint64_t Addr)
{
	return drv.RPM<int>(Addr + OFF_iMaxHealth);
}

int GetShield(uint64_t Addr)
{
	return drv.RPM<int>(Addr + OFF_iShield);
}

int GetMaxShield(uint64_t Addr)
{
	return drv.RPM<int>(Addr + OFF_iMaxShield);
}

int GetArmor(uint64_t Addr)
{
	return drv.RPM<int>(Addr + OFF_Armor);
}

int GetLifeState(uint64_t Addr)
{
	return drv.RPM<int>(Addr + OFF_LifeState);
}

Vector3 GetPosition(uint64_t Addr)
{
	return drv.RPM<Vector3>(Addr + OFF_VecAbsOrigin);
}

int GetKnocked(uint64_t Addr)
{
	return drv.RPM<int>(Addr + OFF_bleedoutState);
}

std::string GetName(uint64_t Addr)
{
	uint64_t NameIndex = drv.RPM<uint64_t>(Addr + OFF_NameIndex);
	uint64_t NameOffset = drv.RPM<uint64_t>(Global::GameBase + OFF_NAMELIST + (NameIndex - 1) * 24);
	
	std::string PlayerName = ReadStr32(NameOffset);
	return PlayerName;
}

float GetDistance(Vector3* p1, Vector3* p2)
{
	Vector3 tmp = { 0,0,0 };
	tmp.x = p1->x - p2->x;
	tmp.y = p1->y - p2->y;
	tmp.z = p1->z - p2->z;

	return (float)sqrt((double)tmp.x * tmp.x + (double)tmp.y * tmp.y + (double)tmp.z * tmp.z);
}

float GetDistance(Vector3 LocalPlayer, Vector3 Entity)
{
	Vector3 tmp = { 0,0,0 };
	tmp.x = LocalPlayer.x - Entity.x;
	tmp.y = LocalPlayer.y - Entity.y;
	tmp.z = LocalPlayer.z - Entity.z;

	return (float)sqrt((double)tmp.x * tmp.x + (double)tmp.y * tmp.y + (double)tmp.z * tmp.z);
}

Vector3 NewHitbox(uintptr_t ent, int HitBox) {
	DWORD64 Bones = drv.RPM<DWORD64>(ent + OFF_Bone);
	if (!Bones) return Vector3();
	uintptr_t Model = drv.RPM<uintptr_t>(ent + OFF_StudioHdr);

	DWORD64 StudioHdr = drv.RPM<DWORD64>(Model + 8);
	if (!StudioHdr) return Vector3();

	uint16_t HitboxCache = drv.RPM<uint16_t>(StudioHdr + 0x34);
	uint64_t HitboxArray = StudioHdr + ((uint16_t)(HitboxCache & 0xFFFE) << (4 * (HitboxCache & 1)));

	int HitboxNum = HitBox;

	uint16_t IndexCache = drv.RPM<uint16_t>(HitboxArray + 4);
	int HitboxIndex = ((uint16_t)(IndexCache & 0xFFFE) << (4 * (IndexCache & 1)));
	uint16_t Bone = drv.RPM<uint16_t>(HitboxIndex + HitboxArray + (HitboxNum * 0x20));

	Vector3 BoneOff;

	Matrix3x4 BoneMatrix = drv.RPM<Matrix3x4>(Bones + (Bone * sizeof(Matrix3x4)));
	BoneOff = { BoneMatrix._14, BoneMatrix._24, BoneMatrix._34 };

	Vector3 Pos = GetPosition(ent) + BoneOff;
	return Pos;
}