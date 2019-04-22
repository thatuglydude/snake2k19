#pragma once

#include "Stage.h"

namespace tbd {

class StageMenu : public Stage
{
public:
	explicit StageMenu(EntityManager& entityManager, const TextureDictionary& textureDictionary)
		: Stage{"StageMenu", entityManager, textureDictionary}
	{}

	void handleEvents(const SDL_Event& e) override
	{
		// pass
	}

	void handleCollisions(const std::map<EntityId, std::vector<EntityId>>& collisions) override
	{
		// pass
	}

	void updateSystems(STimer& /*m_systemTimer*/, SPhysics& /*m_systemPhysics*/, SCollider& /*m_systemCollider*/, SRenderer& /*m_systemRenderer*/)
	{
		// pass
	}

private:

};

} // namespace tbd {
