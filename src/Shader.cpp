#include <cstdio>
#include <exception>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);

    

    
}