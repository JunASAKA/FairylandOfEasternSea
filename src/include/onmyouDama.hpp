#pragma once

#include "gameObject.hpp"

class onmyouDama : public gameObject
{
public:
    float radius; // 半径
    bool stuck;   // 是否固定在自机身上

    // 建构函数
    onmyouDama();
    onmyouDama(glm::vec2 pos, glm::vec2 texPos, glm::vec2 texSize, glm::vec2 imageSize, float radius, glm::vec2 velocity, texture2D sprite);

    glm::vec2 move(float deltaT, uint32_t windowWidth); // 移动
    void reset(glm::vec2 position, glm::vec2 velocity); // 重置
};