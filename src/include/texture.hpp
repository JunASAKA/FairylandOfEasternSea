#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class texture_2D
{
public:
    // id
    uint32_t id;
    // 材质大小
    uint32_t width, height;
    // 格式
    uint32_t internal_format; // 内部材质对象
    uint32_t image_format;    // 材质图片
    // 属性
    uint32_t wrap_s;     // S轴wrapping mode
    uint32_t wrap_t;     // T轴wrapping mode
    uint32_t filter_min; // 放大用filtering mode
    uint32_t filter_max; // 缩小用filtering mode
    // 建构函数，用于设置缺省属性
    texture_2D();
    // 从读入的图片data生成材质
    void generate(uint32_t width, uint32_t height, unsigned char *data);
    // 将纹理与激活的GL_TEXTURE_2D绑定
    const void bind();
};
