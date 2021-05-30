#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "include/ResourceManager.hpp"
#include "include/game.hpp"

/*事件处理函数之声明*/
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) ==
      GLFW_PRESS) {                         //判定ESCAPE键是否按下
    glfwSetWindowShouldClose(window, true); //标记窗体window应该关闭
  }
}

/*宣告ＧＬＦＷ有关函数*/
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode);

const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 960;

Game FairylandOfEasternSea(SCREEN_WIDTH, SCREEN_HEIGHT);

/*程式入口*/
int main() {

  /*定义定点数据*/
  float vertices[] = {
      0.5f,  0.5f,  0.0f,
      0.5f,  -0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
      -0.5f, 0.5f,  0.0f
  };
  unsigned int indices[]{0, 1, 3, 1, 2, 3};

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
  if (window == NULL) {
    std::cout << "【错误】：窗体创建失败" << std::endl;
    glfwTerminate(); //终止ＧＬＦＷ
    return -1;       //返回－１暂且代表出错。
  } else {
    std::cout << "【信息】：窗体创建成功" << std::endl;
  }
  glfwMakeContextCurrent(window); //将ｗｉｎｄｏｗ作为当前进程的主要上下文。

  /*初始化ＧＬＥＷ*/
  glewExperimental = true; //启用ＧＬＥＷ实验性功能
  if (glewInit() != GLEW_OK) {
    std::cout << "【错误】：ＧＬＥＷ初始化失败" << std::endl;
    glfwTerminate();
    return -1;
  } else {
    std::cout << "【信息】：ＧＬＥＷ初始化成功" << std::endl;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glViewport(0, 0, SCREEN_WIDTH,
             SCREEN_HEIGHT); //指定渲染范围（起始点与范围）。
  glEnable(GL_BLEND); //启用混合功能
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //混合因子

  FairylandOfEasternSea.Init();
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  /*设置ＶＡＯ与ＶＢＯ*/
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  /*设置ＥＢＯ*/
  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  /*将定点数据导入ＶＢＯ*/
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  /*将数据从ＶＢＯ导入ＶＡＯ*/
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  ResourceManager::LoadShader("../src/GLSL/vertexSource.glsl", "../src/GLSL/fragmentSource.glsl", GLM_NULLPTR,"myShader");

  /*窗体window的任务*/
  while (!glfwWindowShouldClose(window)) {

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents(); //接收事件

    /*处理输入事件*/
    FairylandOfEasternSea.ProcessInput(deltaTime);

    FairylandOfEasternSea.Update(deltaTime);

    /*渲染*/
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //指定清屏用颜色（RGBA）
    glClear(GL_COLOR_BUFFER_BIT);         //指定清理的暂存区
    FairylandOfEasternSea.Render();

    glfwSwapBuffers(window); //交换双暂存区

    processInput(window); //处理输入（声明于上文）

    glClearColor(1.0f, 1.0f, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    /*使能Ｓｈａｄｅｒ　Ｐｏｇｒａｍ　并绘制*/
    glBindVertexArray(VAO);
    ResourceManager::GetShader("myShader").Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  return 0; //返回值０代表正常退出。
}
