#pragma once

#include "SDLRenderer.h"
#include "SDLError.h"
#include <SDL_image.h>
#include "Logging.h"

namespace tbd {

SDLRenderer::~SDLRenderer()
{
	SDL_DestroyRenderer(m_renderer);
}

void SDLRenderer::init(SDL_Window* window)
{
	if (m_renderer)
	{
		throw SDLError("SDL_Renderer already initialized!", "");
	}

	if (m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
	{
		// Initialize renderer color
		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		// Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			throw SDLError{"SDL_image could not initialize! SDL_image Error: ", IMG_GetError()};
		}

		// Set the render colour - this will be used when clearing
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // black
	}
	else
	{
		throw SDLError{"Renderer could not be created! SDL Error: ", SDL_GetError()};
	}
}

SDL_Renderer* SDLRenderer::get() const
{
	return m_renderer;
}

void SDLRenderer::preFrameWork()
{
	// Clear screen
	if (SDL_RenderClear(m_renderer))
	{
		LOG_WRN << "Error while calling: SDL_RenderClear, err: " << SDL_GetError();
	}
}

void SDLRenderer::render(const Texture& texture, const SDL_Rect& textureClip, const SDL_Rect& drawRect, const double rotateAngle)
{
	if (SDL_RenderCopyEx(m_renderer, texture, &textureClip, &drawRect, rotateAngle, nullptr, SDL_FLIP_NONE))
	{
		LOG_WRN << "Error while calling: SDL_RenderCopyEx, err: " << SDL_GetError();
	}
}

void SDLRenderer::postFrameWork()
{
	// Update screen
	SDL_RenderPresent(m_renderer);
}

} // namespace tbd {
