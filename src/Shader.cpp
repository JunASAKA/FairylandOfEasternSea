#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Shader.hpp"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {

  std::ifstream vertexFile;
  std::ifstream fragmentFile;
  std::stringstream vertexSStream;
  std::stringstream fragmentSStream;

  vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {

    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);
    if (!vertexFile.is_open() || !fragmentFile.is_open()) {
      throw std::logic_error("ＧＬＳＬ文件读取失败。\n");
    }

    vertexSStream << vertexFile.rdbuf();
    fragmentSStream << fragmentFile.rdbuf();

    vertexStr = vertexSStream.str();
    fragmentStr = fragmentSStream.str();

    vertexSource = vertexStr.c_str();
    fragmentSource = fragmentStr.c_str();

    printf("%s%s", vertexSource, fragmentSource);

  } catch (std::ifstream::failure &e) {
    printf("%s", e.what());
  }
}