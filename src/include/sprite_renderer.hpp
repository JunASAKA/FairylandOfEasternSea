#pragma once

#include <GL/glew.h>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "texture.hpp"
#include "shader.hpp"

class sprite_renderer
{
public:
    // 建构函数
    sprite_renderer(class shader shader);
    // 解构函数
    ~sprite_renderer();
    /**/
    void draw_sprite(texture_2D texture, glm::vec2 position, glm::vec2 size, glm::vec2 tex_pos, glm::vec2 tex_size, glm::vec2 image_size, float rotate = 0.0f, glm::vec3 colour = glm::vec3(1.0f), bool mirror = false);

private:
    class shader shader;
    uint32_t quad_vao;
    // 初始化并配置渲染属性
    void init_render_data();
};
