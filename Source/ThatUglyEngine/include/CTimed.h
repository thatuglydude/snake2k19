#pragma once

#include "CType.h"
#include <functional>

#include "CContainer.h"
#include "Singleton.h"
#include "EntityId.h"

namespace tbd {

class CTimed
{
public:
	explicit CTimed(const EntityId& entityId, std::function<void()> callback)
		: m_entityId{entityId}, m_callback{callback}
	{
		Singleton<CContainer<CTimed>>::instance().insert(m_entityId, this);
	}

	~CTimed()
	{
		Singleton<CContainer<CTimed>>::instance().remove(m_entityId);
	}

	const std::function<void()>& callback() const
	{
		return m_callback;
	}

	const EntityId& entityId() const
	{
		return m_entityId;
	}

public:
	static constexpr CType COMPONENT_TYPE = CType::COMPONENT_TYPE_TIMED;

private:
	const EntityId m_entityId;
	std::function<void()> m_callback;
};

} // namespace tbd {
