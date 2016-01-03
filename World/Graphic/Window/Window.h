// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#ifndef WINDOW_GL_H
#define WINDOW_GL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Keyboard.h"
#include "Mouse.h"
#include <functional>


class Window
{
public:
  Window(const glm::uvec2 &size);
  ~Window();

  /// Инициализация оконной системы.
  static void WindowSystemInitialize();

  /// Завершить работу с оконной системой.
  static void WindowSystemFinally();

  /// Обработать события.
  static void WindowSystemPollEvents();

  /// Установить текущий контекст для данного окна.
  void SetCurrentContext();

  /// Должно ли окно закрыться?
  bool WindowShouldClose();

  /// Переключить буферы.
  void SwapBuffers();

  const glm::uvec2 &GetSize() const;

  void SetResizeCallback(std::function<void(glm::uvec2)> callback);

  /// Установить имя окна.
  void SetTitle(const std::string &title);

  /// Получить клавиатуру.
  Keyboard &GetKeyboard();

  /// Получить мышь.
  Mouse &GetMouse();

private:

  struct WindowDeleter
  {
    void operator()(GLFWwindow *window) const
    {
      printf("window delete\n");
      glfwDestroyWindow(window);
    }
  };

  std::unique_ptr<GLFWwindow, WindowDeleter> mWindow;

  std::unique_ptr<Keyboard> mKeyboard;

  Mouse mMouse;

  std::function<void(glm::uvec2)> mResizeCallback;

  glm::uvec2 mSize;

};

#endif // WINDOW_GL_H
