/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : image.cpp                                 *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 1, 2022                           *
 *                                                                            *
 *                    Last Update : January 21, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For image processing. And all the operations to images.                  *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include <ctime>
#include <easyx.h>
#include <Windows.h>

#include "image.h"
#include "config.h"
#include "auxilliary.h"


/********************************************************************
** Global canvas.
*/
Canvas canvas;


/******************************************************************************
 * ImagePool::ImagePool -- Constructor of the object.                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _pTargetImage -- The target image.                                *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
ImagePool::ImagePool(IMAGE* _pTargetImage)
{
	pTargetImage = _pTargetImage;
}


/******************************************************************************
 * ImagePool::~ImagePool -- Deconstructor of the object.                      *
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
ImagePool::~ImagePool() {}


/******************************************************************************
 * ImagePool::setTargetImage -- Set target image.                             *
 *                                                                            *
 *    The image will be drawn on the target image.                            *
 *                                                                            *
 * INPUT:   _pTargetImage                                                     *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
void ImagePool::setTargetImage(IMAGE* _pTargetImage)
{
	pTargetImage = _pTargetImage;
}


/******************************************************************************
 * ImagePool::add -- Put a symbol into the pool.                              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   item -- The symbol item to be put into the pool.                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  A copy of symbol should be added in the pool, NOT a pointer!!!  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *   2022/01/10 Tony : Changed pointer to reference.                          *
 *============================================================================*/
void ImagePool::add(const Symbol& item)
{
	imgHeap.push(item);
}


/******************************************************************************
 * ImagePool::draw -- Draw all symbols to the target image.                   *
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
 *   2022/01/21 Tony : Added imgPos as the real coordinate of the image.      *
 *============================================================================*/
void ImagePool::draw()
{
	Symbol item;

	while (!imgHeap.empty())
	{
		item = imgHeap.top();
		imgHeap.pop();

		putRotatedTransparentImage(
			pTargetImage,
			item.pos.x + item.offset.x,
			item.pos.y + item.offset.y,
			item.img,
			item.radian);
	}
}


/******************************************************************************
 * ImagePool::clear -- Clear the image pool.                                  *
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
void ImagePool::clear()
{
	while (!imgHeap.empty())
		imgHeap.pop();
}



/******************************************************************************
 * Canvas::Canvas -- Default constructor of canvas object.                    *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *   2022/01/03 Tony : Add initializing constant members.                     *
 *============================================================================*/
Canvas::Canvas()
{
	hWnd = nullptr;
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
}



/******************************************************************************
 * Canvas::~Canvas -- Default deconstructor of canvas object.                 *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *   2022/01/03 Tony : Add closegraph.                                        *
 *============================================================================*/
Canvas::~Canvas()
{
	if (hWnd)
		closegraph();
}


/******************************************************************************
 * Canvas::create -- Create a canvas.                                         *
 *                                                                            *
 *    This one create a new canvas with the given size.                       *
 *                                                                            *
 * INPUT:   _width  -- The actual width of the graph.                         *
 *          _height -- The actual height of the graph.                        *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   It should only be called once.                                 *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *   2022/01/03 Tony : Added some member to the class.                        *
 *   2022/01/04 Tony : Added image.                                           *
 *   2022/02/05 Tony : Added uniform aspect ratio.                            *
 *   2022/02/15 Tony : The size of the window... changes???                   *
 *============================================================================*/
void Canvas::create(int _width, int _height)
{
	width = _width;
	height = _height;

#ifdef _DEBUG
	hWnd = initgraph(width, height, EW_SHOWCONSOLE);
#else
	hWnd = initgraph(width, height);
#endif

	setbkmode(TRANSPARENT);

	image.Resize(width, height);

	xAsp = 1.0f * screenWidth / width;
	yAsp = 1.0f * screenHeight / height;

	asp = (xAsp > yAsp) ? yAsp : xAsp;

	/*
	** Here exists a problem that the size assigned may be
	** larger than the user's computer screen. But... leave
	** it to solve later.
	*/
	SetWindowPos(hWnd, HWND_TOP, (screenWidth - width) >> 1, (screenHeight - height) >> 1, width, height, SWP_SHOWWINDOW);
	Resize(nullptr, width, height);

	isFullscreen = false;

	SetWorkingImage(&image);
	setbkcolor(BLACK);
	cleardevice();
	SetWorkingImage(NULL);

	BeginBatchDraw();
}


/******************************************************************************
 * Canvas::close -- Close the canvas.                                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/11 Tony : Created.                                               *
 *============================================================================*/
void Canvas::close()
{
	EndBatchDraw();

	closegraph();
}


/******************************************************************************
 * Canvas::getImage -- Get the canvas' image buffer.                          *
 *                                                                            *
 *    See above...                                                            *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  The canvas' image buffer.                                         *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/04 Tony : Created.                                               *
 *   2022/01/05 Tony : Changed to inline.                                     *
 *============================================================================*/
IMAGE* Canvas::getImage()
{
	return &image;
}


/******************************************************************************
 * Canvas::expand -- Expand the window to full screen.                        *
 *                                                                            *
 *    This one check the size of user's computer screen and strech to fit it. *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *   2022/01/03 Tony : Removed some unnecessary calculation.                  *
 *============================================================================*/
void Canvas::expand()
{
	if (isFullscreen)
		return;

	/*
	** Set window style. The caption is hidden when displayed fullscreen.
	*/
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & (~WS_CAPTION));
	SetWindowPos(hWnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);

	/*
	** Adjust content size and position.
	*/
	if (xAsp > yAsp)
	{
		origin.x = (screenWidth - (int)(width * yAsp)) >> 1;
		origin.y = 0;
	}
	else
	{
		origin.x = 0;
		origin.y = (screenHeight - (int)(height * xAsp)) >> 1;
	}
	setaspectratio(asp, asp);
	setorigin(origin.x, origin.y);

	/*
	** Here, we also need to resize the EaxyX graph.
	*/
	Resize(nullptr, screenWidth, screenHeight);

	cleardevice();

	isFullscreen = true;
}


/******************************************************************************
 * Canvas::shrink -- Shrink the window to original size.                      *
 *                                                                            *
 *    Opposite to expand. It shrink the window to original size assigned in   *
 *    Canvas::create, and center the window.                                  *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *   2022/01/03 Tony : Removed some unnecessary calculation.                  *
 *============================================================================*/
void Canvas::shrink()
{
	if (!isFullscreen)
		return;

	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) | WS_CAPTION);
	SetWindowPos(hWnd, HWND_TOP, (screenWidth - width) >> 1, (screenHeight - height) >> 1, width, height, SWP_SHOWWINDOW);

	setaspectratio(1.0, 1.0);
	origin.x = origin.y = 0;
	setorigin(0, 0);
	Resize(nullptr, width, height);

	isFullscreen = false;
}


/******************************************************************************
 * Canvas::switchSize -- Switch between fullscreen and original size.         *
 *                                                                            *
 *    Change current display size.                                            *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/02 Tony : Created.                                               *
 *============================================================================*/
void Canvas::switchSize()
{
	static clock_t lastTime = 0;

	if (clock() - lastTime < 500)
		return;
	lastTime = clock();

	if (isFullscreen)
		shrink();
	else
		expand();
}


/******************************************************************************
 * Canvas::clear -- Clear the canvas.                                         *
 *                                                                            *
 *    Each frame should be drawn on an empty canvas. :(                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   Remember to set working image to NULL!!!                       *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/10 Tony : Created.                                               *
 *============================================================================*/
void Canvas::clear()
{
	SetWorkingImage(&image);
	cleardevice();
	SetWorkingImage(NULL);
}


/******************************************************************************
 * Canvas::draw -- Draw prepared image to the device.                         *
 *                                                                            *
 *    Here we just need the original putimage, as transparent effect is done  *
 *    by Camera. And as canvas is the whole screen, we just need to draw at   *
 *    the original point.                                                     *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/04 Tony : Created.                                               *
 *   2022/01/05 Tony : Changed to inline.                                     *
 *   2022/02/13 Tony : Added FlushBatchDraw.                                  *
 *============================================================================*/
void Canvas::draw()
{
	SetWorkingImage(NULL);
	putimage(0, 0, &image);

	FlushBatchDraw();
}


/******************************************************************************
 * Canvas::convert -- Convert physical coordinate to logical coordinate.      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   physical -- Physical coordinate of the device.                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
Coord Canvas::convert(Coord physical)
{
	Coord logical;

	if (isFullscreen)
	{
		logical.x = (int)((float)(physical.x - origin.x) / asp);
		logical.y = (int)((float)(physical.y - origin.y) / asp);
	}
	else
		logical = physical;

	return logical;
}


/******************************************************************************
 * Canvas::darken -- Darken the canvas.                                       *
 *                                                                            *
 *    This one darken the canvas to total black during given time. This will  *
 *    pause all other processes.                                              *
 *                                                                            *
 * INPUT:   milliseconds -- Total time used.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/14 Tony : Created.                                               *
 *============================================================================*/
void Canvas::darken(int milliseconds)
{
	if (milliseconds <= 0)
		return;


	static IMAGE tempImage;
	int cnt = milliseconds / DELAY;
	double k = 255.0 / (double)cnt;

	tempImage = image;
	for (int i = 0; i < cnt; i++)
	{
		clear();
		putAlphaImage(&image, 0, 0, &tempImage, (int)(255 - i * k));
		draw();
		
		Sleep(DELAY);
	}
}


/******************************************************************************
 * Canvas::brighten -- Brighten the canvas to original color.                 *
 *                                                                            *
 *    The reverse of darken.                                                  *
 *                                                                            *
 * INPUT:   milliseconds                                                      *
 *          pMaskImage   -- The new image to mask the previous one.           *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/14 Tony : Created.                                               *
 *============================================================================*/
void Canvas::brighten(int milliseconds)
{
	if (milliseconds <= 0)
		return;


	static IMAGE tempImage;
	int cnt = milliseconds / DELAY;
	double k = 255.0 / (double)cnt;

	tempImage = image;
	for (int i = 0; i < cnt; i++)
	{
		clear();
		putAlphaImage(&image, 0, 0, &tempImage, (int)(i * k));
		draw();
		
		Sleep(DELAY);
	}
}


/******************************************************************************
 * Canvas::snip -- To take a screen shot.                                     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
void Canvas::snip()
{
	SYSTEMTIME sysTime;
	wchar_t str[20];
	std::wstring filename;

	GetLocalTime(&sysTime);
	
	//YYYYMMDDHHMMSS
	swprintf_s(str, L"%4hu%02hu%02hu%02hu%02hu%02hu", \
		sysTime.wYear, sysTime.wMonth, sysTime.wDay, \
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	filename = PATH_SCREEN;
	if (_waccess(filename.c_str(), 0) == -1)	//do not exist
		_wmkdir(filename.c_str());

	filename += str;
	filename += L".png";

	SetWorkingImage(&image);
	saveimage(filename.c_str());
	SetWorkingImage(NULL);
}

/******************************************************************************
 * putTransparentImage -- Draw transparent image.                             *
 *                                                                            *
 *    This one draws oridinary transparent images on assigned image buffer.   *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/yangw/transparent-putimage                 *
 *                                                                            *
 * INPUT:   pDestImg         -- Destination image buffer.                     *
 *          destX, destY     -- Position on destination image.                *
 *          pSrcImg          -- Source image buffer.                          *
 *          transparentColor -- Transparent color in source image.            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Be careful about illegal pointers! And this function            *
 *            cann't change the size of the image with the screen.            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/01 Tony : Created.                                               *
 *   2022/01/09 Tony : Fixed out of range check.                              *
 *============================================================================*/
void putTransparentImage(IMAGE* pDestImg, int destX, int destY, IMAGE* pSrcImg, unsigned int transparentColor)
{
	DWORD* pDestBuffer = GetImageBuffer(pDestImg);
	DWORD* pSrcBuffer = GetImageBuffer(pSrcImg);
	int srcWidth = pSrcImg->getwidth();
	int srcHeight = pSrcImg->getheight();
	int destWidth = (pDestImg == NULL ? getwidth() : pDestImg->getwidth());
	int destHeight = (pDestImg == NULL ? getheight() : pDestImg->getheight());

	/*
	** Return if the whole image is out of the buffer
	** 2022/01/09
	** Fixed that the image would also out from right.
	*/
	if ((destX + srcWidth < 0) || (destY + srcHeight < 0) \
		|| (destX >= destWidth) || (destY >= destHeight))
		return;

	/*
	** Adjust image size and position.
	*/
	int width = MIN(destX + srcWidth, destWidth) - MAX(destX, 0);
	int height = MIN(destY + srcHeight, destHeight) - MAX(destY, 0);
	if (destX < 0)
	{
		pSrcBuffer -= destX;
		destX = 0;
	}
	if (destY < 0)
	{
		pSrcBuffer -= destY * srcWidth;
		destY = 0;
	}
	pDestBuffer += destWidth * destY + destX;

	/*
	** Modify transparent color. Here, the highest 8 bits may differ,
	** so I obliterate them.
	*/
	transparentColor = 0x00ffffff & BGR(transparentColor);

	// Put src image to the dest buffer.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((pSrcBuffer[j] & 0x00ffffff) != transparentColor)
				pDestBuffer[j] = pSrcBuffer[j];
		}
		pDestBuffer += destWidth;
		pSrcBuffer += srcWidth;
	}
}


/******************************************************************************
 * putTransparentImage -- Draw transparent image.                             *
 *                                                                            *
 *    This one draws oridinary transparent images on current image buffer.    *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/yangw/transparent-putimage                 *
 *                                                                            *
 * INPUT:   destX, destY     -- Position on destination image.                *
 *          pSrcImg          -- Source image buffer.                          *
 *          transparentColor -- Transparent color in source image.            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:                                                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void putTransparentImage(int destX, int destY, IMAGE* pSrcImg, unsigned int transparentColor)
{
	IMAGE* pDestImg = GetWorkingImage();

	putTransparentImage(pDestImg, destX, destY, pSrcImg, transparentColor);
}


/******************************************************************************
 * putRotatedTransparentImage -- Draw rotated transparent image.              *
 *                                                                            *
 *    This one first rotate the image and then draw it's rotated copy.        *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/yangw/transparent-putimage                 *
 *                                                                            *
 * INPUT:   pDestImg         -- Destination image buffer.                     *
 *          destX, destY     -- Position on destination image.                *
 *          pSrcImg          -- Source image buffer.                          *
 *          degree           -- Rotate counter-clockwise in degree.           *
 *          transparentColor -- Transparent color in source image.            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Be careful about illegal pointers! And this function            *
 *            cann't change the size of the image with the screen.            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/01 Tony : Created.                                               *
 *   2022/01/03 Tony : Made rotated_image a static virable.                   *
 *============================================================================*/
void putRotatedTransparentImage(IMAGE* pDestImg, int destX, int destY, IMAGE* pSrcImg, int degree, unsigned int transparentColor)
{
	if (degree == 0)
	{
		putTransparentImage(pDestImg, destX, destY, pSrcImg, transparentColor);
		return;
	}

	static IMAGE rotated_image;

	rotateimage(&rotated_image, pSrcImg, PI * (degree / 180.0), transparentColor, false, false);
	putTransparentImage(pDestImg, destX, destY, &rotated_image, transparentColor);
}


/******************************************************************************
 * putRotatedTransparentImage -- Draw rotated transparent image.              *
 *                                                                            *
 *    This one first rotate the image and then draw it's rotated copy.        *
 *                                                                            *
 * REFERENCE:   https://codebus.cn/yangw/transparent-putimage                 *
 *                                                                            *
 * INPUT:   pDestImg         -- Destination image buffer.                     *
 *          destX, destY     -- Position on destination image.                *
 *          pSrcImg          -- Source image buffer.                          *
 *          radian           -- Rotate counter-clockwise in radian.           *
 *          transparentColor -- Transparent color in source image.            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Be careful about illegal pointers! And this function            *
 *            cann't change the size of the image with the screen.            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/03 Tony : Created.                                               *
 *============================================================================*/
void putRotatedTransparentImage(IMAGE* pDestImg, int destX, int destY, IMAGE* pSrcImg, double radian, unsigned int transparentColor)
{
	/*
	** Althougth they are defined in two functions with the same name
	** at the static memories, they are actually different and have
	** different address.
	*/
	static IMAGE rotated_image;

	rotateimage(&rotated_image, pSrcImg, radian, transparentColor, false, false);
	putTransparentImage(pDestImg, destX, destY, &rotated_image, transparentColor);
}



/******************************************************************************
 * putAlpha -- Draw image with alpha info.                                    *
 *                                                                            *
 *    This one draws alpha image on assigned image buffer. Quite like the one *
 *    which draw transparent image.                                           *
 *                                                                            *
 * REFERENCE:   https://www.cnblogs.com/mengfanrong/p/4325852.html            *
 *                                                                            *
 * INPUT:   pDestImg     -- Destination image buffer.                         *
 *          destX, destY -- Position on destination image.                    *
 *          pSrcImg      -- Source image buffer.                              *
 *          alpha        -- Alpha info of the source image.                   *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Well... we do not check if alpha is out of [0, 256). :)         *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/14 Tony : Created.                                               *
 *============================================================================*/
void putAlphaImage(IMAGE* pDestImg, int destX, int destY, IMAGE* pSrcImg, int alpha)
{
	DWORD* pDestBuffer = GetImageBuffer(pDestImg);
	DWORD* pSrcBuffer = GetImageBuffer(pSrcImg);
	int srcWidth = pSrcImg->getwidth();
	int srcHeight = pSrcImg->getheight();
	int destWidth = (pDestImg == NULL ? getwidth() : pDestImg->getwidth());
	int destHeight = (pDestImg == NULL ? getheight() : pDestImg->getheight());

	if ((destX + srcWidth < 0) || (destY + srcHeight < 0) \
		|| (destX >= destWidth) || (destY >= destHeight))
		return;

	int width = MIN(destX + srcWidth, destWidth) - MAX(destX, 0);
	int height = MIN(destY + srcHeight, destHeight) - MAX(destY, 0);
	if (destX < 0)
	{
		pSrcBuffer -= destX;
		destX = 0;
	}
	if (destY < 0)
	{
		pSrcBuffer -= destY * srcWidth;
		destY = 0;
	}
	pDestBuffer += destWidth * destY + destX;

	// Put src image to the dest buffer.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			pDestBuffer[j] = ARGB(pSrcBuffer[j], pDestBuffer[j], alpha);

		pDestBuffer += destWidth;
		pSrcBuffer += srcWidth;
	}
}