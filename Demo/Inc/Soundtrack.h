#pragma once
#include "Common.h"

class Soundtrack
{
public:
	Soundtrack(std::string filepath);
	~Soundtrack();

	void play();
	void stop();
	void pause();
	void setVolume(float volume);
	double getDuration();
	void setPosition(float pos);
	bool isPaused();

private:
	bool _paused;
	HSTREAM _mp3Stream;
};
