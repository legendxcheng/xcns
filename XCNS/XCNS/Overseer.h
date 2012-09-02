#pragma once
#include <queue>
#include <vector>
#include "Event.h"

namespace XCNS
{
	struct cmpEvent
	{
		bool operator() (Event* a, Event* b)
		{

			if (a->getTimeStamp() <= b->getTimeStamp())
			{
				return true;
			}
			return false;
		}
	};

	class Overseer
	{
	public:
		Overseer(void);
		~Overseer(void);

	private:
		std::priority_queue<Event*, std::vector<Event*>, cmpEvent> m_evq;// event queue;
	};
}

