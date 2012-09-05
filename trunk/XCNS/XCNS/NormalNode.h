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
		int m_sleepTime;

		bool m_isTailNode;

	public:
		NormalNode(void);
		~NormalNode(void);

		virtual void transit(std::string toState);
		virtual void recvPacket(Packet* pkt);
		virtual Packet* sendPacket(int packetType);
		virtual void wakeUp();
		virtual void sleep();
		
		void setAsTailNode();
	};

}