#include "Clock.h"
#include "header.h"

ChessClock::ChessClock(double initial_time, double increment)
{
	total_time = initial_time;
	remaining = initial_time;
	origin = clock();
}

/// @brief Updates the col color clock
/// @param col The color of the player wich clock you want to update
/// @return A 0-1 float as % of remaining time from the initial time.Returns -1 if run out of time
float	ChessClock::updateChessClock()
{
	if (remaining <= 0) return 0;
	remaining -= (float)(clock() - origin) / CLOCKS_PER_SEC;
	origin = clock();
	if (remaining <= 0) return 0;
	return (remaining / total_time);
}

