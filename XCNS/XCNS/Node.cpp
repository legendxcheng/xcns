#include "Node.h"

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

}