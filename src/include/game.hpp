#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "stage.hpp"

/*游戏状态（后续添加）*/
enum game_state
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_END,
    GAME_PAUSE
};

const float playable_character_velocity(400.0f); //自机速率

class game
{
public:
    /*信息*/
    game_state state;
    bool keys[1024];
    uint32_t width, height, playable_zone_x, playable_zone_y, playable_width, playable_hight;
    game(uint32_t width, uint32_t height, uint32_t playable_zone_x, uint32_t playable_zone_y, uint32_t playable_width, uint32_t playable_hight); //建构函数
    ~game();                                                                                                                                     //解构函数
    void init();                                                                                                                                 //初始化
    /*游戏循环*/
    void process_input(float delta_t);
    void update(float delta_t);
    void render();
    std::vector<game_stage> stages; // Stages
    uint32_t stage;

    void do_collision_check();

    void rst_pc();
    void rst_stage();
};
