// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Keyboard.h"

#include <GLFW\glfw3.h>

Keyboard::Keyboard()
{
  for (auto &key : mKeyState)
  {
    key = GLFW_RELEASE;
  }
}

Keyboard::~Keyboard()
{

}


void Keyboard::SetKey(int key, int , int action, int ) 
{
  if(key == GLFW_KEY_UNKNOWN)
  {
    //printf("glfw unknown key\n");
    return;
  }

  std::lock_guard<std::mutex> lock(mMutex);
  mKeyState[key] = action;
}

bool Keyboard::IsKeyPress(int key)
{
  std::lock_guard<std::mutex> lock(mMutex);
  if(mKeyState[key] == GLFW_PRESS)
  {
    mKeyState[key] = GLFW_REPEAT;
    return true;
  }
  return false;
}

bool Keyboard::IsKeyUp(int key)
{
  std::lock_guard<std::mutex> lock(mMutex);
  if(mKeyState[key] == GLFW_RELEASE)
    return true;
  return false;
}

bool Keyboard::IsKeyDown(int key)
{
  std::lock_guard<std::mutex> lock(mMutex);
  if(mKeyState[key] == GLFW_REPEAT || mKeyState[key] == GLFW_PRESS)
    return true;
  return false;
}
