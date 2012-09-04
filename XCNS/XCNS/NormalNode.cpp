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

	Packet* NormalNode::sendPacket(int packetType)
	{
		return NULL;
	}

	void NormalNode::transit(std::string toState)
	{
		m_state = toState;

		// do logic
	}
}