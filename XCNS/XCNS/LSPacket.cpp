#include "LSPacket.h"
#include <string>
namespace XCNS
{


LSPacket::LSPacket(void)
{
	m_type = Packet::PACKET_LS;
}


LSPacket::~LSPacket(void)
{
}

char* LSPacket::getNodeState()
{
	return m_nodeState;
}

void LSPacket::setNodeState(char* src)
{
	memcpy(m_nodeState, src, sizeof(char) * 50);
}



}