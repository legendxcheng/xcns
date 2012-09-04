#include "MessageEvent.h"

namespace XCNS
{

	MessageEvent::MessageEvent(unsigned int a_type)
	{
		m_type = a_type;
	}

	MessageEvent::MessageEvent(void)
	{
	}


	MessageEvent::~MessageEvent(void)
	{
	}

	void MessageEvent::setPacket(Packet* packet)
	{
		m_pakcet = packet;
	}

	int MessageEvent::getNodeID()
	{
		return m_nodeID;
	}

	void MessageEvent::setNodeID(int nid)
	{
		m_nodeID = nid;
	}

}