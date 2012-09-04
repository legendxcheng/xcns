#pragma once

namespace XCNS{
class Packet
{
public:
	static const int PACKET_LS = 0x1000;
	static const int PACKET_ACK = 0x1001;

private:
	int m_type;
	int m_sender;

public:
	Packet(void);
	~Packet(void);
};
}

