#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Shader.hpp"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {

  /*读入ＧＬＳＬ源文件*/
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

    /*编译Ｓｈａｄｅｒ*/
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vertexSource, NULL);
    glShaderSource(fragment, 1, &fragmentSource, NULL);

    glCompileShader(vertex);
    glCompileShader(fragment);

    checkShaderError(vertex, "SHADER");
    checkShaderError(fragment, "SHADER"); //纠错

    /*创建并连结Ｓｈａｄｅｒ　Ｐｒｏｇｒａｍ*/
    ShaderProgramID = glCreateProgram();
    glAttachShader(ShaderProgramID, vertex);
    glAttachShader(ShaderProgramID, fragment);
    glLinkProgram(ShaderProgramID);

    checkShaderError(ShaderProgramID, "PROGRAM"); //纠错

    /*删除用过的Ｓｈａｄｅｒ*/
    glDeleteShader(vertex);
    glDeleteShader(fragment);

  } catch (std::ifstream::failure &e) {
    printf("%s", e.what());
  }
}

void Shader::useShaderProgram() { glUseProgram(Shader::ShaderProgramID); }

void Shader::checkShaderError(GLuint id, std::string type) {
  GLint success;
  GLchar errInfo[1024];

  if (type == "PROGRAM") {
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (success) {
      printf("Ｓｈａｄｅｒ　Ｐｒｏｇｒａｍ连结成功。\n");
    } else {
      glGetProgramInfoLog(id, 1024, NULL, errInfo);
      printf("Ｓｈａｄｅｒ　Ｐｒｏｇｒａｍ连结出错：%s", errInfo);
    }
  } else if (type == "SHADER") {
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success) {
      printf("Ｓｈａｄｅｒ编译成功。\n");
    } else {
      glGetShaderInfoLog(id, 1024, NULL, errInfo);
      printf("Ｓｈａｄｅｒ编译出错：%s", errInfo);
    }
  } else {
    printf("未知纠错目标类型：%s", type.c_str());
  }
}