#include "Node.h"
#include "Logger.h"
#include "Overseer.h"
namespace XCNS
{

void Node::setID(int a_id, int a_groupGUID)
{
	m_id = a_id;
	m_groupGUID = a_groupGUID;
}

bool Node::isBusy()
{
	return m_busy;
}

void Node::setPosition(int pos)
{
	m_pos = pos;
}

int Node::getID()
{
	return m_id;
}

Node::Node(void)
{
	m_state = "Q0";
	m_sleeping = true;
	m_disabled = false;
}


Node::~Node(void)
{
}

bool Node::isSleeping()
{
	return m_sleeping;
}

bool Node::isDisalbed()
{
	return m_disabled;
}

void Node::wakeUp()
{
	m_minIML = 10000; //
	m_sleeping = false;
}


int Node::getPower()
{
	return m_power;
}
int Node::getFrequency()
{
	return m_freq;
}
int Node::getRecvThreshold()
{
	return m_recvThreshold;
}

void Node::sleep()
{
	m_sleeping = true;
}

void Node::copyNodeStates(char* src, char* des)
{
	memcpy(des, src, sizeof(char) * 50);
}

void Node::mergeNodeStates(char* src, char* des)
{
	for (int i = 0; i < 50; ++i)
	{
		des[i] = des[i] | src[i];
	}
}

void Node::resetNodeStates()
{
	memset(m_nodeStates, 0, sizeof(char) * 50);// set all as unknown
	// set self as alive
	setNodeAlive(m_id);
}

void Node::setNodeAlive(int nodeID)
{
	int tmp = nodeID / 4;
	int tmp2 = nodeID % 4;
	switch (tmp2)
	{
	case 0:
		m_nodeStates[tmp] = m_nodeStates[tmp] | 1;
		break;
	case 1:
		m_nodeStates[tmp] = m_nodeStates[tmp] | 4;
		break;
	case 2:
		m_nodeStates[tmp] = m_nodeStates[tmp] | 16;
		break;
	case 3:
		m_nodeStates[tmp] = m_nodeStates[tmp] | 64;
		break;
	}
	 
}

void Node::enable(bool able)
{
	m_disabled = !able;
}

int Node::getPosition()
{
	return m_pos;
}

void Node::setNodeDead(int nodeID)
{
	int tmp = nodeID / 4;
	int tmp2 = nodeID % 4;
	switch (tmp2)
	{
	case 0:
		m_nodeStates[tmp] = m_nodeStates[tmp] | 2;
		break;
	case 1:
		m_nodeStates[tmp] = m_nodeStates[tmp] | 8;
		break;
	case 2:
		m_nodeStates[tmp] = m_nodeStates[tmp] | 32;
		break;
	case 3:
		m_nodeStates[tmp] = m_nodeStates[tmp] | 128;
		break;
	}
}

bool Node::nodeStateComplete()
{
	// from current node id to the tail
	for (int i = m_id; i <= Overseer::getInstance()->getCarriageNum(); ++i)
	{
		int tmp = i / 4;
		int tmp2 = i % 4;
		switch (tmp2)
		{
		case 0:
			if (m_nodeStates[tmp] & 3) continue;
			return false;
			break;
		case 1:
			if (m_nodeStates[tmp] & 12) continue;
			return false;
			break;
		case 2:
			if (m_nodeStates[tmp] & 48) continue;
			return false;
			break;
		case 3:
			if (m_nodeStates[tmp] & 192) continue;
			return false;
			break;
		}
	}
	return true;
}

void Node::printStatistics()
{
	Logger* logger = Logger::getInstance();
	char logStr[300];

	if (m_disabled)
	{
		sprintf(logStr, "Node %d is dead.", m_id);
		Logger::getInstance()->addLogNoTime(1, logStr);

	}
	else
	{
		sprintf(logStr, "Node %d statistics:", m_id);
		Logger::getInstance()->addLogNoTime(1, logStr);
		sprintf(logStr, "	Packets sent: %d", m_sendCount);
		Logger::getInstance()->addLogNoTime(1, logStr);
		sprintf(logStr, "	Packets recv: %d", m_recvCount);
		Logger::getInstance()->addLogNoTime(1, logStr);

	}

	
}


}