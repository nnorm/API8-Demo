#include "clock.h"

Clock::Clock()
{
	startTime_ = std::chrono::high_resolution_clock::now();
	lastRtcDeltaTime_ = startTime_;
	paused_ = false;
}

Clock& Clock::Global()
{
	static Clock clk;
	return clk;
}

double Clock::Elapsed() const
{
	std::chrono::duration<double> dsec;

	if (paused_)
		dsec = pauseTime_ - startTime_;
	else
		dsec = std::chrono::high_resolution_clock::now() - startTime_;

	return dsec.count();
}

double Clock::RtcDelta()
{
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> dsec = now - lastRtcDeltaTime_;
	lastRtcDeltaTime_ = now;

	return dsec.count();
}

void Clock::Reset()
{
	startTime_ = std::chrono::high_resolution_clock::now();
	lastRtcDeltaTime_ = startTime_;
	pauseTime_ = startTime_;
}

void Clock::Offset(double time)
{
	auto dtn = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(time));
	startTime_ -= dtn;
}

void Clock::Pause(bool pause /* = true */)
{
	if (pause == paused_)
		return;

	paused_ = pause;
	if (paused_)
		pauseTime_ = std::chrono::high_resolution_clock::now();
	else
		startTime_ += std::chrono::high_resolution_clock::now() - pauseTime_;

	auto lol = std::chrono::high_resolution_clock::now() - pauseTime_;
}

bool Clock::Paused() const
{
	return paused_;
}
