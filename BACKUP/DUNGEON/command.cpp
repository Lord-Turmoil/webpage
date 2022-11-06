/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : command.cpp                               *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 9, 2022                           *
 *                                                                            *
 *                    Last Update : January 19, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For game controls. Classes and functions for user's commands.            *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include <easyx.h>
#include <conio.h>

#include "command.h"

 /*
 ** Global virable, for the user's commands.
 */
Command command;

CommandFilter filter = ENABLE_ALL;


/******************************************************************************
 * getCommand -- Get user's command.                                          *
 *                                                                            *
 *    This function get all user messages, including keyboard, mouse and      *
 *    input.                                                                  *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *   2022/01/19 Tony : Added VK_E for pick up.                                *
 *   2022/02/05 Tony : Adjusted command sensitivity.                          *
 *============================================================================*/
void getCommand()
{
	ExMessage exMsg;

	command.clear();

	/*
	** Command message. Sooooo many if-elses... :(
	*/

	// Hero's actions.
	if (KEY_DOWN(VK_A))
	{
		command.sluggishKey = (command.instantKey == VK_A) ? VK_NONE : VK_A;
		command.instantKey = VK_A;
		command.commandType |= CMD_LEFT & filter;
		command.flag = true;
	}
	if (KEY_DOWN(VK_D))
	{
		command.sluggishKey = (command.instantKey == VK_D) ? VK_NONE : VK_D;
		command.instantKey = VK_D;
		command.commandType |= CMD_RIGHT & filter;
		command.flag = true;
	}
	if (KEY_DOWN(VK_W))
	{
		command.sluggishKey = (command.instantKey == VK_W) ? VK_NONE : VK_W;
		command.instantKey = VK_W;
		command.commandType |= (CMD_UP & filter);
		command.flag = true;
	}
	if (KEY_DOWN(VK_S))
	{
		command.sluggishKey = (command.instantKey == VK_S) ? VK_NONE : VK_S;
		command.instantKey = VK_S;
		command.commandType |= (CMD_DOWN & filter);
		command.flag = true;
	}
	if (KEY_DOWN(VK_Q))
	{
		command.sluggishKey = (command.instantKey == VK_Q) ? VK_NONE : VK_Q;
		command.instantKey = VK_Q;
		command.commandType |= (CMD_SWITCH & filter);
		command.flag = true;
	}
	if (KEY_DOWN(VK_SPACE))
	{
		command.sluggishKey = (command.instantKey == VK_SPACE) ? VK_NONE : VK_SPACE;
		command.instantKey = VK_SPACE;
		command.commandType |= (CMD_SKILL & filter);
		command.flag = true;
	}
	if (KEY_DOWN(VK_E))
	{
		command.sluggishKey = (command.instantKey == VK_E) ? VK_NONE : VK_E;
		command.instantKey = VK_E;
		command.commandType |= (CMD_ACTIVATE & filter);
		command.flag = true;
	}

	// Game commands.
	if (KEY_DOWN(VK_R))
	{
		command.sluggishKey = (command.instantKey == VK_R) ? VK_NONE : VK_R;
		command.instantKey = VK_R;
		if (command.sluggishKey == VK_R)
			command.commandType = (CMD_RESTART & filter);
		command.flag = true;
	}
	else if (KEY_DOWN(VK_P))
	{
		command.sluggishKey = (command.instantKey == VK_P) ? VK_NONE : VK_P;
		command.instantKey = VK_P;
		if (command.sluggishKey == VK_P)
			command.commandType = (CMD_PAUSE & filter);
		command.flag = true;
	}

	// Interface commands.
	if (KEY_DOWN(VK_C))
	{
		command.sluggishKey = (command.instantKey == VK_C) ? VK_NONE : VK_C;
		command.instantKey = VK_C;
		if (command.sluggishKey == VK_C)
			command.commandType = (CMD_PRINTSCREEN & filter);
		command.flag = true;
	}
	else if (KEY_DOWN(VK_O))
	{
		command.sluggishKey = (command.instantKey == VK_O) ? VK_NONE : VK_O;
		command.instantKey = VK_O;
		if (command.sluggishKey == VK_O)
			command.commandType = CMD_FULLSCREEN & filter;

		command.flag = true;
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		command.sluggishKey = (command.instantKey == VK_ESCAPE) ? VK_NONE : VK_ESCAPE;
		command.instantKey = VK_ESCAPE;
		if (command.sluggishKey == VK_ESCAPE)
			command.commandType = CMD_ESCAPE & filter;
		command.flag = true;
	}

	if (!command.flag)
		command.instantKey = VK_NONE;

	/*
	** Mouse message.
	*/
	while (peekmessage(&exMsg, EM_MOUSE, true))
	{
		if (exMsg.message == WM_MOUSEMOVE)
		{
			command.eventType = EVT_MOUSE_MOVE;
			command.pos.x = exMsg.x;
			command.pos.y = exMsg.y;
		}
		else if (exMsg.message == WM_LBUTTONDOWN)
		{
			command.eventType = EVT_MOUSE_DOWN;
			command.pos.x = exMsg.x;
			command.pos.y = exMsg.y;

			command.commandType |= (CMD_FIRE & filter);
		}
		else if (exMsg.message == WM_LBUTTONUP)
		{
			command.eventType = EVT_MOUSE_UP;
			command.pos.x = exMsg.x;
			command.pos.y = exMsg.y;

			if (CMD_FIRE & filter)
				command.commandType &= (~CMD_FIRE);
		}
	}
	command.convert();


	/*
	** Key message.
	*/
	if (_kbhit())
	{
		command.eventType = EVT_KEY_DOWN;
		command.key = _getch();

		/*
		** 2022/01/21
		** Special check for arrow keys.
		*/
		if (command.key == -32)
		{
			_getch();
			command.keyType = KeyType::KEY_NONE;
			return;
		}

		if ((command.key == '\r') || (command.key == '\n'))
			command.keyType = KeyType::KEY_ENTER;
		else if (command.key == '\b')
			command.keyType = KeyType::KEY_BACKSPC;
		else if (command.key == 27)
			command.keyType = KeyType::KEY_ESC;
		else if (isprint(command.key))
			command.keyType = KeyType::KEY_PRINT;
	}
}