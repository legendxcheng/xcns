#pragma once
#include <string>

namespace XCNS
{


class Packet;

class Node
{
public:
	Node(void);
	~Node(void);
	

// Attributes.
protected:
	int m_pos; // Position in a line.
	int m_groupGUID;
	int m_id; //
	std::string m_state;
	
// Logics.
protected:
	bool m_sleeping;
	bool m_busy; // Boolean for whether the node is busy working.
	int m_maxIML; // the max node id which sended an IML or a LS message to this node
	int m_msgSendCount;// counter
	int m_msgRecvCount;// counter
	int m_curState; // FSM state


public:
	void setID(int a_id, int a_groupGUID);
	void setPosition(int pos);
	bool isBusy();
	int getID();

	virtual void wakeUp(); // Do some cleaning.
	virtual void sleep();

	virtual void recvPacket(Packet* pkt) = 0;
	virtual void sendPacket(Packet* pkt) = 0;
	virtual void transit(std::string toStage) = 0;// FSM transition
};

}

