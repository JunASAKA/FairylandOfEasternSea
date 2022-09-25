#pragma once

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.hpp"
#include "resourceManager.hpp"

/* 宣告ＧＬＦＷ有关函数 */
void key_callback(GLFWwindow *window, int32_t key, int32_t scancode, int32_t action,
                  int32_t mode);

const uint32_t SCREEN_WIDTH = 640;
const uint32_t SCREEN_HEIGHT = 480;

const uint32_t PLAYABLE_ZONE_X = 0;   //自机移动范围左上角座标
const uint32_t PLAYABLE_ZONE_Y = 480; //自机移动范围左上角座标
const uint32_t PLAYABLE_WIDTH = 640;
const uint32_t PLAYABLE_HEIGHT = 0;

game FairylandOfEasternSea(SCREEN_WIDTH, SCREEN_HEIGHT, PLAYABLE_ZONE_X, PLAYABLE_ZONE_Y, PLAYABLE_WIDTH, PLAYABLE_HEIGHT);
void framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height);