// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "World.h"
#include "..\Log.h"
#include <tuple>
#include <utility>
#include <GLFW\glfw3.h>



World::World()
{
  mPlayer = std::make_unique<Player>();
}


World::~World()
{
}

void World::LoadSector(const glm::ivec3 &position)
{
  if (position != mLastLoadPos)
  {
    mListLoad.emplace_back(position);
    mLastLoadPos = position;
  }
}

void World::Update()
{
  mPlayer->Update(GameObjectParams{ this, nullptr, {} });

  bool load = false;
  glm::ivec3 position;
  while (!mListLoad.empty())
  {
    auto it = mSectors.find(mListLoad.front());
    if (it == mSectors.end())
    {
      position = mListLoad.front();
      mListLoad.pop_front();
      load = true;
      break;
    }
    else
    {
      mListLoad.pop_front();
    }
  }

  if (load)
  {
    auto res = mRenderSectors.emplace(std::piecewise_construct,
      std::forward_as_tuple(position),
      std::forward_as_tuple());
    mSectors.emplace(std::piecewise_construct,
      std::forward_as_tuple(position),
      std::forward_as_tuple(position, res.first->second));

//     glm::ivec3 offsets[] =
//     {
//       { -1,-1,0 },
//       { -1,0,0 },
//       { -1,1,0 },
//       { 0,-1,0 },
//       { 0,1,0 },
//       { 1,-1,0 },
//       { 1,0,0 },
//       { 1,1,0 },
//     };
// 
//     for (auto i : offsets)
//     {
//       if (auto sector = GetSector(position + i))
//       {
//         sector->GetRenderSector().Changed();
//       }
//     }

    LOG(info) << "Count sectors: " << mSectors.size();
  }

  for (auto &sector : mSectors)
  {
    mCurrentSector = &sector.second;
    sector.second.Update(this);
  }
}

void World::Draw()
{
  for (auto &sector : mRenderSectors)
  {
    sector.second.Draw();
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

PBlock World::GetBlock(const glm::ivec3 &position)
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

void World::SetBlock(const glm::ivec3 &pos, PBlock block)
{
  auto secPos = pos;
  const int32_t radius = static_cast<int32_t>(Sector::SECTOR_RADIUS);
  secPos.x >= 0 ? secPos.x += radius : secPos.x -= radius;
  secPos.y >= 0 ? secPos.y += radius : secPos.y -= radius;
  secPos.z >= 0 ? secPos.z += radius : secPos.z -= radius;
  secPos /= static_cast<int32_t>(Sector::SECTOR_SIZE);
  if (auto sector = GetSector(secPos))
  {
    sector->SetBlock(pos - secPos * static_cast<int32_t>(Sector::SECTOR_SIZE), block);
    sector->GetRenderSector().Changed();
  }
}

Player *World::GetPlayer()
{
  return mPlayer.get();
}
