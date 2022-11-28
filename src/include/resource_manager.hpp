#pragma once

#include <map>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "texture.hpp"

class resource_manager
{
public:
    // 用于储存的静态变量
    static std::map<std::string, shader> shaders;
    static std::map<std::string, texture_2D> textures;
    // 从源代码加载着色器并储存
    static shader load_shader(const char *vertex_shader_src, const char *frag_shader_src,
                             const char *geo_shader_src, std::string name);
    // 读取已储存的着色器
    static shader get_shader(std::string name);
    // 从图片加载纹理并储存
    static texture_2D load_texture(const char *file, bool alpha, std::string name);
    // 读取已储存的纹理
    static texture_2D get_texture(std::string name);
    // 删除所有已储存的资源
    static void clear();

private:
    // 建构函数
    resource_manager() {}
    // 从源代码加载着色器
    static shader load_shaderFromFile(const char *vertex_shader_src,
                                     const char *frag_shader_src,
                                     const char *geo_shader_src = nullptr);
    // 从图片加载纹理
    static texture_2D load_texture_from_file(const char *file, bool alpha);
};
