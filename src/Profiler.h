

#pragma once

#include "common.h"
#include "time.h"

#ifdef	_WIN32
	#include <windows.h>

	typedef struct ProfilerTimer{
		int		status;

		FILETIME	timeStart;
		FILETIME	timeSum;
	}ProfilerTimer;

#else
	typedef struct ProfilerTimer{
		int		status;

		time_t	timeStart;
		time_t	timeSum;
	}ProfilerTimer;
#endif

typedef enum ProfilerTimerName{
	TIMER_GOP,
	TIMER_DCT3,
	TIMER_Q,
	TIMER_SCAN,
	TIMER_ABAC,

	TIMER_NUM_MAX
}ProfilerTimerName;


extern ProfilerTimer	glbProfilerTimer[TIMER_NUM_MAX];


int Profiler_StartTimer(ProfilerTimerName timerName);
int Profiler_ResetTimer(ProfilerTimerName timerName);
int Profiler_PauseTimer(ProfilerTimerName timerName);
int Profiler_StopTimer(ProfilerTimerName timerName);
double Profiler_ReadTimerInSecond(ProfilerTimerName timerName);
