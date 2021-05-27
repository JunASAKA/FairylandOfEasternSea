#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

/*Ｖｅｒｔｅｘ　Ｓｈａｄｅｒ源代码*/
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColour;\n"
                                 "out vec3 outColour;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0f);\n"
                                 "   outColour = aColour;\n "
                                 "}\0";

/*Ｆｒａｇｍｅｎｔ　Ｓｈａｄｅｒ源代码*/
const char *fragmentShaderSource = "#version 330 core\n"
                                   "in vec3 outColour;\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(outColour, 1.0f);\n"
                                   "}\n\0";

/*事件处理函数之声明*/
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) ==
      GLFW_PRESS) {                         //判定ESCAPE键是否按下
    glfwSetWindowShouldClose(window, true); //标记窗体window应该关闭
  }
}

/*程式入口*/
int main() {
  /*后续纠错用*/
  int success;
  char infoLog[512];

  /*定义定点数据*/
  float vertices[] = {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f,
                      0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f,  1.0f};

  /*初始化ＧＬＦＷ*/
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //ＧＬＦＷ主版本号
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //ＧＬＦＷ亚版本号
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /*创建一个窗体*/
  GLFWwindow *window =
      glfwCreateWindow(1280, 960, "東方瀛洲誌 ~ Firyland of Eastern Sea ~",
                       NULL, NULL); //创建窗体
  if (window == NULL) {
    printf("窗体创建失败\n");
    glfwTerminate(); //终止ＧＬＦＷ
    return -1;       //返回－１暂且代表出错。
  } else {
    printf("窗体创建成功\n");
  }
  glfwMakeContextCurrent(window); //将ｗｉｎｄｏｗ作为当前进程的主要上下文。

  /*初始化ＧＬＥＷ*/
  glewExperimental = true; //启用ＧＬＥＷ实验性功能
  if (glewInit() != GLEW_OK) {
    printf("ＧＬＥＷ初始化失败\n");
    glfwTerminate();
    return -1;
  } else {
    printf("ＧＬＥＷ初始化成功\n");
  }

  glViewport(0, 0, 1280, 960); //指定渲染范围（起始点与范围）。

  Shader give_me_a_name("../src/GLSL/vertexSource.glsl",
                        "../src/GLSL/fragmentSource.glsl");

  /*设置ＶＡＯ与ＶＢＯ*/
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  /*将定点数据导入ＶＢＯ*/
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  /*设置与编译Ｖｅｒｔｅｘ　Ｓｈａｄｅｒ*/
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  /*Ｖｅｒｔｅｘ　Ｓｈａｄｅｒ编译纠错*/
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("Ｖｅｒｔｅｘ　Ｓｈａｄｅｒ编译错误： \n%s", infoLog);
  } else {
    printf("Ｖｅｒｔｅｘ　Ｓｈａｄｅｒ编译成功\n");
  }

  /*设置与编译Ｆｒａｇｍｅｎｔ　Ｓｈａｄｅｒ*/
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  /*Ｆｒａｇｍｅｎｔ　Ｓｈａｄｅｒ编译纠错*/
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("Ｆｒａｇｍｅｎｔ　Ｓｈａｄｅｒ编译错误： \n%s", infoLog);
  } else {
    printf("Ｆｒａｇｍｅｎｔ　Ｓｈａｄｅｒ编译成功\n");
  }

  /*创建Ｓｈａｄｅｒ　Ｐｒｏｇｒａｍ*/
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  /*贴敷Ｓｈａｄｅｒ於Ｐｒｏｇｒａｍ*/
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  /*Ｓｈａｄｅｒ　Ｐｒｏｇｒａｍ设置纠错*/
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("Ｓｈａｄｅｒ　Ｐｒｏｇｒａｍ设置错误： \n%s", infoLog);
  } else {
    printf("Ｓｈａｄｅｒ　Ｐｒｏｇｒａｍ设置成功\n");
  }
  /*删除用过的Ｓｈａｄｅｒ*/
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  /*将数据从ＶＢＯ导入ＶＡＯ*/
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  /*窗体window的任务*/
  while (!glfwWindowShouldClose(window)) {
    /*处理输入事件*/
    processInput(window); //处理输入（声明于上文）

    /*渲染*/
    glClearColor(1.0f, 1.0f, 0, 1.0f); //指定清屏用颜色（RGBA）
    glClear(GL_COLOR_BUFFER_BIT);      //指定清理的暂存区

    /*使能Ｓｈａｄｅｒ　Ｐｒｏｇｒａｍ　并绘制*/
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /*接收事件与交换暂存区*/
    glfwSwapBuffers(window); //交换双暂存区
    glfwPollEvents();        //接收事件
  }

  return 0; //返回值０代表正常退出。
}
