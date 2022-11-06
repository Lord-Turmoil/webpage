/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : animation.h                               *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 9, 2022                           *
 *                                                                            *
 *                    Last Update : February 7, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For objects' animations.                                                 *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _ANIMATION_H_
#define _ANIMATION_H_


#include <ctime>
#include <vector>
#include <string>
#include <easyx.h>

#include "image.h"


/********************************************************************
** The principle of animation effect is as following:
** 1. The Frame stores all images a set of motions needed.
** 2. Animation takes out original images(without rotation and
**    resize) from the Frame.
** 3. And then with the position, rotating angle and layer info
**    provided by the objects, they combine together to a Symbol.
** 4. Then the Symbol will be handed over to the camera.
** 5. And the Camera will inspect them and put the ones insight
**    into the ImagePool, where they will be sorted by layer info.
** 6. Then, the Camera will draw them on the Canvas.
** 7. At last, the Canvas will draw the images on the device. :)
*/



/********************************************************************
** A frame is the whole set of motions of a character. Well, I don't
** want thoes members to be public, but it would be complicated if
** they are all private. :(
*/
class Frame
{
public:
	Frame();
	~Frame();

	/*
	** Load a set of frames in a .ini file. :]
	** 2022/01/11
	** Image resource should be provided first.
	** 2022/02/07
	** No need for image resource.
	*/
	bool load(const std::wstring& file, const std::wstring& section);


	/*
	** A two demensional dynamic array for single frames.
	** A row is a set of motion, and all rows are the whole
	** motions of a character. And if the object has two sides,
	** such as the hero may face left and right, it simply adds
	** a offset to the row. :)
	*/
	std::vector<std::vector<IMAGE>> motionFrame;

	/*
	** How many motions this object has. It is just the row
	** number of the pFrame, but only half if the object has
	** two facings.
	*/
	int motionNum;

	/*
	** Whether the frame has two symmetrical motions. If is true,
	** then the actual number of motions is double of motionNum,
	** meaning that the object has both left and right facing.
	*/
	bool isDual;

	/*
	** Well, still a dynamic array. It is the number of frames
	** each motion has.
	*/
	std::vector<int> frameNum;

	/*
	** 2022/01/13
	** Hmm, the motion can be different, some motion can only be
	** performed once. 0 means infinite, 1 means only once.
	*/
	std::vector<int> playTime;

	/*
	** How long each frame lasts.
	*/
	clock_t frameSpeed;
};


/********************************************************************
** Animation load a Frame and take hold of the behavior of the
** wonderful animations.
*/
class Animation
{
public:
	Animation();
	~Animation();

	/*
	** Load motions from a Frame object.
	*/
	bool load(Frame* _pFrame);

	/*
	** Update animation.
	*/
	bool update(int motion = 0);

	/*
	** Get current frame to display.
	*/
	IMAGE* getFrame(int facing = 0);

	/*
	** Get whether overed.
	*/
	bool over() const;

private:
	Frame* pFrame;

	/*
	** Which motion current animation is.
	*/
	int curMotion;

	/*
	** Which frame in the current motion.
	*/
	int curFrame;

	/*
	** For the facing of the object, it can only be 0 or 1.
	** The default facing plus the offset is the opposite facing.
	*/
	// int offset;

	/*
	** The total time each motion takes, another dynamic array.
	*/
	std::vector<clock_t> duration;

	/*
	** 2022/01/11
	** The beginning time of the motion. This will refresh if
	** motion changes.
	*/
	clock_t prevTimestamp;

	clock_t curTimestamp;

	/*
	** 2022/01/14
	** Whether the animation is over or not.
	*/
	bool isOver;
};

#endif