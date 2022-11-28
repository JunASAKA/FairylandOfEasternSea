#pragma once

#include "game_object.hpp"

// 自机，继承自game_object
class playable_character : public game_object
{

public:
    uint8_t status;

    playable_character();
    playable_character(glm::vec2 pos, glm::vec2 size, texture_2D sprite, glm::vec2 tex_pos, glm::vec2 tex_size, glm::vec2 image_size, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 colour = glm::vec3(1.0f), bool mirror = false, uint8_t status = 0);
};