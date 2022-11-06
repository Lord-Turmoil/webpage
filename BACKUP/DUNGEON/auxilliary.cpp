/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : auxilliary.cpp                            *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 6, 2022                           *
 *                                                                            *
 *                    Last Update : January 28, 2022                          *
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

#include <io.h>			// for _access
#include <cmath>
#include <cstring>
#include <sstream>
#include <ctype.h>
#include <cstdlib>

#include "error.h"
#include "interface.h"
#include "auxilliary.h"



 /******************************************************************************
  * setRectangle -- Reset a RECT size.                                         *
  *                                                                            *
  *    Just the literal meaning.                                               *
  *                                                                            *
  * INPUT:   left                                                              *
  *          top                                                               *
  *          right                                                             *
  *          bottom	                                                          *
  *                                                                            *
  * OUTPUT:  none                                                              *
  *                                                                            *
  * WARNINGS:                                                                  *
  *                                                                            *
  * HISTORY:                                                                   *
  *   2022/01/06 Tony : Created.                                               *
  *============================================================================*/
void setRectangle(RECT* rect, int left, int top, int right, int bottom)
{
	rect->left = left;
	rect->top = top;
	rect->right = right;
	rect->bottom = bottom;
}


/******************************************************************************
 * getDistance -- Get distance between two coordinates.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pos1, pos2 -- Two coordinates.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:                                                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
double getDistance(const Coord& pos1, const Coord& pos2)
{
	double dx = (double)(pos1.x - pos2.x);
	double dy = (double)(pos1.y - pos2.y);

	return sqrt(dx * dx + dy * dy);
}


/******************************************************************************
 * getManhattanDistance -- Get the Manhattan distance.                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pos1, pos2 -- Two coordinates.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:                                                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/25 Tony : Created.                                               *
 *============================================================================*/
int getManhattanDistance(const Coord& pos1, const Coord& pos2)
{
	return ABS(pos1.x - pos2.x) + ABS(pos1.y - pos2.y);
}


/******************************************************************************
 * inRectangle -- Check if a coordinate is in a rectangle.                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   range  -- The rectangle area.                                     *
 *          target -- The coordinate to check.                                *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:                                                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
bool inRectangle(const RECT& range, const Coord& target)
{
	return ((range.left < target.x) && (target.x < range.right) \
		&& (range.top < target.y) && (target.y < range.bottom));
}


/******************************************************************************
 * getModule -- Get the module of a vector.                                   *
 *                                                                            *
 *    Just do it with a little math.                                          *
 *                                                                            *
 * INPUT:   vec -- A vector.                                                  *
 *                                                                            *
 * OUTPUT:  Return the module of the vector.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
double getModule(const Vector& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}


/******************************************************************************
 * getUnit -- Get the unit vector.                                            *
 *                                                                            *
 *    Get the unit vector in the direction of the given vector.               *
 *                                                                            *
 * INPUT:   vec -- A vector.                                                  *
 *                                                                            *
 * OUTPUT:  Return the unit vector required.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
Vector getUnit(const Vector& vec)
{
	double mod = getModule(vec);

	if (mod < EPSILON)
		return ZERO_VECTOR;
	else
		return vec / mod;
}


/******************************************************************************
 * getRatioCoord -- Emm...                                                    *
 *                                                                            *
 *    This one get a third point with the linear combination of the given two.*
 *                                                                            *
 * INPUT:   vec -- A vector.                                                  *
 *                                                                            *
 * OUTPUT:  Return the unit vector required.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
Coord getRatioCoord(const Coord& pos1, const Coord& pos2, double ratio)
{
	return { (int)(pos1.x * ratio + pos2.x * (1.0 - ratio)), (int)(pos1.y * ratio + pos2.y * (1.0 - ratio)) };
}


/******************************************************************************
 * getRadian -- Get the radian to rotate.                                     *
 *                                                                            *
 *    This one get the radian needed to rotate to the desired direction. It   *
 *    based on the direction of x-axis. And mirror is used for objects that   *
 *    has two sides, since left and right images are symmetrical.             *
 *    If radius assigned, which is for the weapon, it will return the radian  *
 *    to make the muzzle to its target.                                       *
 *                                                                            *
 * INPUT:   dir    -- The target direction.                                   *
 *          radius -- The rotation radius.                                    *
 *          mirror -- Whether a mirror option should be taken or not.         *
 *                                                                            *
 * OUTPUT:  Return the unit vector required.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
double getRadian(Coord dir, bool mirror)
{
	double rv;

	dir.y = -dir.y;

	if (dir.x == 0)
		rv = (dir.y < 0) ? (1.5 * PI) : (0.5 * PI);
	else if (dir.x > 0)
		rv = atan((double)dir.y / (double)dir.x);
	else
		rv = atan((double)dir.y / (double)dir.x) + (mirror ? 0.0 : PI);

	return rv;
}

double getRadian(Coord dir, int radius, bool mirror)
{
	double r1 = getRadian(dir, mirror);
	if (radius == 0)
		return r1;

	double dist = getDistance({ 0, 0 }, dir);
	if ((dist < radius) || (dist < EPSILON))
		return r1;

	double r2 = asin((double)radius / dist);

	if (mirror && (dir.x < 0))
		return r1 + r2;

	return r1 - r2;
}


/******************************************************************************
 * rotate -- Rotate the vector or coord.                                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   vec/coord -- The thing to rorate.                                 *
 *          radian    -- How many radians to rorate conter-clockwise.         *
 *                                                                            *
 * OUTPUT:  Return the unit vector required.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
Vector rotate(const Vector& vec, double radian)
{
	double cosx = cos(radian);
	double sinx = sin(radian);

	return { vec.x * cosx - vec.y * sinx, -(vec.x * sinx + vec.y * cosx) };
}

Coord rotate(const Coord& coord, double radian)
{
	double cosx = cos(radian);
	double sinx = sin(radian);

	return { (int)((double)coord.x * cosx - (double)coord.y * sinx), -(int)((double)coord.x * sinx + (double)coord.y * cosx) };
}


/******************************************************************************
 * extractInt -- Get a series of ints from a string.                          *
 *                                                                            *
 *    This function extract ints from a string. For example, get 1, 2, 3 from *
 *    the string "1 2 3". The numbers must be divided by space.               *
 *                                                                            *
 * INPUT:   src  -- The source buffer of the string.                          *
 *          dest -- The destination array.                                    *
 *                                                                            *
 * OUTPUT:  Return the number of integers get.                                *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/12 Tony : Created.                                               *
 *   2022/02/05 Tony : Now use string stream.                                 *
 *   2022/02/07 Tony : Now use vector.                                        *
 *============================================================================*/
int extractInt(const std::wstring& src, std::vector<int>& dest)
{
	std::wstringstream stream(src);
	int cnt = 0;
	int val;

	while (stream >> val)
	{
		dest.push_back(val);
		cnt++;
	}

	return cnt;
}


/******************************************************************************
 * extractString -- Get a series of string from a string.                     *
 *                                                                            *
 *    This function extract strings from a string. For example, get "a", "b", *
 *    "c" from "a b c". Strings must be divided by space.                     *
 *                                                                            *
 * INPUT:   src  -- The source buffer of the string.                          *
 *          dest -- The destination vector.                                   *
 *                                                                            *
 * OUTPUT:  Return the number of strings get.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/07 Tony : Created.                                               *
 *============================================================================*/
int extractString(const std::wstring& src, std::vector<std::wstring>& dest)
{
	std::wstringstream stream(src);
	std::wstring str;
	int cnt = 0;

	while (stream >> str)
	{
		dest.push_back(str);
		cnt++;
	}

	return cnt;
}


/******************************************************************************
 * random -- Get a random number between left and right bound.                *
 *                                                                            *
 *    The result can be left or right.                                        *
 *                                                                            *
 * INPUT:   left  -- The left boundary of the result.                         *
 *          right -- The right boundary of the result.                        *
 *                                                                            *
 * OUTPUT:  Return a random number between left and right.                    *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/13 Tony : Created.                                               *
 *============================================================================*/
int random(int left, int right)
{
	return rand() % (right - left + 1) + left;
}


/******************************************************************************
 * randomEven -- Get an even number between left and right bound.             *
 *                                                                            *
 *    The result include left but doens't include right.                      *
 *                                                                            *
 * INPUT:   left  -- The left boundary of the result.                         *
 *          right -- The right boundary of the result.                        *
 *                                                                            *
 * OUTPUT:  Return a random even number between left and right.               *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/13 Tony : Created.                                               *
 *============================================================================*/
int randomEven(int left, int right)
{
	return left + (((rand() % (right - left)) >> 1) << 1);
}


/******************************************************************************
 * randomPos -- Get a random position around assigned coordinate.             *
 *                                                                            *
 *    Well, just a tricky function.                                           *
 *                                                                            *
 * INPUT:   center -- The center coordinatehe result.                         *
 *          radius -- The radius of this random.                              *
 *                                                                            *
 * OUTPUT:  Return a random coordinate.                                       *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/28 Tony : Created.                                               *
 *============================================================================*/
Coord randomPos(Coord center, int radius)
{
	return { center.x + random(-radius, radius), center.y + random(-radius, radius) };
}


/******************************************************************************
 * parseInt -- Parse an integer from a C-style string.                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   src -- The C-style string.                                        *
 *                                                                            *
 * OUTPUT:  Return the result.                                                *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
int parseInt(const char* src)
{
	if (src == NULL)
		return 0;

	int i = 0;
	bool negative = false;
	int rv = 0;

	while ((src[i] != '\0') && !isdigit(src[i]))
	{
		if (src[i] == '-')
			negative = !negative;
		i++;
	}
	while ((src[i] != '\0') && isdigit(src[i]))
	{
		rv = (rv << 1) + (rv << 3) + (src[i] - '0');
		i++;
	}
	if (negative)
		rv = -rv;

	return rv;
}

int parseInt(const wchar_t* src)
{
	if (src == NULL)
		return 0;

	int i = 0;
	bool negative = false;
	int rv = 0;

	while ((src[i] != L'\0') && !iswdigit(src[i]))
	{
		if (src[i] == L'-')
			negative = !negative;
		i++;
	}
	while ((src[i] != L'\0') && iswdigit(src[i]))
	{
		rv = (rv << 1) + (rv << 3) + (src[i] - L'0');
		i++;
	}
	if (negative)
		rv = -rv;

	return rv;
}


/******************************************************************************
 * parseInt -- Parse an integer from a C-style string.                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val -- The place to store result.                                 *
 *          src -- The C-style string.                                        *
 *                                                                            *
 * OUTPUT:  Return the end of the integer in the string.                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
int parseInt(int* val, const char* src)
{
	*val = 0;

	if (src == NULL)
		return 0;

	int i = 0;
	bool negative = false;

	while ((src[i] != '\0') && !isdigit(src[i]))
	{
		if (src[i] == '-')
			negative = !negative;
		i++;
	}
	while ((src[i] != '\0') && isdigit(src[i]))
	{
		*val = (*val << 1) + (*val << 3) + (src[i] - '0');
		i++;
	}
	if (negative)
		*val = -(*val);

	return i;
}

int parseInt(int* val, const wchar_t* src)
{
	*val = 0;

	if (src == NULL)
		return 0;


	int i = 0;
	bool negative = false;

	while ((src[i] != L'\0') && !iswdigit(src[i]))
	{
		if (src[i] == '-')
			negative = !negative;
		i++;
	}
	while ((src[i] != L'\0') && iswdigit(src[i]))
	{
		*val = (*val << 1) + (*val << 3) + (src[i] - L'0');
		i++;
	}
	if (negative)
		*val = -(*val);

	return i;
}


/******************************************************************************
 * parseCoord -- Parse a coord from a C-style string.                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
Coord parseCoord(const char* src)
{
	Coord rv;

	rv.y = parseInt(src + parseInt(&rv.x, src));

	return rv;
}

Coord parseCoord(const wchar_t* src)
{
	Coord rv;

	rv.y = parseInt(src + parseInt(&rv.x, src));

	return rv;
}


/******************************************************************************
 * parseColor -- Parse the color from rgb string.                             *
 *                                                                            *
 *    The format should be "xxx xxx xxx", can be "(xx, xx, xx)".              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
COLORREF parseColor(const char* src)
{
	int r, g, b;
	int pos = 0;

	pos += parseInt(&r, src);
	pos += parseInt(&g, src + pos);
	parseInt(&b, src + pos);

	return RGB(r, g, b);
}



/******************************************************************************
 * parseXMLAttribute -- Parse xml attribute.                                  *
 *                                                                            *
 *    Emm... to simplify the tinyxml's read process.                          *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool parseXMLAttribute(int* val, const char* attribute)
{
	if (attribute == NULL)
		return false;

	*val = parseInt(attribute);

	return true;
}

bool parseXMLAttribute(Coord* val, const char* attribute)
{
	if (attribute == NULL)
		return false;

	*val = parseCoord(attribute);

	return true;
}

bool parseXMLAttribute(bool* val, const char* attribute)
{
	if (attribute == NULL)
		return false;

	if (strcmp(attribute, "true") == 0)
		*val = true;
	else if (strcmp(attribute, "false") == 0)
		*val = false;
	else
		return false;

	return true;
}

bool parseXMLAttribute(COLORREF* val, const char* attribute)
{
	if (attribute == NULL)
		return false;

	*val = parseColor(attribute);

	return true;
}

bool parseXMLAttribute(std::string* val, const char* attribute)
{
	if (attribute == NULL)
		return false;

	*val = attribute;

	return true;
}

bool parseXMLAttribute(std::wstring* val, const char* attribute)
{
	if (attribute == NULL)
		return false;

	wchar_t w_attr[55];
	widen(w_attr, attribute);
	*val = w_attr;

	return true;
}

bool parseXMLAttribute(TransitStyle* style, const char* attribute)
{
	if (attribute == NULL)
		return false;

	std::string type;
	int pos = parseInt(&(style->duration), attribute);
	while (attribute[pos] == ' ')
		pos++;
	type = (attribute + pos);

	auto it = TRANSIT_TYPE_MAP.find(type);
	if (it == TRANSIT_TYPE_MAP.end())
	{
		reportf("Unrecognized type: %s", type.c_str(), "Parsing XML");
		return false;
	}
	style->type = it->second;

	return true;
}



/******************************************************************************
 * widen -- Widen char to wchar_t.                                            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   dest -- The destination wchar_t buffer.                           *
 *          src  -- The source char buffer.                                   *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool widen(wchar_t* dest, const char* src)
{
	size_t ret;

	errno_t err = mbstowcs_s(&ret, dest, strlen(src) + 1, src, 50);
	if (err != 0)
		return false;
	else
		return true;
}


/******************************************************************************
 * isAccessible -- To check if a path is accessible or not.                   *
 *                                                                            *
 *    This is mainly used to check image file state.                          *
 *                                                                            *
 * INPUT:   path -- The file path to check.                                   *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
bool isAccessible(const char* path)
{
	if (_access(path, 0) != -1)
		return true;

	return false;
}

bool isAccessible(const wchar_t* path)
{
	if (_waccess(path, 0) != -1)
		return true;

	return false;
}