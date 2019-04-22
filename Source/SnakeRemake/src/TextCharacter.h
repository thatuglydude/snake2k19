#pragma once

#include "Entity.h"
#include "CDrawable.h"

namespace tbd {

class TextCharacter : public Entity
{
public:
	explicit TextCharacter(const EntityId& entityId, const TextureId& textureId, const SDL_Rect& textureClip, const SDL_Rect& drawRect)
		: Entity{entityId, CType::COMPONENT_TYPE_DRAWABLE},
		m_cDrawable{m_entityId, textureId, textureClip, drawRect}
	{}

private:
	CDrawable m_cDrawable;
};

} // namespace tbd {
