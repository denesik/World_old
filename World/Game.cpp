// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Game.h"

#include <gl/glew.h>
#include "Graphic/Window/Window.h"
#include <iostream>
#include <sstream>
#include "Graphic/Render/TextureManager.h"
#include "Graphic/Render/Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Graphic/RegistryGraphic.h"

#include <fstream>
#include "FpsCounter.h"
#include "Graphic/Render/Shader.h"
#include <memory>
#include "Log.h"
#include "Graphic/Render/OpenGLCall.h"
#include <vector>
#include "Core/GameObject.h"
#include "Core/RenderAgent.h"
#include "Core/Sector.h"
#include "Core/RegistryCore.h"
#include "Core/World.h"
#include "Core/ModelBlockGenerator.h"

Game::Game()
{
  try
  {
    REGISTRY_GRAPHIC;
    Initialized = true;
  }
  catch (const char *e)
  {
    LOG(error) << e << std::endl;
    return;
  }

  //GL_CALL(glViewport(0, 0, REGISTRY_GRAPHIC.GetWindow().GetSize().x, REGISTRY_GRAPHIC.GetWindow().GetSize().y)); 
}

Game::~Game()
{

}


int Game::Run()
{
  if (!Initialized)
  {
    system("pause");
    return -1;
  }

  {
    REGISTRY_GRAPHIC.GetCamera().Resize(REGISTRY_GRAPHIC.GetWindow().GetSize());

    REGISTRY_GRAPHIC.GetTextureManager().LoadTexture({ "Textures/stone.png", "Textures/sand.png" });
    REGISTRY_GRAPHIC.GetTextureManager().Compile();

    {
      auto block = std::make_shared<GameObject>();
      auto &mg = *static_cast<ModelBlockGenerator *>(static_cast<RenderAgent *>(block->GetFromFullName(StringIntern("RenderAgent")))->GetModelGenerator());
      mg.SetTexture(ModelBlockGenerator::ALL, "Textures/sand.png");
      REGISTRY_CORE.GetBlocksLibrary().Registry(StringIntern("BlockSand"), block);
    }
    {
      auto block = std::make_shared<GameObject>();
      auto &mg = *static_cast<ModelBlockGenerator *>(static_cast<RenderAgent *>(block->GetFromFullName(StringIntern("RenderAgent")))->GetModelGenerator());
      mg.SetTexture(ModelBlockGenerator::ALL, "Textures/stone.png");
      REGISTRY_CORE.GetBlocksLibrary().Registry(StringIntern("BlockStone"), block);
    }


    REGISTRY_CORE.GetWorld().LoadSector({ 0,0,0 });

    REGISTRY_CORE.GetWorld().LoadSector({ -1,-1,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ 0,-1,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ 1,-1,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ -1,0,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ 1,0,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ -1,1,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ 0,1,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ 1,1,0 });

    FpsCounter fps;
    while (!REGISTRY_GRAPHIC.GetWindow().WindowShouldClose())
    {
      fps.Update();
      glm::ivec3 camPos = REGISTRY_GRAPHIC.GetCamera().GetPos();
      REGISTRY_GRAPHIC.GetWindow().SetTitle(
        std::to_string(fps.GetCount()) + std::string(" fps. x: ") +
        std::to_string(camPos.x) + std::string(" y: ") +
        std::to_string(camPos.y) + std::string(" z: ") +
        std::to_string(camPos.z)
        );

      Update();
      Draw();

      REGISTRY_GRAPHIC.GetWindow().SwapBuffers();
      Window::WindowSystemPollEvents();
    }
  }

  return 0;
}

void Game::Update()
{
  const float speed = 0.06f;

  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_LEFT))
  {
    REGISTRY_GRAPHIC.GetCamera().Rotate({ 0.0f, 0.0f, -speed / 2.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_RIGHT))
  {
    REGISTRY_GRAPHIC.GetCamera().Rotate({ 0.0f, 0.0f, speed / 2.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_DOWN))
  {
    REGISTRY_GRAPHIC.GetCamera().Rotate({ speed / 2.0f, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_UP))
  {
    REGISTRY_GRAPHIC.GetCamera().Rotate({ -speed / 2.0f, 0.0f, 0.0f });
  }

  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_D))
  {
    REGISTRY_GRAPHIC.GetCamera().Move({ speed, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_A))
  {
    REGISTRY_GRAPHIC.GetCamera().Move({ -speed, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_W))
  {
    REGISTRY_GRAPHIC.GetCamera().Move({ 0.0f, speed, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_S))
  {
    REGISTRY_GRAPHIC.GetCamera().Move({ 0.0f, -speed, 0.0f });
  }

  float ay = REGISTRY_GRAPHIC.GetWindow().GetMouse().IsMoveX() / 30.0f;
  float ax = REGISTRY_GRAPHIC.GetWindow().GetMouse().IsMoveY() / 30.0f;
  //REGISTRY_GRAPHIC.GetCamera().Rotate(glm::vec3(ax, ay, 0.0f) / 2.0f);

//   REGISTRY_GRAPHIC.GetCamera().SetPos(REGISTRY_CORE.GetPlayer().GetPosition());
// 
  REGISTRY_GRAPHIC.GetCamera().Update();

  glm::ivec3 camPos = REGISTRY_GRAPHIC.GetCamera().GetPos();
  camPos.z = 0;
  camPos /= static_cast<int32_t>(Sector::SECTOR_RADIUS);
  camPos.x >= 0 ? ++camPos.x : --camPos.x;
  camPos.y >= 0 ? ++camPos.y : --camPos.y;
  camPos.z >= 0 ? ++camPos.z : --camPos.z;
  camPos /= 2;

  glm::ivec3 offsets[8] =
  {
    { -1,-1,0 },
    { -1,0,0 },
    { -1,1,0 },
    { 0,-1,0 },
    { 0,1,0 },
    { 1,-1,0 },
    { 1,0,0 },
    { 1,1,0 },
  };
  for (auto i : offsets)
  {
    REGISTRY_CORE.GetWorld().LoadSector(camPos + i);
  }
  
//   REGISTRY_CORE.GetPlayer().SetDirection(REGISTRY_GRAPHIC.GetCamera().GetDirection());
// 
//   if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_D))
//   {
//     REGISTRY_CORE.GetPlayer().Move({ speed, 0.0f, 0.0f });
//   }
//   if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_A))
//   {
//     REGISTRY_CORE.GetPlayer().Move({ -speed, 0.0f, 0.0f });
//   }
//   if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_W))
//   {
//     REGISTRY_CORE.GetPlayer().Move({ 0.0f, speed, 0.0f });
//   }
//   if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_S))
//   {
//     REGISTRY_CORE.GetPlayer().Move({ 0.0f, -speed, 0.0f });
//   }
// 
//   REGISTRY_GRAPHIC.GetWindow().GetMouse().Update();

}


void Game::Draw()
{
  GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));     // Очистка экрана

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(REGISTRY_GRAPHIC.GetCamera().GetProject()));

  glMatrixMode(GL_MODELVIEW);
  GL_CALL(glLoadIdentity());                               // Сброс просмотра
  GL_CALL(glTranslatef(-1.5f, 0.0f, -6.0f));
  glLoadMatrixf(glm::value_ptr(REGISTRY_GRAPHIC.GetCamera().GetView()));

  //glColor3f(1.0f, 0.0f, 0.0f);

  REGISTRY_CORE.GetWorld().Update();
}
