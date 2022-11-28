#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

class shader
{
public:
    // id
    uint32_t id;
    // 建构函数
    shader();
    // 使用（激活）着色器
    shader &use();
    // 用给定的源代码编译着色器
    void compile(const char *vertex_source, const char *fragment_source, const char *geometry_source = nullptr); // note: geometry source code is optional
    // 实用工具
    void set_float(const char *name, float value, bool use_shader = false);
    void set_integer_32(const char *name, int32_t value, bool use_shader = false);
    void set_vector_2f(const char *name, float x, float y, bool use_shader = false);
    void set_vector_2f(const char *name, const glm::vec2 &value, bool use_shader = false);
    void set_vector_3f(const char *name, float x, float y, float z, bool use_shader = false);
    void set_vector_3f(const char *name, const glm::vec3 &value, bool use_shader = false);
    void set_vector_4f(const char *name, float x, float y, float z, float w, bool use_shader = false);
    void set_vector_4f(const char *name, const glm::vec4 &value, bool use_shader = false);
    void set_matrix_4(const char *name, const glm::mat4 &matrix, bool use_shader = false);
    void set_matrix_2(const char *name, const glm::mat2 &matrix, bool use_shader = false);

private:
    // 纠错用
    void check_compile_errors(uint32_t object, std::string type);
};
