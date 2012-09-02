#include "Event.h"
#include "Overseer.h"
namespace XCNS
{

unsigned int Event::m_eventCount = 0;

Event::Event(void)
{
	++m_eventCount;
	m_id = m_eventCount;
	m_timeStamp = Overseer::getInstance()->getTime();
}


Event::~Event(void)
{
}

void Event::setTimeStamp(unsigned long tstp)
{
	m_timeStamp = tstp;
}

unsigned int Event::getTimeStamp()
{
	return m_timeStamp;
}



int Event::getType()
{
	return m_type;
}

}