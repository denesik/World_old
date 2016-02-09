// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef World_h__
#define World_h__

#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>
#include <list>
#include "Sector.h"
#include "Player.h"

namespace std
{
  template <>
  struct hash<SPos>
  {
    std::size_t operator()(SPos const& v) const
    {
      std::size_t h1 = std::hash<int32_t>()(v.x);
      std::size_t h2 = std::hash<int32_t>()(v.y);
      std::size_t h3 = std::hash<int32_t>()(v.z);
      return ((h1 ^ (h2 << 1)) >> 1) ^ (h3 << 1);
    }
  };
}

class World
{
public:
  World();
  ~World();

  void LoadSector(const SPos &position);

  void Update();

  void Draw();

  /// Получить сектор по позиции сектора.
  Sector *GetSector(const SPos &position);

  PBlock GetBlock(const WBPos &position);

  /// Установить блок в заданную позицию.
  /// Существующий блок будет удален.
  void SetBlock(const WBPos &pos, PBlock block);

  Player *GetPlayer();

private:
  std::unordered_map<SPos, Sector> mSectors;
  std::unordered_map<SPos, RenderSector> mRenderSectors;

  SPos mLastLoadPos;
  std::list<SPos> mListLoad;

  Sector *mCurrentSector;

  std::unique_ptr<Player> mPlayer;
};



#endif // World_h__