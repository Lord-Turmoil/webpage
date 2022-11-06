/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : image.h                                   *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 1, 2022                           *
 *                                                                            *
 *                    Last Update : February 5, 2022                          *
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

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <queue>
#include <vector>
#include <easyx.h>
#include <Windows.h>
#include <functional>

#include "define.h"


 // Default window size
const int CANVAS_WIDTH = 640;
const int CANVAS_HEIGHT = 480;

// Default transparent color.
const unsigned int TRANSPARENT_COLOR = 0x00ff00ff;

// Some default layers.
enum DefaultLayer
{
	LAYER_BACK = -10,
	LAYER_NORMAL = 0,
	LAYER_BULLET = 5,
	LAYER_WEAPON = 10,
	LAYER_HIGH = 15
};


/********************************************************************
** Symbol Integrate info of a image for multiple layers and
** rotation. And it is accompanied by the function object for
** comparasion.
*/
struct Symbol
{
	IMAGE* img;
	Coord pos;

	/*
	** 2022/01/21
	** ... pos is used for sorting the layer. :(
	*/
	Coord offset;

	/*
	** 2022/01/09
	** Changed from degree to radian.
	*/
	double radian;

	/*
	** layer less than 0 means it is part of the background.
	*/
	int layer;

	/*
	** 2022/01/09
	** Changed to initializing lists.
	*/
	Symbol()
		: img(nullptr), pos({ 0, 0 }), offset({ 0, 0 }), radian(0.0), layer(0) {}
	Symbol(IMAGE* _img, Coord _pos, Coord _offset, double _radian, int _layer)
		: img(_img), pos(_pos), offset(_offset), radian(_radian), layer(_layer) {}
};


/********************************************************************
** Used to sort symbols in image pool.
** 2022/01/10
** Layer should be compared first.
** 2022/01/10
** WARNING: Many symbol are temporary created, so we shouldn't use
**          pointers as elements in the heap!!!
*/
struct CompareSymbol
{
	bool operator() (const Symbol& img1, const Symbol& img2)
	{
		if (img1.layer != img2.layer)
			return img1.layer > img2.layer;
		else
			return img1.pos.y > img2.pos.y;
	};
};


/********************************************************************
** Collects all images and draw them altogether to a certain buffer.
*/
class ImagePool
{
public:
	ImagePool(IMAGE* _pTargetImage = nullptr);
	~ImagePool();

	/*
	** 2022/01/10
	*/
	void setTargetImage(IMAGE* _pTargetImage);

	/*
	** Put an Image in to the pool
	*/
	void add(const Symbol& item);

	/*
	** Draw all images at once. nullptr is the device.
	*/
	void draw();

	/*
	** Clear the pool.
	*/
	void clear();

private:
	IMAGE* pTargetImage;
	std::priority_queue<Symbol, std::vector<Symbol>, CompareSymbol> imgHeap;
};


/********************************************************************
** To take hold of the window and the graph of EasyX. And drawing
** info like FPS.
*/
class Canvas
{
public:
	Canvas();
	~Canvas();

	/*
	** Create a graph in the center of the screen.
	*/
	void create(int width, int height);

	void close();

	/*
	** 2022/01/04
	** Get the canvas' image buffer. Here we cann't add
	** const to the function.
	*/
	IMAGE* getImage();

	/*
	** Expand to full screen, or shrink to original size,
	** or switch between these two size.
	*/
	void expand();
	void shrink();
	void switchSize();

	/*
	** 2022/01/10
	** Initializing the canvas. i.e. clear the canvas.
	*/
	void clear();

	/*
	** Draw the image to the device.
	*/
	void draw();

	/*
	** 2022/02/05
	** Convert physical coordinate to logical coordinate.
	*/
	Coord convert(Coord physical);

	/*
	** Some advanced operation.
	*/
	void darken(int milliseconds);
	void brighten(int milliseconds);

	void snip();

private:
	/*
	** The handle of the current window.
	*/
	HWND hWnd;

	/*
	** 2022/01/04
	** Image buffer of the canvas.
	*/
	IMAGE image;

	/*
	** Original width and height of the window.
	*/
	int width;
	int height;

	/*
	** 2022/01/03
	** These property doesn't change.
	*/
	int screenWidth;
	int screenHeight;
	float xAsp;
	float yAsp;
	float asp;

	/*
	** 2022/02/05
	** The origin of the logical coordinate, used to
	** handle cursor coordinate.
	*/
	Coord origin;

	bool isFullscreen;
};



/********************************************************************
** Some brothers to draw transparent images.
*/
void putTransparentImage(IMAGE* pDestImg, int destX, int destY, IMAGE* pSrcImg, unsigned int transparentColor = TRANSPARENT_COLOR);
void putTransparentImage(int destX, int destY, IMAGE* pSrcImg, unsigned int transparentColor = TRANSPARENT_COLOR);
void putRotatedTransparentImage(IMAGE* pDestImg, int destX, int destY, IMAGE* pSrcImg, int degree, unsigned int transparentColor = TRANSPARENT_COLOR);
void putRotatedTransparentImage(IMAGE* pDestImg, int destX, int destY, IMAGE* pSrcImg, double radian, unsigned int transparentColor = TRANSPARENT_COLOR);


/********************************************************************
** Some functions to handle alpha property.
*/
// Parse R, G, B in a color.
#define PA(color) (((color) & 0xFF000000) >> 24)
#define PB(color) (((color) & 0x00FF0000) >> 16)
#define PG(color) (((color) & 0x0000FF00) >> 8)
#define PR(color) (((color) & 0x000000FF))

// Get the color width alpha info.
// REFERENCE: https://codebus.cn/tonyddg/gradienter
// s: Color of the source image.
// d: Color of the destination image.
// a: Alpha value.
#define ARGB(s, d, a) RGB((((PR(s) - PR(d)) * a) >> 8), (((PG(s) - PG(d)) * a) >> 8), (((PB(s) - PB(d)) * a) >> 8))

void putAlphaImage(IMAGE* pDestImg, int destX, int destY, IMAGE* pSrcImg, int alpha);


#endif