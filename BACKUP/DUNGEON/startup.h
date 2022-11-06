/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : startup.h                                 *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : February 15, 2022                         *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For the pre-process and start up of the programme.                       *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _STARTUP_H_
#define _STARTUP_H_


/********************************************************************
** Initialize and close global ones.
*/
bool initialize();
bool close();


/********************************************************************
** Connect widgets inside one interface.
*/
bool render();


/********************************************************************
** Connect interfaces so they can transit to one another.
*/
bool arrange();


/********************************************************************
** Load and unload all interfaces of the game.
** unload is mainly for music...
*/
bool loadInterface();
bool unloadInterface();


/********************************************************************
** Launch the game.
*/
void launch();


#endif