// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef CoordsConvert_h__
#define CoordsConvert_h__

#include <glm/glm.hpp>

glm::ivec3 CoordWorldToSector(const glm::vec3 &pos);

glm::ivec3 CoordWorldToBlock(const glm::vec3 &pos);

#endif // CoordsConvert_h__