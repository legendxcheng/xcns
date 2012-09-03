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
	int m_state;
	
// Logics.
private:
	bool m_busy; // Boolean for whether the node is busy working.
	int m_maxIML; // the max node id which sended an IML or a LS message to this node
	int m_msgSendCount;// counter
	int m_msgRecvCount;// counter

public:
	void setID(int a_id, int a_groupGUID);
	void setPosition(int pos);
	bool isBusy();

	virtual void recvPacket(Packet* pkt) = 0;
	virtual void sendPacket(Packet* pkt) = 0;
};

}

