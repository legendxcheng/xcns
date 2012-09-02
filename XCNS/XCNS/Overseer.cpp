#include "Overseer.h"

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
}


Overseer::~Overseer(void)
{
}

unsigned int Overseer::getTime()
{
	return m_time;
}

}
