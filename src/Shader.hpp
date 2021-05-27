#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
public:
  Shader(const char *vertexPath, const char *fragmentPath);
  std::string vertexStr;
  std::string fragmentStr;
  const char *vertexSource;
  const char *fragmentSource;
};
#endif