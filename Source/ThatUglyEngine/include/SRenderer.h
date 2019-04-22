#pragma once

#include "CDrawable.h"
#include "CRigidBody.h"
#include "CContainer.h"
#include "SDLRenderer.h"
#include "TextureDictionary.h"

namespace tbd {

class SRenderer
{
public:
	// TODO: CRigidBody is too inclusive: not everything will collide, but will move on the screen
	SRenderer(
		SDLRenderer& renderer, 
		const CContainer<CDrawable>& drawables, 
		const CContainer<CRigidBody>& rigidBodies, 
		const TextureDictionary& textureDictionary,
		const int drawTileSize)
		: m_renderer{renderer}, 
		m_drawables{drawables}, 
		m_rigidBodies{rigidBodies}, 
		m_textureDictionary{textureDictionary}, 
		m_drawTileSize{drawTileSize}
	{}

	virtual ~SRenderer() = default;

	void run()
	{
		m_renderer.preFrameWork();

		for (auto it = m_drawables.data().rbegin(); it != m_drawables.data().rend(); ++it)
		{

			if (const auto* rigidBody = m_rigidBodies.tryFindConst(it->second->entityId()))
			{
				const auto& drawable = it->second;
				const auto& texture = m_textureDictionary.getTexture(drawable->textureId());
				auto drawRect = rigidBody->rect();
				drawRect.x = rigidBody->x() * m_drawTileSize;
				drawRect.y = rigidBody->y() * m_drawTileSize;
				drawRect.w = rigidBody->w() * m_drawTileSize;
				drawRect.h = rigidBody->h() * m_drawTileSize;

				m_renderer.render(texture, drawable->textureClip(), drawRect, static_cast<int>(rigidBody->rotation()) * 90.0);
			}
			else
			{
				const auto& drawable = it->second;
				const auto& texture = m_textureDictionary.getTexture(drawable->textureId());
				m_renderer.render(texture, drawable->textureClip(), drawable->drawRect(), 0.0);
			}
		}

		m_renderer.postFrameWork();
	}

private:
	SDLRenderer& m_renderer;
	const CContainer<CDrawable>& m_drawables;
	const CContainer<CRigidBody>& m_rigidBodies;
	const TextureDictionary& m_textureDictionary;

	const int m_drawTileSize;
};

} // namespace tbd {
