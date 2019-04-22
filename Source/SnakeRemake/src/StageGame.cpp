#pragma once

#include "StageGame.h"

#include "STimer.h"

#include "Logging.h"

namespace tbd {

StageGame::StageGame(const int DRAW_SIZE, EntityManager& entityManager, const TextureDictionary& textureDictionary)
	: Stage{"StageGame", entityManager, textureDictionary},	
	TILE_SIZE{8},	// texture entry size
	m_snakeEId{m_entityManager.create<Snake>(m_entityManager, Stage::textureDictionary().getId("resources/texture/snake.p8.png"), TILE_SIZE, DRAW_SIZE)},
	m_foodGeneratorEId{m_entityManager.create<FoodGenerator>(m_entityManager, Stage::textureDictionary().getId("resources/texture/snake.p8.png"), 5, 15, 1, 14, 1, 14)},	// spawn, expiry, minX, maxX, minY, maxY
	m_scoreLabelEId{m_entityManager.create<TextLabel>(m_entityManager, 10, 16 * DRAW_SIZE, Stage::textureDictionary().getId("resources/texture/bitmapfont.png"), "score:0")},
	m_levelLabelEId{m_entityManager.create<TextLabel>(m_entityManager, 8 * DRAW_SIZE, 16 * DRAW_SIZE, Stage::textureDictionary().getId("resources/texture/bitmapfont.png"), "level:0")},
	m_gameOverEid{0}
{
	setupBorders(DRAW_SIZE);
}

void StageGame::setupBorders(const int DRAW_SIZE)
{
	// TODO: add a convenience function to not error in these params
	// The four map borders
	// North
	m_borderEIds.emplace_back(
		m_entityManager.create<Border>(
			"northWall",
			SDL_Rect{0, 0, 16, 1},
			textureDictionary().getId("resources/texture/snake.p8.png"),
			SDL_Rect{0 * TILE_SIZE, 0 * TILE_SIZE, 16 * TILE_SIZE, TILE_SIZE},
			SDL_Rect{0, 0, 16 * DRAW_SIZE, DRAW_SIZE}));

	// South
	m_borderEIds.emplace_back(
		m_entityManager.create<Border>(
			"southWall",
			SDL_Rect{0, 15, 16, 1},
			textureDictionary().getId("resources/texture/snake.p8.png"),
			SDL_Rect{0 * TILE_SIZE, 15 * TILE_SIZE, 16 * TILE_SIZE, TILE_SIZE},
			SDL_Rect{0, 0, 16 * DRAW_SIZE, DRAW_SIZE}));

	// West
	m_borderEIds.emplace_back(
		m_entityManager.create<Border>(
			"westWall",
			SDL_Rect{0, 1, 1, 14},
			textureDictionary().getId("resources/texture/snake.p8.png"),
			SDL_Rect{0 * TILE_SIZE, 1 * TILE_SIZE, 1 * TILE_SIZE, 14 * TILE_SIZE},
			SDL_Rect{0, 1, 1 * DRAW_SIZE, 14 * DRAW_SIZE}));

	// East
	m_borderEIds.emplace_back(
		m_entityManager.create<Border>(
			"eastWall",
			SDL_Rect{15, 1, 1, 14},
			textureDictionary().getId("resources/texture/snake.p8.png"),
			SDL_Rect{15 * TILE_SIZE, 1 * TILE_SIZE, 1 * TILE_SIZE, 14 * TILE_SIZE},
			SDL_Rect{0, 0, 1 * DRAW_SIZE, 14 * DRAW_SIZE}));

	std::copy(m_borderEIds.begin(), m_borderEIds.end(), std::back_inserter(getEntityList()));
}

void StageGame::handleEvents(const SDL_Event& e)
{
	//reapExpired();
	auto& snake = dynamic_cast<Snake&>(m_entityManager.get(m_snakeEId)); // TODO: should check if succeeded?

	// User presses a key
	if (e.type == SDL_KEYDOWN)
	{
		// Select surfaces based on key press
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			snake.tryTurn(Rotation::ROTATION_NORTH);
			break;
		case SDLK_d:
			snake.tryTurn(Rotation::ROTATION_EAST);
			break;
		case SDLK_s:
			snake.tryTurn(Rotation::ROTATION_SOUTH);
			break;
		case SDLK_a:
			snake.tryTurn(Rotation::ROTATION_WEST);
			break;
		case SDLK_x:
			snake.addSegement();
			break;
		case SDLK_u:
			m_gameScore.increaseDifficulty();
			break;
		case SDLK_RETURN:
			if (m_gameOverEid)
			{

			}
			break;
		}
	}
}

void StageGame::handleCollisions(const std::map<EntityId, std::vector<EntityId>>& collisions)
{
	auto& snake = dynamic_cast<Snake&>(m_entityManager.get(m_snakeEId)); // TODO: should check if succeeded?

	const auto headCollions = collisions.find(snake.headId());

	if (headCollions != collisions.end())
	{
		for (const auto& borderEId : m_borderEIds)
		{
			if (std::find(std::begin(headCollions->second), std::end(headCollions->second), borderEId)
				!= std::end(headCollions->second))
			{
				m_done = true;
				break;
			}
		}

		if (!m_done)
		{
			const auto tailIds = snake.tailIds();
			for (const auto& tailId : tailIds)
			{
				if (std::find(std::begin(headCollions->second), std::end(headCollions->second), tailId)
					!= std::end(headCollions->second))
				{
					m_done = true;
					break;
				}
			}
		}

		if (!m_done)
		{
			for (const auto& foodEId : headCollions->second)
			{
				m_entityManager.remove(foodEId);
				dynamic_cast<FoodGenerator&>(m_entityManager.get(m_foodGeneratorEId)).remove(foodEId);

				snake.addSegement();
				m_gameScore.increaseScore(m_gameScore.currentLevel());

				if (snake.length() % 3 == 0)
				{
					m_gameScore.increaseDifficulty();
				}
			}

			std::stringstream scoreStream;
			scoreStream << "score:" << m_gameScore.score();	// TODO: split into to vars - one for the text, one for the numeric value
			auto& scoreLabel = dynamic_cast<TextLabel&>(m_entityManager.get(m_scoreLabelEId)); // TODO: should check if succeeded?
			scoreLabel.setText(scoreStream.str());

			std::stringstream levelStream;
			levelStream << "level:" << m_gameScore.currentLevel();
			auto& levelLabel = dynamic_cast<TextLabel&>(m_entityManager.get(m_levelLabelEId));
			levelLabel.setText(levelStream.str());
		}
	}

	if (m_done)
	{
		m_gameOverEid = m_entityManager.create<GameOver>(
			textureDictionary().getId("resources/texture/game_over.png"),
			SDL_Rect{0, 0, 192, 64},
			SDL_Rect{100, 100, 192, 64});
	}
}

void StageGame::updateSystems(STimer& m_systemTimer, SPhysics& /*m_systemPhysics*/, SCollider& /*m_systemCollider*/, SRenderer& /*m_systemRenderer*/)
{
	m_systemTimer.setUpdateInterval(m_gameScore.getCurrentInterval());
}

} // namespace tbd {
