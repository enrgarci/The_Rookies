#if !defined(CLOCK_H)
#define CLOCK_H
#include <ctime>

class ChessClock
{
private:
	double	m_total_time;
	double	m_remaining;
	double	m_increment;
	clock_t	m_origin;
	
public:
	/// @brief Created a Chess Clock
	/// @param initial_time sets the initial time of the clock to initial_time in seconds
	ChessClock(double initial_time = -1, double increment = 0);
	float	updateChessClock();
	float	getInitialTime();
	float	getIncremet();
	void	setOrigin();
	void	setTime(float time);
};

inline float ChessClock::getInitialTime(){return (float)m_total_time;}
inline float ChessClock::getIncremet(){return (float)m_increment;}
inline void ChessClock::setOrigin(){m_origin = clock();}
inline void ChessClock::setTime(float time){m_total_time = time;}
#endif // CLOCK_H
