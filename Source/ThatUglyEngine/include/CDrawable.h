#pragma once

#include "Texture.h"
#include "TextureId.h"
#include "CType.h"
#include <SDL.h>

#include "CContainer.h"
#include "Singleton.h"
#include "EntityId.h"

namespace tbd {

class CDrawable
{
public:
	explicit CDrawable(const EntityId& entityId, const TextureId& textureId, const SDL_Rect& textureClip, const SDL_Rect& drawRect)
		:  m_entityId{entityId}, m_textureId{textureId}, m_textureClip{textureClip}, m_drawRect{drawRect}
	{
		Singleton<CContainer<CDrawable>>::instance().insert(m_entityId, this);
	}

	~CDrawable()
	{
		Singleton<CContainer<CDrawable>>::instance().remove(m_entityId);
	}

	const TextureId& textureId() const
	{
		return m_textureId;
	}

	void setTextureClip(const SDL_Rect& textureClip)
	{
		m_textureClip = textureClip;
	}
	
	const SDL_Rect& textureClip() const
	{
		return m_textureClip;
	}

	const SDL_Rect& drawRect() const
	{
		return m_drawRect;
	}

	const EntityId& entityId() const
	{
		return m_entityId;
	}

public:
	static constexpr CType COMPONENT_TYPE = CType::COMPONENT_TYPE_DRAWABLE;

private:
	const EntityId m_entityId;

	const TextureId m_textureId;
	SDL_Rect m_textureClip;
	const SDL_Rect m_drawRect;
};

} // namespace tbd {
