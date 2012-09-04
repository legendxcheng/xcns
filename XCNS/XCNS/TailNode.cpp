#include "TailNode.h"
#include "MessageEvent.h"
#include "Overseer.h"
#include "LSPacket.h"
#include "IMLPacket.h"


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

	}

	Packet* TailNode::sendPacket(int packetType)
	{
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
			LSPacket* pkt = new LSPacket();
			mevt->setPacket(pkt);
			Overseer::getInstance()->addEvent(mevt);
		}
	}

}