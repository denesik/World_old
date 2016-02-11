// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Shader_h__
#define Shader_h__


#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader;
typedef std::shared_ptr<Shader> PShader;

/// Шейдер.
class Shader
{
public:
  Shader(const std::string &shaderName);
  ~Shader();

  /// Установить шейдер.
  void Use();

  template<class T>
  bool SetUniform(const T &val, const char *name = "")
  {
    return SetUniform_(val, name);
  };

#define UNIFORM_QUOTE(name) #name
#define UNIFORM_MAKE_STR(macro) UNIFORM_QUOTE(macro)
#define SetUniform(val) SetUniform(val, UNIFORM_MAKE_STR(val))

private:

  unsigned int mProgram;

private:

  /// Загрузить шейдер.
  unsigned int CreateShader(const std::string &data, int type);

  /// Удалить шейдер
  void DeleteShader(unsigned int shader);

  /// Прочитать файл.
  std::string ReadTxtFile(const std::string &fileName);

  int GetUniformLocation(const char *name);

private:

  bool SetUniform_(const glm::mat4 &val, const char *name);

  bool SetUniform_(int val, const char *name);

  bool SetUniform_(const glm::vec4 &val, const char *name);

  bool SetUniform_(const glm::vec3 &val, const char *name);

  bool SetUniform_(const glm::vec2 &val, const char *name);

private:

  std::unordered_map<std::string, int> mUniforms;

};


#endif // Shader_h__
