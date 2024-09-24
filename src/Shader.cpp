#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
Shader::Shader(const char* vertexPath, const char* fragmentPath){
    
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    int success;
    char infoLog[512];
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    
    vShaderFile.close();
    fShaderFile.close();
    
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    int vertexShader,fragmentShader;
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vShaderCode,NULL);
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fShaderCode,NULL);
    
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
    glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
    std::cout<<"vertex shader failed: "<<infoLog<<std::endl;
    }
    
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
    glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
    std::cout<<"fragment shader failed: "<<infoLog<<std::endl;
    }
    ID = glad_glCreateProgram();
    glAttachShader(ID,vertexShader);
    glAttachShader(ID,fragmentShader);
    glad_glLinkProgram(ID);
        

    glad_glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
    glad_glGetProgramInfoLog(ID,512,NULL,infoLog);
    std::cout<<"program failed: "<<infoLog<<std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use(){
    glad_glUseProgram(ID);
}
