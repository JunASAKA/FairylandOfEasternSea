#pragma once

#include <tuple>
#include <iostream>

#include "game_object.hpp"
#include "onmyou_dama.hpp"

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

    collision collision_check(onmyou_dama &one, game_object &two); // 碰撞检测

    direction vector_direction(glm::vec2 target); // 碰撞方位检测

}
