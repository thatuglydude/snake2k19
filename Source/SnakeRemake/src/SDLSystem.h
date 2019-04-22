#pragma once

// Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

// Engine
#include "Texture.h"
#include "TextureDictionary.h"

// Game specifics
#include "Stage.h"

// Utils
#include "Logging.h"
#include "Singleton.h"


// ECS: Subsystems
#include "STimer.h"
#include "SPhysics.h"
#include "SCollider.h"
#include "SRenderer.h"

// ECS: Compo containers
#include "CRigidBody.h"
#include "CDrawable.h"
#include "CTimed.h"
#include "CVelocity.h"

#include "CContainer.h"

// Simple SDL2 wrapper
#include "SDLRenderer.h"
#include "SDLWindow.h"

#include "EntityManager.h"

namespace tbd {

class SDLSystem
{
public:
	explicit SDLSystem(const int screenWidth, const int screenHeight, const int drawTileSize);

	virtual ~SDLSystem();

	void init();
	void spin();

	template<class StageT>
	void setStage()
	{
		loadTextures(StageT::textureList());
		m_currentStage = std::make_shared<tbd::StageGame>(m_drawTileSize, m_entityManager, m_textureDictionary);
	}

	const TextureDictionary& textureDictionary() const
	{
		return m_textureDictionary;	// TODO: split the guy in two? unlikely stages need the 'load' interface
	}

private:
	// javadoc: TODO: does not throw directly, but may throw if the TextureLoader fails
	void loadTextures(const std::vector<std::string>& textureList);

private:
	const int m_drawTileSize;

	// The rendering window
	SDLWindow m_window;

	// The window renderer
	SDLRenderer m_renderer;

	// Container of the loaded textures
	TextureDictionary m_textureDictionary;

	// Stage to be displayed, handle events, etc.
	std::shared_ptr<Stage> m_currentStage; // TODO: REWORK

	// TODO: try to relax the singleton dependency -> make do without, how viable?
	// ECS: Subsystems
	STimer m_systemTimer;
	SPhysics m_systemPhysics;
	SCollider m_systemCollider;
	SRenderer m_systemRenderer;

	// ECS: Component containers
	Singleton<CContainer<CRigidBody>> m_ccRigidBody;
	Singleton<CContainer<CDrawable>> m_ccDrawable;
	Singleton<CContainer<CTimed>> m_ccTimed;
	Singleton<CContainer<CVelocity>> m_ccVelocity;

	EntityManager m_entityManager;
};

} // namespace tbd {
