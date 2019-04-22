#pragma once

#include "CTimed.h"
#include "CContainer.h"
#include <cstdint>
#include <chrono>

namespace tbd {

class STimer
{
public:
	explicit STimer(const std::chrono::milliseconds& updateInterval, const CContainer<CTimed>& timeds)
		: m_clock{0}, m_timeds{timeds}, m_lastTick{std::chrono::system_clock::now()}, m_updateInterval{updateInterval}
	{}

	void setUpdateInterval(const std::chrono::milliseconds& updateInterval)
	{
		m_updateInterval = updateInterval;
	}

	bool run()
	{
		const auto now = std::chrono::system_clock::now();
		if (now - m_lastTick > m_updateInterval)
		{
			m_lastTick = now;
			m_clock++;

			for (const auto& el : m_timeds.data())
			{
				auto& timed = el.second;
				(timed->callback())();
			}

			return true; // tick!
		}

		return false;	// interval not yet elapsed
	}

private:
	uint32_t m_clock;
	std::chrono::time_point<std::chrono::system_clock> m_lastTick;
	std::chrono::milliseconds m_updateInterval;

	const CContainer<CTimed>& m_timeds;
};

} // namespace tbd {
