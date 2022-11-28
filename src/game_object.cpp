#include "include/game_object.hpp"

game_object::game_object()
    : position(0.0f, 0.0f), size(1.0f, 1.0f), image_size(), tex_size(), tex_pos(), velocity(), colour(1.0f), rotation(0.0f), sprite(), is_solid(false), destroyed(false) {}

game_object::game_object(glm::vec2 pos, glm::vec2 size, texture_2D sprite, glm::vec2 tex_pos, glm::vec2 tex_size, glm::vec2 image_size, glm::vec2 velocity, glm::vec3 colour, bool mirror)
    : position(pos), size(size), velocity(velocity), colour(colour), rotation(0.0f), sprite(sprite), tex_pos(tex_pos), tex_size(tex_size), image_size(image_size), is_solid(false), destroyed(false), mirror(false) {}

void game_object::draw(sprite_renderer &renderer)
{
    renderer.draw_sprite(this->sprite, this->position, this->size, this->tex_pos, this->tex_size, this->image_size, this->rotation, this->colour, this->mirror);

    return;
}