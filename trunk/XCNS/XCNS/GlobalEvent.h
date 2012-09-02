#pragma once
#include "event.h"
namespace XCNS
{



class GlobalEvent :
	public Event
{
public:
	GlobalEvent(unsigned int a_type);
	GlobalEvent(void);
	~GlobalEvent(void);
};

}
