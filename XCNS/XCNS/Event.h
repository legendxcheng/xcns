#pragma once
namespace XCNS
{
	class Event
	{
	public:
		Event(void);
		~Event(void);
	public:
		int getType();
		unsigned int getTimeStamp();
		void setTimeStamp(unsigned long tstp);
	protected:
		unsigned long m_timeStamp;
		unsigned int m_id;// Every event has a unique id.
		static unsigned int m_eventCount;
		unsigned int m_type;
	public: // Constant.
		static const int EVENT_GLOBAL_SIMSTART = 0X1000;
		static const int EVENT_GLOBAL_SIMEND = 0x10001;
		static const int EVENT_MESSAGE_ACK = 0x10002;
		static const int EVENT_MESSAGE_LS = 0x10003;
		static const int EVENT_MESSAGE_IML = 0x10004;
	};
}

