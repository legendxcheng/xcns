#pragma once
#include "Node.h"
class NodeMgr;

namespace XCNS
{


	class TailNode : public Node
	{
	private:
		int m_timeBeforeSleep;
		int m_LSgap;
	public:
		friend class NodeMgr;
		TailNode(void);
		~TailNode(void);
		virtual void recvPacket(Packet* pkt);
		virtual Packet* sendPacket(int packetType);
		virtual void transit(std::string toStage);
		virtual void wakeUp();
	};

}