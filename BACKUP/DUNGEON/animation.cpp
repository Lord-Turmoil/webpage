/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : animation.cpp                             *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 11, 2022                          *
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


#include <easyx.h>
#include <Windows.h>

#include "straw.h"
#include "error.h"
#include "timing.h"
#include "config.h"
#include "define.h"
#include "animation.h"
#include "auxilliary.h"


extern Time globalTimer;


/******************************************************************************
 * Frame::Frame -- Constructor of the object.                                 *
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
 *   2022/01/11 Tony : Created.                                               *
 *============================================================================*/
Frame::Frame() {}


/******************************************************************************
 * Frame::~Frame -- Deconstructor of the object.                              *
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
 *   2022/01/11 Tony : Created.                                               *
 *============================================================================*/
Frame::~Frame() {}


/******************************************************************************
 * Frame::load -- Load frames from a .ini file. :)                            *
 *                                                                            *
 *    See data format in config.h. :)                                         *
 *                                                                            *
 * INPUT:   file    -- Filename of the .ini.                                  *
 *          section -- Which section to load.                                 *
 *                                                                            *
 * OUTPUT:  Return whether succeeded.                                         *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/11 Tony : Created.                                               *
 *============================================================================*/
bool Frame::load(const std::wstring& file, const std::wstring& section)
{
	Straw straw(file, section);

	// Load motion num.
	motionNum = straw.suckInt(L"motionNum");

	// Load whether is dual.
	isDual = (straw.suckString(L"isDual") == L"yes") ? true : false;

	// Load frame numbers.
	extractInt(straw.suckString(L"frameNum"), frameNum);
	if (frameNum.size() != motionNum)
	{
		wreportf(FAILED_TO_LOAD_FW, section.c_str(), LOAD_FRAME_W);
		return false;
	}

	// Load play time.
	extractInt(straw.suckString(L"playTime"), playTime);
	if (playTime.size() != motionNum)
	{
		wreportf(FAILED_TO_LOAD_FW, section.c_str(), LOAD_FRAME_W);
		return false;
	}

	// Load frame speed.
	frameSpeed = straw.suckInt(L"frameSpeed");

	// Load motion images.
	Coord start = straw.suckCoord(L"start");
	int width = straw.suckInt(L"frameWidth");
	int height = straw.suckInt(L"frameHeight");
	int n = isDual ? (motionNum << 1) : motionNum;
	std::wstring src = straw.suckString(L"src");
	IMAGE srcImg;
	int id;

	src = PATH_IMAGE + src;
	if (!isAccessible(src.c_str()))
	{
		wreportf(FAILED_TO_LOAD_FW, src.c_str(), LOAD_IMAGE_W);
		return false;
	}
	loadimage(&srcImg, src.c_str());

	SetWorkingImage(&srcImg);

	motionFrame.resize(n);
	for (int i = 0; i < n; i++)
	{
		id = (i < motionNum) ? i : i - motionNum;
		motionFrame[i].resize(frameNum[id]);
		for (int j = 0; j < frameNum[id]; j++)
			getimage(&motionFrame[i][j], start.x + j * width, start.y + i * height, width, height);
	}

	return true;
}



/******************************************************************************
 * Animation::Animation -- Constructor of the object.                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Initialize the pointers.                                        *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/11 Tony : Created.                                               *
 *   2022/01/14 Tony : Added isOver.                                          *
 *   2022/01/19 Tony : Removed offset.                                        *
 *============================================================================*/
Animation::Animation()
{
	pFrame = nullptr;

	// offset = 0;

	/*
	** -1 is invalid. But when the animation loaded and updates, if new
	** motion is different from the current one, the preTimestamp will
	** refresh for the first time. :)
	*/
	curMotion = -1;

	isOver = false;
}


/******************************************************************************
 * Animation::~Animation -- Deconstructor of the object.                      *
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
 *   2022/01/11 Tony : Created.                                               *
 *============================================================================*/
Animation::~Animation() {}


/******************************************************************************
 * Animation::load -- Load frames of a animation.                             *
 *                                                                            *
 *    This will load frams of motions from a loaded Frame object.             *
 *                                                                            *
 * INPUT:   _pFrame -- The frame to be loaded.                                *
 *                                                                            *
 * OUTPUT:  Return whether succeeded or not.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/11 Tony : Created.                                               *
 *   2022/01/13 Tony : Added initialization to (??? > <)                      *
 *   2022/01/18 Tony : Removed offset.                                        *
 *============================================================================*/
bool Animation::load(Frame* _pFrame)
{
	pFrame = _pFrame;

	for (int i = 0; i < pFrame->motionNum; i++)
		duration.push_back(pFrame->frameNum[i] * pFrame->frameSpeed);

	/*
	** 2022/01/13
	** If the motion only have one frame, then it is just a single
	** one, so curMotion doesn't need to be -1.
	*/
	if ((pFrame->motionNum == 0) && (pFrame->frameNum[0] == 0))
		curMotion = 0;

	curFrame = 0;
	
	// offset = 0;

	return true;
}


/******************************************************************************
 * Animation::update -- Update the frame of the animation.                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   motion -- The motion id of the object.                            *
 *                                                                            *
 * OUTPUT:  If the motion can only be played once, then return false if it is *
 *          over. Return true in other cases.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/11 Tony : Created.                                               *
 *   2022/01/13 Tony : Added play time of a frame.                            *
 *   2022/01/14 Tony : Added isOver.                                          *
 *   2022/01/19 Tony : Removed facing and added invalid motion.               *
 *============================================================================*/
bool Animation::update(int motion)
{
	// New motion assigned.
	if ((curMotion != motion) && (motion != -1))
	{
		curMotion = motion;
		curFrame = 0;
		prevTimestamp = globalTimer.getTimestamp();
		isOver = false;
	}
	
	// offset = facing;

	curTimestamp = globalTimer.getTimestamp();
	if (curTimestamp - prevTimestamp > pFrame->frameSpeed)
	{
		curFrame++;
		if (curFrame >= pFrame->frameNum[curMotion])
		{
			if (pFrame->playTime[curMotion])
			{
				isOver = true;
				curFrame = pFrame->frameNum[curMotion] - 1;
				return false;
			}
			else
				curFrame = 0;
		}
		prevTimestamp = curTimestamp;
	}

	return true;
}


/******************************************************************************
 * Animation::getFrame -- Get current frame to display.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   facing -- The facing of the object.                               *
 *                                                                            *
 * OUTPUT:  Return the address of the image to display.                       *
 *                                                                            *
 * WARNINGS:  facing can only be 0 or 1.                                      *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/11 Tony : Created.                                               *
 *   2022/01/19 Tony : Added facing.                                          *
 *============================================================================*/
IMAGE* Animation::getFrame(int facing)
{
	return &pFrame->motionFrame[curMotion + facing * pFrame->motionNum][curFrame];
}


/******************************************************************************
 * Animation::getState -- Get whether overed.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether the animation is overed or not.                    *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
bool Animation::over() const
{
	return isOver;
}