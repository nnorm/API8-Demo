#pragma once

#include <chrono>

class Clock
{
public:
	Clock();

	static Clock& Global();

	double Elapsed() const;
	double RtcDelta();
	void   Reset();
	void   Offset(double time);
	void   Pause(bool pause = true);
	bool   Paused() const;

private:
	std::chrono::high_resolution_clock::time_point startTime_;
	std::chrono::high_resolution_clock::time_point lastRtcDeltaTime_;
	std::chrono::high_resolution_clock::time_point pauseTime_;

	bool paused_;
};
