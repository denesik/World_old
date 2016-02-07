// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Mouse_h__
#define Mouse_h__

#include <glm/glm.hpp>
#include <mutex>


class Mouse
{
public:
  Mouse(struct GLFWwindow &window);
  ~Mouse(void);

  float IsMoveX();

  float IsMoveY();

  glm::vec2 GetMoved();

  void Update();

private:
  struct GLFWwindow &mWindow;

  glm::vec2 mPos;
  glm::vec2 mMoved;

  std::mutex mMutex;

  bool mIsFocused;
};



#endif // Mouse_h__
