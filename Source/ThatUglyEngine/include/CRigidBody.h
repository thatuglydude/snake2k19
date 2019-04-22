#pragma once

#include "CType.h"
#include <SDL_rect.h>
#include "Physics.h"

#include "CContainer.h"
#include "Singleton.h"
#include "EntityId.h"

namespace tbd {

class CRigidBody
{
public:
	explicit CRigidBody(const EntityId& entityId, const SDL_Rect& rect, const Rotation rotation=Rotation::ROTATION_NORTH)
		: m_entityId{entityId}, m_rect{rect}, m_rotation{rotation}
	{
		Singleton<CContainer<CRigidBody>>::instance().insert(m_entityId, this);
	}

	~CRigidBody()
	{
		Singleton<CContainer<CRigidBody>>::instance().remove(m_entityId);
	}

	const int x() const
	{
		return m_rect.x;
	}

	const int y() const
	{
		return m_rect.y;
	}

	const int w() const
	{
		return m_rect.w;
	}

	const int h() const
	{
		return m_rect.h;
	}

	const Rotation& rotation() const
	{
		return m_rotation;
	}

	void setPosition(const int x, const int y)
	{
		m_rect.x = x;
		m_rect.y = y;
	}

	void setRotation(const Rotation rotation)
	{
		m_rotation = rotation;
	}


	const SDL_Rect& rect() const
	{
		return m_rect;
	}

	const EntityId& entityId() const
	{
		return m_entityId;
	}

public:
	static constexpr CType COMPONENT_TYPE = CType::COMPONENT_TYPE_RIGID_BODY;

private:
	const EntityId m_entityId;

	SDL_Rect m_rect;	// TODO: relax the dependency to SDL_Rect!
	Rotation m_rotation;
};

} // namespace tbd {
