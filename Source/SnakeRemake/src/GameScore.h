#pragma once

#include <chrono>
#include <cstdint>

namespace tbd {

class GameScore
{
public:
	void increaseDifficulty()
	{
		m_currentLevel++;
	}

	std::chrono::milliseconds getCurrentInterval() const
	{
		return std::chrono::milliseconds{static_cast<uint32_t>(BASE_INTERVAL.count() * std::pow(INTERVAL_MULTIPLIER, m_currentLevel - 1))};
	}

	void increaseScore(const uint32_t score)
	{
		m_score += score;
	}

	const uint32_t currentLevel() const
	{
		return m_currentLevel;
	}

	const uint32_t score() const
	{
		return m_score;
	}

private:
	const std::chrono::milliseconds BASE_INTERVAL = std::chrono::milliseconds{500};
	const double INTERVAL_MULTIPLIER = 0.9;

	uint32_t m_currentLevel = 1;
	uint32_t m_score = 0;
};

} // namespace tbd {
