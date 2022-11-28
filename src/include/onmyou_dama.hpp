#pragma once

#include "game_object.hpp"

class onmyou_dama : public game_object
{
public:
    float radius; // 半径
    bool stuck;   // 是否固定在自机身上

    // 建构函数
    onmyou_dama();
    onmyou_dama(glm::vec2 pos, glm::vec2 tex_pos, glm::vec2 tex_size, glm::vec2 image_size, float radius, glm::vec2 velocity, texture_2D sprite);

    glm::vec2 move(float delta_t, uint32_t window_width); // 移动
    void reset(glm::vec2 position, glm::vec2 velocity); // 重置
};