#pragma once
#include "Offsets.hpp"
#include "Structs.hpp"
#include "Memory/Interface.hpp"

uint64_t GetEntityById(uint64_t Entity, uint64_t BaseAddr)
{
	uint64_t EntityList = BaseAddr + OFF_ENTITYLIST;
	uint64_t BaseEntity = I::Read<uint64_t>(EntityList);

	if (!BaseEntity)
		return NULL;
	return I::Read<uint64_t>(EntityList + (Entity << 5));
}