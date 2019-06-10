#pragma once

#include "Entity.h"

#include "CTimed.h"
#include "EntityManager.h"

#include "SnakeSegment.h"
#include "Logging.h"

namespace tbd {

class Snake : public Entity
{
public:
	explicit Snake(
		const EntityId& entityId,
		EntityManager& entityManager,
		const TextureId baseTexture,
		const int tileSize,
		const int drawSize)
		: Entity{entityId, "snake", CType::COMPONENT_TYPE_TIMED},
		m_entityManager{entityManager},
		m_baseTexture{baseTexture},
		m_tileSize{tileSize},
		m_drawSize{drawSize},
		m_cTimed{1, [this]() { updateDirections(); }}
	{
		const int SNAKE_STARTING_X = 4;
		const int SNAKE_STARTING_Y = 7;

		m_snakeSegmentEIDs.emplace_back(m_entityManager.create<SnakeSegment>(
			SDL_Rect{SNAKE_STARTING_X, SNAKE_STARTING_Y, 1, 1},
			m_baseTexture,
			SDL_Rect{9 * m_tileSize, 7 * m_tileSize, m_tileSize, m_tileSize},
			SDL_Rect{0, 0, m_drawSize, m_drawSize},
			1));

		addSegement();
		addSegement();
	}

	const EntityId headId() const
	{
		return m_snakeSegmentEIDs.front();
	}

	std::vector<EntityId> tailIds() const
	{
		std::vector<EntityId> tailIds;
		std::copy(m_snakeSegmentEIDs.begin(), m_snakeSegmentEIDs.end(), std::back_inserter(tailIds));
		return tailIds;
	}

	void addSegement()
	{
		const auto headPosition = getTail().getPosition();

		m_snakeSegmentEIDs.emplace_back(m_entityManager.create<SnakeSegment>(
			SDL_Rect{headPosition.first, headPosition.second, 1, 1},
			m_baseTexture,
			SDL_Rect{9 * m_tileSize, 8 * m_tileSize, m_tileSize, m_tileSize},
			SDL_Rect{0, 0, m_drawSize, m_drawSize},
			0)); // segments initially don't move!
	}

	void tryTurn(const Rotation targetRotation)
	{
		auto& headSegment = getHead();
		const auto currentRotation = headSegment.rotation();

		const auto headPosition = getHead().getPosition();
		const auto firstSegmentPosition = getSegment(1).getPosition();

		switch (targetRotation)
		{
		case Rotation::ROTATION_NORTH:
			if ((currentRotation == Rotation::ROTATION_EAST || currentRotation == Rotation::ROTATION_WEST) && headPosition.second != firstSegmentPosition.second + 1)
			{
				headSegment.setRotation(targetRotation);
			}
			break;
		case Rotation::ROTATION_EAST:
			if ((currentRotation == Rotation::ROTATION_NORTH || currentRotation == Rotation::ROTATION_SOUTH) && headPosition.first != firstSegmentPosition.first - 1)
			{
				headSegment.setRotation(targetRotation);
			}
			break;
		case Rotation::ROTATION_SOUTH:
			if ((currentRotation == Rotation::ROTATION_EAST || currentRotation == Rotation::ROTATION_WEST) && headPosition.second != firstSegmentPosition.second - 1)
			{
				headSegment.setRotation(targetRotation);
			}
			break;
		case Rotation::ROTATION_WEST:
			if ((currentRotation == Rotation::ROTATION_NORTH || currentRotation == Rotation::ROTATION_SOUTH) && headPosition.first != firstSegmentPosition.first + 1)
			{
				headSegment.setRotation(targetRotation);
			}
			break;
		default:
			throw std::runtime_error{"Invalid rotation specified"};
		}
	}

	void updateDirections()
	{
		for (size_t i = 1; i < m_snakeSegmentEIDs.size(); ++i)
		{
			auto& tailSegment = getSegment(i);
			const auto tailPosition = tailSegment.getPosition();
			const auto headPosition = getSegment(i-1).getPosition();

			if (tailPosition.first < headPosition.first)
			{
				tailSegment.setRotation(Rotation::ROTATION_EAST);
				tailSegment.setSpeed(1);
			}
			else if (tailPosition.first > headPosition.first)
			{
				tailSegment.setRotation(Rotation::ROTATION_WEST);
				tailSegment.setSpeed(1);
			}
			else if (tailPosition.second > headPosition.second)
			{
				tailSegment.setRotation(Rotation::ROTATION_NORTH);
				tailSegment.setSpeed(1);
			}
			else if (tailPosition.second < headPosition.second)
			{
				tailSegment.setRotation(Rotation::ROTATION_SOUTH);
				tailSegment.setSpeed(1);
			}
		}
	}

	size_t length() const
	{
		return m_snakeSegmentEIDs.size();
	}

private:
	SnakeSegment& getSegment(const size_t index) const
	{
		if (index >= m_snakeSegmentEIDs.size())
		{
			throw std::runtime_error{"Requested SnakeSegment index exceeding the current length!"};
		}

		return dynamic_cast<SnakeSegment&>(m_entityManager.get(m_snakeSegmentEIDs[index]));
	}

	SnakeSegment& getHead() const
	{
		return getSegment(0);
	}

	SnakeSegment& getTail() const
	{
		return getSegment(m_snakeSegmentEIDs.size() - 1);
	}

private:
	EntityManager& m_entityManager;

	const TextureId m_baseTexture;
	const int m_tileSize;
	const int m_drawSize;

	std::vector<EntityId> m_snakeSegmentEIDs;

	CTimed m_cTimed;
};

} // namespace tbd {
