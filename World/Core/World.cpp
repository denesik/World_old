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

void World::Draw()
{
  for (auto &sector : mSectors)
  {
    mCurrentSector = &sector.second;
    sector.second.Draw(this);
  }
}

Sector *World::GetSector(const glm::ivec3 &position)
{
  auto it = mSectors.find(position);
  if (it != mSectors.end())
  {
    return &it->second;
  }

  return nullptr;
}

PGameObject World::GetBlock(const glm::ivec3 &position)
{
  auto secPos = position;
  const int32_t radius = static_cast<int32_t>(Sector::SECTOR_RADIUS);
  secPos.x >= 0 ? secPos.x += radius : secPos.x -= radius;
  secPos.y >= 0 ? secPos.y += radius : secPos.y -= radius;
  secPos.z >= 0 ? secPos.z += radius : secPos.z -= radius;
  secPos /= static_cast<int32_t>(Sector::SECTOR_SIZE);
  if (auto sector = GetSector(secPos))
  {
    return sector->GetBlock(position - secPos * static_cast<int32_t>(Sector::SECTOR_SIZE));
  }
  return nullptr;
}
