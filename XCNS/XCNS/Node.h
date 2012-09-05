#pragma once
#include <string>
class NodeMgr;
class Overseer;
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
	friend class NodeMgr;
	int m_pos; // Position in a line.
	int m_groupGUID;
	int m_id; //
	int m_power;
	int m_recvThreshold;
	int m_handleDelay;
	int m_dropRate;
	int m_freq;

// Logics.
protected:
	bool m_disabled;
	bool m_sleeping;
	bool m_busy; // Boolean for whether the node is busy working.
	int m_minIML; // the max node id which sended an IML or a LS message to this node
	int m_msgSendCount; // counter
	int m_msgRecvCount; // counter
	int m_lastLSFromMinIMLTime; 
	int m_lastRecvTime;
	std::string m_state;
	/*
		Every 2 bits represents a node's state
		00 unknown
		01 alive
		10 dead
		11 dead
		Using | can simply merge node states
	*/
	char m_nodeStates[50];

public:
	friend class NodeMgr;
	friend class Overseer;
	void setID(int a_id, int a_groupGUID);
	void setPosition(int pos);
	int getPosition();
	int getPower();
	int getFrequency();
	int getRecvThreshold();
	bool isBusy();
	int getID();

	virtual void wakeUp(); // Do some cleaning.
	virtual void sleep();

	virtual void recvPacket(Packet* pkt) = 0;
	virtual Packet* sendPacket(int packetType) = 0;
	virtual void transit(std::string toStage) = 0;// FSM transition

	bool nodeStateComplete();
	void resetNodeStates();
	void copyNodeStates(char* src, char* des);
	void mergeNodeStates(char* src, char* des);
	void setNodeAlive(int nodeID);
	void setNodeDead(int nodeID);
};

}

