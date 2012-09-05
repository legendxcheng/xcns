#include "TailNode.h"
#include "MessageEvent.h"
#include "Overseer.h"
#include "LSPacket.h"
#include "IMLPacket.h"
#include "NodeEvent.h"

namespace XCNS
{


	TailNode::TailNode(void)
	{
	}


	TailNode::~TailNode(void)
	{
	}

	void TailNode::wakeUp()
	{
		// Enter Q1.
		transit("Q1");
	}

	void TailNode::recvPacket(Packet* pkt)
	{
		if (m_sleeping || m_disabled) 
			return;

		switch (pkt->getType())
		{
		case Packet::PACKET_LS:
			// Absolutly the ls must be sent from front nodes.

			// Insert a sleep event
			NodeEvent* nevt = new NodeEvent(Event::EVENT_NODE_SLEEP);
			nevt->setTimeStamp(Overseer::getInstance()->getTime());
			nevt->setNodeID(m_id);
			Overseer::getInstance()->addEvent(nevt);

			// Insert a wakeUP event
			nevt = new NodeEvent(Event::EVENT_NODE_WAKEUP);
			nevt->setTimeStamp(Overseer::getInstance()->getTime() + m_sleepTime);
			nevt->setNodeID(m_id);
			Overseer::getInstance()->addEvent(nevt);
			break;
		}
	}

	Packet* TailNode::sendPacket(int packetType)
	{
		if (m_sleeping || m_disabled)
			return NULL;
		switch(packetType)
		{
		case Packet::PACKET_LS:
			LSPacket* lspkt = new LSPacket();
			lspkt->setNodeState(m_nodeStates);
			lspkt->setSenderID(m_id);

			// Add a new event
			MessageEvent* mevt = new MessageEvent(Event::EVENT_MESSAGE_LS);
			mevt->setNodeID(m_id);
			mevt->setTimeStamp(Overseer::getInstance()->getTime() + m_LSgap);
			// the info tells that this node has to send an ls message
			Overseer::getInstance()->addEvent(mevt);

			return lspkt;
			break;
		}
		return NULL;
	}

	void TailNode::transit(std::string toState)
	{
		m_state = toState;

		// Do logic.
		// current state is Q1
		if (toState.compare("Q1") == 0)
		{
			// Every m_LSgap sends an LS.
			// Create an event
			MessageEvent* mevt = new MessageEvent(Event::EVENT_MESSAGE_LS);
			mevt->setNodeID(m_id);
			mevt->setTimeStamp(Overseer::getInstance()->getTime());
			// the info tells that this node has to send an ls message
			Overseer::getInstance()->addEvent(mevt);
		}
	}

}