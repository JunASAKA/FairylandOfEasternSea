
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"
#include "Texture.hpp"

class ResourceManager {
public:
  /*资源文件储存*/
  static std::map<std::string, Shader> Shaders;
  static std::map<std::string, Texture2D> Textures;

  static Shader LoadShader(const char *vertShaderFile,
                           const char *frageomShaderFile,
                           const char *geomShaderFile,
                           std::string name); //从文件生成三种着色器
  static Shader GetShader(std::string name);  //索取储存的着色器
  static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
  static Texture2D GetTexture(std::string name);
  static void Clear(); //清空资源文件储存
private:
  ResourceManager() {} //建构函数（无需对象）
  /*内部用函数*/
  static Shader loadShaderFromFile(const char *vertShaderFile,
                                   const char *frageomShaderFile,
                                   const char *geomShaderFile = nullptr);
  static Texture2D loadTextureFromFile(const char *file, bool alpha);
};

#endif