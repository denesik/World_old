// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "World.h"
#include "..\Log.h"
#include <tuple>
#include <utility>
#include <GLFW\glfw3.h>
#include "..\tools\CoordSystem.h"



World::World()
{
  mPlayer = std::make_unique<Player>();
}


World::~World()
{
}

void World::LoadSector(const SPos &position)
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
  SPos position;
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

Sector *World::GetSector(const SPos &position)
{
  auto it = mSectors.find(position);
  if (it != mSectors.end())
  {
    return &it->second;
  }

  return nullptr;
}

PBlock World::GetBlock(const WBPos &position)
{
  auto secPos = cs::BlockToSector(position);
  if (auto sector = GetSector(secPos))
  {
    return sector->GetBlock(position - secPos * static_cast<int32_t>(SECTOR_SIZE));
  }
  return nullptr;
}

void World::SetBlock(const WBPos &pos, PBlock block)
{
  auto secPos = cs::BlockToSector(pos);
  if (auto sector = GetSector(secPos))
  {
    sector->SetBlock(pos - secPos * static_cast<int32_t>(SECTOR_SIZE), block);
    sector->GetRenderSector().Changed();
  }
}

Player *World::GetPlayer()
{
  return mPlayer.get();
}
