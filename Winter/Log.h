#pragma once

#include<vector>
#include<string>

#include"include/GLFW/glfw3.h"

/*

LOG Ŭ������ ���������� ȣ�Ⱑ���� LOG��� Ŭ�����Դϴ�.
LogType�� ���� Entry�� LOG���� ����Ǹ� Filter�� ���� LOG���� ���͸��� �� �ֽ��ϴ�.

*/


enum class LogType : unsigned int
{
	LOG_DEFAULT = 0,
	LOG_DEBUG = 2,
	LOG_INIT = 4,
	LOG_WARNING = 8,
	LOG_ERROR = 16,
};

class Log
{
private:
	static std::vector<std::vector<std::string>> log_Entries;
	
	static unsigned int filter;

public:
	static void Message(const std::string& _message, const LogType _type = LogType::LOG_DEFAULT);
	static void Message(const std::string& _message, const GLubyte* _glMessage, const LogType _type = LogType::LOG_DEFAULT);
	static void SetFilter(unsigned int _filter);

private:
	static void PrintMessage(const std::string& _message, const GLubyte* _glMessage, const LogType _type);
	static bool IsFiltered();
};