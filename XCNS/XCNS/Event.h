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
	private:
		unsigned int m_timeStamp;
	};
}

