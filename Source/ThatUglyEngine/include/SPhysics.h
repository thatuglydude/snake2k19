#pragma once

#include <algorithm>
#include "CContainer.h"
#include "CVelocity.h"
#include "CRigidBody.h"

#include "Logging.h"

namespace tbd {

class SPhysics
{
public:
	SPhysics(const CContainer<CVelocity>& velocities, CContainer<CRigidBody>& rigidBodies)
		: m_velocities{velocities}, m_rigidBodies{rigidBodies}
	{}

	void run()
	{
		for (const auto& el : m_velocities.data())
		{
			if (auto* rigidBody = m_rigidBodies.tryFind(el.second->entityId()))
			{
				switch (el.second->rotation())
				{
				case Rotation::ROTATION_NORTH:
					rigidBody->setPosition(rigidBody->x(), rigidBody->y() - el.second->speed());
					break;
				case Rotation::ROTATION_EAST:
					rigidBody->setPosition(rigidBody->x() + el.second->speed(), rigidBody->y());
					break;
				case Rotation::ROTATION_SOUTH:
					rigidBody->setPosition(rigidBody->x(), rigidBody->y() + el.second->speed());
					break;
				case Rotation::ROTATION_WEST:
					rigidBody->setPosition(rigidBody->x() - el.second->speed(), rigidBody->y());
					break;
				default:
					throw std::runtime_error{"Invalid rotation specified"};
				}
			}
			else
			{
				LOG_WRN << "Could not find the corresponding RigidBody for Velocity with EntityId: " << el.second->entityId();
			}
		}
	}

private:
	const CContainer<CVelocity>& m_velocities;
	CContainer<CRigidBody>& m_rigidBodies;
};

} // namespace tbd {
