#ifndef __UTILITY_LOGGER_H__
#define __UTILITY_LOGGER_H__

#include <ctime>
#include <Windows.h>
#include <typeinfo.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>

namespace Utility
{
	class Logger
	{
	public:
		enum LogMessageType
		{
			LOG_ERROR,
			LOG_WARNING,
			LOG_MESSAGE
		};

		Logger();
		~Logger();
		static Logger* GetInstance();
		static void ResetInstance();
		void Log(const LogMessageType P_TYPE, const char* P_MESSAGE);
		void Log(const LogMessageType P_TYPE, const char* P_MESSAGE, const int P_LINENUMBER, const char* P_FILE);
		void LogMemoryDump(void* const P_ADDRESS, const int P_SIZE, char* const P_NAME);
		void SetErrorLoggingState(const bool P_STATE);
		void SetWarningLoggingState(const bool P_STATE);
		void SetMessagesLoggingState(const bool P_STATE);
		void SetFileLoggingState(const bool P_STATE);
		void SetConsoleLoggingState(const bool P_STATE);
	
	
	private:
		static Logger* m_logger;
		tm* m_programStarted;
		std::string m_logFilename;
		std::ofstream* m_fileToWrite;
		bool m_logErrors;
		bool m_logWarnings;
		bool m_logMessages;
		bool m_logToConsole;
		bool m_logToFile;
	
		void Initialize();
		void OpenLogFile();
		void CloseLogFile();
		void LogToFile(const char* P_HEADER, const char* P_MESSAGE);
		void LogToFile(const char* P_HEADER, const char* P_MESSAGE, const int P_LINENUMBER, const char* P_FILE);
		void LogToConsole(const char* P_HEADER, const char* P_MESSAGE);
		void LogToConsole(const char* P_HEADER, const char* P_MESSAGE, const int P_LINENUMBER, const char* P_FILE);
		tm* GetProgramStarted();
		std::string GetProgramStartedFormatted();
		std::string GetTimeDurationFormatted();
		void SetProgramStarted();
		void SetLogFilename();
	
	};
}

#endif
