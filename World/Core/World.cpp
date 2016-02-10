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
#include "RenderSector.h"
#include "MapGen\LevelWorker.h"


World::World()
{
  mPlayer = std::make_unique<Player>();
}


World::~World()
{
}

void World::Update()
{
  mPlayer->Update(GameObjectParams{ this, nullptr, {} });

  for (auto &sector : mSectors)
  {
    sector.second->Update(this);
  }
}

void World::Draw()
{
  for (auto &sector : mSectors)
  {
    sector.second->GetRenderSector().Draw();
  }
}

std::shared_ptr<Sector> World::GetSector(const SPos &position)
{
  auto it = mSectors.find(position);
  if (it != mSectors.end())
  {
    return it->second;
  }

  auto psec = LevelWorker::instance().GetSector(position);
  if (psec)
    mSectors[position] = psec;

  return psec;
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
