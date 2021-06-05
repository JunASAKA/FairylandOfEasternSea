
#include "include/Shader.hpp"

#include <iostream>

Shader &Shader::Use() {
    glUseProgram(this->ID);
    return *this;
}

void Shader::Compile(const char *vertexSource, const char *fragmentSource,
		     const char *geometrySource) {
    unsigned int interVertexShader, interFragmentShader, interGeometryShader;
    /*顶点着色器*/
    interVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(interVertexShader, 1, &vertexSource, NULL);
    glCompileShader(interVertexShader);
    checkCompileErrors(interVertexShader, "VERTEX");
    /*ＦＲＡＧＭＥＮＴ着色器*/
    interFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(interFragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(interFragmentShader);
    checkCompileErrors(interFragmentShader, "FRAGMENT");
    /*几何着色器*/
    if (geometrySource != nullptr) {
	interGeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(interGeometryShader, 1, &geometrySource, NULL);
	glCompileShader(interGeometryShader);
	checkCompileErrors(interGeometryShader, "GEOMETRY");
    }
    /*着色器程式*/
    this->ID = glCreateProgram();
    glAttachShader(this->ID, interVertexShader);
    glAttachShader(this->ID, interFragmentShader);
    if (geometrySource != nullptr)
	glAttachShader(this->ID, interGeometryShader);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    /*删除用过的着色器*/
    glDeleteShader(interVertexShader);
    glDeleteShader(interFragmentShader);
    if (geometrySource != nullptr) glDeleteShader(interGeometryShader);
}

void Shader::SetFloat(const char *name, float value, bool useShader) {
    if (useShader) this->Use();
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetInteger(const char *name, int value, bool useShader) {
    if (useShader) this->Use();
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetVector2f(const char *name, float x, float y, bool useShader) {
    if (useShader) this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::SetVector2f(const char *name, const glm::vec2 &value,
			 bool useShader) {
    if (useShader) this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::SetVector3f(const char *name, float x, float y, float z,
			 bool useShader) {
    if (useShader) this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::SetVector3f(const char *name, const glm::vec3 &value,
			 bool useShader) {
    if (useShader) this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y,
		value.z);
}
void Shader::SetVector4f(const char *name, float x, float y, float z, float w,
			 bool useShader) {
    if (useShader) this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::SetVector4f(const char *name, const glm::vec4 &value,
			 bool useShader) {
    if (useShader) this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z,
		value.w);
}
void Shader::SetMatrix4(const char *name, const glm::mat4 &matrix,
			bool useShader) {
    if (useShader) this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false,
		       glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
	glGetShaderiv(object, GL_COMPILE_STATUS, &success);
	if (!success) {
	    glGetShaderInfoLog(object, 1024, NULL, infoLog);
	    std::cout
		<< "| 【错误】：着色器编译失败；【对象类型】： " << type << "\n"
		<< infoLog
		<< "\n -- --------------------------------------------------- "
		   "-- "
		<< std::endl;
	}
    } else {
	glGetProgramiv(object, GL_LINK_STATUS, &success);
	if (!success) {
	    glGetProgramInfoLog(object, 1024, NULL, infoLog);
	    std::cout
		<< "| 【错误】：着色器连结失败；【对象类型】：" << type << "\n"
		<< infoLog
		<< "\n -- --------------------------------------------------- "
		   "-- "
		<< std::endl;
	}
    }
}
