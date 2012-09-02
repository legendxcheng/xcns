#include "ConfigReader.h"
#include "Overseer.h"
#include "tinyxml.h"
#include "tinystr.h"
#include <string>
#include "Logger.h"

namespace XCNS
{



ConfigReader::ConfigReader(void)
{
}


ConfigReader::~ConfigReader(void)
{
}

// Static function
void ConfigReader::ReadConfig()
{
	Overseer* ovsr = Overseer::getInstance();
	
	TiXmlDocument *myDocument = new TiXmlDocument("config.xml");
	myDocument->LoadFile();
	TiXmlElement *RootElement = myDocument->RootElement();
	Logger* logger = Logger::getInstance();
	TiXmlElement *carriageLength = RootElement->FirstChildElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *recvThreshold = nodePower->NextSiblingElement();
	TiXmlElement *nodeDelayOfHandlingMessage = recvThreshold->NextSiblingElement();
	TiXmlElement *groupGUID = nodeDelayOfHandlingMessage->NextSiblingElement();
	TiXmlElement *carriageNum = groupGUID->NextSiblingElement();
	TiXmlElement *simulatedPeriod = carriageNum->NextSiblingElement();
	TiXmlElement *nodeSleepTime = simulatedPeriod->NextSiblingElement();
	TiXmlElement *logVerbosity = nodeSleepTime->NextSiblingElement();

}

}
