#pragma once

#include "Food.h"
#include "Singleton.h"
#include "SCollider.h"
#include "CTimed.h"
#include "EntityManager.h"
#include <random>
#include <vector>

namespace tbd {

class FoodGenerator : public Entity
{
public:
	enum FoodType
	{
		FOOD_TYPE_APPLE = 0x00,
		FOOD_TYPE_CHERRY = 0x01,
	};

	// TODO: clearly too many params, and more would come
	FoodGenerator(
		const EntityId& entityId,
		EntityManager& entityManager,
		const TextureId foodTexture,
		const int spawnInterval,
		const int expiryDuration, 
		int spawnMinX,
		int spawnMaxX,
		int spawnMinY,
		int spawnMaxY)
		:	Entity{entityId, "foodGenerator", CType::COMPONENT_TYPE_TIMED},
			m_entityManager{entityManager},
			m_cTimed{m_entityId, [this]() { generate(); }},
			m_foodTexture{foodTexture},
			m_spawnInterval{spawnInterval},
			m_untilSpawn{3},
			m_expiryDuration{expiryDuration},
			m_generator{std::random_device{}()},
			m_distrType{FOOD_TYPE_APPLE, FOOD_TYPE_CHERRY},
			m_distrPosX{spawnMinX, spawnMaxX},
			m_distrPosY{spawnMinY, spawnMaxY}
	{}

	void generate()
	{
		if (--m_untilSpawn)
		{
			return; // waiting
		}
		m_untilSpawn = m_spawnInterval;

		LOG_DBG << "Generating food";

		std::pair<int, int> spawnLocation{m_distrPosX(m_generator), m_distrPosY(m_generator)};
		// TODO: enable foodGenerator to check for valid location prior to spawn!
		//while (Singleton<SCollider>::instance().isColliding(spawnLocation))
		//{
		//	spawnLocation = std::pair<int, int>{m_distrPosX(m_generator), m_distrPosY(m_generator)};
		//}
		
		switch (m_distrType(m_generator))
		{
		case FOOD_TYPE_APPLE:
			m_foodEIds.emplace_back(m_entityManager.create<Food>(
				SDL_Rect{spawnLocation.first, spawnLocation.second, 1, 1},
				m_foodTexture,
				std::vector<SDL_Rect>{ {6 * 8, 4 * 8, 8, 8}, {7 * 8, 4 * 8, 8, 8}, {8 * 8, 4 * 8, 8, 8} },
				SDL_Rect{0, 0, 24, 24},	// TODO: this class depends on StageGame internals too much				
				m_expiryDuration)); // TODO: strongly typed position
			break;
		case FOOD_TYPE_CHERRY:
			m_foodEIds.emplace_back(m_entityManager.create<Food>(
				SDL_Rect{spawnLocation.first, spawnLocation.second, 1, 1},
				m_foodTexture,
				std::vector<SDL_Rect>{ {10 * 8, 13 * 8, 8, 8}, {11 * 8, 13 * 8, 8, 8}, {12 * 8, 13 * 8, 8, 8} },
				SDL_Rect{0, 0, 24, 24},	// TODO: this class depends on StageGame internals too much
				m_expiryDuration)); // TODO: strongly typed position
			break;
		default: 
			throw std::runtime_error{"Unexpected food type requested!"};
		}

		LOG_DBG << "Created food id: " << m_foodEIds.back();
		reapExpired();
	}

	void remove(const EntityId& id)
	{
		m_foodEIds.erase(std::remove(m_foodEIds.begin(), m_foodEIds.end(), id), m_foodEIds.end());
	}

private:
	void reapExpired()
	{
		for (auto foodIter = m_foodEIds.begin(); foodIter != m_foodEIds.end(); ++foodIter)
		{
			auto& food = dynamic_cast<Food&>(m_entityManager.get(*foodIter));
			if (food.expired())
			{
				m_entityManager.remove(*foodIter);
				foodIter = m_foodEIds.erase(foodIter);
			}
		}
	}

private:
	EntityManager& m_entityManager;
	CTimed m_cTimed;

	TextureId m_foodTexture;

	const int m_spawnInterval;
	int m_untilSpawn;
	const int m_expiryDuration;

	std::mt19937 m_generator;
	std::uniform_int_distribution<> m_distrType;
	std::uniform_int_distribution<> m_distrPosX;
	std::uniform_int_distribution<> m_distrPosY;

	std::vector<EntityId> m_foodEIds;
};

} // namespace tbd {
