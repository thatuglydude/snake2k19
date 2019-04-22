#pragma once

#include "EntityId.h"
#include <cstdint>
#include <map>
#include <sstream>

namespace tbd {

// TODO: decouple from containers? could be abstract - seems to make more sense
template<class T>
class CContainer
{
public:
	void insert(const EntityId& entityId, T* const component)	// TODO: memory unsafe, how do make self-registering in CTOR-s viable?
	{
		const auto insertResult = m_data.insert({entityId, component});
		if (!insertResult.second)
		{
			std::stringstream errStream;
			errStream << "Element with ID already exists in the map: " << entityId;
			throw std::runtime_error{errStream.str()};
		}
	}

	void remove(const EntityId& entityId)
	{
		auto componentIter = m_data.find(entityId);
		if (componentIter == std::end(m_data))
		{
			std::stringstream errStream;
			errStream << "Requested component to be removed could not be found: " << entityId;
			throw std::runtime_error{errStream.str()};
		}

		m_data.erase(componentIter);
	}

	T* tryFind(const EntityId& entityId)
	{
		auto componentIter = m_data.find(entityId);
		if (componentIter != std::end(m_data))
		{
			return componentIter->second;
		}

		return nullptr;
	}

	const T* tryFindConst(const EntityId entityId) const
	{
		auto componentIter = m_data.find(entityId);
		if (componentIter != std::end(m_data))
		{
			return componentIter->second;
		}

		return nullptr;
	}

	const std::map<EntityId, T* const>& data() const
	{
		return m_data;
	}


	std::map<EntityId, T* const>& dataRaw()
	{
		return m_data;
	}

private:
	std::map<EntityId, T* const> m_data;	// TODO: access to this map has to be protected from all threads!
};

} // namespace tbd {
