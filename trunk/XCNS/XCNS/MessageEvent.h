#pragma once
#include "event.h"
#include "Packet.h"
namespace XCNS
{



	class MessageEvent :
		public Event
	{
	private:
		int m_nodeID;
	public:
		int getNodeID();
		void setNodeID(int nid);
		MessageEvent(unsigned int a_type);
		MessageEvent(void);
		~MessageEvent(void);

	};
}