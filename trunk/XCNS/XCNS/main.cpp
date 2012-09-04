#include "stdio.h"
#include "stdlib.h"
#include "ConfigReader.h"
#include "Overseer.h"
/*
	The time unit of this system is 0.1ms, so time is represented by an uint.
	For example, 3600 means 360ms, that is, 1 hour.
*/
void main()
{
	// XML test
	XCNS::Overseer* ovsr = XCNS::Overseer::getInstance();
	ovsr->initialize();
	ovsr->simulate();
}