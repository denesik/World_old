// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Keyboard_GLFW_h__
#define Keyboard_GLFW_h__

#include <vector>

class Keyboard
{
public:
  Keyboard();
  ~Keyboard();

  void SetKey(int key, int scancode, int action, int mods);

  bool IsKeyPress(int key);
  bool IsKeyUp(int key);
  bool IsKeyDown(int key);

private:

  std::vector<int> mKeyState;
};


#endif // Keyboard_GLFW_h__
