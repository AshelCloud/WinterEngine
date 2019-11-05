#pragma once

#include<vector>
#include<string>

/*

LOG 클래스는 전역적으로 호출가능한 LOG출력 클래스입니다.
LogType에 따라 Entry에 LOG들이 저장되며 Filter를 통해 LOG들을 필터링할 수 있습니다.

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