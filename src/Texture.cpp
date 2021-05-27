#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.hpp"
#include "Texture.hpp"

unsigned int loadTexture(std::string texPath) {
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  int width, height, nrChannels;
  unsigned char *data =
    stbi_load(texPath.c_str(), &width, &height, &nrChannels, 0);

  if (data) {

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    printf("贴图加载成功。\n");
    return texture;
  } else {
    printf("贴图加载失败。\n");
    return 1;
  }
  stbi_image_free(data);
}

void background() {
  Shader myShader = Shader("../src/GLSL/bgVertexSource.glsl",
                           "../src/GLSL/bgFragmentSource.glsl");
  unsigned int bgTexture = loadTexture("../src/assets/bg.png");
  unsigned int bgVAO, bgVBO, bgEBO;
  glGenVertexArrays(1, &bgVAO);
  glGenBuffers(1, &bgVBO);
  glBindVertexArray(bgVAO);
  glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
  glGenBuffers(1, &bgEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bgEBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(backgroundVertices), backgroundVertices,
               GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(backgroundIndices),
               backgroundIndices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindTexture(GL_TEXTURE_2D, bgTexture);
  glBindVertexArray(bgVAO);
  myShader.useShaderProgram();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  return;
}