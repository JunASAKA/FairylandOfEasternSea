#include "include/onmyou_dama.hpp"

onmyou_dama::onmyou_dama()
    : game_object(), radius(12.5f), stuck(true) {}

onmyou_dama::onmyou_dama(glm::vec2 pos, glm::vec2 tex_pos, glm::vec2 tex_size, glm::vec2 image_size, float radius, glm::vec2 velocity, texture_2D sprite)
    : game_object(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, tex_pos, tex_size, image_size, velocity), radius(radius), stuck(true) {}

glm::vec2 onmyou_dama::move(float delta_t, uint32_t window_width)
{
    if (!this->stuck)
    {
        this->position += this->velocity * delta_t;
        // 与边界碰撞
        if (this->position.x <= 0.0f)
        {
            this->velocity.x *= -1;
            this->position.x = 0.0f;
        }
        else if (this->position.x + this->size.x >= window_width)
        {
            this->velocity.x *= -1;
            this->position.x = window_width - this->size.x;
        }
        if (this->position.y <= 0.0f)
        {
            this->velocity.y = -1.0f * abs(this->velocity.y);   // 解决阴阳玉嵌入自机内部而出现的碰撞检测问题
            this->position.y = 0.0f;
        }
        // if(this->position.y >= 480.0f)
        // {
        //     this->velocity.y *= -1;
        //     this->position.y = 480.0f;
        // }
    }
    return this->position;
}

// 初始化位置
void onmyou_dama::reset(glm::vec2 position, glm::vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;
    this->stuck = true;

    return;
}
