#include "include/resource_manager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <fstream>
#include <iostream>
#include <sstream>

#include "include/stb_image.hpp"

// 实例化用于储存的静态变量
std::map<std::string, texture_2D> resource_manager::textures;
std::map<std::string, shader> resource_manager::shaders;

shader resource_manager::load_shader(const char *vertex_shader_src,
                                   const char *frag_shader_src,
                                   const char *geo_shader_src, std::string name)
{
    shaders[name] = load_shaderFromFile(vertex_shader_src, frag_shader_src, geo_shader_src);
    return shaders[name];
}

shader resource_manager::get_shader(std::string name) { return shaders[name]; }

texture_2D resource_manager::load_texture(const char *file, bool alpha,
                                       std::string name)
{
    textures[name] = load_texture_from_file(file, alpha);
    return textures[name];
}

texture_2D resource_manager::get_texture(std::string name)
{
    return textures[name];
}

void resource_manager::clear()
{
    // 删除已储存的着色器
    for (auto iter : shaders)
    {
        glDeleteProgram(iter.second.id);
    }
    // 删除已储存的纹理
    for (auto iter : textures)
    {
        glDeleteTextures(1, &iter.second.id);
    }

    return;
}

shader resource_manager::load_shaderFromFile(const char *vertex_shader_src,
                                           const char *frag_shader_src,
                                           const char *geo_shader_src)
{

    std::string vertex_code;
    std::string fragment_code;
    std::string geometry_code;
    try
    {
        // 标记打开文件
        std::ifstream vertex_shader_file(vertex_shader_src);
        std::ifstream fragment_shader_file(frag_shader_src);
        std::stringstream vertex_shader_stream, frag_shader_stream;
        // 将文件缓冲读入流
        vertex_shader_stream << vertex_shader_file.rdbuf();
        frag_shader_stream << fragment_shader_file.rdbuf();
        // 标记关闭文件
        vertex_shader_file.close();
        fragment_shader_file.close();
        // 读入string
        vertex_code = vertex_shader_stream.str();
        fragment_code = frag_shader_stream.str();
        // 处理可有可无的几何着色器源码
        if (geo_shader_src != nullptr)
        {
            std::ifstream geo_shader_file(geo_shader_src);
            std::stringstream geo_shader_stream;
            geo_shader_stream << geo_shader_file.rdbuf();
            geo_shader_file.close();
            geometry_code = geo_shader_stream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "【ERROR】シェーダーのソースコードファイルを読み取れない。"
                  << std::endl;
    }
    const char *vertex_shader_code = vertex_code.c_str();
    const char *frag_shader_code = fragment_code.c_str();
    const char *geo_shader_code = geometry_code.c_str();
    // 创建并编译着色器
    shader shader;
    shader.compile(vertex_shader_code, frag_shader_code,
                   geo_shader_src != nullptr ? geo_shader_code : nullptr);
    return shader;
}

texture_2D resource_manager::load_texture_from_file(const char *file, bool alpha)
{
    // 创建纹理
    texture_2D texture;
    if (alpha)
    {
        texture.internal_format = GL_RGBA;
        texture.image_format = GL_RGBA;
    }
    // 加载图像
    int32_t width, height, nr_channels;
    unsigned char *data = stbi_load(file, &width, &height, &nr_channels, 0);

    // 生成纹理
    // texture.generate((endX-startX), (endY-startY), dataFin);
    texture.generate(width, height, data);
    // 释放图像
    stbi_image_free(data);
    // stbi_image_free(dataFin);
    return texture;
}
