#pragma once

#include <tuple>
#include <iostream>

#include "gameObject.hpp"
#include "onmyouDama.hpp"

// 物理碰撞相关
enum direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<bool, direction, glm::vec2> collision;

namespace physics
{

    collision collisionCheck(onmyouDama &one, gameObject &two); // 碰撞检测

    direction vectorDirection(glm::vec2 target); // 碰撞方位检测

}
