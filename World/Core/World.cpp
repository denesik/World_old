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
#include "MapGen\WorldWorker.h"


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

void World::Draw(Render &render)
{
  for (auto &sector : mSectors)
  {
    sector.second->GetRenderSector().Draw(render);
  }
}

void World::GetSector(const SPos &position)
{
  auto it = mSectors.find(position);
  if (it == mSectors.end())
  {
    if (auto psec = WorldWorker::instance().GetSector(position))
    {
      mSectors[position] = psec;
    }
  }
}

std::shared_ptr<Sector> World::FindSector(const SPos &position)
{
  auto it = mSectors.find(position);
  if (it != mSectors.end())
  {
    return it->second;
  }

  return nullptr;
}

PBlock World::GetBlock(const WBPos &wbpos)
{
  auto spos = cs::WBtoS(wbpos);
  if (auto sector = FindSector(spos))
  {
    return sector->GetBlock(cs::WBtoSB(wbpos, spos));
  }

  return nullptr;
}

void World::SetBlock(const WBPos &wbpos, PBlock block)
{
  auto spos = cs::WBtoS(wbpos);
  if (auto sector = FindSector(spos))
  {
    sector->SetBlock(cs::WBtoSB(wbpos, spos), block);
    sector->GetRenderSector().Changed();
  }
}

Player *World::GetPlayer()
{
  return mPlayer.get();
}
