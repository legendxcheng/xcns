#pragma once
#include "event.h"
#include <string>

namespace XCNS
{


class NodeEvent :
	public Event
{
private:
	int m_nodeID;
	std::string m_fromState;
	std::string m_toState;
	bool m_isBusy;
public:
	NodeEvent(unsigned int atype, int a_nodeID, std::string fromS, std::string toS); // state change event
	NodeEvent(unsigned int atype, int a_nodeID, bool a_busy);
	int getNodeID();
	NodeEvent(void);
	~NodeEvent(void);
	std::string getToState();
};
}

