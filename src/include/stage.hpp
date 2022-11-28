#pragma once

#include <vector>
#include <iostream>
#include "glm/glm/glm.hpp"

#include "game_object.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"

class game_stage
{
public:
    std::vector<game_object> bricks;
    // 建构函数
    game_stage() {}
    // 读取文件
    void load(const char *file, uint32_t stage_width, uint32_t stage_height);
    // 渲染
    void draw(sprite_renderer &renderer);
    // 是否通过
    bool isCompleted();

private:
    // 初始化
    void init(std::vector<std::vector<uint32_t>> stage_data, uint32_t stage_width, uint32_t stage_height);
};
