#include"include/GL/glew.h"
#include"include/GLFW/glfw3.h"
#include<iostream>

static void ErrorCallback(int errorCode, const char* errorDscription)
{
	fprintf(stderr, "Error %s\n", errorDscription);
}

int main()
{
	glfwSetErrorCallback(ErrorCallback);
	return 0;
}