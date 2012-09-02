#include "Overseer.h"
#include "GlobalEvent.h"
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
	GlobalEvent* ge = new GlobalEvent(Event::EVENT_GLOBAL_SIMSTART);
	ge->setTimeStamp(0);
	m_evq.push(ge);
	ge = new GlobalEvent(Event::EVENT_GLOBAL_SIMEND);
	ge->setTimeStamp(m_simulatePeriod);
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



void handleEvent(Event* evt)
{
	switch(evt->getType())
	{
	case Event::EVENT_GLOBAL_SIMEND:

		break;
	case Event::EVENT_GLOBAL_SIMSTART:
		break;
	case Event::EVENT_MESSAGE_ACK:
		break;
	case Event::EVENT_MESSAGE_IML:
		break;
	case Event::EVENT_MESSAGE_LS:
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

}
