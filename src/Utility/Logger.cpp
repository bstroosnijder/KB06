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

void Utility::Logger::LogToFile(const char* p_header, const char* p_message, const int p_lineNumber, const char* p_file)
{
	*m_fileToWrite << p_header << "\t | "
			"T:[" << GetTimeDurationFormatted() << "]\t| " <<
			"M:" << p_message << " | " <<
			"L:" << p_lineNumber << " | " <<
			"F:[" << p_file << "] " << std::endl;
}

void Utility::Logger::LogToFile(const char* p_header, const char* p_message)
{
	*m_fileToWrite << p_header << "\t | "
			"T:[" << GetTimeDurationFormatted() << "]\t| " <<
			"M:" << p_message << std::endl;
}

void Utility::Logger::LogToConsole(const char* p_header, const char* p_message, const int p_lineNumber, const char* p_file)
{
	std::cout << "+---=[ " << p_header << " ]=---" << std::endl;
	std::cout << "|Time: \t\t" << GetTimeDurationFormatted() << std::endl;
	std::cout << "|Message: \t" << p_message << std::endl;
	std::cout << "|Line: \t\t" << p_lineNumber << std::endl;
	std::cout << "|File: \t\t" << p_file << std::endl;
}

void Utility::Logger::LogToConsole(const char* p_header, const char* p_message)
{
	std::cout << "+---=[ " << p_header << " ]=---" << std::endl;
	std::cout << "|Time: \t\t" << GetTimeDurationFormatted() << std::endl;
	std::cout << "|Message: \t" << p_message << std::endl;
}

void Utility::Logger::Log(const LogMessageType p_type, const char* p_message, const int p_lineNumber, const char* p_file)
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
			LogToFile(header, p_message, p_lineNumber, p_file);
		}
	
		if (m_logToConsole)
		{
			LogToConsole(header, p_message, p_lineNumber, p_file);
		}
	}
}

void Utility::Logger::Log(LogMessageType p_type, const char* p_message)
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
			LogToFile(header, p_message);
		}
	
		if (m_logToConsole)
		{
			LogToConsole(header, p_message);
		}
	}
}

void Utility::Logger::LogMemoryDump(void* const p_address, const int p_size, char* const p_name)
{
	if (m_logToFile && m_fileToWrite != NULL)
	{
		const char* c = reinterpret_cast<const char*>(p_address);

		*m_fileToWrite <<
				"MEMDUMP\t | " <<
				"N:[" << p_name << "]\t | " <<
				"A:[0x" << p_address << "]\t | " <<
				"S:" << p_size << " | " <<
				"D:[ ";

		for (int i = 0; i < p_size; ++i)
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

void Utility::Logger::SetErrorLoggingState(const bool p_state)
{
	m_logErrors = p_state;
}

void Utility::Logger::SetMessagesLoggingState(const bool p_state)
{
	m_logMessages = p_state;
}

void Utility::Logger::SetWarningLoggingState(const bool p_state)
{
	m_logWarnings = p_state;
}

void Utility::Logger::SetFileLoggingState(const bool p_state)
{
	if (m_logToFile && !p_state)
	{
		CloseLogFile();
	}
	else if (!m_logToFile && p_state)
	{
		OpenLogFile();
	}

	m_logToFile = p_state;
}

void Utility::Logger::SetConsoleLoggingState(bool p_state)
{
	m_logToConsole = p_state;
}