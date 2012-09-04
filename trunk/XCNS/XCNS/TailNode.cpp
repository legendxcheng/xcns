#include "TailNode.h"

namespace XCNS
{


	TailNode::TailNode(void)
	{
	}


	TailNode::~TailNode(void)
	{
	}

	void TailNode::recvPacket(Packet* pkt)
	{

	}

	void TailNode::sendPacket(Packet* pkt)
	{

	}

	void TailNode::transit(std::string toState)
	{
		m_state = toState;

		// do logic
	}

}