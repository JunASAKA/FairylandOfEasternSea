#ifndef SPRITE_RENDERER_HPP
#define SPRITE_RENDERER_HPP

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "texture.hpp"
#include "shader.hpp"



class spriteRenderer
{
public:
    // 建构函数
    spriteRenderer(class shader shader);
    // 解构函数
    ~spriteRenderer();
    /**/
    void drawSprite(texture2D texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
    class shader       shader; 
    unsigned int quadVAO;
    // 初始化并配置渲染属性
    void initRenderData();
};

#endif