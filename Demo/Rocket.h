#pragma once
#include "Common.h"

class Rocket
{
public:
	Rocket(const string& trackPath);
	~Rocket();

	void Connect(const string& host);
};
