#include "ConfigReader.h"
#include "Overseer.h"
#include "tinyxml.h"
#include "tinystr.h"
#include <string>


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
	//��ø�Ԫ�أ���Persons��
	TiXmlElement *RootElement = myDocument->RootElement();
	//�����Ԫ�����ƣ������Persons��
	
	printf("%s", RootElement->Value());
	TiXmlElement *carriageLength = RootElement->FirstChildElement();
	//��õ�һ��Person��name�ڵ��age�ڵ��ID���ԡ�
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
}

}
