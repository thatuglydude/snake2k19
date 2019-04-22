#pragma once

#include "EntityId.h"

namespace tbd {

class EntityIdProvider
{
public:
	EntityId nextId()
	{
		return m_currentEntityId++;
	}

private:
	EntityId m_currentEntityId = {0};		// TODO: access to this var has to be protected from all threads! - atomic?
};

} // namespace tbd {
