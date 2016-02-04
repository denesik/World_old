// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef GameObjectParams_h__
#define GameObjectParams_h__

#include <glm/glm.hpp>

struct GameObjectParams
{
  class World *world;
  class Sector *sector;
  glm::vec3 pos;
};

#endif // GameObjectParams_h__