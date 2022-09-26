#include "include/onmyouDama.hpp"

onmyouDama::onmyouDama()
    : gameObject(), radius(12.5f), stuck(true) {}

onmyouDama::onmyouDama(glm::vec2 pos, glm::vec2 texPos, glm::vec2 texSize, glm::vec2 imageSize, float radius, glm::vec2 velocity, texture2D sprite)
    : gameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, texPos, texSize, imageSize, velocity), radius(radius), stuck(true) {}

glm::vec2 onmyouDama::move(float deltaT, uint32_t windowWidth)
{
    if (!this->stuck)
    {
        this->position += this->velocity * deltaT;
        // 与边界碰撞
        if (this->position.x <= 0.0f)
        {
            this->velocity.x *= -1;
            this->position.x = 0.0f;
        }
        else if (this->position.x + this->size.x >= windowWidth)
        {
            this->velocity.x *= -1;
            this->position.x = windowWidth - this->size.x;
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
void onmyouDama::reset(glm::vec2 position, glm::vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;
    this->stuck = true;

    return;
}
