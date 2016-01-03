// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Shader.h"


#include <GL/glew.h>
#include <vector>
#include <assert.h>
#include <fstream>
#include "OpenGLCall.h"

Shader::Shader(const std::string &shaderName)
{
  // Читаем и создаем шейдеры.
  // Если файл не существует, шейдер не создается.
  std::vector<int> shaders;

  try
  {
    shaders.push_back(CreateShader(ReadTxtFile(shaderName + ".vs"), GL_VERTEX_SHADER));
    shaders.push_back(CreateShader(ReadTxtFile(shaderName + ".fs"), GL_FRAGMENT_SHADER));
  }
  catch (char *)
  {
    // Удалим все созданные шейдеры.
    for (auto it = shaders.begin(); it != shaders.end(); ++it)
    {
      DeleteShader(*it);
    }
    throw;
  }

  // Пытаемся собрать программу из всех прочитанных шейдеров.
  GL_CALL(mProgram = glCreateProgram());
  for (auto it = shaders.begin(); it != shaders.end(); ++it)
  {
    if (*it)
    {
      GL_CALL(glAttachShader(mProgram, *it));
    }
  }
  GL_CALL(glLinkProgram(mProgram));

  // Удаляем шейдеры.
  for (auto it = shaders.begin(); it != shaders.end(); ++it)
  {
    DeleteShader(*it);
  }

  // Проверяем статус линковки
  GLint link = GL_FALSE;
  GL_CALL(glGetProgramiv(mProgram, GL_LINK_STATUS, &link));
  if (link != GL_TRUE || glGetError())
  {
    GLint linkerLogSize = 0;
    GL_CALL(glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &linkerLogSize));
    if (linkerLogSize)
    {
      std::string linkerLog(linkerLogSize, '\0');
      GL_CALL(glGetProgramInfoLog(mProgram, linkerLogSize, NULL, &linkerLog[0]));
    }

    GL_CALL(glDeleteProgram(mProgram));
    throw "Shader not created.";
  }
}


Shader::~Shader()
{
  GL_CALL(glDeleteProgram(mProgram));
}

void Shader::Use()
{
  GL_CALL(glUseProgram(mProgram));
}

unsigned int Shader::CreateShader(const std::string &data, int type)
{
  if (data.empty())
  {
    return 0;
  }

  GLuint shader = 0;
  //GL_CALL(shader = glCreateShader(type));
  shader = glCreateShader(type);

  if (glGetError())
  {
    throw "Shader not created.";
  }

  char const *sourcePointer = data.c_str();
  GL_CALL(glShaderSource(shader, 1, &sourcePointer, NULL));
  GL_CALL(glCompileShader(shader));

  GLint compiled = GL_FALSE;
  GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled));

  if (compiled != GL_TRUE || glGetError())
  {
    int infoLogLength = 0;
    GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength));
    if (infoLogLength)
    {
      std::vector<char> VertexShaderErrorMessage(infoLogLength);
      GL_CALL(glGetShaderInfoLog(shader, infoLogLength, NULL, &VertexShaderErrorMessage[0]));
    }

    GL_CALL(glDeleteShader(shader));
    throw "Shader not created.";
  }

  return shader;
}

void Shader::DeleteShader(unsigned int shader)
{
  GL_CALL(glDeleteShader(shader));
}

std::string Shader::ReadTxtFile(const std::string &fileName)
{
  std::string code;
  std::ifstream file(fileName, std::ios::in);
  if (file.is_open())
  {
    std::string line = "";
    while (getline(file, line))
      code += "\n" + line;
    file.close();
  }

  return code;
}

bool Shader::SetUniform_(const glm::mat4 &val, const char *name)
{
  int location = GetUniformLocation(name);
  if (location >= 0)
  {
    GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, &val[0][0]));
  }
  return (location >= 0);
}

bool Shader::SetUniform_(int val, const char *name)
{
  int location = GetUniformLocation(name);
  if (location >= 0)
  {
    GL_CALL(glUniform1i(location, val));
  }
  return (location >= 0);
}

bool Shader::SetUniform_(const glm::vec4 &val, const char *name)
{
  int location = GetUniformLocation(name);
  if (location >= 0)
  {
    GL_CALL(glUniform4fv(location, 1, &val[0]));
  }
  return (location >= 0);
}

bool Shader::SetUniform_(const glm::vec3 &val, const char *name)
{
  int location = GetUniformLocation(name);
  if (location >= 0)
  {
    GL_CALL(glUniform3fv(location, 1, &val[0]));
  }
  return (location >= 0);
}

bool Shader::SetUniform_(const glm::vec2 &val, const char *name)
{
  int location = GetUniformLocation(name);
  if (location >= 0)
  {
    GL_CALL(glUniform2fv(location, 1, &val[0]));
  }
  return (location >= 0);
}

int Shader::GetUniformLocation(const char *name)
{
  auto it = mUniforms.find(name);
  if (it == mUniforms.end())
  {
    int location = 0;
    GL_CALL(location = glGetUniformLocation(mProgram, name));
    if (location >= 0)
    {
      mUniforms.insert({ name, location });
    }
    return location;
  }
  
  return (*it).second;
}
