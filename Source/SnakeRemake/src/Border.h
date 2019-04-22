#pragma once

#include "Entity.h"

#include "CRigidBody.h"
#include "CDrawable.h"

namespace tbd {

class Border : public Entity
{
public:
	explicit Border(const EntityId& entityId, const std::string& name, const SDL_Rect& areaRect, const TextureId& textureId, const SDL_Rect& textureClip, const SDL_Rect& drawRect)
		: Entity{entityId, name, CType::COMPONENT_TYPE_RIGID_BODY | CType::COMPONENT_TYPE_DRAWABLE},
		m_cRigidBody{m_entityId, areaRect},
		m_cDrawable{m_entityId, textureId, textureClip, drawRect}
	{}

private:
	CRigidBody m_cRigidBody;
	CDrawable m_cDrawable;
};

} // namespace tbd {
