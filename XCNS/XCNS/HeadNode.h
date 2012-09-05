#pragma once
#include "Node.h"
class NodeMgr;

namespace XCNS
{


	class HeadNode : public Node
	{
	private:
		int m_timeBeforeSleep;
		int m_timeBeforeJudgingDeath;
		int m_sleepTime;
		int m_LSgap;
	public:
		friend class NodeMgr;
		HeadNode(void);
		~HeadNode(void);
		virtual void recvPacket(Packet* pkt);
		virtual Packet* sendPacket(int packetType);
		virtual void transit(std::string toStage);
		virtual void wakeUp(); // Do some cleaning.
		virtual void sleep();
	};

}