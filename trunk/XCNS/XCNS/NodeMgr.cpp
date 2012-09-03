#include "NodeMgr.h"

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

void NodeMgr::initialize()
{

}

}

