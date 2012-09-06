#pragma once

#include <string>
namespace XCNS
{

// Singleton class.
class Logger
{
public:

	~Logger(void);
	static Logger* getInstance();
	void setVerbosity(int verbo);
	void addLog(int verbo, std::string logStr);
	void addLogNoTime(int verbo, std::string logStr);
private:
	Logger(void);
	static Logger* m_instance;
	int m_verbosity;
	FILE* m_logFile;
};

}

