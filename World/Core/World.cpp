// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "World.h"



World::World()
{
  
}


World::~World()
{
}

void World::LoadSector(const glm::ivec3 &position)
{
  auto it = mSectors.find(position);
  if (it == mSectors.end())
  {
    mSectors.emplace(position, position);
  }
}

void World::Update()
{
  for (auto &sector : mSectors)
  {
    mCurrentSector = &sector.second;
    sector.second.Update(this);
  }
}
