#include "../../include/Utility/Logger.h"

Utility::Logger* Utility::Logger::m_logger = NULL;

Utility::Logger::Logger()
{
	m_logErrors = true;
	m_logWarnings = true;
	m_logMessages = true;
	m_logToConsole = true;
	
	//File logging default turned off to save disk space
	//Use SetFileLoggingState(true) to enable file logging
	m_logToFile = false;
	
	m_programStarted = NULL;
	m_fileToWrite = NULL;

	Initialize();
}

Utility::Logger::~Logger()
{
	if (m_fileToWrite != NULL && m_fileToWrite->is_open())
	{
		m_fileToWrite->close();
	}
	
	delete m_fileToWrite;
}

void Utility::Logger::Initialize()
{
	SetProgramStarted();
	SetLogFilename();
}

void Utility::Logger::ResetInstance()
{
	delete m_logger;
	m_logger = NULL;
}

void Utility::Logger::OpenLogFile()
{
	if (m_fileToWrite == NULL)
	{
		_mkdir("Log");
		m_fileToWrite = new std::ofstream(m_logFilename, std::ofstream::app);
	}
}

void Utility::Logger::CloseLogFile()
{
	if (m_fileToWrite != NULL && m_fileToWrite->is_open())
	{
		m_fileToWrite->close();
	}
	
	delete m_fileToWrite;
	m_fileToWrite = NULL;
}

void Utility::Logger::LogToFile(const char* P_HEADER, const char* P_MESSAGE, const int P_LINENUMBER, const char* P_FILE)
{
	*m_fileToWrite << P_HEADER << "\t | "
			"T:[" << GetTimeDurationFormatted() << "]\t| " <<
			"M:" << P_MESSAGE << " | " <<
			"L:" << P_LINENUMBER << " | " <<
			"F:[" << P_FILE << "] " << std::endl;
}

void Utility::Logger::LogToFile(const char* P_HEADER, const char* P_MESSAGE)
{
	*m_fileToWrite << P_HEADER << "\t | "
			"T:[" << GetTimeDurationFormatted() << "]\t| " <<
			"M:" << P_MESSAGE << std::endl;
}

void Utility::Logger::LogToConsole(const char* P_HEADER, const char* P_MESSAGE, const int P_LINENUMBER, const char* P_FILE)
{
	std::cout << "+---=[ " << P_HEADER << " ]=---" << std::endl;
	std::cout << "|Time: \t\t" << GetTimeDurationFormatted() << std::endl;
	std::cout << "|Message: \t" << P_MESSAGE << std::endl;
	std::cout << "|Line: \t\t" << P_LINENUMBER << std::endl;
	std::cout << "|File: \t\t" << P_FILE << std::endl;
}

void Utility::Logger::LogToConsole(const char* P_HEADER, const char* P_MESSAGE)
{
	std::cout << "+---=[ " << P_HEADER << " ]=---" << std::endl;
	std::cout << "|Time: \t\t" << GetTimeDurationFormatted() << std::endl;
	std::cout << "|Message: \t" << P_MESSAGE << std::endl;
}

void Utility::Logger::Log(const LogMessageType P_TYPE, const char* P_MESSAGE, const int P_LINENUMBER, const char* P_FILE)
{
	char* header = "";
	bool typeState;

	switch ( P_TYPE )
	{
	case LOG_ERROR:
		header = "ERROR";
		typeState = m_logErrors;
		break;
	case LOG_WARNING:
		header = "WARNING";
		typeState = m_logWarnings;
		break;
	case LOG_MESSAGE:
		header = "MESSAGE";
		typeState = m_logMessages;
		break;
	}

	if (typeState)
	{
		if (m_logToFile)
		{
			LogToFile(header, P_MESSAGE, P_LINENUMBER, P_FILE);
		}
	
		if (m_logToConsole)
		{
			LogToConsole(header, P_MESSAGE, P_LINENUMBER, P_FILE);
		}
	}
}

void Utility::Logger::Log(LogMessageType p_type, const char* P_MESSAGE)
{
	char* header = "";
	bool typeState;

	switch ( p_type )
	{
	case LOG_ERROR:
		header = "ERROR";
		typeState = m_logErrors;
		break;
	case LOG_WARNING:
		header = "WARNING";
		typeState = m_logWarnings;
		break;
	case LOG_MESSAGE:
		header = "MESSAGE";
		typeState = m_logMessages;
		break;
	}

	if (typeState)
	{
		if (m_logToFile)
		{
			LogToFile(header, P_MESSAGE);
		}
	
		if (m_logToConsole)
		{
			LogToConsole(header, P_MESSAGE);
		}
	}
}

void Utility::Logger::LogMemoryDump(void* const P_ADDRESS, const int P_SIZE, char* const P_NAME)
{
	if (m_logToFile && m_fileToWrite != NULL)
	{
		const char* c = reinterpret_cast<const char*>(P_ADDRESS);

		*m_fileToWrite <<
				"MEMDUMP\t | " <<
				"N:[" << P_NAME << "]\t | " <<
				"A:[0x" << P_ADDRESS << "]\t | " <<
				"S:" << P_SIZE << " | " <<
				"D:[ ";

		for (int i = 0; i < P_SIZE; ++i)
		{
			*m_fileToWrite << "0x" << std::hex << int(c[i]) << " ";
		}

		*m_fileToWrite << "]" << std::endl;
	}
}

Utility::Logger* Utility::Logger::GetInstance()
{
	if (m_logger == NULL)
	{
		m_logger = new Utility::Logger();
	}
	
	return m_logger;
}

void Utility::Logger::SetProgramStarted()
{
	time_t timer;
	time(&timer);

	//Debugger gives a warning, localtime is deprecated.
	//Microsoft suggests using localtime_s instead, but according to ansi-c, this function is not deprecated yet.
	m_programStarted = localtime(&timer);
}

void Utility::Logger::SetLogFilename()
{
	m_logFilename.clear();

	m_logFilename.append("Log/Log ");
	m_logFilename.append(GetProgramStartedFormatted());
	m_logFilename.append(".txt");
}

tm* Utility::Logger::GetProgramStarted()
{
	if (m_programStarted == NULL)
	{
		SetProgramStarted();
	}

	return m_programStarted;
}

std::string Utility::Logger::GetProgramStartedFormatted()
{
	if (m_programStarted == NULL)
	{
		SetProgramStarted();
	}

	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H-%M-%S", m_programStarted);

	return buffer;
}

std::string Utility::Logger::GetTimeDurationFormatted()
{
	int time = clock();
	int secTotal =  time / CLOCKS_PER_SEC;
	int minTotal = secTotal / 60;
	
	int hour = minTotal / 60;
	int min = minTotal - hour*60;
	int sec = secTotal - min*60 - hour*60*60;
	int mil = time - (sec + min*60 + hour*60*60)*1000;

	std::stringstream ss;
	ss << "H=" << hour << " "
			"M=" << min << " "
			"S=" << sec << " "
			"Ms=" << mil;

	return ss.str();
}

void Utility::Logger::SetErrorLoggingState(const bool P_STATE)
{
	m_logErrors = P_STATE;
}

void Utility::Logger::SetMessagesLoggingState(const bool P_STATE)
{
	m_logMessages = P_STATE;
}

void Utility::Logger::SetWarningLoggingState(const bool P_STATE)
{
	m_logWarnings = P_STATE;
}

void Utility::Logger::SetFileLoggingState(const bool P_STATE)
{
	if (m_logToFile && !P_STATE)
	{
		CloseLogFile();
	}
	else if (!m_logToFile && P_STATE)
	{
		OpenLogFile();
	}

	m_logToFile = P_STATE;
}

void Utility::Logger::SetConsoleLoggingState(bool P_STATE)
{
	m_logToConsole = P_STATE;
}