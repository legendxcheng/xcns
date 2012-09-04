#pragma once
#include "Node.h"
class NodeMgr;

namespace XCNS
{


	class TailNode : public Node
	{
	public:
		friend class NodeMgr;
		TailNode(void);
		~TailNode(void);
		virtual void recvPacket(Packet* pkt);
		virtual void sendPacket(Packet* pkt);
		virtual void transit(std::string toStage);
	};

}