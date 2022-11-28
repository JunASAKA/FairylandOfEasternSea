#include "include/stage.hpp"

#include <fstream>
#include <sstream>

void game_stage::load(const char *file, uint32_t stage_width, uint32_t stage_height)
{
    this->bricks.clear();
    // 读取文件
    uint32_t brick_code;
    game_stage stage;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<uint32_t>> stage_data;
    if (fstream)
    {
        while (std::getline(fstream, line)) // 每一行
        {
            std::istringstream sstream(line);
            std::vector<uint32_t> row;
            while (sstream >> brick_code)
                row.push_back(brick_code);
            stage_data.push_back(row);
        }
        if (stage_data.size() > 0)
        {
            this->init(stage_data, stage_width, stage_height);
        }
    }

    return;
}

void game_stage::draw(sprite_renderer &renderer)
{
    for (game_object &obj : this->bricks)
    {
        if (!obj.destroyed)
        {
            obj.draw(renderer);
        }
    }
    return;
}

bool game_stage::isCompleted()
{
    for (game_object &obj : this->bricks)
    {

        if (!obj.is_solid && !obj.destroyed)
        {
            return false;
        }
    }

    return true;
}

void game_stage::init(std::vector<std::vector<uint32_t>> stage_data, uint32_t stage_width, uint32_t stage_height)
{
    // 横纵砖块数
    uint32_t height = stage_data.size();
    uint32_t width = stage_data[0].size();
    float unit_width = stage_width / static_cast<float>(width), unit_height = stage_height / height;

    // 生成game_object
    for (uint32_t y = 0; y < height; ++y)
    {
        for (uint32_t x = 0; x < width; ++x)
        {
            // 检测是否是不可摧毁的
            if (stage_data[y][x] == 1) // 不可摧毁
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);

                game_object *obj = new game_object(pos, size, resource_manager::get_texture("texture"), glm::vec2(100.0f, 353.0f), glm::vec2(32.0f, 32.0f), glm::vec2(216.0f, 1090.0f));
                obj->is_solid = true;
                this->bricks.push_back(*obj);
            }
            else if (stage_data[y][x] > 1) // 可摧毁
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                this->bricks.push_back(game_object(pos, size, resource_manager::get_texture("texture"), glm::vec2(100.0f, 225.0f), glm::vec2(32.0f, 32.0f), glm::vec2(216.0f, 1090.0f)));
            }
        }
    }

    return;
}