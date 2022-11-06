/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : error.h                                   *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : February 15, 2022                         *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   To log error info during the game.                                       *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _ERROR_H_
#define _ERROR_H_

const char		ERROR_FILE[]	= R"(.\error.txt)";
const wchar_t	ERROR_FILE_W[]	= LR"(.\error.txt)";

const char		LOAD_WIDGET[]		= "Loading widget";
const char		LOAD_INTF[]			= "Loading interface";
const char		RENDER_INTF[]		= "Rendering interface";
const char		LOAD_RESOURCE[]		= "Loading resource";
const char		LOAD_IMAGE[]		= "Loading image";
const char		LOAD_SOUND[]		= "Loading sound";
const char		FAILED_TO_LOAD_F[]	= "Failed to load %s";
const wchar_t	LOAD_IMAGE_W[]		= L"Loading image";
const wchar_t	LOAD_RESOURCE_W[]	= L"Loading resource";
const wchar_t	LOAD_FRAME_W[]		= L"Loading frame";
const wchar_t	FAILED_TO_LOAD_FW[]	= L"Failed to load %s";
const wchar_t	FAILED_AT_FW[]		= L"Failed at [%s]";

const char		IN_GAME[]			= "In game";
const char		NO_BLANK[]			= "Insufficient blank";
const char		NO_BLANK_F[]		= "Insufficient blank for %s";

void report(const char* description = nullptr, const char* category = nullptr);
void wreport(const wchar_t* description = nullptr, const wchar_t* category = nullptr);
void reportf(const char* format, const char* arg, const char* category = nullptr);
void wreportf(const wchar_t* format, const wchar_t* arg, const wchar_t* category = nullptr);

#endif