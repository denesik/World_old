// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Mouse_h__
#define Mouse_h__

#include <glm/glm.hpp>

class Mouse
{
public:
  Mouse(void);
  ~Mouse(void);

  void SetPos(const glm::vec2 &pos);

  float IsMoveX();

  float IsMoveY();

  void Update();

private:

  glm::vec2 mPos;

  glm::vec2 mMoved;

};



#endif // Mouse_h__
