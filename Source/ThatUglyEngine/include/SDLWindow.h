#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "ThatUglyEngine.h"

namespace tbd {

class DLLEXPORT SDLWindow
{
public:
	explicit SDLWindow(const int screenWidth, const int screenHeight);
	virtual ~SDLWindow();

	void init();

	SDL_Window* get() const;

private:
	// Screen dimension constants
	const int m_screenWidth;
	const int m_screenHeight;

	// TODO: should be unusable without a setup window, but don't introduce checking on every call!
	SDL_Window* m_window = nullptr;
};

} // namespace tbd {
