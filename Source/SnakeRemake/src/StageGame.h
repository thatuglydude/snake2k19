#pragma once

#include "Stage.h"

#include "GameScore.h"

#include "Snake.h"
#include "FoodGenerator.h"
#include "Border.h"
#include "Food.h"
#include "GameOver.h"

#include "TextLabel.h"
#include "EntityId.h"

namespace tbd {

class StageGame : public Stage
{
public:
	// TODO: solves the problem - textureDictionary.load("path"), StageGame::ctor(), init_list:Snake{preloaded textureId}
	static std::vector<std::string> textureList()
	{
		return {
			"resources/texture/snake.p8.png",		// 128x128
			"resources/texture/game_over.png",		// 192x64
			"resources/texture/bitmapfont.png"};	// 500x220, each letter 20x20	// TODO: solve the hard-coded paths problem, albeit locally it isn't *that* bad
	}

	// TODO: kinda ugly, this may be parametrized - influences the basic visible tile size
	explicit StageGame(const int DRAW_SIZE, EntityManager& entityManager, const TextureDictionary& textureDictionary);

	void handleEvents(const SDL_Event& e) override;
	void handleCollisions(const std::map<EntityId, std::vector<EntityId>>& collisions) override;
	void updateSystems(STimer& m_systemTimer, SPhysics& m_systemPhysics, SCollider& m_systemCollider, SRenderer& m_systemRenderer) override;

private:
	void setupBorders(const int DRAW_SIZE);

private:
	const int TILE_SIZE;

	EntityId m_snakeEId;
	EntityId m_foodGeneratorEId;
	std::vector<EntityId> m_borderEIds;

	EntityId m_scoreLabelEId;
	EntityId m_levelLabelEId;
	GameScore m_gameScore;

	EntityId m_gameOverEid;
};

} // namespace tbd {
