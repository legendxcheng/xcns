#include "HeadNode.h"

namespace XCNS
{


	HeadNode::HeadNode(void)
	{
	}


	HeadNode::~HeadNode(void)
	{
	}

	void HeadNode::recvPacket(Packet* pkt)
	{

	}

	Packet* HeadNode::sendPacket(int packetType)
	{
		return NULL;
	}

	void HeadNode::transit(std::string toState)
	{
		m_state = toState;

		// do logic
	}

}