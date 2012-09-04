#include "LSPacket.h"
#include "stdlib.h"
namespace XCNS
{


LSPacket::LSPacket(void)
{
	m_type = Packet::PACKET_LS;
}


LSPacket::~LSPacket(void)
{
}

void LSPacket::setNodeState(char* src)
{
	memcpy(m_nodeState, src, sizeof(char) * 50);
}



}