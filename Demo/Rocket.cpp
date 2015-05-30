#include "Rocket.h"
#include "Clock.h"
#include "Soundtrack.h"

Rocket::Rocket(const string& trackPath)
{
	tempo_ = 128.0;
	rowsPerBeat_ = 8.0;
	rowRate_ = (tempo_ / 60.0) * rowsPerBeat_;

	syncDevice_ = sync_create_device(trackPath.c_str());
	soundtrack_ = nullptr;
}

Rocket::~Rocket()
{
	sync_destroy_device(syncDevice_);
}

void Rocket::LinkToSoundtrack(Soundtrack* st)
{
	soundtrack_ = st;
}

Soundtrack* Rocket::GetSoundtrack()
{
	return soundtrack_;
}

void Rocket::SetTempo(double tempo)
{
	tempo_ = tempo;
	rowRate_ = (tempo_ / 60.0) * rowsPerBeat_;
}

void Rocket::SetRowsPerBeat(double rowsPerBeat)
{
	rowsPerBeat_ = rowsPerBeat;
	rowRate_ = (tempo_ / 60.0) * rowsPerBeat_;
}

double Rocket::GetRowFromTime(double time)
{
	return time * rowRate_;
}

double Rocket::GetTimeFromRow(double row)
{
	return row / rowRate_;
}

void Rocket::Connect(const string& host)
{
	sync_connect(syncDevice_, host.c_str(), SYNC_DEFAULT_PORT);
}

void Rocket::Update()
{
#ifdef SYNC_PLAYER
	static sync_cb* s_callbacks = nullptr;

	if (!s_callbacks)
	{
		s_callbacks = new sync_cb;
		s_callbacks->pause = [](void* d, int flag) { if (flag){ ((Rocket*)d)->GetSoundtrack()->pause(); Clock::Global().Pause(); } else { ((Rocket*)d)->GetSoundtrack()->play(); Clock::Global().Pause(false); } };
		s_callbacks->is_playing = [](void* d) -> int    { /* return true if paused, false otherwise */ if (((Rocket*)d)->GetSoundtrack()->isPaused()) { return true; } else { return false; } };
		s_callbacks->set_row    = [](void* d, int row)  {
			double rTime = ((Rocket*)d)->GetTimeFromRow(double(row));

			// Set global clock to rTime
			Clock::Global().Reset();
			Clock::Global().Offset(rTime);


			// Set song position too !
			((Rocket*)d)->GetSoundtrack()->setPosition(float(rTime));
		};
	}

	double globalTime = 0.0 /* global demo clock time */;
	int row = int(GetRowFromTime(globalTime));
	sync_update(syncDevice_, row, s_callbacks, this);
#endif
}
