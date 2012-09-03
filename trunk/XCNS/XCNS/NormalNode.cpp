#include "NormalNode.h"

namespace XCNS
{


	NormalNode::NormalNode(void)
	{
	}


	NormalNode::~NormalNode(void)
	{
	}

	void NormalNode::recvPacket(Packet* pkt)
	{

	}

	void NormalNode::sendPackrt(Packet* pkt)
	{

	}

	void NormalNode::transit(std::string toState)
	{
		m_state = toState;

		// do logic
	}
}