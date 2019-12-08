#include "Shader.hpp"

#include"Log.hpp"

#include<fstream>

Shader::Shader(const std::string& _fileName, GLenum _shaderType):
	shaderString(""), shaderID(0), shaderType(_shaderType)
{
	Log::Message("Loading " + _fileName);

	std::string line;

	std::ifstream shaderFileStream(_fileName);

	if(!shaderFileStream)
	{
		Log::Message("Could not open shader " + _fileName + ": File Does Not Exist", LogType::LOG_ERROR);

		shaderID = 0;

		return;
	}

	while(std::getline(shaderFileStream, line))
	{
		shaderString += line;

		if(shaderFileStream.peek() != EOF) shaderString += '\n';
	}
	
	shaderID = glCreateShader(shaderType);
	Log::Message("Compiling " + _fileName);

	const GLchar* cShaderString = shaderString.c_str();
	glShaderSource(shaderID, 1, &cShaderString, nullptr);

	glCompileShader(shaderID);
	
	//Error Check
	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

	if(compileStatus != GL_TRUE)
	{
		GLint compileLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &compileLogLength);

		GLchar* compileLog = new GLchar[compileLogLength + 1];
		glGetShaderInfoLog(shaderID, compileLogLength + 1, nullptr, compileLog);

		std::string sCompileLog(compileLog);
		Log::Message("Shader " + _fileName + "faile to compile : " + sCompileLog, LogType::LOG_ERROR);

		return;
	}

	Log::Message(_fileName + " Succesfully Compiled as Shader: " + std::to_string(shaderID));
}

Shader::~Shader()
{
	glDeleteShader(shaderID);
}

GLuint Shader::GetShaderID()
{
	return shaderID;
}
