
#include "include/shader.hpp"

#include <iostream>

shader &shader::use()
{
    glUseProgram(this->ID);
    return *this;
}

shader::shader(){}

void shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    uint32_t sVertex, sFragment, gShader;
    // 顶点着色器
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // 片段着色器
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // 编译可有可无的几何着色器
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    // 着色器应用程式
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->ID, gShader);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    // 删除已连结的着色器
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void shader::setFloat(const char *name, float value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void shader::setInteger32(const char *name, int value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void shader::setVector2f(const char *name, float x, float y, bool useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void shader::setVector2f(const char *name, const glm::vec2 &value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void shader::setVector3f(const char *name, float x, float y, float z, bool useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void shader::setVector3f(const char *name, const glm::vec3 &value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void shader::setVector4f(const char *name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void shader::setVector4f(const char *name, const glm::vec4 &value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void shader::setMatrix4(const char *name, const glm::mat4 &matrix, bool useShader)
{
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}
void shader::setMatrix2(const char *name, const glm::mat2 &matrix, bool useShader)
{
    if (useShader)
        this->use();
    glUniformMatrix2fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}


void shader::checkCompileErrors(uint32_t object, std::string type)
{
    int32_t success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| [ERROR]Something went run when COMPILING Shader、エラーオブジェクトタイプは" << type << std::endl
                << infoLog<< std::endl << "---------------------------------------------------------- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| [ERROR]Something went run when LINKING Shader、エラーオブジェクトタイプは" << type << std::endl
                << infoLog << std::endl <<"---------------------------------------------------------- "
                << std::endl;
        }
    }
}