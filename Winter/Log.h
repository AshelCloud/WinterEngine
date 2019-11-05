#pragma once

#include<vector>
#include<string>

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
	static void Message(const std::string& message, const LogType type = LogType::LOG_DEFAULT);

private:
	static void PrintMessage(const std::string& message, const LogType type);
};