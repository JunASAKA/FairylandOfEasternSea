#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "include/game.hpp"
#include "include/resourceManager.hpp"

/*宣告ＧＬＦＷ有关函数*/
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode);

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;

game FairylandOfEasternSea(SCREEN_WIDTH, SCREEN_HEIGHT);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
/*程式入口*/
int main() {

  /*初始化ＧＬＦＷ*/
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //ＧＬＦＷ主版本号
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //ＧＬＦＷ亚版本号
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_RESIZABLE, false); //不允许调整窗体大小

  /*创建一个窗体*/
  GLFWwindow *window = glfwCreateWindow(
      SCREEN_WIDTH, SCREEN_HEIGHT, "東方瀛洲誌 ~ Fairyland of Eastern Sea ~",
      nullptr, nullptr); //创建窗体
  glfwMakeContextCurrent(window); //将ｗｉｎｄｏｗ作为当前进程的主要上下文。
  if (window == NULL) {
    std::cout << "【ERROR】：ウィンドウの作成に失敗する。" << std::endl;
    glfwTerminate(); //终止ＧＬＦＷ
    return -1;       //返回－１暂且代表出错。
  } else {
    std::cout << "【告】：ウィンドウの作成に成功する。" << std::endl;
  }

  /*初始化ＧＬＥＷ*/
  glewExperimental = true; //启用ＧＬＥＷ实验性功能
  if (glewInit() != GLEW_OK) {
    std::cout << "【ERROR】：GLEWの初期化に失敗する。" << std::endl;
    glfwTerminate();
    return -1;
  } else {
    std::cout << "【告】：GLEWの初期化に成功する。" << std::endl;
  }
  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glViewport(0, 0, SCREEN_WIDTH,
             SCREEN_HEIGHT); //指定渲染范围（起始点与范围）。
  glEnable(GL_BLEND);        //启用混合功能
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //混合因子

  FairylandOfEasternSea.init();
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  FairylandOfEasternSea.State = GAME_ACTIVE;

  /*窗体window的任务*/
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents(); //接收事件

    /*处理输入事件*/
    FairylandOfEasternSea.processInput(deltaTime);

    FairylandOfEasternSea.update(deltaTime);

    /*渲染*/
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //指定清屏用颜色（RGBA）
    glClear(GL_COLOR_BUFFER_BIT);         //指定清理的暂存区

    FairylandOfEasternSea.render();

    glfwSwapBuffers(window); //交换双暂存区
  }

  resourceManager::clear();

  glfwTerminate();

  return 0; //返回值０代表正常退出。
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS)
      FairylandOfEasternSea.Keys[key] = GL_TRUE;
    else if (action == GLFW_RELEASE)
      FairylandOfEasternSea.Keys[key] = GL_FALSE;
  }
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  /*保证ｖｉｅｗ　ｐｏｉｎｔ与窗体大小吻合*/
  glViewport(0, 0, width, height);
}