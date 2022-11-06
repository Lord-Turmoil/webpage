/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : command.h                                 *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 7, 2022                           *
 *                                                                            *
 *                    Last Update : February 13, 2022                         *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For game controls. Classes and functions for user's commands.            *
 * -------------------------------------------------------------------------- *
 * Functions:                                                                 *
 ******************************************************************************/

#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <Windows.h>
#include <functional>

#include "define.h"


/********************************************************************
** Command message map.
*/
enum CommandType : unsigned
{
	CMD_NONE = 0x000000,

	// Figure commands. 0x0000XX
	CMD_LEFT = 0x000001,
	CMD_RIGHT = 0x000002,
	CMD_UP = 0x000004,
	CMD_DOWN = 0x000008,
	CMD_FIRE = 0x000010,
	CMD_SWITCH = 0x000020,	// switch weapon
	CMD_SKILL = 0x000040,	// VK_SPACE
	CMD_ACTIVATE = 0x000080,	// pick up weapon or open create

	// Game commands. 0x00XX00
	CMD_RESTART = 0x000100,
	CMD_PAUSE = 0x000200,

	// Interface commands. 0xXX0000
	CMD_PRINTSCREEN = 0x010000,
	CMD_FULLSCREEN = 0x020000,
	CMD_ESCAPE = 0x040000
};


/********************************************************************
** Mode of command, to filter commands.
*/
enum CommandFilter
{
	DISABLE_ALL = 0,
	ESCAPE_ONLY = CMD_ESCAPE,
	ENABLE_ALL = 0xFFFFFF,
};


/********************************************************************
** Keyboard message map.
*/
enum class KeyType : unsigned
{
	KEY_NONE = 0,	// nothing
	KEY_PRINT,			// a printable character
	KEY_ENTER,
	KEY_ESC,
	KEY_BACKSPC
};


/********************************************************************
** Command event types.
*/
enum EventType : unsigned
{
	EVT_NONE = 0x00,

	EVT_MOUSE_MOVE = 0x01,
	EVT_MOUSE_DOWN = 0x02,
	EVT_MOUSE_UP = 0x04,

	EVT_KEY_DOWN = 0x10,
	EVT_KEY_UP = 0x20
};


/********************************************************************
** Some additional defines to windows virtual keys.
*/
#define VK_NONE	0x00	//
#define VK_A	0x41	// CMD_LEFT
#define VK_B	0x42	//
#define VK_C	0x43	// CMD_PRINTSCREEN
#define VK_D	0x44	// CMD_RIGHT
#define VK_E	0x45	// CMD_ACTIVE
#define VK_F	0x46	//
#define VK_G	0x47	//
#define VK_H	0x48	//
#define VK_I	0x49	//
#define VK_J	0x4A	//
#define VK_K	0x4B	//
#define VK_L	0x4C	//
#define VK_M	0x4D	//
#define VK_N	0x4E	//
#define VK_O	0x4F	// CMD_FULLSCREEN
#define VK_P	0x50	// CMD_PAUSE
#define VK_Q	0x51	// CMD_SWITCH
#define VK_R	0x52	// CMD_RESTART
#define VK_S	0x53	// CMD_DOWN
#define VK_T	0x54	//
#define VK_U	0x55	//
#define VK_V	0x56	//
#define VK_W	0x57	// CMD_UP
#define VK_X	0x58	//
#define VK_Y	0x59	//
#define VK_Z	0x5A	//


/********************************************************************
** Macro function to check a key state.
*/
#define KEY_DOWN(KEY) (GetAsyncKeyState(KEY) & 0x8000)


/********************************************************************
** For user's keyboard and mouse message.
*/
struct Command
{
	/*
	** Because there exists multiple events or commands,
	** we need to use OR. So they two should be unsigned.
	*/
	unsigned eventType;
	unsigned commandType;

	KeyType keyType;

	/*
	** Valid when a key is down, and is still valid throughout
	** the time until the key is up.
	*/
	BYTE instantKey;

	/*
	** Only valid when a key is up. Used for commands that
	** shouldn't be activated multiple times if a key is only
	** pressed once.
	** 2022/01/08
	** Note that, this one should be updated before instantKey.
	*/
	BYTE sluggishKey;

	/*
	** flag is used for updating instantKey. If no key
	** is down, then the instantKey will be set to VK_NONE
	** after the process.
	*/
	bool flag;

	/*
	** 2022/01/08
	** The ASCII code for the key. Used for input box.
	*/
	char key;

	/*
	** Physical coordinate of the mouse.
	*/
	Coord pos;

	/*
	** Logical coordinate of the mouse.
	*/
	Coord logicalPos;

	/*
	** Relative coordinate of the mouse in camera.
	*/
	Coord relativePos;

	/*
	** Two callback function for conversion.
	*/
	std::function<Coord(Coord)> pLogicalConvert;
	std::function<Coord(Coord)> pRelativeConvert;

	Command()
	{
		eventType = EVT_NONE;
		commandType = CMD_NONE;
		keyType = KeyType::KEY_NONE;
		instantKey = sluggishKey = VK_NONE;
		key = 0;
		flag = false;

		pLogicalConvert = nullptr;
		pRelativeConvert = nullptr;
	}

	void clear()
	{
		eventType = EVT_NONE;
		keyType = KeyType::KEY_NONE;

		/*
		** As WM_MOUSEDOWN is an instant message, I can only use this
		** clumsy way to make sure CMD_FIRE is valid until the mouse is
		** up.
		*/
		commandType = (commandType & CMD_FIRE) ? CMD_FIRE : CMD_NONE;

		key = 0;

		flag = false;
	}

	void convert()
	{
		if (pLogicalConvert)
		{
			logicalPos = pLogicalConvert(pos);
			if (pRelativeConvert)
				relativePos = pRelativeConvert(logicalPos);
		}
	}
};



/********************************************************************
** Receive command from the user.
*/
void getCommand();

#endif