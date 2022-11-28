#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "texture.hpp"
#include "sprite_renderer.hpp"

class game_object
{
public:
    // 属性
    glm::vec2 position, size, velocity;
    glm::vec3 colour;
    glm::vec2 tex_pos, tex_size, image_size;
    float rotation;
    bool is_solid;
    bool destroyed;
    bool mirror;
    // uint8_t status;

    texture_2D sprite;
    // 建构函数
    game_object();
    // 座标 尺寸 精灵对象 贴图座标 贴图尺寸 原图尺寸 速度 颜色
    game_object(glm::vec2 pos, glm::vec2 size, texture_2D sprite, glm::vec2 tex_pos, glm::vec2 tex_size, glm::vec2 image_size, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 colour = glm::vec3(1.0f), bool mirror = false);
    // 绘制用函数
    virtual void draw(sprite_renderer &renderer);
};
