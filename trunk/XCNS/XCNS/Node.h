#pragma once
#include <string>
class NodeMgr;

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
	int m_power;
	int m_recvThreshold;
	int m_handleDelay;
	int m_dropRate;

// Logics.
protected:
	bool m_sleeping;
	bool m_busy; // Boolean for whether the node is busy working.
	int m_maxIML; // the max node id which sended an IML or a LS message to this node
	int m_msgSendCount;// counter
	int m_msgRecvCount;// counter
	std::string m_state;


public:
	friend class NodeMgr;
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

