#pragma once
#include "Node.h"
namespace XCNS
{


	class NormalNode : public Node
	{
	public:
		NormalNode(void);
		~NormalNode(void);

		virtual void transit(std::string toState);
		virtual void recvPacket(Packet* pkt);
		virtual void sendPackrt(Packet* pkt);
	};

}