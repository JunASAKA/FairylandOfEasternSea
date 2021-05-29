#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdio.h>
#include <string>
#include "Shader.hpp"

unsigned int loadTexture(std::string texPath);
Shader prepareBackground(unsigned int *bgTexture, unsigned int *bgVAO);
void useBackground(unsigned int *bgTexture, unsigned int *bgVAO, Shader myShader);

const float backgroundVertices[] = {
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f
  };

const unsigned int backgroundIndices[] = {
    0,1,3,
    1,2,3
  };

#endif