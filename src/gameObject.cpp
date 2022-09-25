#include "include/gameObject.hpp"

gameObject::gameObject()
    : position(0.0f, 0.0f), size(1.0f, 1.0f), imageSize(), texSize(), texPos(), velocity(), colour(1.0f), rotation(0.0f), sprite(), isSolid(false), destroyed(false) {}

gameObject::gameObject(glm::vec2 pos, glm::vec2 size, texture2D sprite, glm::vec2 texPos, glm::vec2 texSize, glm::vec2 imageSize, glm::vec2 velocity, glm::vec3 colour, bool mirror)
    : position(pos), size(size), velocity(velocity), colour(colour), rotation(0.0f), sprite(sprite), texPos(texPos), texSize(texSize), imageSize(imageSize), isSolid(false), destroyed(false), mirror(false) {}

void gameObject::draw(spriteRenderer &renderer)
{
    renderer.drawSprite(this->sprite, this->position, this->size, this->texPos, this->texSize, this->imageSize, this->rotation, this->colour, this->mirror);

    return;
}