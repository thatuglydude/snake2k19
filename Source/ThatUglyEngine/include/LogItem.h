#pragma once

#include <cstdint>
#include <string>
#include <sstream>

#include "ThatUglyEngine.h"

namespace tbd
{

class DLLEXPORT LogItem
{
public:
	enum class LogLevel : uint8_t
	{
		LOG_LEVEL_VERBOSE,
		LOG_LEVEL_DEBUG,
		LOG_LEVEL_INFORMATION,
		LOG_LEVEL_WARNING,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_FATAL,
	};

	explicit LogItem(const LogLevel logLevel);

	virtual ~LogItem();

	template<class T>
	LogItem& operator<<(const T& msg)
	{
		m_buffer << msg;
		return *this;
	}

private:
	void addTimeString();
	void addLogLevelString();

private:
	const LogLevel m_logLevel;
	std::stringstream m_buffer;
};

} // namespace tbd {
