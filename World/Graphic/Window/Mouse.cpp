// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Mouse.h"
#include <GLFW/glfw3.h>


Mouse::Mouse(GLFWwindow &window)
  : mWindow(window)
{
  mIsFocused = (glfwGetWindowAttrib(&mWindow, GLFW_FOCUSED) == GL_TRUE);

  glm::ivec2 size;
  glfwGetWindowSize(&mWindow, &size.x, &size.y);
  size /= 2;
  glfwSetCursorPos(&mWindow, size.x, size.y);

  double cx, cy;
  glfwGetCursorPos(&mWindow, &cx, &cy);

  std::lock_guard<std::mutex> lock(mMutex);
  mPos = decltype(mPos)(cx, cy);
}


Mouse::~Mouse(void)
{
}

float Mouse::IsMoveX()
{
  std::lock_guard<std::mutex> lock(mMutex);
  return mMoved.x;
}

float Mouse::IsMoveY()
{
  std::lock_guard<std::mutex> lock(mMutex);
  return mMoved.y;
}

void Mouse::Update()
{
  glm::ivec2 size;
  glfwGetWindowSize(&mWindow, &size.x, &size.y);
  size /= 2;

  double cx(size.x), cy(size.y);
  bool focused = (glfwGetWindowAttrib(&mWindow, GLFW_FOCUSED) == GL_TRUE);
  if (focused && mIsFocused)
  {
    glfwGetCursorPos(&mWindow, &cx, &cy);
  }
  mIsFocused = focused;
  glm::vec2 newPos(cx, cy);

  glfwSetCursorPos(&mWindow, size.x, size.y);

  std::lock_guard<std::mutex> lock(mMutex);
  mMoved = newPos - mPos;
  mPos = size;
}
