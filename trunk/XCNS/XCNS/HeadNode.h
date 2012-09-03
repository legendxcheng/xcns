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
	public:
		friend class NodeMgr;
		HeadNode(void);
		~HeadNode(void);
		virtual void recvPacket(Packet* pkt);
		virtual void sendPacket(Packet* pkt);
		virtual void transit(std::string toStage);
	};

}