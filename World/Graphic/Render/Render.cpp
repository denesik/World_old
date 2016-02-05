// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Render.h"

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../RegistryGraphic.h"
#include "OpenGLCall.h"

Render::Render(void)
{
  GL_CALL(glGetIntegerv(GL_MAJOR_VERSION, &mVersion.major));
  GL_CALL(glGetIntegerv(GL_MINOR_VERSION, &mVersion.minor));

  mVersion.major = 1;
  mVersion.minor = 4;

  // Настройки для старого огл.
  if (mVersion.major < 3)
  {
    GL_CALL(glEnable(GL_TEXTURE_2D));
  }

  GL_CALL(glEnable(GL_CULL_FACE));
  GL_CALL(glCullFace(GL_BACK));

  GL_CALL(glEnable(GL_DEPTH_TEST));            // Разрешить тест глубины
  GL_CALL(glDepthFunc(GL_LEQUAL));            // Тип теста глубины

  GL_CALL(glClearColor(117.0f / 255.0f, 187.0f / 255.0f, 253.0f / 255.0f, 1.0f));

  try
  {
    mShader.reset(new Shader("Graphic/Shaders/t"));
  }
  catch (const char* msg)
  {
    std::cout << msg << std::endl;
  }
}

Render::~Render(void)
{
}

void Render::Initialize()
{
  glewExperimental = true; // Needed in core profile

  GLenum error = glewInit();
  if(error != GLEW_OK)
  {
    std::cout << "glew error: " << glewGetErrorString(error) << std::endl;
    throw "GLEW not initialized.";
  }
  glGetError();
}

const Render::Version &Render::GetVersion() const
{
  return mVersion;
}

void Render::Draw(const StaticModel &model)
{
  model.GetTexture()->Set(TEXTURE_SLOT_0);
  //model.GetMesh().Draw();
}

void Render::Draw(const DinamicModel &model)
{
  model.GetTexture()->Set(TEXTURE_SLOT_0);
  model.GetMesh()->Draw();
}



