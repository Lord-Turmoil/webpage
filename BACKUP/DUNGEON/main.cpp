/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : main.cpp                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : February 15, 2022                         *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   The main source file of the project.                                     *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 * -------------------------------------------------------------------------- *
 * Comment:                                                                   *
 *     This is an exercise project of New Desire Studio to practice skills of *
 *   programming of its members. The whole thing is simply for fun and there  *
 *   is no intention of business use at all.                                  *
 *                                                                            *
 *     The original motive comes from a game I used to play - Soul Knight. It *
 *   is quite fun despite the need of money to purchase fancy figures. As for *
 *   the design of the icon hero originally comes from Doodle Jump, a classic *
 *   one. However, he already revealed himself in the previous Tony's Jumper. *
 *                                                                            *
 *     Thanks for Mom and Dad who support me all the time. And Many thanks to *
 *   the authors of EasyX, you enlightened me a great deal!                   *
 ******************************************************************************/

#include "startup.h"

int main()
{
	initialize();
	
	if (!loadInterface())
		return -1;

	launch();

	unloadInterface();
	close();

	return 0;
}