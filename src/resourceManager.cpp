#include "include/resourceManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <fstream>
#include <iostream>
#include <sstream>

#include "include/stb_image.hpp"


// 实例化用于储存的静态变量
std::map<std::string, texture2D>    resourceManager::textures;
std::map<std::string, shader>       resourceManager::shaders;


shader resourceManager::loadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaders[name];
}

shader resourceManager::getShader(std::string name)
{
    return shaders[name];
}

texture2D resourceManager::loadTexture(const char *file, bool alpha, std::string name)
{
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

texture2D resourceManager::getTexture(std::string name)
{
    return textures[name];
}

void resourceManager::clear()
{
    // 删除已储存的着色器	
    for (auto iter : shaders)
        glDeleteProgram(iter.second.ID);
    // 删除已储存的纹理
    for (auto iter : textures)
        glDeleteTextures(1, &iter.second.ID);
}

shader resourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // 标记打开文件
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // 将文件缓冲读入流
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // 标记关闭文件
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // 读入string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // 处理可有可无的几何着色器源码
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "【ERROR】シェーダーのソースコードファイルを読み取れない。" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
    // 创建并编译着色器
    shader shader;
    shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

texture2D resourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    // 创建纹理
    texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // 加载图像
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // 生成纹理
    texture.generate(width, height, data);
    // 释放图像
    stbi_image_free(data);
    return texture;
}