#pragma once
#include "Common.h"

class Soundtrack
{
public:
	Soundtrack(std::string filepath);
	~Soundtrack();

	void play();
	void stop();
	void setVolume(float volume);
	double getDuration();

private:
	HSTREAM _mp3Stream;
};