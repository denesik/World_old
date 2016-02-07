// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Bresenham3D_h__
#define Bresenham3D_h__

#include <glm/glm.hpp>
#include <vector>

std::vector<glm::ivec3> Bresenham3D(const glm::ivec3 &begin, const glm::ivec3 &end);

#endif // Bresenham3D_h__
