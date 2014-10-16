#pragma once
#include <Windows.h>

class GameTimer
{
public:


	float elapsedTime, accumulatedTime, frameMin, totalTime, frameTime;

	__int64 start, end, freq, numTicks;

	void Pause();
	void Resume();

	bool UpdateTime()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&end);
		elapsedTime = (float)(end - start)/(float)freq;
		QueryPerformanceCounter((LARGE_INTEGER*)&start);

		totalTime = totalTime + elapsedTime;
		accumulatedTime = accumulatedTime + elapsedTime;

		if(accumulatedTime < frameMin)
			return false;
		else
		{
			frameTime = accumulatedTime;
			accumulatedTime = 0;
			return true;
		}
	}

	GameTimer(void)
	{
		totalTime = 0;
		accumulatedTime = 0;
		frameMin = 0.001;
		QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
		QueryPerformanceCounter((LARGE_INTEGER*)&start);
	}

	~GameTimer(void)
	{}
};
