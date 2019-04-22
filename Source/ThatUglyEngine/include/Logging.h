#pragma once

#include "LogItem.h"

#define __FILENAME__ (std::strrchr(__FILE__, '\\') ? std::strrchr(__FILE__, '\\') + 1 : __FILE__)
#define LOG_LOCATION "[" << __FILENAME__ << ":" << __LINE__ << ":" << __func__ << "] "

#define LOG_VER tbd::LogItem{tbd::LogItem::LogLevel::LOG_LEVEL_VERBOSE} << LOG_LOCATION
#define LOG_DBG tbd::LogItem{tbd::LogItem::LogLevel::LOG_LEVEL_DEBUG} << LOG_LOCATION
#define LOG_INF tbd::LogItem{tbd::LogItem::LogLevel::LOG_LEVEL_INFORMATION} << LOG_LOCATION
#define LOG_WRN tbd::LogItem{tbd::LogItem::LogLevel::LOG_LEVEL_WARNING} << LOG_LOCATION
#define LOG_ERR tbd::LogItem{tbd::LogItem::LogLevel::LOG_LEVEL_ERROR} << LOG_LOCATION
#define LOG_FTL tbd::LogItem{tbd::LogItem::LogLevel::LOG_LEVEL_FATAL} << LOG_LOCATION
