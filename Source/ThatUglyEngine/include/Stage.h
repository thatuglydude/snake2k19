#pragma once

#include "Texture.h"
#include "TextureId.h"
#include "Entity.h"
#include <string>
#include <vector>
#include <map>
#include "EntityId.h"

#include "EntityManager.h"
#include "TextureDictionary.h"

namespace tbd {

using TextureList = std::vector<std::string>;
using EntityList = std::vector<EntityId>;

class STimer;
class SPhysics ;
class SCollider;
class SRenderer;

class Stage
{
public:
	explicit Stage(const std::string& name, EntityManager& entityManager, const TextureDictionary& textureDictionary)
		: m_name{name}, m_entityManager{entityManager}, m_textureDictionary{textureDictionary}
	{}

	const EntityList& entityList() const
	{
		return m_entityList;
	}

	bool isDone() const
	{
		return m_done;
	}

	virtual void handleEvents(const SDL_Event& e) = 0;
	virtual void handleCollisions(const std::map<EntityId, std::vector<EntityId>>& collisions) = 0;
	virtual void updateSystems(STimer& m_systemTimer, SPhysics& m_systemPhysics, SCollider& m_systemCollider, SRenderer& m_systemRenderer) = 0;

	const TextureDictionary& textureDictionary() const
	{
		return m_textureDictionary;
	}

protected:
	EntityList& getEntityList()
	{
		return m_entityList;
	}


protected:
	bool m_done = false;

	EntityManager& m_entityManager;
	const TextureDictionary& m_textureDictionary; // TODO: avoid protected?

private:
	const std::string m_name;
	EntityList m_entityList;
};

} // namespace tbd {
