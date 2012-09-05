#include "HeadNode.h"
#include "Packet.h"
#include "LSPacket.h"
#include "IMLPacket.h"
#include "NodeEvent.h"
#include "Overseer.h"
#include "MessageEvent.h"
namespace XCNS
{


	HeadNode::HeadNode(void)
	{
	}


	HeadNode::~HeadNode(void)
	{
	}

	void HeadNode::sleep()
	{

	}

	void HeadNode::wakeUp()
	{
		// Transit to Q1
		transit("Q1");
		resetNodeStates();
	}

	void HeadNode::recvPacket(Packet* pkt)
	{
		if (m_sleeping || m_disabled) 
			return;

		switch (pkt->getType())
		{
		case Packet::PACKET_LS:
			if (m_state.compare("Q1") == 0)
			{
				// merge
				LSPacket* lspkt = (LSPacket*)pkt;
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
			else if (m_state.compare("Q2") == 0)
			{
				m_lastRecvTime = Overseer::getInstance()->getTime();
			}
			// If ls is from front nodes, the packet acts as ACK
			// else if ls is from previous node, update nodestates
			// then check if nodestates are completed

			break;
		case Packet::PACKET_IML:
			// only recv packet from previous node
			// update nodestates
			if (m_state.compare("Q1") == 0)
			{
				setNodeAlive(pkt->getSenderID());
				if (pkt->getSenderID() < m_minIML)
				{
					m_minIML = pkt->getSenderID();
					m_lastLSFromMinIMLTime = -1;
				}
				if (nodeStateComplete())
				{
					transit("Q1");
					return;
				}
			}
			else if (m_state.compare("Q2") == 0)
			{
				m_lastRecvTime = Overseer::getInstance()->getTime();
			}
			break;
		}
	}

	Packet* HeadNode::sendPacket(int packetType)
	{
		switch (packetType)
		{
		case Packet::PACKET_IML:/*
			IMLPacket* imlpkt = new IMLPacket();
			imlpkt->setSenderID(m_id);

			// Add a new event
			MessageEvent* mevt = new MessageEvent(Event::EVENT_MESSAGE_IML);
			mevt->setNodeID(m_id);
			mevt->setTimeStamp(Overseer::getInstance()->getTime() + m_IMLgap);
			// the info tells that this node has to send an ls message
			Overseer::getInstance()->addEvent(mevt);


			return imlpkt;
			*/

			break;
		case Packet::PACKET_LS:
			if (m_state.compare("Q2") == 0)
			{
				if (Overseer::getInstance()->getTime() - m_lastRecvTime > m_timeBeforeSleep)
				{
					transit("Q0");
				}
				else
				{
					MessageEvent* mevt = new MessageEvent(Event::EVENT_MESSAGE_LS);
					mevt->setNodeID(m_id);
					mevt->setTimeStamp(Overseer::getInstance()->getTime() + m_LSgap);
					// the info tells that this node has to send an ls message
					Overseer::getInstance()->addEvent(mevt);
				}
			}
			return NULL;
			break;
		}
		return NULL;
	}

	void HeadNode::transit(std::string toState)
	{
		m_state = toState;

		// Do logic.
		// current state is Q1
		if (toState.compare("Q1") == 0)
		{
			
		}
		else if (toState.compare("Q2") == 0)
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