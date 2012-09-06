#pragma once

#include <vector>
#include "Node.h"
/*
	Class for managine nodes.
	Singleton
*/
class Packet;

namespace XCNS
{


class NodeMgr
{
private:
	NodeMgr(void);
	static NodeMgr* m_instance;
	
private:
	std::vector<Node*> m_nodes;

public:
	static NodeMgr* getInstance();
	~NodeMgr(void);
	static bool NodeMgr::canReceiveSignal( double distance, double frequency, double sendingPower, double threshold );
public:
	Node* getNodeByID(int id);
	void initialize();
	int getNodeNum();
	void broadcastPacket(Packet* pkt);
	void disableNode(int nodeID);
	void enableNode(int nodeID);
	void printStatistics();
};
}

