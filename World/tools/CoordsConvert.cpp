#include "CoordsConvert.h"
#include "..\Core\Sector.h"

// Сместить диапазон чисел. [N..0) to (N..0]
inline float move(float val)
{
  return val + static_cast<int32_t>(1.0f - (static_cast<int32_t>(val) - val));
}

glm::ivec3 CoordWorldToSector(const glm::vec3 &pos)
{
  const int32_t size = static_cast<int32_t>(Sector::SECTOR_SIZE);
  glm::ivec3 secPos;

  if (pos.x >= 0) secPos.x = static_cast<int32_t>(pos.x) / size;
  if (pos.y >= 0) secPos.y = static_cast<int32_t>(pos.y) / size;
  if (pos.z >= 0) secPos.z = static_cast<int32_t>(pos.z) / size;

  if (pos.x < 0) secPos.x = static_cast<int32_t>(move(pos.x)) / size - 1;
  if (pos.y < 0) secPos.y = static_cast<int32_t>(move(pos.y)) / size - 1;
  if (pos.z < 0) secPos.z = static_cast<int32_t>(move(pos.z)) / size - 1;

  return secPos;
}

glm::ivec3 CoordWorldToBlock(const glm::vec3 &pos)
{
  glm::ivec3 bpos;
  using vtype = decltype(bpos)::value_type;

  bpos.x = (pos.x >= 0) ? static_cast<vtype>(pos.x) : static_cast<vtype>(move(pos.x)) - vtype(1);
  bpos.y = (pos.y >= 0) ? static_cast<vtype>(pos.y) : static_cast<vtype>(move(pos.y)) - vtype(1);
  bpos.z = (pos.z >= 0) ? static_cast<vtype>(pos.z) : static_cast<vtype>(move(pos.z)) - vtype(1);

  return bpos;
}

