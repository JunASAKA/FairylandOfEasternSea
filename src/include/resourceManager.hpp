
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "texture.hpp"


class resourceManager
{
public:
    // 用于储存的静态变量
    static std::map<std::string, shader>    shaders;
    static std::map<std::string, texture2D> textures;
    // 从源代码加载着色器并储存
    static shader    loadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    // 读取已储存的着色器
    static shader    getShader(std::string name);
    // 从图片加载纹理并储存
    static texture2D loadTexture(const char *file, bool alpha, std::string name);
    // 读取已储存的纹理
    static texture2D getTexture(std::string name);
    // 删除所有已储存的资源
    static void      clear();
private:
    // 建构函数
    resourceManager() { }
    // 从源代码加载着色器
    static shader    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    // 从图片加载纹理
    static texture2D loadTextureFromFile(const char *file, bool alpha);
};

#endif