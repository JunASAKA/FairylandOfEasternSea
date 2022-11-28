
#include "include/shader.hpp"

#include <iostream>

shader &shader::use()
{
    glUseProgram(this->id);
    return *this;
}

shader::shader() {}

void shader::compile(const char *vertex_source, const char *fragment_source, const char *geometry_source)
{
    uint32_t vertex_shader, fragment_shader, geometry_shader;
    // 顶点着色器
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    check_compile_errors(vertex_shader, "VERTEX");
    // 片段着色器
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);
    check_compile_errors(fragment_shader, "FRAGMENT");
    // 编译可有可无的几何着色器
    if (geometry_source != nullptr)
    {
        geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry_shader, 1, &geometry_source, NULL);
        glCompileShader(geometry_shader);
        check_compile_errors(geometry_shader, "GEOMETRY");
    }
    // 着色器应用程式
    this->id = glCreateProgram();
    glAttachShader(this->id, vertex_shader);
    glAttachShader(this->id, fragment_shader);
    if (geometry_source != nullptr)
    {
        glAttachShader(this->id, geometry_shader);
    }
    glLinkProgram(this->id);
    check_compile_errors(this->id, "PROGRAM");
    // 删除已连结的着色器
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    if (geometry_source != nullptr)
    {
        glDeleteShader(geometry_shader);
    }

    return;
}

void shader::set_float(const char *name, float value, bool use_shader)
{
    if (use_shader)
    {
        this->use();
    }
    glUniform1f(glGetUniformLocation(this->id, name), value);

    return;
}
void shader::set_integer_32(const char *name, int value, bool use_shader)
{
    if (use_shader)
    {
        this->use();
    }
    glUniform1i(glGetUniformLocation(this->id, name), value);

    return;
}
void shader::set_vector_2f(const char *name, float x, float y, bool use_shader)
{
    if (use_shader)
    {
        this->use();
    }
    glUniform2f(glGetUniformLocation(this->id, name), x, y);

    return;
}
void shader::set_vector_2f(const char *name, const glm::vec2 &value, bool use_shader)
{
    if (use_shader)
    {
        this->use();
    }
    glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);

    return;
}
void shader::set_vector_3f(const char *name, float x, float y, float z, bool use_shader)
{
    if (use_shader)
    {
        this->use();
    }
    glUniform3f(glGetUniformLocation(this->id, name), x, y, z);

    return;
}
void shader::set_vector_3f(const char *name, const glm::vec3 &value, bool use_shader)
{
    if (use_shader)
    {
        this->use();
    }
    glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);

    return;
}
void shader::set_vector_4f(const char *name, float x, float y, float z, float w, bool use_shader)
{
    if (use_shader)
    {
        this->use();
    }
    glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);

    return;
}
void shader::set_vector_4f(const char *name, const glm::vec4 &value, bool use_shader)
{
    if (use_shader)
    {
        this->use();
    }
    glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);

    return;
}
void shader::set_matrix_4(const char *name, const glm::mat4 &matrix, bool use_shader)
{
    if (use_shader)
    {
        this->use();
    }
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(matrix));

    return;
}
void shader::set_matrix_2(const char *name, const glm::mat2 &matrix, bool use_shader)
{
    if (use_shader)
    {
        this->use();
    }
    glUniformMatrix2fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(matrix));

    return;
}

void shader::check_compile_errors(uint32_t object, std::string type)
{
    int32_t success;
    char info_log[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, info_log);
            std::cout << "| [ERROR]Something went run when COMPILING Shader、エラーオブジェクトタイプは" << type << std::endl
                      << info_log << std::endl
                      << "---------------------------------------------------------- "
                      << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, info_log);
            std::cout << "| [ERROR]Something went run when LINKING Shader、エラーオブジェクトタイプは" << type << std::endl
                      << info_log << std::endl
                      << "---------------------------------------------------------- "
                      << std::endl;
        }
    }

    return;
}