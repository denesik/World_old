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

class World
{
public:
  World();
  ~World();

  void Update();

  void Draw();

  /// Получить сектор по позиции сектора.
  std::shared_ptr<Sector> GetSector(const SPos &position);

  PBlock GetBlock(const WBPos &position);

  /// Установить блок в заданную позицию.
  /// Существующий блок будет удален.
  void SetBlock(const WBPos &pos, PBlock block);

  Player *GetPlayer();

private:
  std::unordered_map<SPos, std::shared_ptr<Sector>> mSectors;

  Sector *mCurrentSector;

  std::unique_ptr<Player> mPlayer;
};



#endif // World_h__