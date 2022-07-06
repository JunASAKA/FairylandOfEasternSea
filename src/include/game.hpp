#ifndef GAME_HPP
#define GAME_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*游戏状态（后续添加）*/
enum gameState { GAME_ACTIVE, GAME_MENU, GAME_END, GAME_PAUSE };
const float PC_VELOCITY(250.0f); //自机速率
class game {
   public:
    /*信息*/
    gameState State;
    bool Keys[1024];
    uint32_t Width, Height, Playable_Zone_X, Playable_Zone_Y, Playable_Width, Playable_Hight;
    game(uint32_t width, uint32_t height, uint32_t playable_zone_x, uint32_t playable_zone_y, uint32_t playable_width, uint32_t playable_hight);  //建构函数
    ~game();					    //解构函数
    void init();				    //初始化
    /*游戏循环*/
    void processInput(float delta_time);
    void update(float delta_time);
    void render();
};

#endif
