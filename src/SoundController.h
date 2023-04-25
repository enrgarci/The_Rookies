#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;
class SoundController
{
public:
	void play(string soundname); //for sounds that play on events
	void playMusica(string soundname, bool loop); //for ambient sounds
	void stopMusica(); //to stop the music
};

