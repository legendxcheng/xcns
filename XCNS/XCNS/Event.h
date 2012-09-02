#pragma once
namespace XCNS
{
	class Event
	{
	public:
		Event(void);
		~Event(void);
	public:
		unsigned int getTimeStamp();
	protected:
		unsigned int m_timeStamp;
		unsigned int m_id;// Every event has a unique id.
		static unsigned int m_eventCount;
		unsigned int m_type;
	public: // Constant.
		static const int EVENT_GLOBAL_SIMSTART = 0X1000;
		static const int EVENT_GLOBAL_SIMSEND = 0x10001;
		static const int EVENT_MESSAGE = 0x10002;
	};
}

