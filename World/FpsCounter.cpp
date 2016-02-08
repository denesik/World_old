// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "FpsCounter.h"

#include <GLFW/glfw3.h>


FpsCounter::FpsCounter(void)
{
  currentTime = glfwGetTime();
  lastTime = currentTime;
  fpsTime = 0;
}


FpsCounter::~FpsCounter(void)
{
}

void FpsCounter::Update()
{
  currentTime = glfwGetTime();
  double frameTime = currentTime - lastTime;

  fpsTime += frameTime;
  fpsStack.push_back(frameTime);

  while(fpsTime > 1)
  {
    fpsTime -= fpsStack.front();
    fpsStack.pop_front();
  }

  lastTime = currentTime;
}

size_t FpsCounter::GetCount()
{
  return fpsStack.size();
}
