// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Game.h"

#include <gl/glew.h>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/thread/thread.hpp>

#include <fstream>
#include "FpsCounter.h"
#include <memory>
#include "Log.h"
#include "Render/OpenGLCall.h"
#include <vector>
#include <thread>
#include <atomic>
#include "tools/Bresenham3D.h"
#include "tools/CoordSystem.h"
#include "Core\MapGen\LevelWorker.h"
#include "Render/TextureManager.h"
#include "Core/DB.h"
#include "Core/BlockRenderStratery.h"

Game::Game()
{
  Window::WindowSystemInitialize();

  try
  {
    mWindow = std::make_unique<Window>(glm::uvec2(600, 600));
    mWindow->SetCurrentContext();

    Render::Initialize();
    mRender = std::make_unique<Render>();

    LOG(info) << "Render created. Version: " << mRender->GetVersion().major << "." << mRender->GetVersion().minor;

    Initialized = true;
  }
  catch (const char *e)
  {
    LOG(error) << e << std::endl;
    return;
  }

  //GL_CALL(glViewport(0, 0, REGISTRY_GRAPHIC.GetWindow().GetSize().x, REGISTRY_GRAPHIC.GetWindow().GetSize().y)); 

  mWorld = std::make_unique<World>();
}

Game::~Game()
{
  mRender.reset();
  mWindow.reset();
  Window::WindowSystemFinally();
}


int Game::Run()
{
  if (!Initialized)
  {
    system("pause");
    return -1;
  }

  mCamera.Resize(mWindow->GetSize());

  TextureManager::Get().LoadTexture({ "Textures/stone.png", "Textures/sand.png", "Textures/brick.png" });
  TextureManager::Get().Compile();

  {
    auto strategy = MakeRenderStrategy<BlockRenderStratery>();
    auto &mg = strategy->GetGenerator();
    mg.SetTexture(MeshBlockGenerator::ALL, "Textures/sand.png");
    mg.Generate();
    auto block = MakeGameObject<Block>();
    block->GetFromFullName<RenderAgent>(StringIntern("RenderAgent"))->SetStrategy(strategy);
    DB::Get().Registry(StringIntern("BlockSand"), block);
  }
  {
    auto strategy = MakeRenderStrategy<BlockRenderStratery>();
    auto &mg = strategy->GetGenerator();
    mg.SetTexture(MeshBlockGenerator::ALL, "Textures/stone.png");
    mg.Generate();
    auto block = MakeGameObject<Block>();
    block->GetFromFullName<RenderAgent>(StringIntern("RenderAgent"))->SetStrategy(strategy);
    DB::Get().Registry(StringIntern("BlockStone"), block);
  }
  {
    auto strategy = MakeRenderStrategy<BlockRenderStratery>();
    auto &mg = strategy->GetGenerator();
    mg.SetTexture(MeshBlockGenerator::ALL, "Textures/brick.png");
    mg.Generate();
    auto block = MakeGameObject<Block>();
    block->GetFromFullName<RenderAgent>(StringIntern("RenderAgent"))->SetStrategy(strategy);
    DB::Get().Registry(StringIntern("BlockBrick"), block);
  }

  std::atomic<bool> close = false;

  mWorld->GetPlayer()->SetPosition({ 0,0,30 });

  boost::thread th([&close]() {
    while (!close)
    {
      LevelWorker::instance().Process();
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  boost::thread thread([this, &close]
  {
    SPos offsets[] =
    {
      { -1,-1,0 },
      { -1,0,0 },
      { -1,1,0 },
      { 0,-1,0 },
      { 0,0,0 },
      { 0,1,0 },
      { 1,-1,0 },
      { 1,0,0 },
      { 1,1,0 },
    };
    for (auto i : offsets)
    {
      mWorld->GetSector(i);
    }


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
  while (!mWindow->WindowShouldClose())
  {
    fps.Update();
    glm::vec3 camPos = mCamera.GetPos();
    
    auto &moved = mWindow->GetMouse().GetPos();
    auto ray = mCamera.GetRay(moved);
    ray *= 10;

    auto points = Bresenham3D(camPos, camPos + ray);

    auto far = camPos + ray;
    glm::vec3 blockPos;
    //for (auto &p : points)
    //{
    //  if (REGISTRY_CORE.GetWorld().GetBlock(p))
    //  {
    //    blockPos = p;
    //    if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyPress(GLFW_KEY_SPACE))
    //    {
    //      REGISTRY_CORE.GetWorld().SetBlock(p, REGISTRY_CORE.GetBlocksLibrary().Create(StringIntern("BlockBrick")));
    //    }
    //    break;
    //  }
    //}

    mWindow->SetTitle(
      std::to_string(fps.GetCount()) + std::string(" fps. pos: [x: ") +
      std::to_string(camPos.x) + std::string(" y: ") +
      std::to_string(camPos.y) + std::string(" z: ") +
      std::to_string(camPos.z) + std::string("] block: [x: ") +
      std::to_string(blockPos.x) + std::string(" y: ") +
      std::to_string(blockPos.y) + std::string(" z: ") +
      std::to_string(blockPos.z) + std::string("]")
      );

    auto lastTime = currTime;
    currTime = glfwGetTime();
    Draw(currTime - lastTime);

    mWindow->Update();
  }

  close = true;
  thread.join();
  th.join();

  return 0;
}

void Game::Update(double dt)
{
  float speedRot = static_cast<float>(3.0 * dt);

  if (mWindow->GetKeyboard().IsKeyDown(GLFW_KEY_LEFT))
  {
    mWorld->GetPlayer()->Rotate({ 0.0f, 0.0f, -speedRot });
    mCamera.Rotate({ 0.0f, 0.0f, -speedRot });
  }
  if (mWindow->GetKeyboard().IsKeyDown(GLFW_KEY_RIGHT))
  {
    mWorld->GetPlayer()->Rotate({ 0.0f, 0.0f, speedRot });
    mCamera.Rotate({ 0.0f, 0.0f, speedRot });
  }
  if (mWindow->GetKeyboard().IsKeyDown(GLFW_KEY_DOWN))
  {
    mWorld->GetPlayer()->Rotate({ speedRot, 0.0f, 0.0f });
    mCamera.Rotate({ speedRot, 0.0f, 0.0f });
  }
  if (mWindow->GetKeyboard().IsKeyDown(GLFW_KEY_UP))
  {
    mWorld->GetPlayer()->Rotate({ -speedRot, 0.0f, 0.0f });
    mCamera.Rotate({ -speedRot, 0.0f, 0.0f });
  }

  auto moved = mWindow->GetMouse().GetMoved();
  moved *= static_cast<float>(dt) * 0.07f;
  mWorld->GetPlayer()->Rotate(glm::vec3(moved.y, 0.0f, moved.x));
  mCamera.Rotate(glm::vec3(moved.y, 0.0f, moved.x));

  static float k = 1.0f;
  if (mWindow->GetKeyboard().IsKeyPress(GLFW_KEY_9))
  {
    k += 1.0f;
  }
  if (mWindow->GetKeyboard().IsKeyPress(GLFW_KEY_0))
  {
    k -= 1.0f;
  }
  if (k < 1.0f)
  {
    k = 1.0f;
  }
  float speedMov = static_cast<float>(15.0 * dt) * k;

  if (mWindow->GetKeyboard().IsKeyDown(GLFW_KEY_D))
  {
    mWorld->GetPlayer()->Move({ speedMov, 0.0f, 0.0f });
  }
  if (mWindow->GetKeyboard().IsKeyDown(GLFW_KEY_A))
  {
    mWorld->GetPlayer()->Move({ -speedMov, 0.0f, 0.0f });
  }
  if (mWindow->GetKeyboard().IsKeyDown(GLFW_KEY_W))
  {
    mWorld->GetPlayer()->Move({ 0.0f, speedMov, 0.0f });
  }
  if (mWindow->GetKeyboard().IsKeyDown(GLFW_KEY_S))
  {
    mWorld->GetPlayer()->Move({ 0.0f, -speedMov, 0.0f });
  }

  SPos secPos = cs::WtoS(mWorld->GetPlayer()->GetPosition());
  secPos.z = 0;

  SPos offsets[8] =
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
    mWorld->GetSector(secPos + i);
  }

  mWorld->Update();
}


void Game::Draw(double dt)
{
  mCamera.SetPos(mWorld->GetPlayer()->GetPosition() + glm::vec3{ 0.0f, 0.0f, 1.7f });
  mCamera.Update();



  GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));     // Очистка экрана

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(mCamera.GetProject()));

  glMatrixMode(GL_MODELVIEW);
  GL_CALL(glLoadIdentity());                               // Сброс просмотра
  glLoadMatrixf(glm::value_ptr(mCamera.GetView()));
  //GL_CALL(glTranslatef(0.5f, 0.5f, 0.5f));

  mWorld->Draw(*mRender);
}

