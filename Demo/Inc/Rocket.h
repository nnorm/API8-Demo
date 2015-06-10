#pragma once
#include "Common.h"

#define SYNC_PLAYER

struct sync_device;
struct sync_track;
class Soundtrack;

class Rocket
{
public:
	class Track
	{
	public:
		Track(Rocket* r, const string& name);
		float GetValueAt(double row);

	private:
		const sync_track* track_;
	};

	Rocket(const string& trackPath);
	~Rocket();

	sync_device* GetRawDevice();

	void LinkToSoundtrack(Soundtrack* st);
	Soundtrack* GetSoundtrack();

	void SetTempo(double tempo);
	void SetRowsPerBeat(double rowsPerBeat);
	double GetRowFromTime(double time);
	double GetTimeFromRow(double row);

#ifdef _DEBUG
	void Connect(const string& host);
#endif
	void Update();

	Track* CreateOrGet(const string& name);

private:
	sync_device* syncDevice_;

	double tempo_;
	double rowsPerBeat_;
	double rowRate_;
	double row_;

	Soundtrack* soundtrack_;

	unordered_map<string, Track*> tracks_;
};
