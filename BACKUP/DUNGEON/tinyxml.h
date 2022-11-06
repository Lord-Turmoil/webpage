/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : tinyxml.h                                 *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : February 13, 2022                         *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For xml file read and write.                                             *
 * -------------------------------------------------------------------------- *
 * REFERENCE:   https://github.com/leethomason/tinyxml2                       *
 *              https://www.cnblogs.com/happykoukou/p/6307257.html            *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _TINYXML_H_
#define _TINYXML_H_

#include "inc/tinyxml2.h"

#ifdef _DEBUG
#pragma comment(lib, "lib/x64/Debug/tinyxml2.lib")
#else
#pragma comment(lib, "lib/x64/Release/tinyxml2.lib")
#endif

 // There's a conflict of XMLDocument in msxml.h. :(
using XMLDoc = tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

#endif