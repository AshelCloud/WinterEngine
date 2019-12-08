#include "Log.hpp"

#include<iostream>

//LogType의 개수에 따라 Entry를 초기화합니다.

int logTypes = static_cast<int>(LogType::LOG_ERROR) - static_cast<int>(LogType::LOG_DEFAULT) + 1;
std::vector<std::vector<std::string>> Log::log_Entries = std::vector<std::vector<std::string>>(logTypes);

//출력하고 싶은 로그 타입을 필터로 초기화합니다.

unsigned int Log::filter = static_cast<unsigned int>(LogType::LOG_DEFAULT) |
						   static_cast<unsigned int>(LogType::LOG_DEBUG)   |
						   static_cast<unsigned int>(LogType::LOG_INIT)	   |
						   static_cast<unsigned int>(LogType::LOG_WARNING) |
						   static_cast<unsigned int>(LogType::LOG_ERROR);

void Log::Message(const std::string& _message, const LogType _type)
{
	int logType = static_cast<int>(_type);
	log_Entries[logType].push_back(_message);

	if (IsFiltered())
	{
		Log::PrintMessage(_message, (GLubyte*)"", _type);
	}
}

void Log::Message(const std::string& _message, const GLubyte* _glMessage, const LogType _type)
{
	int logType = static_cast<int>(_type);
	log_Entries[logType].push_back(_message);

	if(IsFiltered())
	{
		Log::PrintMessage(_message, _glMessage, _type);
	}
}

void Log::SetFilter(unsigned int _filter)
{
	filter = _filter;
}

void Log::PrintMessage(const std::string& _message, const GLubyte* _glMessage, const LogType _type)
{
	std::string typeName = "DEFAULT";
	if(_type == LogType::LOG_DEBUG)		{ typeName = "DEBUG"; }
	if(_type == LogType::LOG_INIT)		{ typeName = "INIT"; }
	if(_type == LogType::LOG_WARNING)	{ typeName = "WARNING"; }
	if(_type == LogType::LOG_ERROR)		{ typeName = "ERROR"; }

	std::cout << typeName << ": " << _message << ": " << _glMessage << std::endl;
}

bool Log::IsFiltered()
{
	if (static_cast<unsigned int>(LogType::LOG_DEFAULT) && filter & static_cast<unsigned int>(LogType::LOG_DEFAULT) ||
		static_cast<unsigned int>(LogType::LOG_DEBUG) && filter & static_cast<unsigned int>(LogType::LOG_DEBUG) ||
		static_cast<unsigned int>(LogType::LOG_INIT) && filter & static_cast<unsigned int>(LogType::LOG_INIT) ||
		static_cast<unsigned int>(LogType::LOG_WARNING) && filter & static_cast<unsigned int>(LogType::LOG_WARNING) ||
		static_cast<unsigned int>(LogType::LOG_ERROR) && filter & static_cast<unsigned int>(LogType::LOG_ERROR))
	{
		return true;
	}

	return false;
}
