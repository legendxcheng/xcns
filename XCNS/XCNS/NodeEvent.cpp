#include "NodeEvent.h"

namespace XCNS
{

NodeEvent::NodeEvent(unsigned int atype)
{
	m_type = atype;
}

NodeEvent::NodeEvent(void)
{
}


NodeEvent::~NodeEvent(void)
{
}

NodeEvent::NodeEvent(unsigned int atype, int a_nodeID, bool a_busy)
{
	m_nodeID = a_nodeID;
	m_type = atype;
	m_isBusy = a_busy;

}

std::string NodeEvent::getToState()
{
	return m_toState;
}


NodeEvent::NodeEvent(unsigned int a_type, int a_nodeID, std::string fromS, std::string toS)
{
	m_nodeID = a_nodeID;
	m_type = a_type;
	m_fromState = fromS;
	m_toState = toS;
}	

int NodeEvent::getNodeID()
{
	return m_nodeID;
}

void NodeEvent::setNodeID(int nid)
{
	m_nodeID = nid;
}

}