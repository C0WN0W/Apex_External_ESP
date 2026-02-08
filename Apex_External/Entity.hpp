#pragma once
#include "Functions.hpp"

bool world_to_screen(Vec3 from, float* m_vMatrix, int targetWidth, int targetHeight, Vec3& to)
{
    float w = m_vMatrix[12] * from.x + m_vMatrix[13] * from.y + m_vMatrix[14] * from.z + m_vMatrix[15];

    if (w < 0.01f) {
        return false;
    }

    to.x = m_vMatrix[0] * from.x + m_vMatrix[1] * from.y + m_vMatrix[2] * from.z + m_vMatrix[3];
    to.y = m_vMatrix[4] * from.x + m_vMatrix[5] * from.y + m_vMatrix[6] * from.z + m_vMatrix[7];

    float invw = 1.0f / w;
    to.x *= invw;
    to.y *= invw;

    float x = (float)targetWidth / 2.f;
    float y = (float)targetHeight / 2.f;

    x += 0.5f * to.x * targetWidth + 0.5f;
    y -= 0.5f * to.y * targetHeight + 0.5f;

    to.x = x;
    to.y = y;
    to.z = 0;
    return true;
}
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