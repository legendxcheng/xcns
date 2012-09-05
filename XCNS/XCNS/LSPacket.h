#pragma once
#include "packet.h"
namespace XCNS
{


class LSPacket :
	public Packet
{
private:
	char m_nodeState[50];
public:
	char* getNodeState();
	void setNodeState(char* src);
	LSPacket(void);
	~LSPacket(void);
};

}

