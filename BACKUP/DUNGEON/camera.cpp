/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : camera.cpp                                *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 10, 2022                          *
 *                                                                            *
 *                    Last Update : January 13, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   The area that the player can see. It takes hold of images and draw them, *
 *   and follows the player.                                                  *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include <easyx.h>
#include <queue>
#include <ctime>

#include "camera.h"
#include "timing.h"
#include "auxilliary.h"

extern Time globalTimer;

/******************************************************************************
 * Camera::Camera -- Constructor of the object.                               *
 *                                                                            *
 *    The camera's pos(ition) is the absolute position on the destination     *
 *    image. The camera will draw the final width * height image at this pos  *
 *    on the pDestImg.                                                        *
 *                                                                            *
 * INPUT:   _pos    -- The position to draw the sights.                       *
 *          _width  -- The width of the camera's sight.                       *
 *          _height -- The height of the camera's sight.                      *
 *          _speed  -- The speed of the camera.                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
Camera::Camera(Coord _pos,
	int _width,
	int _height,
	double _factor)
{
	pos = _pos;
	width = _width;
	height = _height;
	factor = _factor;

	isSteady = false;

	film.Resize(width, height);
	SetWorkingImage(&film);
	setbkcolor(TRANSPARENT_COLOR);
	cleardevice();
	SetWorkingImage(NULL);
}


/******************************************************************************
 * Camera::~Camera -- Deconstructor of the object.                            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
Camera::~Camera() {}


/******************************************************************************
 * Camera::init -- Initialize a camera.                                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _pos    -- Absolute position of the camera.                       *
 *          _width  -- Width of the camera.                                   *
 *          _height -- Height of the camera.                                  *
 *          _speed  -- Speed of the camera.                                   *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
void Camera::init(Coord _pos,
	int _width,
	int _height,
	double _factor)
{
	pos = _pos;
	width = _width;
	height = _height;
	factor = _factor;

	offset = { width >> 1, height >> 1 };
	curPos = pos;
	curCenter = tarCenter = curPos + offset;

	isSteady = false;

	/*
	** Remember to resize!
	*/
	film.Resize(width, height);
	SetWorkingImage(&film);
	cleardevice();
	SetWorkingImage(NULL);
}


/******************************************************************************
 * Camera::setTargetImage -- Set the target image to develop the film. :)     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pTargetImage -- The target image.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
void Camera::setTargetImage(IMAGE* _pTargetImage)
{
	pTargetImage = _pTargetImage;
	imagePool.setTargetImage(pTargetImage);
}


/******************************************************************************
 * Camera::setTargetStyle -- Set the moving style of the camera.              *
 *                                                                            *
 *    The camera can move in two styles, false means move gradually, and true *
 *    means steadily.                                                         *
 *                                                                            *
 * INPUT:   _isSteady -- Whether to move steady or not.                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
void Camera::setStyle(bool _isSteady)
{
	isSteady = _isSteady;
}


/******************************************************************************
 * Camera::focus -- Make the target center of the camera.                     *
 *                                                                            *
 *    This will move the camera to the target immediately.                    *
 *                                                                            *
 * INPUT:   target -- The target coordinate to focus.                         *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
void Camera::focus(Coord target)
{
	curCenter = tarCenter = target;
	curPos = curCenter - offset;
}


/******************************************************************************
 * Camera::follow -- Set the target for the camera to follow.                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   target -- The target to follow.                                   *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
void Camera::follow(Coord target)
{
	tarCenter = target;
}


/******************************************************************************
 * Camera::move -- Move the camera.                                           *
 *                                                                            *
 *    This will make the camera move towards its target.                      *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether moved or not.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
bool Camera::move()
{
	if (curCenter == tarCenter)
		return false;

	double dist = getDistance(curCenter, tarCenter);
	double step;

	if (isSteady)
	{
		step = CAM_SPEED * globalTimer.getDeltaTime() * 10000.0 * factor;
		step = MAX(step, 1.5);
	}
	else
	{
		step = CAM_SPEED * globalTimer.getDeltaTime() * dist * dist * factor;
		step = MAX(step, 1.5);
	}

	// Already very close.
	if (step > dist)
	{
		curCenter = tarCenter;
		curPos = curCenter - offset;
		return true;
	}

	Coord dir = tarCenter - curCenter;
	Vector vec;

	vec.x = (double)dir.x;
	vec.y = (double)dir.y;

	vec = getUnit(vec) * step;
	curCenter.x += (int)vec.x;
	curCenter.y += (int)vec.y;
	curPos = curCenter - offset;

	return true;
}


/******************************************************************************
 * Camera::getImage -- Get the camera's image.                                *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the camera's image.                                        *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
IMAGE* Camera::getImage()
{
	return &film;
}


/******************************************************************************
 * Camera::getTargetImage -- Get the target image.                            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the camera's target image.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
IMAGE* Camera::getTargetImage()
{
	return pTargetImage;
}


/******************************************************************************
 * Camera::capture -- Capture a symbol.                                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   symbol -- The image symbol to be captured.                        *
 *                                                                            *
 * OUTPUT:  Return whether captured.                                          *
 *                                                                            *
 * WARNINGS:  The parameter symbol mustn't be changed.                        *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *   2022/01/13 Tony : Added isAbsolute.                                      *
 *   2022/02/18 Tony : Removed isAbsolute. :)                                 *s
 *============================================================================*/
bool Camera::capture(Symbol symbol)
{
	int srcWidth = symbol.img->getwidth();
	int srcHeight = symbol.img->getheight();
	Coord src = symbol.pos + symbol.offset;

	// Check if the symbol is out of sight.
	if ((src.x + srcWidth < curPos.x) || (src.y + srcHeight < curPos.y) \
		|| (src.x >= curPos.x + width) || (src.y >= curPos.y + height))
		return false;

	symbol.pos = pos + (symbol.pos - curPos);
	imagePool.add(symbol);

	return true;
}


/******************************************************************************
 * Camera::captureStatic -- Capture a static symbol.                          *
 *                                                                            *
 *    The symbol's position is absolute.                                      *
 *                                                                            *
 * INPUT:   symbol -- The image symbol to be captured.                        *
 *                                                                            *
 * OUTPUT:  Return whether captured.                                          *
 *                                                                            *
 * WARNINGS:  The parameter symbol mustn't be changed.                        *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *   2022/01/13 Tony : Added isAbsolute.                                      *
 *   2022/02/18 Tony : Removed isAbsolute. :)                                 *s
 *============================================================================*/
bool Camera::captureStatic(Symbol symbol)
{
	int srcWidth = symbol.img->getwidth();
	int srcHeight = symbol.img->getheight();
	Coord src = symbol.pos + symbol.offset;

	// Check if the symbol is out of sight.
	if ((src.x + srcWidth < 0) || (src.y + srcHeight < 0) \
		|| (src.x >= width) || (src.y >= height))
		return false;

	imagePool.add(symbol);

	return true;
}


/******************************************************************************
 * Camera::develop -- Develop the film.                                       *
 *                                                                            *
 *    Develop the film to the target image. Vividly, isn't it?                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
void Camera::develop()
{
	imagePool.draw();
	putTransparentImage(pTargetImage, 0, 0, &film);

	SetWorkingImage(&film);
	cleardevice();
	SetWorkingImage(NULL);
}


/******************************************************************************
 * Camera::convert -- Convert coordinate.                                     *
 *                                                                            *
 *    Convert the coordinate of the mouse.                                    *
 *                                                                            *
 * INPUT:   coord -- logical coordinate of the mouse.                         *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
Coord Camera::convert(const Coord& coord)
{
	return curPos + coord;
}