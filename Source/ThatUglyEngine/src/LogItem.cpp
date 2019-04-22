#pragma once

#include "LogItem.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

namespace tbd
{

LogItem::LogItem(const LogLevel logLevel)
	: m_logLevel{logLevel}
{
	addTimeString();
	addLogLevelString();
}

LogItem::~LogItem()
{

	std::cout << m_buffer.str() << std::endl;	// newline and flush
}

void LogItem::addTimeString()
{
	const auto now = std::chrono::system_clock::now();
	const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	const auto timer = std::chrono::system_clock::to_time_t(now);

	m_buffer << "[" << std::put_time(std::localtime(&timer), "%Y-%m-%dT%H:%M:%S") << "." << std::setfill('0') << std::setw(3) << ms.count() << "] ";
}

void LogItem::addLogLevelString() 
{
	switch (m_logLevel)
	{
	case LogLevel::LOG_LEVEL_VERBOSE:
		m_buffer << "[VER] ";
		return;
	case LogLevel::LOG_LEVEL_DEBUG:
		m_buffer << "[DBG] ";
		return;
	case LogLevel::LOG_LEVEL_INFORMATION:
		m_buffer << "[INF] ";
		return;
	case LogLevel::LOG_LEVEL_WARNING:
		m_buffer << "[WRN] ";
		return;
	case LogLevel::LOG_LEVEL_ERROR:
		m_buffer << "[ERR] ";
		return;
	case LogLevel::LOG_LEVEL_FATAL:
		m_buffer << "[FTL] ";
		return;
	}

	throw std::runtime_error{"Unsupported LogLevel requested"};
}

} // namespace tbd {
