#pragma once

#include"include/GL/glew.h"
#include"include/GLFW/glfw3.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

class System
{
public:
	System();
	~System();

public:
	bool Initialize();
	void Run();
	void Release();

private:
	GLFWwindow* window;
};

