#pragma once
#include "Offsets.hpp"

bool world_to_screen(Vector3 from, Matrix m, int targetWidth, int targetHeight, Vector3& to)
{
    float w = m.matrix[12] * from.x + m.matrix[13] * from.y + m.matrix[14] * from.z + m.matrix[15];

    if (w < 0.01f) {
        return false;
    }

    to.x = m.matrix[0] * from.x + m.matrix[1] * from.y + m.matrix[2] * from.z + m.matrix[3];
    to.y = m.matrix[4] * from.x + m.matrix[5] * from.y + m.matrix[6] * from.z + m.matrix[7];

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

std::string ReadStr32(uint64_t src)
{
	StrBuf32 ret = drv.RPM<StrBuf32>(src);
	return std::string::basic_string(ret.buf);
}