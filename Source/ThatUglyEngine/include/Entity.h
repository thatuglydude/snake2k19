#pragma once

#include "CType.h"	// TODO: is componentMask useful anyhow?
#include "EntityId.h"
#include <string>

namespace tbd {

class Entity
{
public:
	Entity(const EntityId& EntityId, const ComponentMask componentMask)
		: m_entityId{EntityId},
		m_componentMask{componentMask},
		m_expired{false}
	{}

	Entity(const EntityId& EntityId, const std::string& name, const ComponentMask componentMask)
		: m_entityId{EntityId},
		m_name{name},
		m_componentMask{componentMask},
		m_expired{false}
	{}

	virtual ~Entity() = default;

	const EntityId entityId() const
	{
		return m_entityId;
	}

	const std::string& name() const
	{
		return m_name;
	}

	const bool expired() const
	{
		return m_expired;
	}

	void doExpire()
	{
		m_expired = true;
	}

	Entity(const Entity& rhs) = delete;
	Entity& operator=(const Entity& rhs) = delete;
	Entity(Entity&& rhs) = delete;
	Entity& operator=(Entity&& rhs) = delete;

protected:
	const EntityId m_entityId;
	const std::string m_name;
	const ComponentMask m_componentMask;

	bool m_expired;
};

} // namespace tbd {
