#include "include/ResourceManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

/*实例化储存资源用静态变量*/
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char *vertShaderFile,
                                   const char *fregeomShaderFile,
                                   const char *geomShaderFile,
                                   std::string name)
{
  Shaders[name] =
      loadShaderFromFile(vertShaderFile, fregeomShaderFile, geomShaderFile);
  return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name) { return Shaders[name]; }

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha,
                                       std::string name)
{
  Textures[name] = loadTextureFromFile(file, alpha);
  return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
  return Textures[name];
}

void ResourceManager::Clear()
{
  for (auto iter : Shaders)
    glDeleteProgram(iter.second.ID);
  for (auto iter : Textures)
    glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char *vertShaderFile,
                                           const char *fregeomShaderFile,
                                           const char *geomShaderFile)
{
  /*读取着色器源代码*/
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;
  try
  {
    /*标记打开文件*/
    std::ifstream vertexShaderFile(vertShaderFile);
    std::ifstream fragmentShaderFile(fregeomShaderFile);
    std::stringstream vertShaderStream, frageomShaderStream;
    /*读取*/
    vertShaderStream << vertexShaderFile.rdbuf();
    frageomShaderStream << fragmentShaderFile.rdbuf();
    /*标记关闭文件*/
    vertexShaderFile.close();
    fragmentShaderFile.close();
    /*存入字符串变量*/
    vertexCode = vertShaderStream.str();
    fragmentCode = frageomShaderStream.str();
    /*针对指定源代码的几何着色器*/
    if (geomShaderFile != nullptr)
    {
      std::ifstream geometryShaderFile(geomShaderFile);
      std::stringstream geomShaderStream;
      geomShaderStream << geometryShaderFile.rdbuf();
      geometryShaderFile.close();
      geometryCode = geomShaderStream.str();
    }
  }
  catch (std::exception e)
  {
    std::cout << "【错误】：读取着色器文件失败。" << std::endl;
  }
  const char *vertShaderCode = vertexCode.c_str();
  const char *frageomShaderCode = fragmentCode.c_str();
  const char *geomShaderCode = geometryCode.c_str();
  /*生成着色器*/
  Shader shader;
  shader.Compile(vertShaderCode, frageomShaderCode,
                 geomShaderFile != nullptr ? geomShaderCode : nullptr);
  return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
  Texture2D texture;
  if (alpha)
  {
    texture.Internal_Format = GL_RGBA;
    texture.Image_Format = GL_RGBA;
  }
  /*加载贴图*/
  int width, height, nrChannels;
  unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
  texture.Generate(width, height, data); //生成贴图
  stbi_image_free(data);                 //释放图片
  return texture;
}