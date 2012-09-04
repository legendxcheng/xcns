#pragma once
#include <queue>
#include <vector>
#include "Event.h"
#include "NodeMgr.h"

class ConfigReader;

namespace XCNS
{


	class Overseer
	{
	public:
		struct cmpEvent
		{
			bool operator()(Event* a, Event* b)
			{

				return *b < *a;
			}
		};
	public:
		void addEvent(Event* evt);
		friend class NodeMgr;
		void initialize();
		friend class ConfigReader;
		unsigned int getTime();
		static Overseer* getInstance();
		void simulate();
		static bool canReceiveSignal( double distance, double frequency, double sendingPower, double threshold );
		~Overseer(void);
	private:
		void handleEvent(Event* evt);
		static Overseer* m_instance;
		Overseer(void);
	private:
		std::priority_queue<Event*, std::vector<Event*>, cmpEvent> m_evq;// event queue;
		unsigned int m_time;

	// Global variable
	private:
		int m_carriageLength; // In meter
		int m_nodePower; // In mW
		int m_recvThreshold; // In mW
		int m_nodeDelayOfHandlingMessage;// in 0.1ms
		int m_groupGUID;// 
		int m_carriageNum;// number of carriage
		unsigned long m_simulationPeriod; // in 0.1ms
		unsigned long m_nodeSleepTime; // in 0.1ms
		int m_logVerbosity; // 1 ~ 5
		int m_IMLgap;
		int m_ACKgap;
		int m_LSgap;
		int m_timeBeforeJudgingDeath;
		int m_timeBeforeSleep;
		int m_dropRate;
		int m_nodeFreq;
	// Getter
	public:
		int getCarriageNum();
	// Event handlers
	private:
		void nodeWakeUpHandler(Event* evt);
		void nodeSleepHandler(Event* evt);
		void nodeFSMHandler(Event* evt);
		void nodeBusyHandler(Event* evt);
		void nodeIdleHandler(Event* evt);
		void ACKMsgHandler(Event* evt);
		void LSMsgHandler(Event* evt);
		void IMLMsgHandler(Event* evt);
		

	};
}

