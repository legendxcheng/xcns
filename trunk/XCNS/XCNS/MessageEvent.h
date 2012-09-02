#pragma once
#include "event.h"
namespace XCNS
{



	class MessageEvent :
		public Event
	{
	public:
		MessageEvent(unsigned int a_type);
		MessageEvent(void);
		~MessageEvent(void);
	};
}