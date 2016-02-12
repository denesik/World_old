// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Sector_h__
#define Sector_h__

#include <array>
#include <glm/glm.hpp>

#include "../tools/CoordSystem.h"
#include "Block.h"
#include "Config.h"
#include "RenderSector.h"

class Sector
{
public:
  Sector(const SPos &position);
  ~Sector();

  const SPos &GetSectorPosition() const;

  /// ¬ернуть блок в локальных координатах сектора.
  PBlock GetBlock(const SBPos &pos);

  /// ”становить блок в заданную позицию.
  /// —уществующий блок будет удален.
  void SetBlock(const SBPos &pos, PBlock block);

  void Update(class World *world);

  RenderSector &GetRenderSector();

private:

  friend class WorldWorker;
  std::array<PBlock, SECTOR_SIZE * SECTOR_SIZE * SECTOR_SIZE> mBlocks;
  std::array<SBPos, SECTOR_SIZE * SECTOR_SIZE * SECTOR_SIZE> mBlocksPos;

  SPos mPos;

  RenderSector mRenderSector;
};



#endif // Sector_h__