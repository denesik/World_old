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
#include "Core/StaticRenderAgent.h"
#include "Core/Sector.h"
#include "Core/RegistryCore.h"
#include "Core/World.h"
#include "Core/MeshBlockGenerator.h"
#include <thread>
#include <atomic>
#include "Core/BlockStaticRenderAgent.h"
#include "Core/agent_cast.h"
#include "Core/Block.h"
#include "tools/Bresenham3D.h"

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

  REGISTRY_GRAPHIC.GetCamera().Resize(REGISTRY_GRAPHIC.GetWindow().GetSize());

  REGISTRY_GRAPHIC.GetTextureManager().LoadTexture({ "Textures/stone.png", "Textures/sand.png" });
  REGISTRY_GRAPHIC.GetTextureManager().Compile();

  {
    auto block = std::make_shared<Block>();
    auto &mg = (agent_cast<BlockStaticRenderAgent>(block->GetFromFullName(StringIntern("StaticRenderAgent"))))->GetMeshBlockGenerator();
    mg.SetTexture(MeshBlockGenerator::ALL, "Textures/sand.png");
    mg.Generate();
    REGISTRY_CORE.GetBlocksLibrary().Registry(StringIntern("BlockSand"), block);
  }
  {
    auto block = std::make_shared<Block>();
    auto &mg = (agent_cast<BlockStaticRenderAgent>(block->GetFromFullName(StringIntern("StaticRenderAgent"))))->GetMeshBlockGenerator();
    mg.SetTexture(MeshBlockGenerator::ALL, "Textures/stone.png");
    mg.Generate();
    REGISTRY_CORE.GetBlocksLibrary().Registry(StringIntern("BlockStone"), block);
  }

  std::atomic<bool> close = false;

  REGISTRY_CORE.GetWorld().GetPlayer()->SetPosition({ 0,0,10 });

  std::thread thread([this, &close]
  {
    REGISTRY_CORE.GetWorld().LoadSector({ 0,0,0 });

    REGISTRY_CORE.GetWorld().LoadSector({ -1,-1,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ 0,-1,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ 1,-1,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ -1,0,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ 1,0,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ -1,1,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ 0,1,0 });
    REGISTRY_CORE.GetWorld().LoadSector({ 1,1,0 });


    auto currTime = glfwGetTime();
    while (!close)
    {
      auto lastTime = currTime;
      currTime = glfwGetTime();
      Update(currTime - lastTime);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  FpsCounter fps;
  auto currTime = glfwGetTime();
  while (!REGISTRY_GRAPHIC.GetWindow().WindowShouldClose())
  {
    fps.Update();
    glm::ivec3 camPos = glm::round(REGISTRY_GRAPHIC.GetCamera().GetPos());
    
    auto &moved = REGISTRY_GRAPHIC.GetWindow().GetMouse().GetPos();
    auto ray = REGISTRY_GRAPHIC.GetCamera().GetRay(moved);
    ray *= 3;

    auto points = Bresenham3D(camPos, camPos + glm::ivec3(glm::round(ray)));

    glm::ivec3 block;
    for (auto &p : points)
    {
      if (REGISTRY_CORE.GetWorld().GetBlock(p))
      {
        block = p;
        break;
      }
    }

    REGISTRY_GRAPHIC.GetWindow().SetTitle(
      std::to_string(fps.GetCount()) + std::string(" fps. pos: [x: ") +
      std::to_string(camPos.x) + std::string(" y: ") +
      std::to_string(camPos.y) + std::string(" z: ") +
      std::to_string(camPos.z) + std::string("] block: [x: ") +
      std::to_string(block.x) + std::string(" y: ") +
      std::to_string(block.y) + std::string(" z: ") +
      std::to_string(block.z) + std::string("]")
      );

    auto lastTime = currTime;
    currTime = glfwGetTime();
    Draw(currTime - lastTime);

    REGISTRY_GRAPHIC.GetWindow().Update();
  }

  close = true;
  thread.join();

  return 0;
}

void Game::Update(double dt)
{
  float speedRot = static_cast<float>(3.0 * dt);

  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_LEFT))
  {
    REGISTRY_CORE.GetWorld().GetPlayer()->Rotate({ 0.0f, 0.0f, -speedRot });
    REGISTRY_GRAPHIC.GetCamera().Rotate({ 0.0f, 0.0f, -speedRot });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_RIGHT))
  {
    REGISTRY_CORE.GetWorld().GetPlayer()->Rotate({ 0.0f, 0.0f, speedRot });
    REGISTRY_GRAPHIC.GetCamera().Rotate({ 0.0f, 0.0f, speedRot });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_DOWN))
  {
    REGISTRY_CORE.GetWorld().GetPlayer()->Rotate({ speedRot, 0.0f, 0.0f });
    REGISTRY_GRAPHIC.GetCamera().Rotate({ speedRot, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_UP))
  {
    REGISTRY_CORE.GetWorld().GetPlayer()->Rotate({ -speedRot, 0.0f, 0.0f });
    REGISTRY_GRAPHIC.GetCamera().Rotate({ -speedRot, 0.0f, 0.0f });
  }

  auto moved = REGISTRY_GRAPHIC.GetWindow().GetMouse().GetMoved();
  moved *= static_cast<float>(dt) * 0.07f;
  REGISTRY_CORE.GetWorld().GetPlayer()->Rotate(glm::vec3(moved.y, 0.0f, moved.x));
  REGISTRY_GRAPHIC.GetCamera().Rotate(glm::vec3(moved.y, 0.0f, moved.x));

  static float k = 1.0f;
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyPress(GLFW_KEY_9))
  {
    k += 1.0f;
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyPress(GLFW_KEY_0))
  {
    k -= 1.0f;
  }
  if (k < 1.0f)
  {
    k = 1.0f;
  }
  float speedMov = static_cast<float>(15.0 * dt) * k;

  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_D))
  {
    REGISTRY_CORE.GetWorld().GetPlayer()->Move({ speedMov, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_A))
  {
    REGISTRY_CORE.GetWorld().GetPlayer()->Move({ -speedMov, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_W))
  {
    REGISTRY_CORE.GetWorld().GetPlayer()->Move({ 0.0f, speedMov, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_S))
  {
    REGISTRY_CORE.GetWorld().GetPlayer()->Move({ 0.0f, -speedMov, 0.0f });
  }

  glm::ivec3 secPos = glm::round(REGISTRY_CORE.GetWorld().GetPlayer()->GetPosition());
  const int32_t radius = static_cast<int32_t>(Sector::SECTOR_RADIUS);
  secPos.x >= 0 ? secPos.x += radius : secPos.x -= radius;
  secPos.y >= 0 ? secPos.y += radius : secPos.y -= radius;
  secPos.z >= 0 ? secPos.z += radius : secPos.z -= radius;
  secPos /= static_cast<int32_t>(Sector::SECTOR_SIZE);
  secPos.z = 0;

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
    REGISTRY_CORE.GetWorld().LoadSector(secPos + i);
  }

  REGISTRY_CORE.GetWorld().Update();
}


void Game::Draw(double dt)
{
  REGISTRY_GRAPHIC.GetCamera().SetPos(REGISTRY_CORE.GetWorld().GetPlayer()->GetPosition() + glm::vec3{ 0.0f, 0.0f, 1.7f });
  REGISTRY_GRAPHIC.GetCamera().Update();



  GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));     // Очистка экрана

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(REGISTRY_GRAPHIC.GetCamera().GetProject()));

  glMatrixMode(GL_MODELVIEW);
  GL_CALL(glLoadIdentity());                               // Сброс просмотра
  GL_CALL(glTranslatef(-1.5f, 0.0f, -6.0f));
  glLoadMatrixf(glm::value_ptr(REGISTRY_GRAPHIC.GetCamera().GetView()));

  REGISTRY_CORE.GetWorld().Draw();
}

// glm::vec3 near = glm::unProject(glm::vec3(
//   Mouse::getCursorPos().x, RESY - Mouse::getCursorPos().y, 0.f), 
//   cam->getModel() * cam->getView(), 
//   cam->getProjection(), 
//   cam->getViewport()
//   );
// 
