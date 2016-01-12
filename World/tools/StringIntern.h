// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef StringIntern_h__
#define StringIntern_h__

#include <string>
//#include <boost/flyweight.hpp>

using StringIntern = std::string;
//using StringIntern = boost::flyweight<std::string>;
// 
// StringIntern operator+(const StringIntern &a, const StringIntern &b);

#endif // StringIntern_h__