#include "Log.h"

#include<iostream>

//LogType의 개수에 따라 Entry를 초기화합니다.

int logTypes = LogType::LOG_ERROR - LogType::LOG_DEFAULT + 1;
std::vector<std::vector<std::string>> Log::log_Entries = std::vector<std::vector<std::string>>(logTypes);

//출력하고 싶은 로그 타입을 필터로 초기화합니다.

unsigned int Log::filter = static_cast<unsigned int>(LogType::LOG_DEFAULT) |
						   static_cast<unsigned int>(LogType::LOG_DEBUG)   |
						   static_cast<unsigned int>(LogType::LOG_INIT)	   |
						   static_cast<unsigned int>(LogType::LOG_WARNING) |
						   static_cast<unsigned int>(LogType::LOG_ERROR);

void Log::Message(const std::string& message, const LogType type)
{
	int logType = static_cast<int>(type);
	log_Entries[logType].push_back(message);

	Log::PrintMessage(message, type);
}

void Log::PrintMessage(const std::string& message, const LogType type)
{
	std::string typeName = "DEFAULT";
	if(type == LogType::LOG_DEBUG)		{ typeName = "DEBUG"; }
	if(type == LogType::LOG_INIT)		{ typeName = "INIT"; }
	if(type == LogType::LOG_WARNING)	{ typeName = "WARNING"; }
	if(type == LogType::LOG_ERROR)		{ typeName = "ERROR"; }


	std::cout << typeName << ": "<< message << std::endl;
}
