#pragma once

#include "CType.h"
#include "Physics.h"

#include "CContainer.h"
#include "Singleton.h"
#include "EntityId.h"

namespace tbd {

class CVelocity
{
public:
	explicit CVelocity(const EntityId& entityId, const Rotation rotation, const Speed speed)
		: m_entityId{entityId}, m_rotation{rotation}, m_speed{speed}
	{
		Singleton<CContainer<CVelocity>>::instance().insert(m_entityId, this);
	}

	~CVelocity()
	{
		Singleton<CContainer<CVelocity>>::instance().remove(m_entityId);
	}

	const Rotation rotation() const
	{
		return m_rotation;
	}

	const Speed speed() const
	{
		return m_speed;
	}

	const EntityId& entityId() const
	{
		return m_entityId;
	}

	void setRotation(const Rotation rotation)
	{
		m_rotation = rotation;
	}

	void setSpeed(const Speed speed)
	{
		m_speed = speed;
	}

public:
	static constexpr CType COMPONENT_TYPE = CType::COMPONENT_TYPE_VELOCITY;

private:
	const EntityId m_entityId;

	Rotation m_rotation;
	Speed m_speed;
};

} // namespace tbd {
