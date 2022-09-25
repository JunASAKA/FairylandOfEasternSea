#include "include/playableCharacter.hpp"

// 管理自机
playableCharacter::playableCharacter()
    : gameObject(), status(0) {}

playableCharacter::playableCharacter(glm::vec2 pos, glm::vec2 size, texture2D sprite, glm::vec2 texPos, glm::vec2 texSize, glm::vec2 imageSize, glm::vec2 velocity, glm::vec3 colour, bool mirror, uint8_t status)
    : gameObject(pos, size, sprite, texPos, texSize, imageSize, velocity, colour, false), status(0) {}
