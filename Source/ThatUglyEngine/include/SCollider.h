#pragma once

#include "CContainer.h"
#include "CRigidBody.h"
#include <algorithm>
#include <map>
#include <vector>

namespace tbd {

class SCollider
{
public:
	SCollider(const CContainer<CRigidBody>& rigidBodies)
		: m_rigidBodies{rigidBodies}
	{}

	// TODO: this naive implementation will only get us so far, n^2 is way too much
	// TODO: how to report and process collision effectively?
	std::map<EntityId, std::vector<EntityId>> run()
	{
		std::map<EntityId, std::vector<EntityId>> collisions;

		const auto& bodies = m_rigidBodies.data();
		for (auto lhsIter = bodies.begin(); lhsIter != bodies.end(); ++lhsIter)
		{
			for (auto rhsIter = std::next(lhsIter, 1); rhsIter != bodies.end(); ++rhsIter)
			{
				if (SDL_HasIntersection(&lhsIter->second->rect(), &rhsIter->second->rect()))
				{
					//LOG_DBG << "Found an intersection of two elements: "
					//	<< logRect(lhsIter->second->rect()) << " " << Singleton<CContainer<Entity>>::instance().tryFind(lhsIter->second->entityId())->name() << " [" << lhsIter->second->entityId() << "], "
					//	<< logRect(rhsIter->second->rect()) << " " << Singleton<CContainer<Entity>>::instance().tryFind(rhsIter->second->entityId())->name() << " [" << rhsIter->second->entityId() << "]";
					LOG_DBG << "COLLISION: Found an intersection of two elements: "
						<< "\n\t" << logRect(lhsIter->second->rect()) << " [" << lhsIter->second->entityId() << "]"
						<< "\n\t" << logRect(rhsIter->second->rect()) << " [" << rhsIter->second->entityId() << "]";

					collisions[lhsIter->second->entityId()].push_back(rhsIter->second->entityId());
				}
			}
		}

		return collisions;
	}

	bool isColliding(const std::pair<int, int>& location) const
	{
		return false;
	}

private:

	// TODO: temporary for easier debugging
	std::string logRect(const SDL_Rect& msg)
	{
		std::stringstream sstream;
		sstream << "SDL_Rect(" << msg.x << "," << msg.y << "," << msg.w << "," << msg.h << ")";
		return sstream.str();
	}


private:
	const CContainer<CRigidBody>& m_rigidBodies;
};

} // namespace tbd {
