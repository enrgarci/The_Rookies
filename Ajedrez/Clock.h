#if !defined(CLOCK_H)
#define CLOCK_H
#include <ctime>

class ChessClock
{
private:
	double	total_time;
	double	remaining;
	double	increment;
	clock_t	origin;
	
public:
	/// @brief Created a Chess Clock
	/// @param initial_time sets the initial time of the clock to initial_time in seconds
	ChessClock(double initial_time = 600, double increment = 0);
	float	updateChessClock();
};


#endif // CLOCK_H
