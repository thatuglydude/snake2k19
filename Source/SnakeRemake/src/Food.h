#pragma once

#include "Entity.h"

#include "CRigidBody.h"
#include "CDrawable.h"
#include "CTimed.h"

#include <vector>

namespace tbd {

class Food : public Entity
{
public:
	// TODO: clearly too many args, refactor
	explicit Food(
		const EntityId& entityId,
		const SDL_Rect& areaRect,
		const TextureId& textureId,
		const std::vector<SDL_Rect> textureClipVector,
		const SDL_Rect& drawRect, 
		const uint32_t expiryDuration)
		: Entity{entityId, "food", CType::COMPONENT_TYPE_RIGID_BODY | CType::COMPONENT_TYPE_DRAWABLE | CType::COMPONENT_TYPE_TIMED},
		m_cRigidBody{m_entityId, areaRect},
		m_cDrawable{m_entityId, textureId, textureClipVector.front(), drawRect},
		m_cTimed{m_entityId, [this]() { tick(); }},
		m_textureClipVector{textureClipVector},
		m_currentPhase{0},
		m_expiryDuration{expiryDuration},
		m_untilExpiration{expiryDuration}
	{}

	void tick()
	{
		if (m_expired) 
		{ 
			return; // expired, skip
		}

		if (--m_untilExpiration == 0)
		{
			if (++m_currentPhase == m_textureClipVector.size())	// reached last phase, expire!
			{
				m_expired = true;
			}
			else
			{
				m_untilExpiration = m_expiryDuration;	// reset the timer, next phase
				m_cDrawable.setTextureClip(m_textureClipVector[m_currentPhase]);
			}
		}
	}

private:
	CRigidBody m_cRigidBody;
	CDrawable m_cDrawable;
	CTimed m_cTimed;

	const std::vector<SDL_Rect> m_textureClipVector;
	size_t m_currentPhase;

	const uint32_t m_expiryDuration;
	uint32_t m_untilExpiration;
};

} // namespace tbd {
