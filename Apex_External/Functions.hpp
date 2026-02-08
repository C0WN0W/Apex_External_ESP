#pragma once
#include "Offsets.hpp"

bool world_to_screen(Vector3 from, float* m_vMatrix, int targetWidth, int targetHeight, Vector3& to)
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

float GameUnitsToMeters(float units)
{
    return units / 39.37007874;
}