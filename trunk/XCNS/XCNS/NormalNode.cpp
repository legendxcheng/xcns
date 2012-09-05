#include "NormalNode.h"
#include "MessageEvent.h"
#include "IMLPacket.h"
#include "NodeEvent.h"
#include "LSPacket.h"
#include "Overseer.h"


namespace XCNS
{


	NormalNode::NormalNode(void)
	{
		m_isTailNode = false;
	}


	NormalNode::~NormalNode(void)
	{
	}

	void NormalNode::wakeUp()
	{
		m_lastLSFromMinIMLTime = -1;
		m_lastRecvTime = -1;
		resetNodeStates();
		if (m_isTailNode)
			transit("Q2");
		else
			transit("Q1");
	}

	void NormalNode::sleep()
	{

	}

	void NormalNode::recvPacket(Packet* pkt)
	{
		switch (pkt->getType())
		{
		case Packet::PACKET_IML:
			if (m_state.compare("Q1") == 0)
			{
				if (pkt->getSenderID() < m_id) //  IML from previous node, do not process it
				{
					return;
				}
				else if (pkt->getSenderID() > m_id)
				{
					setNodeAlive(pkt->getSenderID());
					if (pkt->getSenderID() < m_minIML)
					{
						m_minIML = pkt->getSenderID();
						m_lastLSFromMinIMLTime = -1;
					}
				}
			}
			else if (m_state.compare("Q2") == 0)
			{
				m_lastRecvTime = Overseer::getInstance()->getTime();
			}
			break;
		case Packet::PACKET_LS:
			if (m_state.compare("Q1") == 0)
			{
				// merge
				LSPacket* lspkt = (LSPacket*)pkt;
				if (lspkt->getSenderID() > m_id) // ls from nodes behind
				{
					mergeNodeStates(lspkt->getNodeState(), m_nodeStates);
					if (nodeStateComplete())
					{
						transit("Q2");
						return;
					}
					if (pkt->getSenderID() == m_minIML)
					{
						// recv an ls from minIML
						if (m_lastLSFromMinIMLTime < 0) // never recv ls from minIML
						{
							m_lastLSFromMinIMLTime = Overseer::getInstance()->getTime();
						}
						else if (Overseer::getInstance()->getTime() - m_lastLSFromMinIMLTime 
						> m_timeBeforeJudgingDeath)
						{
							for (int i = m_id + 1; i < m_minIML; ++i)
							{
								setNodeDead(i);
							}
							transit("Q2");
						}
					}
					else if (pkt->getSenderID() < m_minIML)
					{
						m_minIML = pkt->getSenderID();
						m_lastLSFromMinIMLTime = Overseer::getInstance()->getTime();
					}
				}
				else if (lspkt->getSenderID() < m_id) // ls from front nodes, claiming they are completed
				{
					transit("Q2");
				}
				
			}
			else if (m_state.compare("Q2") == 0)
			{
				m_lastRecvTime = Overseer::getInstance()->getTime();
			}
			break;
		}

	}

	void NormalNode::setAsTailNode()
	{
		m_isTailNode = true;
	}

	Packet* NormalNode::sendPacket(int packetType)
	{
		switch (packetType)
		{
		case Packet::PACKET_IML:
			if (m_state.compare("Q1") == 0)
			{
				IMLPacket* imlpkt = new IMLPacket();
				imlpkt->setSenderID(m_id);

				// Add a new event
				MessageEvent* mevt = new MessageEvent(Event::EVENT_MESSAGE_IML);
				mevt->setNodeID(m_id);
				mevt->setTimeStamp(Overseer::getInstance()->getTime() + m_IMLgap);
				// the info tells that this node has to send an ls message
				Overseer::getInstance()->addEvent(mevt);

				return imlpkt;
			}

			break;
		case Packet::PACKET_LS:
			if (m_state.compare("Q2") == 0)
			{
				LSPacket* lspkt = new LSPacket();
				lspkt->setSenderID(m_id);
				lspkt->setNodeState(m_nodeStates);

				// Add a new event
				MessageEvent* mevt = new MessageEvent(Event::EVENT_MESSAGE_LS);
				mevt->setNodeID(m_id);
				mevt->setTimeStamp(Overseer::getInstance()->getTime() + m_LSgap);
				// the info tells that this node has to send an ls message
				Overseer::getInstance()->addEvent(mevt);

				if (m_lastRecvTime >= 0 && Overseer::getInstance()->getTime() - m_lastRecvTime > m_timeBeforeSleep)
				{
					transit("Q0");
				}
				return lspkt;
			}
			break;
		}
		return NULL;
	}

	void NormalNode::transit(std::string toState)
	{
		m_state = toState;

		// do logic
		if (m_state.compare("Q1") == 0)
		{
			// Every m_LSgap sends an LS.
			// Create an event
			MessageEvent* mevt = new MessageEvent(Event::EVENT_MESSAGE_IML);
			mevt->setNodeID(m_id);
			mevt->setTimeStamp(Overseer::getInstance()->getTime());
			// the info tells that this node has to send an ls message
			Overseer::getInstance()->addEvent(mevt);
		}
		else if(m_state.compare("Q2") == 0)
		{
			// Every m_LSgap sends an LS.
			// Create an event
			MessageEvent* mevt = new MessageEvent(Event::EVENT_MESSAGE_LS);
			mevt->setNodeID(m_id);
			mevt->setTimeStamp(Overseer::getInstance()->getTime());
			// the info tells that this node has to send an ls message
			Overseer::getInstance()->addEvent(mevt);
		}
		else if (m_state.compare("Q0") == 0)
		{
			NodeEvent* mevt = new NodeEvent(Event::EVENT_NODE_SLEEP);
			mevt->setNodeID(m_id);
			mevt->setTimeStamp(Overseer::getInstance()->getTime());
			// the info tells that this node has to send an ls message
			Overseer::getInstance()->addEvent(mevt);

		}
	}
}