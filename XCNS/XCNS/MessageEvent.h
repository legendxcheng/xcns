#pragma once
#include "event.h"
namespace XCNS
{



	class MessageEvent :
		public Event
	{
	private:
		int m_nodeID;
	public:
		int getNodeID();
		MessageEvent(unsigned int a_type);
		MessageEvent(void);
		~MessageEvent(void);
	};
}