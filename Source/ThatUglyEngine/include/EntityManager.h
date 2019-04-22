#pragma once

#include "EntityId.h"
#include "EntityIdProvider.h"
#include <map>
#include <stdexcept>
#include <memory>
#include <sstream>

namespace tbd {

class Entity;

class EntityManager
{
public:
	EntityManager() = default;

	template<class EntityT, class... Args>
	EntityId create(Args&&... args)
	{
		const auto entityId = m_entityIdProvider.nextId();
		m_entities.insert(std::make_pair(entityId, std::make_unique<EntityT>(entityId, std::forward<Args>(args)...)));
		return entityId;
	}

	Entity& get(const EntityId& entityId) const
	{
		const auto eIter = m_entities.find(entityId);
		if (eIter == m_entities.end())
		{
			std::stringstream errStream;
			errStream << "get() failed: could not find requested entity with ID: " << entityId;
			throw std::runtime_error{errStream.str()};	// TODO: use CRTP exception logging stream
		}

		return *(eIter->second);	// TODO: assume entity cannot be null
	}

	void remove(const EntityId& entityId)
	{
		const auto eIter = m_entities.find(entityId);
		if (eIter != m_entities.end())
		{
			m_entities.erase(eIter);
			return;
		}

		std::stringstream errStream;
		errStream << "remove() failed: could not find requested entity with ID: " << entityId;
		throw std::runtime_error{errStream.str()};	// TODO: use CRTP exception logging stream
	}

	EntityManager(const EntityManager& rhs) = delete;
	EntityManager& operator=(const EntityManager& rhs) = delete;
	EntityManager(EntityManager&& rhs) = delete;
	EntityManager& operator=(EntityManager&& rhs) = delete;

private:
	EntityIdProvider m_entityIdProvider;
	std::map<EntityId, std::unique_ptr<Entity>> m_entities;			// TODO: is smart ptr here that useful?
};

} // namespace tbd {
