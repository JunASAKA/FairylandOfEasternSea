#include "include/physics.hpp"

collision physics::collision_check(onmyou_dama &one, game_object &two) // AABB - Circle collision
{
    // 取得圆心
    glm::vec2 centre(one.position + one.radius);
    // 计算矩形半长和中心
    glm::vec2 aabb_half_ext(two.size.x / 2.0f, two.size.y / 2.0f);
    glm::vec2 aabb_centre(
        two.position.x + aabb_half_ext.x,
        two.position.y + aabb_half_ext.y);
    // 差向量
    glm::vec2 difference = centre - aabb_centre;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_ext, aabb_half_ext); // 取最小
    // 圆与矩形最近点
    glm::vec2 closest = aabb_centre + clamped;
    // 计算圆心与最近点的距离
    difference = closest - centre;
    // return glm::length(difference) < one.radius;

    if (glm::length(difference) <= one.radius)
    {
        std::cout << "圆心：(" << centre.x << "," << centre.y << ")\t"
                  << "差向量：(" << difference.x << "," << difference.y << ")\t" << std::endl;
        return std::make_tuple(true, vector_direction(difference), difference);
    }
    else
    {
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
    }
}

direction physics::vector_direction(glm::vec2 target)
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

    std::cout << "碰撞方向：" << (direction)bestMatch << std::endl;
    return (direction)bestMatch;
}
