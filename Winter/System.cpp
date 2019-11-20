#include "System.h"

#include"Log.h"
#include<iostream>

int framebufferWidth, framebufferHeight;
GLuint triangleVertexArrayObject;
GLuint triangleShaderProgramID;
GLuint trianglePositionVertexBufferObjectID, triangleColorVertexBufferObjectID;

bool initShaderProgram() {

	//#3
	const GLchar* vertexShaderSource =
		"#version 330 core\n"
		"in vec3 positionAttribute;"
		"in vec3 colorAttribute;"
		"out vec3 passColorAttribute;"
		"void main()"
		"{"
		"gl_Position = vec4(positionAttribute, 1.0);"
		"passColorAttribute = colorAttribute;"
		"}";


	//#4
	const GLchar* fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 passColorAttribute;"
		"out vec4 fragmentColor;"
		"void main()"
		"{"
		"fragmentColor = vec4(passColorAttribute, 1.0);"
		"}";



	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		Log::Message("vertex shader 컴파일 실패", LogType::LOG_ERROR);
		glDeleteShader(vertexShader);
		return false;
	}


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		Log::Message("fragment shader 컴파일 실패", LogType::LOG_ERROR);

		return false;
	}

	//#5
	triangleShaderProgramID = glCreateProgram();

	glAttachShader(triangleShaderProgramID, vertexShader);
	glAttachShader(triangleShaderProgramID, fragmentShader);

	glLinkProgram(triangleShaderProgramID);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glGetProgramiv(triangleShaderProgramID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(triangleShaderProgramID, 512, NULL, errorLog);
		Log::Message("shader program 연결 실패", LogType::LOG_ERROR);

		return false;
	}

	return true;
}

bool defineVertexArrayObject() {

	//#1
	//삼각형을 구성하는 vertex 데이터 - position과 color
	float position[] = {
		0.0f,  0.5f, 0.0f, //vertex 1  위 중앙
		0.5f, -0.5f, 0.0f, //vertex 2  오른쪽 아래
		-0.5f, -0.5f, 0.0f //vertex 3  왼쪽 아래
	};

	float color[] = {
		1.0f, 0.0f, 0.0f, //vertex 1 : RED (1,0,0)
		0.0f, 1.0f, 0.0f, //vertex 2 : GREEN (0,1,0) 
		0.0f, 0.0f, 1.0f  //vertex 3 : BLUE (0,0,1)
	};



	//#2
	//Vertex Buffer Object(VBO)를 생성하여 vertex 데이터를 복사한다.
	glGenBuffers(1, &trianglePositionVertexBufferObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, trianglePositionVertexBufferObjectID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

	glGenBuffers(1, &triangleColorVertexBufferObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, triangleColorVertexBufferObjectID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);



	//#6
	glGenVertexArrays(1, &triangleVertexArrayObject);
	glBindVertexArray(triangleVertexArrayObject);


	GLint positionAttribute = glGetAttribLocation(triangleShaderProgramID, "positionAttribute");
	if (positionAttribute == -1) {
		Log::Message("position 속성 설정 실패", LogType::LOG_ERROR);
		return false;
	}
	glBindBuffer(GL_ARRAY_BUFFER, trianglePositionVertexBufferObjectID);
	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(positionAttribute);

	GLint colorAttribute = glGetAttribLocation(triangleShaderProgramID, "colorAttribute");
	if (colorAttribute == -1) {
		Log::Message("color 속성 설정 실패", LogType::LOG_ERROR);

		return false;
	}
	glBindBuffer(GL_ARRAY_BUFFER, triangleColorVertexBufferObjectID);
	glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorAttribute);


	glBindVertexArray(0);


	return true;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	//처음 2개의 파라미터는 viewport rectangle의 왼쪽 아래 좌표
	//다음 2개의 파라미터는 viewport의 너비와 높이이다.
	//framebuffer의 width와 height를 가져와 glViewport에서 사용한다.
	glViewport(0, 0, width, height);

	framebufferWidth = width;
	framebufferHeight = height;
}

System::System():
	window(nullptr)
{
}

System::~System()
{
}

void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
	if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(_window, GLFW_TRUE);
	}
}

bool System::Initialize()
{
	if (!glfwInit())
	{
		Log::Message("glfwInit Failed", LogType::LOG_ERROR);

		return false;
	}

	//Using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Don't use Deprecated API 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//안티앨리어싱 4X MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(800, 400, "OpenGL", nullptr, nullptr);
	if (!window)
	{
		Log::Message("Failed Create Window", LogType::LOG_ERROR);
		
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	//glew
	glewExperimental = GL_TRUE;

	GLenum errorCode = glewInit();
	if (GLEW_OK != errorCode)
	{
		Log::Message("Faild glew Initialization: ", glewGetErrorString(errorCode), LogType::LOG_ERROR);

		glfwTerminate();
		return false;
	}

	if (!GLEW_VERSION_3_3)
	{
		Log::Message("OpenGL 3.3 API is not available", LogType::LOG_ERROR);

		return false;
	}

	Log::Message("OpenGL version", glGetString(GL_VERSION));
	Log::Message("GLSL version", glGetString(GL_VERSION));
	Log::Message("Vendor", glGetString(GL_VENDOR));
	Log::Message("Renderer", glGetString(GL_VENDOR));

	if (!initShaderProgram()) {

		Log::Message("Shader Program 생성 실패", LogType::LOG_ERROR);

		return false;
	}

	if(!defineVertexArrayObject())
	{
		Log::Message("Shader Program 생성 실패", LogType::LOG_ERROR);

		return false;
	}

	glfwSwapInterval(1);

	glUseProgram(triangleShaderProgramID);
	glBindVertexArray(triangleVertexArrayObject);

	return true;
}

void System::Run()
{
	double lastTime = glfwGetTime();
	int numOfFrames = 0;

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		numOfFrames++;

		if (currentTime - lastTime >= 1.f)
		{
			std::cout << 1000.f / double(numOfFrames) << " ms/frame " << numOfFrames << " fps" << std::endl;
			numOfFrames = 0;
			lastTime = currentTime;
		}

		glClearColor(0.f, 0.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glUseProgram(0);
	glBindVertexArray(0);

	glDeleteProgram(triangleShaderProgramID);
	glDeleteBuffers(1, &trianglePositionVertexBufferObjectID);
	glDeleteBuffers(1, &triangleColorVertexBufferObjectID);
	glDeleteVertexArrays(1, &triangleVertexArrayObject);
}

void System::Release()
{
	glfwTerminate();

	window = nullptr;
}
