/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : auxilliary.h                              *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 1, 2022                           *
 *                                                                            *
 *                    Last Update : February 18, 2022                         *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   Auxilliary functions. For some basic calculations.                       *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _AUXILLIARY_H_
#define _AUXILLIARY_H_


#include <string>
#include <vector>
#include <easyx.h>

#include "define.h"


#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define ABS(X) (((X) < (0)) ? (-(X)) : (X))
#define SIGN(X) (((X) < (0)) ? (-1) : (1))

#define IS_ZERO(X) (ABS(X) < EPSILON)
#define IS_OPPOSITE(X, Y) (((X) < (0.0)) != ((Y) < (0.0)))


 /********************************************************************
 ** Reset a RECT.
 */
void setRectangle(RECT* rect, int left, int top, int right, int bottom);


/********************************************************************
** Get the distance between two coordinates.
*/
double getDistance(const Coord& pos1, const Coord& pos2);


/********************************************************************
** Get the Manhattan distance between two coordinates.
*/
int getManhattanDistance(const Coord& pos1, const Coord& pos2);


/********************************************************************
** Check if a coordinate is in a rectangle.
*/
bool inRectangle(const RECT& range, const Coord& target);


/********************************************************************
** Get the module of a vector.
*/
double getModule(const Vector& vec);


/********************************************************************
** Get the unit vector in its direction.
*/
Vector getUnit(const Vector& vec);

Coord getRatioCoord(const Coord& pos1, const Coord& pos2, double ratio);


/********************************************************************
** Get the radian rotating needs from the direction vector.
*/
double getRadian(Coord dir, bool mirror = false);
double getRadian(Coord dir, int radius, bool mirror = false);

/********************************************************************
** Rotate the... thing...
*/
Vector rotate(const Vector& vec, double radian);
Coord rotate(const Coord& coord, double radian);


/********************************************************************
** Extract a series of int in a string.
*/
int extractInt(const std::wstring& src, std::vector<int>& dest);


/********************************************************************
** Extract a series of strings in a string.
*/
int extractString(const std::wstring& src, std::vector<std::wstring>& dest);


/********************************************************************
** Get a random number between left and right. (Include left and
** right.
*/
int random(int left, int right);


/********************************************************************
** Get an even number between left and right. (right is not included)
*/
int randomEven(int left, int right);


/********************************************************************
** Get a random coordinate around the assigned position.
*/
Coord randomPos(Coord center, int radius = 3);


/********************************************************************
** Get an int from a C-style string.
*/
int parseInt(const char* src);
int parseInt(const wchar_t* src);
int parseInt(int* val, const wchar_t* src);
int parseInt(int* val, const wchar_t* src);


/********************************************************************
** Get a Coord from a C-style of string.
*/
Coord parseCoord(const char* src);
Coord parseCoord(const wchar_t* src);


/********************************************************************
** Get color from rgb.
*/
COLORREF parseColor(const char* src);


/********************************************************************
** Get XML attribute.
*/
bool parseXMLAttribute(int* val, const char* attribute);
bool parseXMLAttribute(Coord* val, const char* attribute);
bool parseXMLAttribute(bool* val, const char* attribute);
bool parseXMLAttribute(COLORREF* val, const char* attribute);
bool parseXMLAttribute(std::string* val, const char* attribute);
bool parseXMLAttribute(std::wstring* val, const char* attribute);
bool parseXMLAttribute(TransitStyle* style, const char* attribute);

/********************************************************************
** Conver char to wchar_t.
*/
bool widen(wchar_t* dest, const char* src);


/********************************************************************
** Check if a path exists or not.
*/
bool isAccessible(const char* path);
bool isAccessible(const wchar_t* path);


#endif