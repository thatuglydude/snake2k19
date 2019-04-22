#pragma once

#include "SDLSystem.h"
#include "SDLError.h"
#include "Logging.h"

// TMP
#include <thread>
#include <chrono>

namespace tbd {

SDLSystem::SDLSystem(const int screenWidth, const int screenHeight, const int drawTileSize)
	:	m_drawTileSize{drawTileSize},
		m_window{screenWidth, screenHeight},
		m_systemTimer{std::chrono::milliseconds(500), m_ccTimed},
		m_systemPhysics{m_ccVelocity, m_ccRigidBody},
		m_systemCollider{m_ccRigidBody},
		m_systemRenderer{m_renderer, m_ccDrawable, m_ccRigidBody, m_textureDictionary, drawTileSize} // TODO: make a var
{}

SDLSystem::~SDLSystem()
{
	LOG_DBG << "Cleaning up...";

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void SDLSystem::init()
{
	LOG_DBG << "Initializing...";

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw SDLError{"SDL could not initialize! SDL Error: ", SDL_GetError()};
	}

	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		LOG_DBG << "Warning: Linear texture filtering not enabled!";
	}

	// Create window
	m_window.init();

	// Create renderer for window
	m_renderer.init(m_window.get());
}

void SDLSystem::loadTextures(const std::vector<std::string>& textureList)
{
	for (const auto& texturePath : textureList)
	{
		m_textureDictionary.load(m_renderer, texturePath);
	}
}

void SDLSystem::SDLSystem::spin()
{
	// Event handler
	SDL_Event e;

	// While application is running
	while (true)
	{
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				return;
			}

			// User presses a key
			else if (e.type == SDL_KEYDOWN)
			{
				// Select surfaces based on key press
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					return;
				}

				// TODO: REWORK STAGES
				// Stage handles the events, TODO: move someplace more specific
				// TODO: split events into various subsystems
				if (m_currentStage && !m_currentStage->isDone())
				{
					m_currentStage->handleEvents(e);
				}
			}
		}

		if (m_currentStage && !m_currentStage->isDone())
		{
			// ECS run subsystems
			if (m_systemTimer.run())
			{
				m_systemPhysics.run();
				const auto collisions = m_systemCollider.run();
				m_currentStage->handleCollisions(collisions);				
			}

			m_currentStage->updateSystems(
				m_systemTimer,
				m_systemPhysics,
				m_systemCollider,
				m_systemRenderer);
		}

		m_systemRenderer.run();
	}
}

} // namespace tbd {
