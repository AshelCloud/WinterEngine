#include "Log.h"

#include<iostream>

//LogType�� ������ ���� Entry�� �ʱ�ȭ�մϴ�.

int logTypes = LogType::LOG_ERROR - LogType::LOG_DEFAULT + 1;
std::vector<std::vector<std::string>> Log::log_Entries = std::vector<std::vector<std::string>>(logTypes);

//����ϰ� ���� �α� Ÿ���� ���ͷ� �ʱ�ȭ�մϴ�.

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
