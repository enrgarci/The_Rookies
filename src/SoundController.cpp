#include "SoundController.h"
#include <iostream>
#include "ETSIDI.h"
using namespace std;
void SoundController::play(string soundname)
{
	string dir = "Music/Effects/" + soundname + ".mp3";
	const char* direction = dir.c_str();
	ETSIDI::play(direction);
}
void SoundController::playMusica(string soundname, bool loop)
{
	string dir = "Music/BGM/" + soundname + ".mp3";
	const char* direction = dir.c_str();
	ETSIDI::playMusica(direction, true);
}
void SoundController::stopMusica()
{
	ETSIDI::stopMusica();
}
