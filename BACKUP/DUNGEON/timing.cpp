/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : image.h                                   *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 1, 2022                           *
 *                                                                            *
 *                    Last Update : January 9, 2022                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For image processing. And all the operations to images.                  *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include <ctime>
#include <Windows.h>

#include "timing.h"


/*
** Global virables.
*/
Time globalTimer;	// The timer used for game speed.
FPSTimer fpsTimer;
HPTimer hpTimer;


/******************************************************************************
 * Time::Time -- Constructor of time object.                                  *
 *                                                                            *
 *    The constructor get the very first info of the current time.            *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/sunxiaoyu/character-rain                   *
 *              https://codebus.cn/yangw/accurate-delay                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *============================================================================*/
Time::Time()
{
	/*
	** High precision timing function. Pretty COOL!
	*/
	QueryPerformanceFrequency(&m_tickPerSecond);
	QueryPerformanceCounter(&m_startTick);
	m_curTick.QuadPart = m_startTick.QuadPart;

	/*
	** In case of division of zero in the first frame.
	*/
	m_lastTick.QuadPart = m_startTick.QuadPart - 1;
	
	m_timestamp = 0;

	update();
}


/******************************************************************************
 * Time::update -- update time info.                                          *
 *                                                                            *
 *    Get new timestamp, and update time info.                                *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/sunxiaoyu/character-rain                   *
 *              https://codebus.cn/yangw/accurate-delay                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *============================================================================*/
void Time::update()
{
	m_lastTick = m_curTick;
	QueryPerformanceCounter(&m_curTick);
	m_time = (m_curTick.QuadPart - m_startTick.QuadPart) / (double)m_tickPerSecond.QuadPart;
	m_deltaTime = (m_curTick.QuadPart - m_lastTick.QuadPart) / (double)m_tickPerSecond.QuadPart;

	m_lastTimestamp = m_curTimestamp;
	m_curTimestamp = (clock_t)(m_time * 1000.0);
	
	m_timestamp += m_curTimestamp - m_lastTimestamp;
}


/******************************************************************************
 * Time::getDeltaTime -- Get delta time between two frames.                   *
 *                                                                            *
 *    Just the literal meaning...                                             *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/sunxiaoyu/character-rain                   *
 *              https://codebus.cn/yangw/accurate-delay                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  DeltaTime between lastest frames.                                 *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *============================================================================*/
double Time::getDeltaTime() const
{
	return m_deltaTime;
}


/******************************************************************************
 * Time::getTime -- Get current precise time in seconds.                      *
 *                                                                            *
 *    Just the literal meaning...                                             *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/sunxiaoyu/character-rain                   *
 *              https://codebus.cn/yangw/accurate-delay                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Current time.                                                     *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *============================================================================*/
double Time::getTime() const
{
	return m_time;
}


/******************************************************************************
 * Time::getTimestamp -- Get current integeral timestamp in milliseconds.     *
 *                                                                            *
 *    Just the literal meaning...                                             *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/sunxiaoyu/character-rain                   *
 *              https://codebus.cn/yangw/accurate-delay                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Current timestamp.                                                *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/11 Tony : Created.                                               *
 *============================================================================*/
clock_t Time::getTimestamp() const
{
	return m_timestamp;
}


/******************************************************************************
 * Time::getDeltaTimestamp -- Get delta timestamp.                            *
 *                                                                            *
 *    Just the literal meaning...                                             *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/sunxiaoyu/character-rain                   *
 *              https://codebus.cn/yangw/accurate-delay                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return delta timestamp.                                           *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/11 Tony : Created.                                               *
 *============================================================================*/
clock_t Time::getDeltaTimestamp() const
{
	return m_curTimestamp - m_lastTimestamp;
}


/******************************************************************************
 * Time::pause -- Pause the time.                                             *
 *                                                                            *
 *    Pause the timeal meaning...                                             *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
void Time::pause()
{
	m_deltaTimestamp = m_timestamp - m_lastTimestamp;
	m_deltaTick.QuadPart = m_curTick.QuadPart - m_lastTick.QuadPart;
}


/******************************************************************************
 * Time::cont -- Continue the time.                                           *
 *                                                                            *
 *    Pause the timeal meaning...                                             *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
void Time::cont()
{
	QueryPerformanceCounter(&m_curTick);
	m_lastTick.QuadPart = m_curTick.QuadPart - m_deltaTick.QuadPart;
	m_time = (m_curTick.QuadPart - m_startTick.QuadPart) / (double)m_tickPerSecond.QuadPart;

	m_curTimestamp = (clock_t)(m_time * 1000.0);
	m_lastTimestamp = m_timestamp - m_deltaTimestamp;
}


/******************************************************************************
 * FPSTimer::FPSTimer -- Default constructor for FPSTimer.                    *
 *                                                                            *
 *    Just the literal meaning...                                             *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/sunxiaoyu/character-rain                   *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:                                                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/03 Tony : Created.                                               *
 *============================================================================*/
FPSTimer::FPSTimer() {}


/******************************************************************************
 * FPSTimer::FPSTimer -- Default deconstructor for FPSTimer.                  *
 *                                                                            *
 *    Just the literal meaning...                                             *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/sunxiaoyu/character-rain                   *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:                                                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/03 Tony : Created.                                               *
 *============================================================================*/
FPSTimer::~FPSTimer() {}


/******************************************************************************
 * FPSTimer::update -- Update current frame time.                             *
 *                                                                            *
 *    Called before the start of a new frame and update static member to get  *
 *    the current timestamp.                                                  *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/sunxiaoyu/character-rain                   *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:                                                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/03 Tony : Created.                                               *
 *============================================================================*/
void FPSTimer::update()
{
	fpsTime.update();
}


/******************************************************************************
 * FPSTimer::getFPS -- Get current FPS count.                                 *
 *                                                                            *
 *    See above.                                                              *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/sunxiaoyu/character-rain                   *
 *                                                                            *
 * INPUT:   fps -- Adress to store fps count.                                 *
 *                                                                            *
 * OUTPUT:  Whether FPS count updated or not.                                 *
 *                                                                            *
 * WARNINGS:   Here I didn't check for invalid pointers. :)                   *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/03 Tony : Created.                                               *
 *============================================================================*/
bool FPSTimer::getFPS(double* fps)
{
	if (fpsTime.getTime() > nextFpsTime)
	{
		nextFpsTime += 1.0;
		*fps = 1.0 / fpsTime.getDeltaTime();

		return true;
	}

	return false;
}


/********************************************************************
** Static members of FPSTimer.
*/
double FPSTimer::nextFpsTime = 0.0;
Time FPSTimer::fpsTime;



/******************************************************************************
 * HPTimer::HPTimer -- Default constructor for HPTimer.                       *
 *                                                                            *
 *    Just the literal meaning...                                             *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/yangw/accurate-delay                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:                                                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *============================================================================*/
HPTimer::HPTimer()
{
	QueryPerformanceFrequency(&m_clock);
	m_frequency = (int)m_clock.QuadPart / 1000;

	// Start counting.
	QueryPerformanceCounter(&m_clock);
	m_oldClock = m_clock.QuadPart;
}


/******************************************************************************
 * HPTimer::HPTimer -- Default deconstructor for HPTimer.                     *
 *                                                                            *
 *    Just the literal meaning...                                             *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/yangw/accurate-delay                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:                                                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *============================================================================*/
HPTimer::~HPTimer() {}

/******************************************************************************
 * HPTimer::Delay -- High precision absolute delay.                           *
 *                                                                            *
 *    Just the literal meaning...                                             *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/yangw/accurate-delay                       *
 *                                                                            *
 * INPUT:   Delay in milliseconds.                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   Although it is high precision, the time used to call it may    *
 *             still slow down the program, and limit the FPS to relatively   *
 *             low. :(                                                        *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *============================================================================*/
void HPTimer::delay(int milliseconds)
{
	LONGLONG elapse = milliseconds * m_frequency;

	m_oldClock += elapse;

	QueryPerformanceCounter(&m_clock);

	if (m_clock.QuadPart > m_oldClock)
		m_oldClock = m_clock.QuadPart;
	else
	{
		do
		{
#ifndef HIGH_PRECISION_DELAY
			Sleep(1);
#endif

			// Get ending clock
			QueryPerformanceCounter(&m_clock);
		} while (m_clock.QuadPart < m_oldClock);
	}
}


/********************************************************************
** Static members of HPTimer.
*/
LARGE_INTEGER HPTimer::m_clock;
LONGLONG HPTimer::m_oldClock = 0;
int HPTimer::m_frequency = 0;