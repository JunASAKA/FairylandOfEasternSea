
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class texture2D
{
public:
    // ID
    unsigned int ID;
    // 材质大小
    unsigned int Width, Height; 
    // 格式
    unsigned int Internal_Format; // 内部材质对象
    unsigned int Image_Format; // 材质图片
    // 属性
    unsigned int Wrap_S; // S轴wrapping mode
    unsigned int Wrap_T; // T轴wrapping mode
    unsigned int Filter_Min; // 放大用filtering mode
    unsigned int Filter_Max; // 缩小用filtering mode
    // 建构函数，用于设置缺省属性
    texture2D();
    // 从读入的图片data生成材质
    void generate(unsigned int width, unsigned int height, unsigned char* data);
    // 将纹理与激活的GL_TEXTURE_2D绑定
    const void bind();
};

#endif