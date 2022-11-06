/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : camera.h                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 1, 2022                           *
 *                                                                            *
 *                    Last Update : February 5, 2022                          *
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

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "define.h"
#include "image.h"

 // Default speed of the camera. pixel/second
const double CAM_SPEED = 20.0;

// Some fixed speed rate of the camera.
const double CAM_FAST = 0.002;
const double CAM_MEDIUM = 0.0005;
const double CAM_SLOW = 0.0001;


/********************************************************************
** Camera, capture what the player sees, and follow the player or...
** anything with a coordinate. (> <)
*/
class Camera
{
public:
	Camera(Coord _pos = { 0, 0 },
		int _width = CANVAS_WIDTH,
		int _height = CANVAS_HEIGHT,
		double _factor = CAM_MEDIUM);
	~Camera();

	void init(Coord _pos,
		int _width,
		int _height,
		double _factor);
	/*
	** Set target image buffer, i.e. where to draw the contents.
	*/
	void setTargetImage(IMAGE* _pTargetImage);

	/*
	** Set the moving style of the camera. It moves gradually
	** by default.
	*/
	void setStyle(bool _isSteady);

	/*
	** Center the coordinate immediately.
	*/
	void focus(Coord target);

	/*
	** Set a new coordinate to follow.
	*/
	void follow(Coord target);

	/*
	** Simply move towards the destination. Return true if it
	** really moves.
	*/
	bool move();

	/*
	** Return camera's image, the film. :)
	*/
	IMAGE* getImage();

	/*
	** Return target image.
	*/
	IMAGE* getTargetImage();

	/*
	** Capture an object in sight.
	** 2022/01/10
	** Changed to a copy.
	** 2022/01/13
	** Add a choice for absolute position.
	** 2022/02/18
	** Seperated the choice for absolute position.
	*/
	bool capture(Symbol symbol);
	bool captureStatic(Symbol symbol);

	/*
	** Develop the film and draw it on assigned buffer. (LOL)
	** Default buffer is the device. Here can use other buffer
	** for camera nesting.
	*/
	void develop();

	/*
	** 2022/02/04
	** Convert absolute coordinate to relative coordinate.
	*/
	Coord convert(const Coord& coord);

private:
	/*
	** Absolute position on the device. Camera will show its
	** vision in an (width * height) area at the pos.
	*/
	Coord pos;

	int width;
	int height;

	/*
	** Camera firstly draw all images to the negative film,
	** and then draw it to the target image.
	*/
	IMAGE film;
	IMAGE* pTargetImage;

	/*
	** Dynamic position. Unless current position is the same as the
	** destination position, the camera will moves to center it.
	*/
	Coord curPos;
	Coord offset;
	Coord curCenter;
	Coord tarCenter;

	/*
	** 2022/01/11
	** Factor of the speed.
	*/
	double factor;

	/*
	** If is steady, then it will move in a constant speed.
	*/
	bool isSteady;

	/*
	** Reserve all images for later use. It only stores Symbols that
	** are insight. :)
	*/
	ImagePool imagePool;
};

#endif