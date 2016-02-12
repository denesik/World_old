// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Render_h__
#define Render_h__

#include "Camera.h"
#include "Shader.h"
#include "Model.h"



class Render
{
public:
  struct Version
  {
    int major = 0;
    int minor = 0;
  };

public:

  Render();
  ~Render();

  static void Initialize();

  const Version &GetVersion() const;

  /// Нарисовать модель.
  /// Устанавливает параметры для рисования и рисует модель.
  void Draw(const Model &model);

private:

  std::unique_ptr<Shader> mShader;
   
  Version mVersion;

};



#endif // Render_h__
