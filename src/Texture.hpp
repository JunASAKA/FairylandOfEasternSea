#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdio.h>
#include <string>

unsigned int loadTexture(std::string texPath);
void background();

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