// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Mouse.h"


Mouse::Mouse(void)
{
}


Mouse::~Mouse(void)
{
}

void Mouse::SetPos(const glm::vec2 &pos)
{
  mMoved = pos - mPos;
  mPos = pos;
}

float Mouse::IsMoveX()
{
  return mMoved.x;
}

float Mouse::IsMoveY()
{
  return mMoved.y;
}

void Mouse::Update()
{
  mMoved = glm::vec2();
}
