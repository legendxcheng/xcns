#include "Logger.h"
#include "Overseer.h"


namespace XCNS
{

	Logger* Logger::m_instance = NULL;

	Logger* Logger::getInstance()
	{
		if (m_instance == NULL)
		{
			m_instance = new Logger();
		}
		return m_instance;
	}

	void Logger::addLog(int verbo, std::string logStr)
	{
		if (verbo <= m_verbosity)
		{
			std::string polishedStr;
			char ss[300];
			memset(ss, 0, sizeof(char) * 300);
			unsigned int curTime = Overseer::getInstance()->getTime();
			sprintf(ss, "%d\.%dms  %s\n", curTime / 10, curTime %10, logStr.c_str());
			fprintf(m_logFile, ss);
		}
		
	}

	void Logger::setVerbosity(int verbo)
	{
		m_verbosity = verbo;
	}



	Logger::Logger(void)
	{
		m_logFile = fopen("XCNS.log", "w");
	}


	Logger::~Logger(void)
	{
		fclose(m_logFile);
	}

}