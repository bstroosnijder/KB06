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
		void Log(const LogMessageType p_type, const char* p_message);
		void Log(const LogMessageType p_type, const char* p_message, const int p_lineNumber, const char* p_file);
		void LogMemoryDump(void* const p_address, const int p_size, char* const p_name);
		void SetErrorLoggingState(const bool p_state);
		void SetWarningLoggingState(const bool p_state);
		void SetMessagesLoggingState(const bool p_state);
		void SetFileLoggingState(const bool p_state);
		void SetConsoleLoggingState(const bool p_state);
	
	
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
		void LogToFile(const char* p_header, const char* p_message);
		void LogToFile(const char* p_header, const char* p_message, const int p_lineNumber, const char* p_file);
		void LogToConsole(const char* p_header, const char* p_message);
		void LogToConsole(const char* p_header, const char* p_message, const int p_lineNumber, const char* p_file);
		tm* GetProgramStarted();
		std::string GetProgramStartedFormatted();
		std::string GetTimeDurationFormatted();
		void SetProgramStarted();
		void SetLogFilename();
	
	};
}

#endif
