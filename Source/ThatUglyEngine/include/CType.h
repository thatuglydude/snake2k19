#pragma once

#include <cstdint>

namespace tbd {

using ComponentMask = uint32_t;

enum CType
{
	COMPONENT_TYPE_NONE = 0x00,
	COMPONENT_TYPE_RIGID_BODY = 0x01,
	COMPONENT_TYPE_DRAWABLE = 0x02,
	COMPONENT_TYPE_TIMED = 0x04,
	COMPONENT_TYPE_VELOCITY = 0x08,
};

} // namespace tbd {
