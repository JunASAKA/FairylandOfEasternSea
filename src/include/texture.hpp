
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class texture2D
{
public:
    // ID
    uint32_t ID;
    // 材质大小
    uint32_t Width, Height;
    // 格式
    uint32_t Internal_Format; // 内部材质对象
    uint32_t Image_Format; // 材质图片
    // 属性
    uint32_t Wrap_S; // S轴wrapping mode
    uint32_t Wrap_T; // T轴wrapping mode
    uint32_t Filter_Min; // 放大用filtering mode
    uint32_t Filter_Max; // 缩小用filtering mode
    // 建构函数，用于设置缺省属性
    texture2D();
    // 从读入的图片data生成材质
    void generate(uint32_t width, uint32_t height, unsigned char* data);
    // 将纹理与激活的GL_TEXTURE_2D绑定
    const void bind();

};

#endif