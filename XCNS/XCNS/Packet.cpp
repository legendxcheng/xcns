#include "Packet.h"

namespace XCNS{

Packet::Packet(void)
{
}


Packet::~Packet(void)
{
}

int Packet::getSenderID()
{
	return m_sender;
}

int Packet::getType()
{
	return m_type;
}

void Packet::setSenderID(int senderID)
{
	m_sender = senderID;
}

}
