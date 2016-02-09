// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef CoordsConvert_h__
#define CoordsConvert_h__

#include <glm/glm.hpp>
#include "../Core/Config.h"

typedef glm::vec3   WPos;     // Мировые координаты.
typedef glm::ivec3  SPos;     // Координаты сектора.
typedef glm::ivec3  WBPos;    // Координаты блока в мире.
typedef glm::ivec3  SBPos;    // Координаты блока в секторе.


/// Система координат.
namespace cs
{
  namespace detail
  {
    inline float move(float val)
    {
      return val + static_cast<int32_t> (1.0f - (static_cast<int32_t> (val) - val));
    }
  }

  inline WBPos WorldToBlock(const WPos &pos)
  {
    WBPos bpos;
    using vtype = decltype(bpos)::value_type;

    bpos.x = (pos.x >= 0) ? static_cast<vtype>(pos.x) : static_cast<vtype>(detail::move(pos.x)) - vtype(1);
    bpos.y = (pos.y >= 0) ? static_cast<vtype>(pos.y) : static_cast<vtype>(detail::move(pos.y)) - vtype(1);
    bpos.z = (pos.z >= 0) ? static_cast<vtype>(pos.z) : static_cast<vtype>(detail::move(pos.z)) - vtype(1);

    return bpos;
  }

  inline SPos WorldToSector(const WPos &pos)
  {
    const int32_t size = static_cast<int32_t>(SECTOR_SIZE);
    SPos secPos;
    using vtype = decltype(secPos)::value_type;

    secPos.x = (pos.x >= 0) ? static_cast<int32_t>(pos.x) / size : static_cast<int32_t>(detail::move(pos.x)) / size - vtype(1);
    secPos.y = (pos.y >= 0) ? static_cast<int32_t>(pos.y) / size : static_cast<int32_t>(detail::move(pos.y)) / size - vtype(1);
    secPos.z = (pos.z >= 0) ? static_cast<int32_t>(pos.z) / size : static_cast<int32_t>(detail::move(pos.z)) / size - vtype(1);

    return secPos;
  }

  inline SPos BlockToSector(const WBPos &pos)
  {
    const int32_t size = static_cast<int32_t>(SECTOR_SIZE);
    SPos secPos;
    using vtype = decltype(secPos)::value_type;

    secPos.x = (pos.x >= 0) ? static_cast<int32_t>(pos.x) / size : static_cast<int32_t>(pos.x) / size - vtype(1);
    secPos.y = (pos.y >= 0) ? static_cast<int32_t>(pos.y) / size : static_cast<int32_t>(pos.y) / size - vtype(1);
    secPos.z = (pos.z >= 0) ? static_cast<int32_t>(pos.z) / size : static_cast<int32_t>(pos.z) / size - vtype(1);

    return secPos;
  }

  inline SPos BlockToSector(const WPos &pos)
  {
    const int32_t size = static_cast<int32_t>(SECTOR_SIZE);
    SPos secPos;
    using vtype = decltype(secPos)::value_type;

    WBPos bpos = WorldToBlock(pos);

    secPos.x = (bpos.x >= 0) ? static_cast<int32_t>(bpos.x) / size : static_cast<int32_t>(bpos.x) / size - vtype(1);
    secPos.y = (bpos.y >= 0) ? static_cast<int32_t>(bpos.y) / size : static_cast<int32_t>(bpos.y) / size - vtype(1);
    secPos.z = (bpos.z >= 0) ? static_cast<int32_t>(bpos.z) / size : static_cast<int32_t>(bpos.z) / size - vtype(1);

    return secPos;
  }
}

#endif // CoordsConvert_h__