#include "Clock.h"
#include "header.h"

ChessClock::ChessClock(double initial_time, double increment)
{
	m_total_time = initial_time;
	m_remaining = initial_time;
	m_increment = increment;
	m_origin = clock();
}

/// @brief Updates the col color clock
/// @param col The color of the player wich clock you want to update
/// @return A 0-1 float as % of remaining time from the initial time.Returns -1 if run out of time
float ChessClock::updateChessClock()
{
	if (m_total_time <= 0 || m_remaining > m_total_time)
		return 1;
	if (m_remaining <= 0)
		return 0;
	m_remaining += m_increment;
	m_remaining -= (float)(clock() - m_origin) / CLOCKS_PER_SEC;
	m_origin = clock();
	if (m_remaining <= 0)
		return 0;
	return (m_remaining / m_total_time);
}
