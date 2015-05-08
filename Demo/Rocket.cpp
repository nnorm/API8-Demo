#include "Rocket.h"

Rocket::Rocket(const string& trackPath)
{
	sync_create_device(trackPath.c_str());
}

Rocket::~Rocket()
{

}

void Rocket::Connect(const string& host)
{

}
