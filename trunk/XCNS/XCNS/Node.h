#pragma once
namespace XCNS
{


class Packet;

class Node
{
public:
	Node(void);
	~Node(void);
	

// Attributes.
private:
	int m_pos; // Position in a line.
	int m_groupGUID;
	int m_id; //

private:
	bool m_busy; // Boolean for whether the node is busy working.

public:
	void setID(int a_id, int a_groupGUID);
	void setPosition(int pos);
	bool isBusy();

	virtual void recvPacket(Packet* pkt) = 0;
	virtual void sendPacket(Packet* pkt) = 0;
};

}

