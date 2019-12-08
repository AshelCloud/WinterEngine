#pragma once

/*
	���̴� �ε��ϴ� Ŭ����
*/
#include"include/GL/glew.h"
#include"include//GLFW//glfw3.h"

#include<string>

class Shader
{
public:
	Shader(const std::string& _fileName, GLenum _shaderType);
	~Shader();

public:
	GLuint GetShaderID();

private:
	std::string shaderString;
	GLint shaderID;
	GLenum shaderType;
};

