#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class Shader {
public:
  Shader(const char *vertexPath, const char *fragmentPath);
  std::string vertexStr;
  std::string fragmentStr;
  const char *vertexSource;
  const char *fragmentSource;
  unsigned int ShaderProgramID;

  void useShaderProgram();

private:
  void checkShaderError(GLuint id, std::string type);

};
#endif