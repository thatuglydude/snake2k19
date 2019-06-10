#pragma once

#include "Entity.h"

#include "CRigidBody.h"
#include "CDrawable.h"
#include "CVelocity.h"

namespace tbd {

class SnakeSegment : public Entity
{
public:
	explicit SnakeSegment(const EntityId& entityId, const SDL_Rect& areaRect, const TextureId& textureId, const SDL_Rect& textureClip, const SDL_Rect& drawRect, const Speed initialSpeed)
		: Entity{entityId, "snakeSegment", CType::COMPONENT_TYPE_RIGID_BODY | CType::COMPONENT_TYPE_DRAWABLE | CType::COMPONENT_TYPE_VELOCITY},
		m_cRigidBody{m_entityId, areaRect, Rotation::ROTATION_EAST},
		m_cDrawable{m_entityId, textureId, textureClip, drawRect},
		m_cVelocity{m_entityId, Rotation::ROTATION_EAST, initialSpeed}
	{}

	void setRotation(const Rotation rotation)
	{
		m_cVelocity.setRotation(rotation);
		m_cRigidBody.setRotation(rotation);
	}

	const Rotation rotation() const
	{
		return m_cRigidBody.rotation();
	}

	std::pair<int, int> getPosition() const
	{
		return {m_cRigidBody.x(), m_cRigidBody.y()};
	}

	void setSpeed(const int speed)
	{
		m_cVelocity.setSpeed(speed);
	}

private:
	CRigidBody m_cRigidBody;
	CDrawable m_cDrawable;
	CVelocity m_cVelocity;
};

} // namespace tbd {
