// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef SectorLoader_h__
#define SectorLoader_h__

#include <glm/glm.hpp>
#include <vector>
class World;

///???
class SectorLoader
{
public:
  SectorLoader(World &world, const glm::ivec3 &pos = {}, unsigned int radius = 3);
  ~SectorLoader();

  /// Радиус зоны загрузки секторов.
  void SetRadius(unsigned int radius);

  /// Позиция сектора.
  void SetPos(const glm::ivec3 &pos);

private:

  World &mWorld;

  glm::ivec3 mPos;

  unsigned int mRadius;

  std::vector<glm::ivec3> mSite;

private:
  SectorLoader(const SectorLoader &) = delete;
  SectorLoader& operator=(const SectorLoader &) = delete;
};



#endif // SectorLoader_h__

