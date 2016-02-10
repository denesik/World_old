// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "SectorLoader.h"
#include "World.h"
#include <GLFW\glfw3.h>
#include <iostream>


SectorLoader::SectorLoader(World &world, const glm::ivec3 &pos, unsigned int radius)
  : mWorld(world), mPos(pos)
{
  SetRadius(radius);
  SetPos(pos);
}

SectorLoader::~SectorLoader()
{
}

void SectorLoader::SetRadius(unsigned int radius)
{
  mRadius = radius;

  mSite.clear();

  int begin = -static_cast<int>(mRadius);
  int end = static_cast<int>(mRadius);
  glm::ivec3 pos(begin); pos.z = -2;
//  for (pos.z = begin; pos.z != end; ++pos.z)
  for (pos.y = begin; pos.y <= end; ++pos.y)
  for (pos.x = begin; pos.x <= end; ++pos.x)
  {
    mSite.push_back(pos);
  }

}

void SectorLoader::SetPos(const glm::ivec3 &pos)
{
  if (mPos == pos)
  {
    return;
  }

  // Пробегаем по всем загруженным на данный момент секторам и выгружаем их.
  for (const auto &site : mSite)
  {
    //mWorld.UnloadSector(mPos + site);
  }

  auto currentTime = glfwGetTime();
  mPos = pos;
  // Загружаем нужные сектора.
  for (const auto &site : mSite)
  {
    mWorld.GetSector(mPos + site);
  }

  std::cout << "MapGen. Count: " << mSite.size() << " time: " << glfwGetTime() - currentTime << std::endl;
}
