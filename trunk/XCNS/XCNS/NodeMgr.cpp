#include "NodeMgr.h"
#include "Overseer.h"
#include "NormalNode.h"
#include "HeadNode.h"


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
}


/*
	Get number of nodes.

*/
int NodeMgr::getNodeNum()
{
	return m_nodes.size();
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

		m_nodes.push_back(newNode);
	}
}

}

