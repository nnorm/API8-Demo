#include "Soundtrack.h"

Soundtrack::Soundtrack(std::string filepath)
{
	this->_paused = true;
	if (!BASS_Init(-1, 44100, 0, 0, NULL))
	{
#ifdef _DEBUG
		int errorCode = BASS_ErrorGetCode();
		std::string errorString;
		switch (errorCode)
		{
		case BASS_ERROR_DX:
			errorString = "DirectX or ALSA not installed!";
			break;
		case BASS_ERROR_DEVICE:
			errorString = "invalid device!";
			break;
		case BASS_ERROR_ALREADY:
			errorString = "device already initialized!";
			break;
		case BASS_ERROR_DRIVER:
			errorString = "no available device driver!";
			break;
		case BASS_ERROR_FORMAT:
			errorString = "specified format is not supported by selected device!";
			break;
		case BASS_ERROR_MEM:
			errorString = "insufficient amount of memory!";
			break;
		case BASS_ERROR_NO3D:
			errorString = "could not initialize 3D support!";
			break;
		case BASS_ERROR_UNKNOWN:
			errorString = "unknown error occurred during initialization, complete mystery!";
			break;
		default:
			errorString = "unknown error occurred during initialization, complete mystery!";
			break;
		}
		std::cout << "[BASS] Error : " << errorString << std::endl;
#endif // _DEBUG
	}
	else
	{
#ifdef _DEBUG
		BASS_DEVICEINFO infoHandler = BASS_DEVICEINFO();
		bool deviceInfo = BASS_GetDeviceInfo(1, &infoHandler);
		std::cout << "[BASS] Device successfully initialized!" << std::endl;
		std::string name(infoHandler.name);
		std::string driver(infoHandler.driver);
		std::cout << "[BASS] Device info : name : " << name << std::endl;
		std::cout << "[BASS] Device info : driver : " << driver << std::endl;
#endif // _DEBUG
		
		this->_mp3Stream = BASS_StreamCreateFile(FALSE, filepath.c_str(), 0, 0, 0);
		if (this->_mp3Stream == 0)
		{
#ifdef _DEBUG
			int errorCode = BASS_ErrorGetCode();
			std::string errorString;
			switch (errorCode)
			{
			case BASS_ERROR_INIT:
				errorString = "BASS_Init has not been successfully called!";
				break;
			case BASS_ERROR_NOTAVAIL:
				errorString = "stream options not available!";
				break;
			case BASS_ERROR_FORMAT:
				errorString = "specified sample format is not supported by selected device/driver!";
				break;
			case BASS_ERROR_SPEAKER:
				errorString = "specified speaker flags are invalid";
				break;
			case BASS_ERROR_MEM:
				errorString = "insufficient amount of memory!";
				break;
			
			case BASS_ERROR_NO3D:
				errorString = "could not initialize 3D support!";
				break;
			case BASS_ERROR_UNKNOWN:
				errorString = "unknown error occurred during initialization, complete mystery!";
				break;
			default:
				errorString = "unknown error occurred during initialization, complete mystery!";
				break;
			}
			std::cout << "[BASS] Error : " << errorString << std::endl;
#endif //_DEBUG
		}
	}
}

Soundtrack::~Soundtrack()
{
	if (!BASS_Free())
	{
#ifdef _DEBUG
		int errorCode = BASS_ErrorGetCode();
		std::cout << "[BASS] Error : " << "BASS_Init has not been successfully called!" << std::endl;
#endif // _DEBUG
	}
}

void Soundtrack::play()
{
	if (!BASS_ChannelPlay(this->_mp3Stream,FALSE))
	{
#ifdef _DEBUG
		int errorCode = BASS_ErrorGetCode();
		std::cout << "[BASS] Error : " << "Cannot play soundtrack : BASS_Init has not been successfully called!" << std::endl;
#endif // _DEBUG
	}
	else
	{
		this->_paused = false;
	}
	
}

void Soundtrack::stop()
{
	if (!BASS_ChannelStop(this->_mp3Stream))
	{
#ifdef _DEBUG
		int errorCode = BASS_ErrorGetCode();
		std::cout << "[BASS] Error : " << "Cannot stop soundtrack : BASS_Init has not been successfully called!" << std::endl;
#endif // _DEBUG
	}
	else
	{
		this->_paused = true;
	}
	
}

void Soundtrack::pause()
{
	if (!BASS_ChannelPause(this->_mp3Stream))
	{
#ifdef _DEBUG
		int errorCode = BASS_ErrorGetCode();
		std::string errorString;
		switch (errorCode)
		{
		case BASS_ERROR_NOPLAY:
			errorString = "channel is not playing";
			break;
		case BASS_ERROR_DECODE:
			errorString = "channel is not playable";
			break;
		case BASS_ERROR_ALREADY:
			errorString = "channel is already paused";
			break;
		default:
			errorString = "unknown error occurred when pausing the channel, complete mystery!";
			break;
		}
		std::cout << "[BASS] Error : " << errorString << std::endl;
#endif
	}
	else
	{
		this->_paused = true;
	}
}

void Soundtrack::setVolume(float volume)
{
	if (!BASS_SetVolume(volume))
	{
#ifdef _DEBUG
		int errorCode = BASS_ErrorGetCode();
		std::string errorString;
		switch (errorCode)
		{
		case BASS_ERROR_INIT:
			errorString = "Cannot set volume : BASS_Init has not been successfully called!";
			break;
		case BASS_ERROR_NOTAVAIL:
			errorString = "No volume control available!";
			break;
		case BASS_ERROR_ILLPARAM:
			errorString = "Volume value provided is invalid!";
			break;
		case BASS_ERROR_UNKNOWN:
			errorString = "unknown error occurred when trying to set volume, complete mystery!";
			break;
		default:
			errorString = "unknown error occurred when trying to set volume, complete mystery!";
			break;
		}
		std::cout << "[BASS] Error : setting volume : " << errorString << std::endl;
#endif // _DEBUG
	}
	else
	{
#ifdef _DEBUG
		std::cout << "[BASS] Volume changed : volume modified to " << volume << std::endl;
#endif // _DEBUG
	}
}

void Soundtrack::setPosition(float pos)
{
	QWORD qwBytes = BASS_ChannelSeconds2Bytes(this->_mp3Stream, double(pos));
	BASS_ChannelSetPosition(this->_mp3Stream, qwBytes, BASS_POS_BYTE);
}

bool Soundtrack::isPaused()
{
	return this->_paused;
}