#include "Node.h"
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
	m_sleeping = true;
}


Node::~Node(void)
{
}

void Node::wakeUp()
{

	m_sleeping = false;
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
}