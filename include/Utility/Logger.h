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
	/**
	 * @brief	Utility Logger to write messages to a file or to a console.
	 *			
	 * @author	Michel van Os.
	 * @todo	comments for private methods
	 */
	class Logger
	{
	public:
		/**
		 * @brief	Messages types used to categorize the log messages.
		 *
		 * @author	Michel van Os.
		 */
		enum LogMessageType
		{
			///Error messages category.
			LOG_ERROR,

			///Warning messages category.
			LOG_WARNING,

			///Regular messages category.
			LOG_MESSAGE	 
		};

		/**
		 * @brief	Creates the Logger.
		 *
		 * @author	Michel van Os.
		 */
		Logger();

		/**
		 * @brief	Destroys the Logger.
		 *
		 * @author	Michel van Os
		 */
		~Logger();

		/**
		 * @brief	Returns a Singleton-instance of the Logger.
		 *
		 * @author	Michel van Os
		 */
		static Logger* GetInstance();

		/**
		 * @brief	Resets the Singleton-instance of the Logger and the Logger will be destroyed.
		 *
		 * @author	Michel van Os
		 */
		static void ResetInstance();
		
		/**
		 * @brief	Logs a message.
		 *
		 * @param	p_type The message Type
		 * @param	p_message The message to log.
		 * @author	Michel van Os.
		 */
		void Log(const LogMessageType p_type, const char* p_message);

		/**
		 * @brief	Logs a message, linenumber and the filename.
		 *
		 * @param	p_type The message Type
		 * @param	p_message The message to log.
		 * @param	p_lineNumber The line number.
		 * @param	p_file The filename.
		 * @author	Michel van Os.
		 */
		void Log(const LogMessageType p_type, const char* p_message, const int p_lineNumber, const char* p_file);

		/**
		 * @brief	Logs a part of the memory.
		 *
		 * @param	p_address	The address of the memory.
		 * @param	p_size		The amount of bytes to log.
		 * @param	p_name		The name for the memory dump.
		 * @author	Michel van Os
		 */
		void LogMemoryDump(void* const p_address, const int p_size, char* const p_name);

		/**
		 * @brief	Sets the error logging state.
		 *
		 *			If set to FALSE. Error messages won't be logged.
		 * @param	p_state The new error logging state.
		 * @author	Michel van Os.
		 */
		void SetErrorLoggingState(const bool p_state);

		/**
		 * @brief	Sets the warning logging state.
		 *					
		 *			If set to FALSE. Warning messages won't be logged.
		 * @param	p_state The new warning logging state.
		 * @author	Michel van Os.
		 */
		void SetWarningLoggingState(const bool p_state);

		/**
		 * @brief	Sets the messages logging state.
		 *					
		 *			If set to FALSE. Regular messages won't be logged.
		 * @param	p_state The new messages logging state.
		 * @author	Michel van Os.
		 */
		void SetMessagesLoggingState(const bool p_state);

		/**
		 * @brief	Sets the file logging state.
		 *					
		 *			If set to FALSE. Messages won't be logged to a file.
		 * @param	p_state The new file logging state.
		 * @author	Michel van Os.
		 */
		void SetFileLoggingState(const bool p_state);

		/**
		 * @brief	Sets the console logging state.
		 *			
		 *			If set to FALSE. Messages won't be logged to a console.
		 * @param	p_state The new console logging state.
		 * @author	Michel van Os.
		 */
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
	
		/**
		* @todo
		*/
		void Initialize();

		/**
		* @todo
		*/
		void OpenLogFile();

		/**
		* @todo
		*/
		void CloseLogFile();

		/**
		* @todo
		*/
		void LogToFile(const char* P_HEADER, const char* P_MASSAGE);

		/**
		* @todo
		*/
		void LogToFile(const char* P_HEADER, const char* P_MASSAGE, const int P_LINENUMBER, const char* P_FILE);

		/**
		* @todo
		*/
		void LogToConsole(const char* P_HEADER, const char* P_MASSAGE);

		/**
		* @todo
		*/
		void LogToConsole(const char* P_HEADER, const char* P_MASSAGE, const int P_LINENUMBER, const char* P_FILE);

		/**
		* @todo
		*/
		tm* GetProgramStarted();

		/**
		* @todo
		*/
		std::string GetProgramStartedFormatted();

		/**
		* @todo
		*/
		std::string GetTimeDurationFormatted();

		/**
		* @todo
		*/
		void SetProgramStarted();

		/**
		* @todo
		*/
		void SetLogFilename();
	
	};
}

#endif
