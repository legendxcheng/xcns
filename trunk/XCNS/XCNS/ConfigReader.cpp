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
	
	TiXmlElement *carriageLength = RootElement->FirstChildElement();
	ovsr->m_carriageLength = atoi(carriageLength->FirstChild()->Value());

	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	ovsr->m_nodePower = atoi(nodePower->FirstChild()->Value());

	TiXmlElement *recvThreshold = nodePower->NextSiblingElement();
	ovsr->m_recvThreshold = atoi(recvThreshold->FirstChild()->Value());

	TiXmlElement *nodeDelayOfHandlingMessage = recvThreshold->NextSiblingElement();
	ovsr->m_nodeDelayOfHandlingMessage = atoi(nodeDelayOfHandlingMessage->FirstChild()->Value());

	TiXmlElement *groupGUID = nodeDelayOfHandlingMessage->NextSiblingElement();
	ovsr->m_groupGUID = atoi(groupGUID->FirstChild()->Value());

	TiXmlElement *carriageNum = groupGUID->NextSiblingElement();
	ovsr->m_carriageNum = atoi(carriageNum->FirstChild()->Value());

	TiXmlElement *simulatedPeriod = carriageNum->NextSiblingElement();
	ovsr->m_simulationPeriod = strtoul(simulatedPeriod->FirstChild()->Value(), NULL, 10);

	TiXmlElement *nodeSleepTime = simulatedPeriod->NextSiblingElement();
	ovsr->m_nodeSleepTime = strtoul(nodeSleepTime->FirstChild()->Value(), NULL, 10);

	TiXmlElement *logVerbosity = nodeSleepTime->NextSiblingElement();
	ovsr->m_logVerbosity = atoi(logVerbosity->FirstChild()->Value());


	TiXmlElement *IMLgap = logVerbosity->NextSiblingElement();
	ovsr->m_IMLgap = atoi(logVerbosity->FirstChild()->Value());


	TiXmlElement *ACKgap = IMLgap->NextSiblingElement();
	ovsr->m_ACKgap = atoi(logVerbosity->FirstChild()->Value());


	TiXmlElement *LSgap = ACKgap->NextSiblingElement();
	ovsr->m_LSgap = atoi(logVerbosity->FirstChild()->Value());


	TiXmlElement *timeBeforeJudgingDeath = LSgap->NextSiblingElement();
	ovsr->m_timeBeforeJudgingDeath = atoi(logVerbosity->FirstChild()->Value());


	TiXmlElement *timeBeforeSleep = timeBeforeJudgingDeath->NextSiblingElement();
	ovsr->m_timeBeforeSleep = atoi(logVerbosity->FirstChild()->Value());

	TiXmlElement *dropRate = timeBeforeSleep->NextSiblingElement();
	ovsr->m_dropRate = atoi(logVerbosity->FirstChild()->Value());

	Logger* logger = Logger::getInstance();
	logger->setVerbosity(ovsr->m_logVerbosity);
}

}
