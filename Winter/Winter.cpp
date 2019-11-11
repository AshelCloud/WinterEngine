#include"include/GL/glew.h"
#include"include/GLFW/glfw3.h"
#include"Log.h"

#include<iostream>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")


static void ErrorCallback(int _errorCode, const char* _errorDscription)
{
	fprintf(stderr, "Error %s\n", _errorDscription);
}

void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
	if(_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(_window, GLFW_TRUE);
	}
}

int main()
{
	glfwSetErrorCallback(ErrorCallback);

	if(!glfwInit())
	{
		Log::Message("glfwInit Failed", LogType::LOG_ERROR);
		return 1;
	}

	//Using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Don't use Deprecated API 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//¾ÈÆ¼¾Ù¸®¾î½Ì 4X MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(800, 400, "OpenGL", nullptr, nullptr);
	if(!window)
	{
		Log::Message("Failed Create Window", LogType::LOG_ERROR);

		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);


	//glew
	glewExperimental = GL_TRUE;

	GLenum errorCode = glewInit();
	if(GLEW_OK != errorCode)
	{
		Log::Message("Faild glew Initialization: ", glewGetErrorString(errorCode), LogType::LOG_ERROR);

		glfwTerminate();
		return 1;
	}

	if(!GLEW_VERSION_3_3)
	{
		Log::Message("OpenGL 3.3 API is not available", LogType::LOG_ERROR);

		glfwTerminate();
		return 1;
	}

	Log::Message("OpenGL version", glGetString(GL_VERSION));
	Log::Message("GLSL version", glGetString(GL_VERSION));
	Log::Message("Vendor", glGetString(GL_VENDOR));
	Log::Message("Renderer", glGetString(GL_VENDOR));

	glfwSwapInterval(1);

	double lastTime = glfwGetTime();
	int numOfFrames = 0;

	while(!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		numOfFrames ++;

		if(currentTime - lastTime >= 1.f)
		{
			std::cout << 1000.f / double(numOfFrames) << " ms/frame " << numOfFrames << " fps" << std::endl;
			numOfFrames = 0;
			lastTime = currentTime;
		}

		glClearColor(0.f, 0.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
