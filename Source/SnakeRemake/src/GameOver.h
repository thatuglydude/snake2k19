#pragma once

#include "Entity.h"
#include "CDrawable.h"

namespace tbd {

class GameOver : public Entity
{
public:
	explicit GameOver(const EntityId& entityId, const TextureId& textureId, const SDL_Rect& textureClip, const SDL_Rect& drawRect)
		: Entity{entityId, "gameOver", CType::COMPONENT_TYPE_DRAWABLE},
		m_cDrawable{m_entityId, textureId, textureClip, drawRect}
	{}

private:
	CDrawable m_cDrawable;
};

} // namespace tbd {
