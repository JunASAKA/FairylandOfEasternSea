#ifndef GAME_H
#define GAME_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*游戏状态（后续添加）*/
enum GameState { GAME_ACTIVE, GAME_MENU, GAME_END };

class Game {
public:
  /*信息*/
  GameState State;
  bool Keys[1024];
  unsigned int Width, Height;
  Game(unsigned int width, unsigned int height); //建构函数
  ~Game();                                       //解构函数
  void Init();                                   //初始化
  /*游戏循环*/
  void ProcessInput(float dt);
  void Update(float dt);
  void Render();
};

#endif