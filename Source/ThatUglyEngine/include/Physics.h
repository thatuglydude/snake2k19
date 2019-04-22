#pragma once

#include <cstdint>

namespace tbd {

using Speed = uint32_t;

enum class Rotation : uint8_t
{
	ROTATION_NORTH,
	ROTATION_EAST,
	ROTATION_SOUTH,
	ROTATION_WEST,
};

} // namespace tbd {
