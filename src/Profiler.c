



#include "Profiler.h"
#include "assert.h"

//Global variables
ProfilerTimer glbProfilerTimer[TIMER_NUM_MAX];


int Profiler_StartTimer(ProfilerTimerName timerName)
{
#ifdef _WIN32
	GetSystemTimeAsFileTime( &(glbProfilerTimer[timerName].timeStart) );
#endif
	return 0;
}

int Profiler_ResetTimer(ProfilerTimerName timerName)
{
#ifdef _WIN32
	glbProfilerTimer[timerName].timeSum.dwHighDateTime = 0;
	glbProfilerTimer[timerName].timeSum.dwLowDateTime = 0;
#else
	glbProfilerTimer[timerName].timeStart = 0;
	glbProfilerTimer[timerName].timeSum = 0;
#endif

	return 0;
}

int Profiler_PauseTimer(ProfilerTimerName timerName)
{
#ifdef _WIN32
	{
		FILETIME	timeNow;
		GetSystemTimeAsFileTime( &timeNow );

		glbProfilerTimer[timerName].timeSum.dwHighDateTime += timeNow.dwHighDateTime 
															- glbProfilerTimer[timerName].timeStart.dwHighDateTime ;
		glbProfilerTimer[timerName].timeSum.dwLowDateTime += timeNow.dwLowDateTime 
															- glbProfilerTimer[timerName].timeStart.dwLowDateTime ;
	}
#endif
	return 0;
}

int Profiler_StopTimer(ProfilerTimerName timerName)
{
	Profiler_PauseTimer(timerName);
	return 0;
}

double Profiler_ReadTimerInSecond(ProfilerTimerName timerName)
{
#ifdef _WIN32
	return  ((double)glbProfilerTimer[timerName].timeSum.dwHighDateTime * (double)1e7
				+ (double)glbProfilerTimer[timerName].timeSum.dwLowDateTime
			)/(double)1e7;

#else
	return 0;
#endif
}