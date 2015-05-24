#pragma once
#include "Common.h"

#define SYNC_PLAYER

struct sync_device;
class Soundtrack;

class Rocket
{
public:
	Rocket(const string& trackPath);
	~Rocket();

	void LinkToSoundtrack(Soundtrack* st);
	Soundtrack* GetSoundtrack();

	void SetTempo(double tempo);
	void SetRowsPerBeat(double rowsPerBeat);
	double GetRowFromTime(double time);
	double GetTimeFromRow(double row);

	void Connect(const string& host);
	void Update();

private:
	sync_device* syncDevice_;

	double tempo_;
	double rowsPerBeat_;
	double rowRate_;
	double row_;

	Soundtrack* soundtrack_;
};
