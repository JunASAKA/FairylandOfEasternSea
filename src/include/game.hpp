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
    unsigned int Width, Height, Playable_Zone_X, Playable_Zone_Y, Playable_Width, Playable_Hight;
    game(unsigned int width, unsigned int height, unsigned int playable_zone_x, unsigned int playable_zone_y, unsigned int playable_width, unsigned int playable_hight);  //建构函数
    ~game();					    //解构函数
    void init();				    //初始化
    /*游戏循环*/
    void processInput(float delta_t);
    void update(float delta_t);
    void render();
};

#endif
