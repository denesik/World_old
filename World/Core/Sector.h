// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Sector_h__
#define Sector_h__

#include <array>
#include "GameObject.h"
#include <glm/glm.hpp>
#include "../Graphic/GameRender/RenderSector.h"

class Sector
{
public:
  enum 
  {
    SECTOR_RADIUS = 2,
    SECTOR_SIZE = SECTOR_RADIUS * 2 + 1,
  };

public:
  Sector(const glm::ivec3 &position);
  ~Sector();

  const glm::ivec3 &GetSectorPosition() const;

  PGameObject GetBlock(const glm::ivec3 &pos);

  void Update(class World *world);

  RenderSector &GetRenderSector();

private:
  template<class T, size_t S>
  using SectorMap = std::array<std::array<std::array<T, S>, S>, S>;

  SectorMap<PGameObject, SECTOR_SIZE> mBlocks;

  glm::ivec3 mSectorPosition;

  RenderSector mRenderSector;
};



#endif // Sector_h__