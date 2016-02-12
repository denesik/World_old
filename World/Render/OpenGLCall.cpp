#include "OpenGLCall.h"
#include "..\tools\Log.h"



void CheckErrorsReal(const char *func, const char *file, long line)
{
  while (unsigned int openGLError = glGetError())
  {
    LOG(error) << "GL Error." << std::endl
      << "[" << std::endl
      << "  function: " << func << std::endl
      << "  error: " << openGLError << std::endl
      << "  file: " << file << std::endl
      << "  line: " << line << std::endl
      << "]";
  };
}

void CheckErrorsFake(const char *, const char *, long)
{

}
