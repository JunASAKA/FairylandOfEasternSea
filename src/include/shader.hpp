#ifndef SHADER_HPP
#define SHADER_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


class shader
{
public:
    // ID
    unsigned int ID; 
    // 建构函数
    shader();
    // 使用（激活）着色器
    shader  &use();
    // 用给定的源代码编译着色器
    void    compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr); // note: geometry source code is optional 
    // 实用工具
    void    setFloat    (const char *name, float value, bool useShader = false);
    void    setInteger  (const char *name, int value, bool useShader = false);
    void    setVector2f (const char *name, float x, float y, bool useShader = false);
    void    setVector2f (const char *name, const glm::vec2 &value, bool useShader = false);
    void    setVector3f (const char *name, float x, float y, float z, bool useShader = false);
    void    setVector3f (const char *name, const glm::vec3 &value, bool useShader = false);
    void    setVector4f (const char *name, float x, float y, float z, float w, bool useShader = false);
    void    setVector4f (const char *name, const glm::vec4 &value, bool useShader = false);
    void    setMatrix4  (const char *name, const glm::mat4 &matrix, bool useShader = false);
    void    setMatrix2(const char *name, const glm::mat2 &matrix, bool useShader = false);
private:
    // 纠错用
    void    checkCompileErrors(unsigned int object, std::string type); 
};

#endif