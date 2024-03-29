#include "Overseer.h"
#include "GlobalEvent.h"
#include "Logger.h"
#include "ConfigReader.h"
#include "NodeEvent.h"
#include "MessageEvent.h"
#include "NodeMgr.h"
#include "LSPacket.h"
#include "IMLPacket.h"
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
	
	// Initialize Node
	NodeMgr::getInstance()->initialize();
	// Insert wakeUp Event.
	// Every node is initialized to be in sleep.
	for (int i = 0; i < NodeMgr::getInstance()->getNodeNum(); ++i)
	{
		NodeEvent* mevt = new NodeEvent(Event::EVENT_NODE_WAKEUP);
		mevt->setTimeStamp(0);
		mevt->setNodeID(i);
		m_evq.push(mevt);
	}
	



}

Overseer::~Overseer(void)
{
}

unsigned int Overseer::getTime()
{
	return m_time;
}





void Overseer::handleEvent(Event* evt)
{
	Logger* logger = Logger::getInstance();
	switch(evt->getType())
	{
	case Event::EVENT_GLOBAL_SIMEND:
		m_simulationEnded = true;
		logger->addLog(1, "Simulation ends.");
		break;
	case Event::EVENT_GLOBAL_SIMSTART:
		logger->addLog(1, "Simulation starts.");
		break;
	case Event::EVENT_NODE_BUSY:
		nodeBusyHandler(evt);
		
		break;
	case Event::EVENT_NODE_IDLE:
		nodeIdleHandler(evt);
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

void Overseer::addEvent(Event* evt)
{
	m_evq.push(evt);
}

int Overseer::getCarriageNum()
{
	return m_carriageNum;
}

/*
	Main function to simulate the network.
	There is a loop here.	
*/
void Overseer::simulate()
{
	m_simulationEnded = false;
	while (!m_evq.empty() && !m_simulationEnded)
	{
		Event* evt = m_evq.top();

		// Update the system time.
		m_time = evt->getTimeStamp();
		
		handleEvent(evt);
		m_evq.pop();
		delete evt;
	}
}

void Overseer::nodeWakeUpHandler(Event* evt)
{
	NodeEvent* nevt = (NodeEvent*)evt;
	
	// Add log.
	char logStr[300];
	sprintf(logStr, "node %d wakes up.", nevt->getNodeID());
	Logger::getInstance()->addLog(1, logStr);

	// Logic.
	NodeMgr::getInstance()->getNodeByID(nevt->getNodeID())->wakeUp();


}
void Overseer::nodeSleepHandler(Event* evt)
{
	NodeEvent* nevt = (NodeEvent*)evt;

	// Add log.
	char logStr[300];
	sprintf(logStr, "node %d sleeps.", nevt->getNodeID());
	Logger::getInstance()->addLog(1, logStr);
	// Logic.
	NodeMgr::getInstance()->getNodeByID(nevt->getNodeID())->sleep();

}
void Overseer::nodeFSMHandler(Event* evt)
{
	NodeEvent* nevt = (NodeEvent*)evt;
	// Add log.
	char logStr[300];
	sprintf(logStr, "node %d changes state, from %s to %s.", 
		nevt->getNodeID(), nevt->m_fromState.c_str(), nevt->m_toState.c_str());
	Logger::getInstance()->addLog(4, logStr);
	// Logic.
	NodeMgr::getInstance()->getNodeByID(nevt->getNodeID())->transit(nevt->getToState());
}
void Overseer::nodeBusyHandler(Event* evt)
{
	NodeEvent* nevt = (NodeEvent*)evt;
	char logStr[300];
	sprintf(logStr, "node %d becomes busy.", nevt->getNodeID());
	Logger::getInstance()->addLog(4, logStr);

	// Logic
}

void Overseer::nodeIdleHandler(Event* evt)
{
	NodeEvent* nevt = (NodeEvent*)evt;
	char logStr[300];
	sprintf(logStr, "node %d becomes idle.", nevt->getNodeID());
	Logger::getInstance()->addLog(4, logStr);

	// Logic

}

// Deprecated.
void Overseer::ACKMsgHandler(Event* evt)
{
	MessageEvent* mevt = (MessageEvent*)evt;
	
	// Add logs.
	char logStr[300];
	sprintf(logStr, "node %d broadcasts ACK message.", mevt->getNodeID());
	Logger::getInstance()->addLog(1, logStr);

	// Logic
	// TODO: find nodes which can recv the message, call thier recvPacket function
}
void Overseer::LSMsgHandler(Event* evt)
{
	MessageEvent* mevt = (MessageEvent*)evt;

	// Logic
	// TODO: get packet
	Node* tnode = NodeMgr::getInstance()->getNodeByID(mevt->getNodeID());
	LSPacket* lspkt = (LSPacket*)tnode->sendPacket(Packet::PACKET_LS);
	// TODO: find nodes which can recv the message, call thier recvPacket function
	if (lspkt) // if no packet return, then the node must be sleeping or disabled
	{
		NodeMgr::getInstance()->broadcastPacket(lspkt);
		// Add logs.
		char logStr[300];
		sprintf(logStr, "node %d broadcasts LS message.", mevt->getNodeID());
		Logger::getInstance()->addLog(1, logStr);
	}

}

int Overseer::getDropRate()
{
	return m_dropRate;
}

void Overseer::IMLMsgHandler(Event* evt)
{
	MessageEvent* mevt = (MessageEvent*)evt;
	// Add logs.
	char logStr[300];
	sprintf(logStr, "node %d broadcasts IML message.", mevt->getNodeID());
	Logger::getInstance()->addLog(1, logStr);

	// Logic
	// TODO: get packet
	Node* tnode = NodeMgr::getInstance()->getNodeByID(mevt->getNodeID());
	IMLPacket* imlpkt = (IMLPacket*)tnode->sendPacket(Packet::PACKET_IML);

	// TODO: find nodes which can recv the message, call thier recvPacket function
	if (imlpkt)
		NodeMgr::getInstance()->broadcastPacket(imlpkt);
}

void Overseer::printStatistics()
{
	NodeMgr::getInstance()->printStatistics();
}

void Overseer::stopSimulation()
{
	m_simulationEnded = true;
}

}
