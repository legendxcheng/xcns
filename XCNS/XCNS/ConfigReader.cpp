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
	//获得根元素，即Persons。
	TiXmlElement *RootElement = myDocument->RootElement();
	//输出根元素名称，即输出Persons。
	
	printf("%s", RootElement->Value());
	TiXmlElement *carriageLength = RootElement->FirstChildElement();
	//获得第一个Person的name节点和age节点和ID属性。
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
	TiXmlElement *nodePower = carriageLength->NextSiblingElement();
}

}
