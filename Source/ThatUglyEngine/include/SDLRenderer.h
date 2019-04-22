#pragma once

#include "Texture.h"
#include <SDL_render.h>
#include "ThatUglyEngine.h"

namespace tbd {

class DLLEXPORT SDLRenderer
{
public:
	virtual ~SDLRenderer();

	void init(SDL_Window* window);

	SDL_Renderer* get() const;

	void preFrameWork();
	void render(const Texture& texture, const SDL_Rect& textureClip, const SDL_Rect& drawRect, const double rotateAngle);
	void postFrameWork();

private:
	SDL_Renderer* m_renderer = nullptr;	// TODO: should be unusable without a setup renderer, but don't introduce checking on every call!
};

} // namespace tbd {
