#pragma once
#include "Functions.hpp"

uint64_t GetEntityById(uint64_t Entity, uint64_t BaseAddr)
{
	uint64_t EntityList = BaseAddr + OFF_ENTITYLIST;
	uint64_t BaseEntity = drv.RPM<uint64_t>(EntityList);

	if (!BaseEntity)
		return NULL;
	return drv.RPM<uint64_t>(EntityList + (Entity << 5));
}

uint64_t GetEntityPtr(int i)
{
	return drv.RPM<uint64_t>(Global::GameBase + OFF_ENTITYLIST + ((uint64_t)i << 5));
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