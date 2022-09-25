#pragma once

#include <vector>
#include <iostream>
#include "glm/glm/glm.hpp"

#include "gameObject.hpp"
#include "resourceManager.hpp"
#include "spriteRenderer.hpp"

class gameStage
{
public:
    std::vector<gameObject> bricks;
    // 建构函数
    gameStage() {}
    // 读取文件
    void load(const char *file, uint32_t stageWidth, uint32_t stageHeight);
    // 渲染
    void draw(spriteRenderer &renderer);
    // 是否通过
    bool isCompleted();

private:
    // 初始化
    void init(std::vector<std::vector<uint32_t>> stageData, uint32_t stageWidth, uint32_t stageHeight);
};
