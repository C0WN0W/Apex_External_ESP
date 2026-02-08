#pragma once
#include "Structs.hpp"
#include "Memory/driver.h"

const uint64_t OFF_ENTITYLIST = 0x669E7A8;
const uint64_t OFF_VIEW_MATRIX = 0x11A350;
const uint64_t OFF_VIEW_RENDER = 0x4177690;
const uint64_t OFF_VecAbsOrigin = 0x17C;
const uint64_t OFF_iHealth = 0x324;
const uint64_t OFF_iMaxHealth = 0x468;
const uint64_t OFF_scriptNameIndex = 0x580;


namespace Global {
	inline uintptr_t GameBase;
	inline uintptr_t ViewRender;
	inline Matrix m;
}