// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef WORLD_LOG_H__
#define WORLD_LOG_H__

#include <boost/log/trivial.hpp>

#define LOG(lvl) BOOST_LOG_TRIVIAL(lvl)

void LogInit(bool consoleLogEnabled = true, bool fileLogEnabled = true);

#endif // WORLD_LOG_H__

