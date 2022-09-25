#include "include/physics.hpp"

collision physics::collisionCheck(onmyouDama &one, gameObject &two) // AABB - Circle collision
{
    // 取得圆心
    glm::vec2 center(one.position + one.radius);
    // 计算矩形半长和中心
    glm::vec2 aabb_half_extents(two.size.x / 2.0f, two.size.y / 2.0f);
    glm::vec2 aabb_center(
        two.position.x + aabb_half_extents.x,
        two.position.y + aabb_half_extents.y);
    // 差向量
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents); // 取最小
    // 圆与矩形最近点
    glm::vec2 closest = aabb_center + clamped;
    // 计算圆心与最近点第距离
    difference = closest - center;
    // return glm::length(difference) < one.radius;

    if (glm::length(difference) <= one.radius)
    {
        return std::make_tuple(true, vectorDirection(difference), difference);
    }
    else
    {
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
    }
}

direction physics::vectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),  // up
        glm::vec2(1.0f, 0.0f),  // right
        glm::vec2(0.0f, -1.0f), // down
        glm::vec2(-1.0f, 0.0f)  // left
    };
    float max = 0.0f;
    uint32_t bestMatch = -1;
    for (uint32_t i = 0; i < 4; i++)
    {
        float dotProd = glm::dot(glm::normalize(target), compass[i]); // 点乘（基底）以得到角度的余弦
        if (dotProd > max)
        {
            max = dotProd;
            bestMatch = i;
        }
    }
    return (direction)bestMatch;
}
