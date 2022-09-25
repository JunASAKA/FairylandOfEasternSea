#pragma once

#include "gameObject.hpp"

// 自机，继承自gameObject
class playableCharacter : public gameObject
{

public:
    uint8_t status;

    playableCharacter();
    playableCharacter(glm::vec2 pos, glm::vec2 size, texture2D sprite, glm::vec2 texPos, glm::vec2 texSize, glm::vec2 imageSize, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 colour = glm::vec3(1.0f), bool mirror = false, uint8_t status = 0);
};