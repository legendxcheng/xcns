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
		static const int EVENT_GLOBAL_SIMEND = 0X1001;

		static const int EVENT_NODE_WAKEUP = 0x10010;
		static const int EVENT_NODE_SLEEP = 0x10011;
		static const int EVENT_NODE_FSM = 0x10012; // state change system
		static const int EVENT_NODE_IDLE = 0x10013;
		static const int EVENT_NOdE_BUSY = 0x10014;

		static const int EVENT_MESSAGE_ACK = 0x11000;
		static const int EVENT_MESSAGE_LS = 0x11001;
		static const int EVENT_MESSAGE_IML = 0x11002;
	};
}

