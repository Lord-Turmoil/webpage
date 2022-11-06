/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : image.h                                   *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 2, 2022                           *
 *                                                                            *
 *                    Last Update : February 5, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For time control and measurement.                                        *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _TIMING_H_
#define _TIMING_H_

#include <ctime>
#include <Windows.h>


/********************************************************************
** If this is defined, then the delay will be more accurate but may
** take more CPU resource.
*/
// #define HIGH_PRECISION_DELAY


/*********************************************************************
** Some constants used in delta time convert.
** COF is short for coefficient.
*/
const double VEL_COF = 100.0;
const double ACC_COF = 100.0;


 /********************************************************************
 ** Time used to calculate FPS.
 ** Reference:   https://codebus.cn/sunxiaoyu/character-rain
 **              https://codebus.cn/yangw/accurate-delay
 */
class Time
{
public:
	Time();
	Time(const Time& t) = delete;
	Time& operator=(const Time& t) = delete;

	void update();
	double getDeltaTime() const;
	double getTime() const;
	clock_t getTimestamp() const;
	clock_t getDeltaTimestamp() const;

	void pause();
	void cont();

private:
	/*
	** 2022/01/10
	** The unit is second.
	*/
	double m_deltaTime;
	double m_time;

	/*
	** 2022/01/11
	** Timestamp is used for frame animation. :)
	** 2022/02/05
	** This one stops if pause accurs.
	*/
	clock_t m_timestamp;

	/*
	** 2022/02/04
	** These two is used for the frame update in case
	** a pause accurs.
	*/
	clock_t m_curTimestamp;
	clock_t m_lastTimestamp;

	clock_t m_deltaTimestamp;
	
	LARGE_INTEGER m_tickPerSecond;
	LARGE_INTEGER m_curTick;
	LARGE_INTEGER m_lastTick;
	LARGE_INTEGER m_startTick;
	LARGE_INTEGER m_deltaTick;
};


/********************************************************************
** Timer for FPS Calculating.
*/
class FPSTimer
{
public:
	FPSTimer();
	~FPSTimer();

	/*
	** Update current time at the beginning of a frame.
	*/
	static void update();

	/*
	** If FPS updated, return true, and change the reference of
	** fps. Or, it does nothing and return false;
	*/
	static bool getFPS(double* fps);

private:
	static Time fpsTime;
	static double nextFpsTime;
};


/********************************************************************
** Timer for high precision delay.
** Reference:   https://codebus.cn/yangw/accurate-delay
*/
class HPTimer
{
public:
	HPTimer();
	~HPTimer();

	/*
	** Absolute delay in high precision.
	*/
	static void delay(int milliseconds);

private:
	/*
	** Complete clock info.
	*/
	static LARGE_INTEGER m_clock;

	/*
	** Timestamp of the start and end of a period.
	*/
	static LONGLONG m_oldClock;

	/*
	** Clock frequency, conversion rate.
	*/
	static int m_frequency;
};

#endif