#include "NodeMgr.h"
#include "Overseer.h"
#include "NormalNode.h"
#include "HeadNode.h"
#include "Packet.h"
#include "Logger.h"
namespace XCNS
{


NodeMgr::NodeMgr(void)
{
}


NodeMgr::~NodeMgr(void)
{
}

NodeMgr* NodeMgr::m_instance = 0;

NodeMgr* NodeMgr::getInstance()
{
	if (!m_instance)
		m_instance = new NodeMgr();
	return m_instance;
}

Node* NodeMgr::getNodeByID(int id)
{
	for (int i = 0; i < m_nodes.size(); ++i)
	{
		if (m_nodes[i]->getID() == id)
			return m_nodes[i];
	}
	return NULL;
}


/*
	Get number of nodes.

*/
int NodeMgr::getNodeNum()
{
	return m_nodes.size();
}

void NodeMgr::disableNode(int nodeID)
{
	char logStr[300];
	sprintf(logStr, "node %d is disabled.", nodeID);
	Logger::getInstance()->addLog(1, logStr);
	m_nodes[nodeID]->enable(false);
}

void NodeMgr::enableNode(int nodeID)
{
	char logStr[300];
	sprintf(logStr, "node %d is enabled.", nodeID);
	Logger::getInstance()->addLog(1, logStr);

	m_nodes[nodeID]->enable(true);
}

/*

	Initializing nodes.
*/
void NodeMgr::initialize()
{
	Overseer* ovsr = Overseer::getInstance();

	// Insert HeadNode first.
	HeadNode* hnode = new HeadNode();
	//Set headnode attributes
	hnode->m_id = 0;
	hnode->setPosition(0);
	hnode->m_power = ovsr->m_nodePower;
	hnode->m_recvThreshold = ovsr->m_recvThreshold;
	hnode->m_timeBeforeJudgingDeath = ovsr->m_timeBeforeJudgingDeath;
	hnode->m_timeBeforeSleep = ovsr->m_timeBeforeSleep;
	hnode->m_sleepTime = ovsr->m_nodeSleepTime;
	hnode->m_freq = ovsr->m_nodeFreq;
	hnode->m_LSgap = ovsr->m_LSgap;

	m_nodes.push_back(hnode);

	for (int i = 1; i <= ovsr->m_carriageNum; ++i)
	{
		// Insert normal nodes.
		NormalNode* newNode = new NormalNode();

		// Set node's attributes.
		newNode->setID(i, ovsr->m_groupGUID);
		newNode->setPosition(ovsr->m_carriageLength * i);
		newNode->m_power = ovsr->m_nodePower;
		newNode->m_recvThreshold = ovsr->m_recvThreshold;
		newNode->m_timeBeforeJudgingDeath = ovsr->m_timeBeforeJudgingDeath;
		newNode->m_timeBeforeSleep = ovsr->m_timeBeforeSleep;
		newNode->m_IMLgap = ovsr->m_IMLgap;
		newNode->m_LSgap = ovsr->m_LSgap;
		newNode->m_ACKgap = ovsr->m_ACKgap;	
		newNode->m_sleepTime = ovsr->m_nodeSleepTime;
		newNode->m_freq = ovsr->m_nodeFreq;

		m_nodes.push_back(newNode);
	}
	disableNode(9);
	disableNode(5);
	disableNode(2);
	NormalNode* tailNode = (NormalNode*)m_nodes[ovsr->m_carriageNum];
	tailNode->setAsTailNode();
}

void NodeMgr::broadcastPacket(Packet* pkt)
{
	for (int i = 0; i < m_nodes.size(); ++i)
	{
		if (i == pkt->getSenderID())
			continue;
		Node* snode = m_nodes[pkt->getSenderID()];
		Node* rnode = m_nodes[i];
		if (canReceiveSignal(abs(snode->getPosition() - rnode->getPosition()), snode->getFrequency(), snode->getPower(), 
			rnode->getRecvThreshold()))
		{
			std::string pkttp;
			switch (pkt->getType())
			{
			case Packet::PACKET_IML:
				pkttp = "IML";
				break;
			case Packet::PACKET_LS:
				pkttp = "LS";
				break;
			}
	
			if (!(rnode->isDisalbed() || rnode->isSleeping()))
			{
				char logStr[300];
				sprintf(logStr, "node %d receives %s packet from node %d.", rnode->getID(), pkttp.c_str(), snode->getID());
				Logger::getInstance()->addLog(2, logStr);
				rnode->recvPacket(pkt);

			}
		}
	}
}

//distance��ʾ������룬��λΪm��frequency��ʾ�ڵ㹤��Ƶ�ʣ���λΪMHz��sendingPower��ʾ���͹��ʣ���λΪmW��
bool NodeMgr::canReceiveSignal( double distance, double frequency, double sendingPower, double threshold )
{
	double receivingPower = 0;
	receivingPower = 1000000 * sendingPower / ( 1753.88 * distance * distance * frequency * frequency );
	if (1000 * receivingPower < threshold)
	{
		return false;
	}
	return true;
}

}

