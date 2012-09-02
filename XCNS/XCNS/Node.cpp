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

Node::Node(void)
{
}


Node::~Node(void)
{
}

}