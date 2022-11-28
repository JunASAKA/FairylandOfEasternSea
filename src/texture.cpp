
#include "include/texture.hpp"

#include <iostream>

texture_2D::texture_2D()
    : width(0), height(0), internal_format(GL_RGB), image_format(GL_RGB), wrap_s(GL_REPEAT), wrap_t(GL_REPEAT), filter_min(GL_LINEAR), filter_max(GL_LINEAR)
{
    glGenTextures(1, &this->id);
}

void texture_2D::generate(uint32_t width, uint32_t height, unsigned char *data)
{
    this->width = width;
    this->height = height;
    // 创建纹理
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0, this->image_format, GL_UNSIGNED_BYTE, data);
    // 设置各种属性
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
    // 解绑纹理
    glBindTexture(GL_TEXTURE_2D, 0);

    return;
}

const void texture_2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->id);

    return;
}