#include "include/stage.hpp"

#include <fstream>
#include <sstream>

void gameStage::load(const char *file, uint32_t stageWidth, uint32_t stageHeight)
{
    this->bricks.clear();
    // 读取文件
    uint32_t brickCode;
    gameStage stage;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<uint32_t>> stageData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // 每一行
        {
            std::istringstream sstream(line);
            std::vector<uint32_t> row;
            while (sstream >> brickCode)
                row.push_back(brickCode);
            stageData.push_back(row);
        }
        if (stageData.size() > 0)
        {
            this->init(stageData, stageWidth, stageHeight);
        }
    }

    return;
}

void gameStage::draw(spriteRenderer &renderer)
{
    for (gameObject &obj : this->bricks)
    {
        if (!obj.destroyed)
        {
            obj.draw(renderer);
        }
    }
    return;
}

bool gameStage::isCompleted()
{
    for (gameObject &obj : this->bricks)
    {

        if (!obj.isSolid && !obj.destroyed)
        {
            return false;
        }
    }

    return true;
}

void gameStage::init(std::vector<std::vector<uint32_t>> stageData, uint32_t stageWidth, uint32_t stageHeight)
{
    // 横纵砖块数
    uint32_t height = stageData.size();
    uint32_t width = stageData[0].size();
    float unitWidth = stageWidth / static_cast<float>(width), unitHeight = stageHeight / height;

    // 生成gameObject
    for (uint32_t y = 0; y < height; ++y)
    {
        for (uint32_t x = 0; x < width; ++x)
        {
            // 检测是否是不可摧毁的
            if (stageData[y][x] == 1) // 不可摧毁
            {
                glm::vec2 pos(unitWidth * x, unitHeight * y);
                glm::vec2 size(unitWidth, unitHeight);

                gameObject *obj = new gameObject(pos, size, resourceManager::getTexture("texture"), glm::vec2(100.0f, 353.0f), glm::vec2(32.0f, 32.0f), glm::vec2(216.0f, 1090.0f));
                obj->isSolid = true;
                this->bricks.push_back(*obj);
            }
            else if (stageData[y][x] > 1) // 可摧毁
            {
                glm::vec2 pos(unitWidth * x, unitHeight * y);
                glm::vec2 size(unitWidth, unitHeight);
                this->bricks.push_back(gameObject(pos, size, resourceManager::getTexture("texture"), glm::vec2(100.0f, 225.0f), glm::vec2(32.0f, 32.0f), glm::vec2(216.0f, 1090.0f)));
            }
        }
    }

    return;
}