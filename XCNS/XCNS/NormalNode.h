#pragma once
#include "Node.h"
namespace XCNS
{


	class NormalNode : public Node
	{
	// Attributes
	private:
		friend class NodeMgr;
		int m_IMLgap;
		int m_ACKgap;
		int m_LSgap;
		int m_timeBeforeJudgingDeath;
		int m_timeBeforeSleep;

	public:
		NormalNode(void);
		~NormalNode(void);

		virtual void transit(std::string toState);
		virtual void recvPacket(Packet* pkt);
		virtual Packet* sendPacket(int packetType);
	};

}