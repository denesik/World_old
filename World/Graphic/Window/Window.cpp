// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Window.h"

#include <assert.h>
#include <iostream>

Window::Window(const glm::uvec2 &size)
  : mSize(size),
    mKeyboard(new Keyboard())
{
  std::cout << "Start window creating" << std::endl;

  GLFWmonitor *monitor = nullptr;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  //mWindow = (decltype(mWindow))(glfwCreateWindow(mSize.x, mSize.y, "title", monitor, nullptr));

  if (!mWindow)
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 0);

    mWindow = (decltype(mWindow))(glfwCreateWindow(mSize.x, mSize.y, "title", monitor, nullptr));
  }

  if (!mWindow)
  {
    throw "Window not created.";
  }

  /// Привязываем к glfw окну указатель на объект WindowGL.
  glfwSetWindowUserPointer(mWindow.get(), this);

  glfwSetKeyCallback(mWindow.get(), [](GLFWwindow *win, int key, int scancode, int action, int mods)
  {
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(win));
    assert(window);
    window->mKeyboard->SetKey(key, scancode, action, mods);
  });

  glfwSetCursorPosCallback(mWindow.get(), [](GLFWwindow *win, double x, double y)
  {
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(win));
    assert(window);
    window->mMouse.SetPos(glm::vec2(static_cast<float>(x), static_cast<float>(y)));
  });

  std::cout << "Window created" << std::endl;
}

Window::~Window()
{
}


// void Window::GlfwResizeCallback(GLFWwindow* window, int width, int height)
// {
//   Window *windowGL = static_cast<Window *>(glfwGetWindowUserPointer(window));
//   if(windowGL && windowGL->mResizeCallback)
//   {
//     windowGL->mResizeCallback(glm::uvec2(width, height));
//   }
// }

void Window::WindowSystemInitialize()
{
  glfwSetErrorCallback([](int ,const char* description)
    {
      std::cout << description << std::endl;
    });

  if (glfwInit() != GL_TRUE)
  {
    throw "GLFW not initialized.";
  }
}

void Window::WindowSystemFinally()
{
  glfwTerminate();
}

void Window::WindowSystemPollEvents()
{
  glfwPollEvents();
}

void Window::SetCurrentContext()
{
  assert(mWindow);
  glfwMakeContextCurrent(mWindow.get());

  glfwSwapInterval(0);

  const GLubyte* renderer = glGetString (GL_RENDERER);
  const GLubyte* version = glGetString (GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl
    << "OpenGL version supported: " << version << std::endl;
}

bool Window::WindowShouldClose()
{
  assert(mWindow);
  return glfwWindowShouldClose(mWindow.get()) == GL_TRUE;
}

void Window::SwapBuffers()
{
  assert(mWindow);
  glfwSwapBuffers(mWindow.get());
}

const glm::uvec2 & Window::GetSize() const
{
  return mSize;
}

Keyboard &Window::GetKeyboard()
{
  return *mKeyboard;
}

void Window::SetResizeCallback(std::function<void(glm::uvec2)> callback)
{
  mResizeCallback = callback;
}

void Window::SetTitle(const std::string &title)
{
  assert(mWindow);
  glfwSetWindowTitle(mWindow.get(), title.c_str());
}

Mouse & Window::GetMouse()
{
  return mMouse;
}





