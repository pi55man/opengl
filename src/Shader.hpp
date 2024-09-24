#pragma once


#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 



class Shader{
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(std::string& name, bool value) const;
	void setInt(std::string& name, int value) const;
	void setFloat(std::string& name, float value) const;
};
