#include "Overseer.h"
#include "GlobalEvent.h"
#include "Logger.h"
#include "ConfigReader.h"
namespace XCNS
{

Overseer* Overseer::m_instance = NULL;

Overseer* Overseer::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new Overseer();
	}
	return m_instance;
}

Overseer::Overseer(void)
{
	m_time = 0;
	// clear the evq
	std::priority_queue<Event*, std::vector<Event*>, cmpEvent> qempty;
	std::swap(m_evq, qempty);

}

void Overseer::initialize()
{
	// read xml
	ConfigReader::ReadConfig();

	GlobalEvent* ge = new GlobalEvent(Event::EVENT_GLOBAL_SIMSTART);
	ge->setTimeStamp(0);
	m_evq.push(ge);
	ge = new GlobalEvent(Event::EVENT_GLOBAL_SIMEND);
	ge->setTimeStamp(m_simulationPeriod);
	m_evq.push(ge);
}

Overseer::~Overseer(void)
{
}

unsigned int Overseer::getTime()
{
	return m_time;
}

//distance表示传输距离，单位为km；frequency表示节点工作频率，单位为MHz。sendingPower表示发送功率，单位为mW。
bool Overseer::canReceiveSignal( double distance, double frequency, double sendingPower, double threshold )
{
	double receivingPower = 0;
	receivingPower = sendingPower / ( 1753.88 * distance * distance * frequency * frequency );
	if (receivingPower < threshold)
	{
		return false;
	}
	return true;
}



void Overseer::handleEvent(Event* evt)
{
	Logger* logger = Logger::getInstance();
	switch(evt->getType())
	{
	case Event::EVENT_GLOBAL_SIMEND:
		logger->addLog(1, "Simulation starts.");
		break;
	case Event::EVENT_GLOBAL_SIMSTART:
		logger->addLog(1, "Simulation ends.");
		break;
	case Event::EVENT_NODE_BUSY:
		nodeBusyHandler(evt);
		
		break;
	case Event::EVENT_NODE_FSM:
		nodeFSMHandler(evt);

		break;
	case Event::EVENT_NODE_SLEEP:
		nodeSleepHandler(evt);
		break;
	case Event::EVENT_NODE_WAKEUP:
		nodeWakeUpHandler(evt);
		break;
	case Event::EVENT_MESSAGE_ACK:
		ACKMsgHandler(evt);
		break;
	case Event::EVENT_MESSAGE_IML:
		IMLMsgHandler(evt);
		break;
	case Event::EVENT_MESSAGE_LS:
		LSMsgHandler(evt);
		break;
	}
}

/*
	Main function to simulate the network.
	There is a loop here.	
*/
void Overseer::simulate()
{
	while (!m_evq.empty())
	{
		Event* evt = m_evq.top();
		m_time = evt->getTimeStamp();

		handleEvent(evt);
		m_evq.pop();
	}
}

void Overseer::nodeWakeUpHandler(Event* evt)
{

}
void Overseer::nodeSleepHandler(Event* evt)
{

}
void Overseer::nodeFSMHandler(Event* evt)
{

}
void Overseer::nodeBusyHandler(Event* evt)
{

}
void Overseer::ACKMsgHandler(Event* evt)
{

}
void Overseer::LSMsgHandler(Event* evt)
{

}
void Overseer::IMLMsgHandler(Event* evt)
{

}

}
