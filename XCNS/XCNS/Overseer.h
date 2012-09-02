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
		unsigned int getTime();
		static Overseer* getInstance();
		~Overseer(void);
	private:
		static Overseer* m_instance;
		Overseer(void);
	private:
		std::priority_queue<Event*, std::vector<Event*>, cmpEvent> m_evq;// event queue;
		unsigned int m_time;
	};
}

