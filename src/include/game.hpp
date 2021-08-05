#ifndef GAME_HPP
#define GAME_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*游戏状态（后续添加）*/
enum gameState { GAME_ACTIVE, GAME_MENU, GAME_END };

class game {
   public:
    /*信息*/
    gameState State;
    bool Keys[1024];
    unsigned int Width, Height;
    game(unsigned int width, unsigned int height);  //建构函数
    ~game();					    //解构函数
    void init();				    //初始化
    /*游戏循环*/
    void processInput(float dt);
    void update(float dt);
    void render();
};

#endif
