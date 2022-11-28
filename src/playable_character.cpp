#include "include/playable_character.hpp"

// 管理自机
playable_character::playable_character()
    : game_object(), status(0) {}

playable_character::playable_character(glm::vec2 pos, glm::vec2 size, texture_2D sprite, glm::vec2 tex_pos, glm::vec2 tex_size, glm::vec2 image_size, glm::vec2 velocity, glm::vec3 colour, bool mirror, uint8_t status)
    : game_object(pos, size, sprite, tex_pos, tex_size, image_size, velocity, colour, false), status(0) {}
