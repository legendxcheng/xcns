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

	void HeadNode::sendPacket(Packet* pkt)
	{

	}

	void HeadNode::transit(std::string toState)
	{
		m_state = toState;

		// do logic
	}

}