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

	// Insert 2 simulation event, the simulation start and simulation end.
	//m_evq.push(new GlobalEvent(Event::EVENT_GLOBAL_SIMSTART));
	//m_evq.push(new GlobalEvent(Event::EVENT_GLOBAL_SIMSEND));
}



Overseer::~Overseer(void)
{
}

unsigned int Overseer::getTime()
{
	return m_time;
}

}
