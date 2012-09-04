#pragma once

namespace XCNS{
class Packet
{
public:
	static const int PACKET_LS = 0x1000;
	static const int PACKET_ACK = 0x1001;
	static const int PACKET_IML = 0x1002;

protected:
	int m_type;
	int m_sender;

public:
	int getType();
	int getSenderID();
	void setSenderID(int senderID);
	Packet(void);
	~Packet(void);
};
}

