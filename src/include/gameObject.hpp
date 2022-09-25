#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "texture.hpp"
#include "spriteRenderer.hpp"

class gameObject
{
public:
    // 属性
    glm::vec2 position, size, velocity;
    glm::vec3 colour;
    glm::vec2 texPos, texSize, imageSize;
    float rotation;
    bool isSolid;
    bool destroyed;
    bool mirror;
    // uint8_t status;

    texture2D sprite;
    // 建构函数
    gameObject();
    // 座标 尺寸 精灵对象 贴图座标 贴图尺寸 原图尺寸 速度 颜色
    gameObject(glm::vec2 pos, glm::vec2 size, texture2D sprite, glm::vec2 texPos, glm::vec2 texSize, glm::vec2 imageSize, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 colour = glm::vec3(1.0f), bool mirror = false);
    // 绘制用函数
    virtual void draw(spriteRenderer &renderer);
};
