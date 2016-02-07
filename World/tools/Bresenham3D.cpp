// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Bresenham3D.h"

std::vector<glm::ivec3> Bresenham3D(const glm::ivec3 &begin, const glm::ivec3 &end)
{
  int x = begin.x;
  int y = begin.y;
  int z = begin.z;
  int dx = glm::abs(end.x - x);
  int dy = glm::abs(end.y - y);
  int dz = glm::abs(end.z - z);
  int sx = glm::sign(end.x - x);
  int sy = glm::sign(end.y - y);
  int sz = glm::sign(end.z - z);

  std::vector<glm::ivec3> points;

  if ((dy >= dx) && (dy >= dz))
  {
    int e_yx = (dx - dy) << 1;
    int e_yz = (dz - dy) << 1;

    e_yx -= (e_yx >> 1);
    e_yz -= (e_yz >> 1);

    for (int i = 0; i < dy; ++i)
    {
      points.push_back(glm::vec3(x, y, z));
      if (e_yx >= 0)
      {
        x += sx;
        e_yx -= (dy << 1);
        points.push_back(glm::vec3(x, y, z));
      }

      if (e_yz >= 0)
      {
        z += sz;
        e_yz -= (dy << 1);
        points.push_back(glm::vec3(x, y, z));
      }

      y += sy;
      e_yx += (dx << 1);
      e_yz += (dz << 1);
    }
  }
  else if ((dx >= dy) && (dx >= dz))
  {
    int e_xy = (dy - dx) << 1;
    int e_xz = (dz - dx) << 1;

    e_xz -= (e_xz >> 1);
    e_xy -= (e_xy >> 1);

    for (int i = 0; i < dx; ++i)
    {
      points.push_back(glm::vec3(x, y, z));

      if (e_xy >= 0)
      {
        y += sy;
        e_xy -= (dx << 1);
        points.push_back(glm::vec3(x, y, z));
      }

      if (e_xz >= 0)
      {
        z += sz;
        e_xz -= (dx << 1);
        points.push_back(glm::vec3(x, y, z));
      }
      x += sx;
      e_xy += (dy << 1);
      e_xz += (dz << 1);
    }
  }
  else // (dz>=dy) && (dz>=dx)
  {
    int e_zx = (dx - dz) << 1;
    int e_zy = (dy - dz) << 1;

    e_zx -= (e_zx >> 1);
    e_zy -= (e_zy >> 1);

    for (int i = 0; i < dz; ++i)
    {
      points.push_back(glm::vec3(x, y, z));

      if (e_zx >= 0)
      {
        x += sx;
        e_zx -= (dz << 1);
        points.push_back(glm::vec3(x, y, z));
      }
      if (e_zy >= 0)
      {
        y += sy;
        e_zy -= (dz << 1);
        points.push_back(glm::vec3(x, y, z));
      }

      z += sz;
      e_zx += (dx << 1);
      e_zy += (dy << 1);
    }
  }
  points.push_back(glm::vec3(x, y, z));
  return points;
}


