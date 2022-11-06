/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : widget.h                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 5, 2022                           *
 *                                                                            *
 *                    Last Update : February 20, 2022                         *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For UI widgets. Based on EasyUI.                                         *
 * -------------------------------------------------------------------------- *
 * Reference:                                                                 *
 *   https://codebus.cn/contributor/zhurong-easyui                            *
 *   Many many many many many thanks! :)                                      *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include <map>
#include <ctime>
#include <string>
#include <cstring>
#include <cstdlib>

#include "image.h"
#include "error.h"
#include "widget.h"
#include "tinyxml.h"
#include "command.h"
#include "auxilliary.h"


extern CommandFilter filter;

 /******************************************************************************
  * DrawCell::DrawCell -- Constructor of DrawCell object.                      *
  *                                                                            *
  * INPUT:   none                                                              *
  *                                                                            *
  * OUTPUT:  none                                                              *
  *                                                                            *
  * WARNINGS:   Remember to initialize the pointer!                            *
  *                                                                            *
  * HISTORY:                                                                   *
  *   2022/01/05 Tony : Created.                                               *
  *============================================================================*/
DrawCell::DrawCell()
{
	isCentered = false;
	pSubCell = nullptr;
}


/******************************************************************************
 * DrawCell::~DrawCell -- Deconstructor of DrawCell object.                   *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   Remember to delete the pointer!                                *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
DrawCell::~DrawCell()
{
	if (pSubCell)
		delete pSubCell;
}


/******************************************************************************
 * DrawCell::setPos -- Set draw cell position.                                *
 *                                                                            *
 *   Set draw cell's top left position.                                       *
 *                                                                            *
 * INPUT:   _pos -- Top left position.                                        *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *   2022/01/11 Tony : Added behavior of setting its sub cell.                *
 *============================================================================*/
void DrawCell::setPos(const Coord& _pos)
{
	Coord offset = _pos - pos;

	pos = _pos;

	/*
	** 2022/01/11
	*/
	if (pSubCell)
		pSubCell->setPos(pSubCell->getPos() + offset);
}


/******************************************************************************
 * DrawCell::translate -- Translate the drawcell.                             *
 *                                                                            *
 *   Translate the drawcell and all its sub cells.                            *
 *                                                                            *
 * INPUT:   offset -- The offset to translate.                                *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
void DrawCell::translate(Coord offset)
{
	pos += offset;

	if (pSubCell)
		pSubCell->translate(offset);
}


/******************************************************************************
 * DrawCell::makeCenter -- Set whether to center the position.                *
 *                                                                            *
 *   If is centered, then the cell will regard its coordinate as its center   *
 *   instead of top left.                                                     *
 *                                                                            *
 * INPUT:   center -- Whether to center the position.                         *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
void DrawCell::makeCenter(bool center)
{
	isCentered = center;
}


/******************************************************************************
 * DrawCell::getPos -- Get draw cell's position.                              *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the draw cell's position.                                  *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
Coord DrawCell::getPos() const
{
	return pos;
}


/******************************************************************************
 * DrawCell::setSubCell -- Attatch a sub-draw cell.                           *
 *                                                                            *
 *   Attatch a sub-draw cell to a draw cell, and it will be displayed on top  *
 *   of the current draw cell.                                                *
 *                                                                            *
 * INPUT:   cell -- sub cell to be attatched.                                 *
 *                                                                            *
 * OUTPUT:  Return the pointer to the current draw cell.                      *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *   2022/01/06 Tony : Added a check for double-attatch.                      *
 *============================================================================*/
DrawCell* DrawCell::setSubCell(DrawCell* cell)
{
	if (pSubCell)
		delete pSubCell;

	pSubCell = cell;

	return this;
}


/******************************************************************************
 * DrawCell::getSubCell -- Get a ell's position.                              *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the draw cell's position.                                  *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
DrawCell* DrawCell::getSubCell()
{
	return pSubCell;
}



/******************************************************************************
 * SimpleCell::SimpleCell -- Constructor for SimpleCell object.               *
 *                                                                            *
 *   Derived class will automatically call it's base class' constructor.      *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
SimpleCell::SimpleCell()
{
	/*
	** Default style.
	*/
	lineColor = WHITE;
	lineStyle.style = BS_SOLID;
	lineStyle.thickness = 0;
	lineStyle.puserstyle = nullptr;
	lineStyle.userstylecount = 0;

	fillColor = WHITE;
	fillStyle.style = PS_SOLID;
	fillStyle.ppattern = nullptr;
	// fillStyle.hatch = 0;

	isFilled = true;
}


/******************************************************************************
 * SimpleCell::~SimpleCell -- Deconstructor for SimpleCell object.            *
 *                                                                            *
 *   No need to do anything.                                                  *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
SimpleCell::~SimpleCell() {}


/******************************************************************************
 * SimpleCell::setFillStyle -- Set fill style.                                *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   fill -- Whether to fill or not.                                   *
 *                                                                            *
 * OUTPUT:  Return the pointer to the current cell.                           *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
SimpleCell* SimpleCell::setFillStyle(bool fill)
{
	isFilled = fill;

	return this;
}


/******************************************************************************
 * SimpleCell::setLineColor -- Set line color.                                *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   color -- Line color to be set.                                    *
 *                                                                            *
 * OUTPUT:  Return the pointer to the current cell.                           *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
SimpleCell* SimpleCell::setLineColor(COLORREF color)
{
	lineColor = color;

	return this;
}


/******************************************************************************
 * SimpleCell::setFillColor -- Set fill color.                                *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   color -- Fill color to be set.                                    *
 *                                                                            *
 * OUTPUT:  Return the pointer to the current cell.                           *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
SimpleCell* SimpleCell::setFillColor(COLORREF color)
{
	fillColor = color;

	return this;
}


/******************************************************************************
 * SimpleCell::setLineColor -- Set line color.                                *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   color -- Line color to be set.                                    *
 *                                                                            *
 * OUTPUT:  Return the pointer to the current cell.                           *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
SimpleCell* SimpleCell::setLineStyle(const LINESTYLE& style)
{
	lineStyle = style;

	return this;
}


/******************************************************************************
 * SimpleCell::setLineThickness -- Set line thickness.                        *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   thickness -- Line thickness to be set.                            *
 *                                                                            *
 * OUTPUT:  Return the pointer to the current cell.                           *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
SimpleCell* SimpleCell::setLineThickness(int thickness)
{
	lineStyle.thickness = thickness;

	return this;
}


/******************************************************************************
 * SimpleCell::getFill -- Get whether is filled style.                        *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether is filled.                                         *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
bool SimpleCell::getFill() const
{
	return isFilled;
}


/******************************************************************************
 * SimpleCell::getLineColor -- Get current line color.                        *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return current line color.                                        *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
COLORREF SimpleCell::getLineColor() const
{
	return lineColor;
}


/******************************************************************************
 * SimpleCell::getFillColor -- Get fill color.                                *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return current fill color.                                        *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
COLORREF SimpleCell::getFillColor() const
{
	return fillColor;
}


/******************************************************************************
 * SimpleCell::getLineStyle -- Get line style.                                *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return current line style.                                        *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
LINESTYLE* SimpleCell::getLineStyle()
{
	return &lineStyle;
}


/******************************************************************************
 * SimpleCell::getFillStyle -- Get fill style.                                *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return current fill style.                                        *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
FILLSTYLE* SimpleCell::getFillStyle()
{
	return &fillStyle;
}


/******************************************************************************
 * SimpleCell::ApplyAttribute -- Apply current styles.                        *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/05 Tony : Created.                                               *
 *============================================================================*/
void SimpleCell::applyAttribute()
{
	setlinecolor(lineColor);
	setfillcolor(fillColor);
	setlinestyle(&lineStyle);
	setfillstyle(&fillStyle);
}



/******************************************************************************
 * SizeProperty::SizeProperty -- Default constructor of the object.           *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
SizeProperty::SizeProperty() {}


/******************************************************************************
 * SizeProperty::SizeProperty -- Default deconstructor of the object.         *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
SizeProperty::~SizeProperty() {}


/******************************************************************************
 * SizeProperty::setSize -- Set the size of the cell.                         *
 *                                                                            *
 *   If is -1, then it remains unchanged.                                     *
 *                                                                            *
 * INPUT:   _width  -- Width to be assigned.                                  *
 *          _height -- Height to be assigned.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void SizeProperty::setSize(int _width, int _height)
{
	width = _width;
	height = _height;
}


/******************************************************************************
 * SizeProperty::getWidth -- Get the width of the cell.                       *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the width of the cell.                                     *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
int SizeProperty::getWidth() const
{
	return width;
}


/******************************************************************************
 * SizeProperty::getHeight -- Get the height of the cell.                     *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the height of the cell.                                    *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
int SizeProperty::getHeight() const
{
	return height;
}



/******************************************************************************
 * CircleCell::CircleCell -- Constructor of the Circle Cell.                  *
 *                                                                            *
 *   Perhaps later we can use initializing list instead.                      *
 *                                                                            *
 * INPUT:   _pos       -- Position of the cell.                               *
 *          _radius    -- Radius of the circle.                               *
 *          _lineColor -- Line color.                                         *
 *          _fillColor -- Fill color.                                         *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
CircleCell::CircleCell(
	Coord _pos,
	int _radius,
	COLORREF _lineColor,
	COLORREF _fillColor)
{
	pos = _pos;
	radius = radius;
	lineColor = _lineColor;
	fillColor = _fillColor;

	isCentered = true;
}


/******************************************************************************
 * CircleCell::~CircleCell -- Deconstructor of the Circle Cell.               *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
CircleCell::~CircleCell() {}


/******************************************************************************
 * CircleCell::setRadius -- Set circle radius.                                *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   _radius -- New radius to be set.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void CircleCell::setRadius(int _radius)
{
	radius = _radius;
}


/******************************************************************************
 * CircleCell::getRadius -- Get circle radius.                                *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the radius.                                                *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
int CircleCell::getRadius() const
{
	return radius;
}


/******************************************************************************
 * CircleCell::draw -- Draw the circle.                                       *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   pDestImg   -- Destination image buffer.                           *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   Remember to set working image back.                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *   2022/01/07 Tony : Removed makeCenter.                                    *
 *============================================================================*/
void CircleCell::draw(IMAGE* pDestImg)
{
	Coord coord;

	SetWorkingImage(pDestImg);
	applyAttribute();

	if (isCentered)
		coord = pos;
	else
	{
		coord.x = pos.x + radius;
		coord.y = pos.y + radius;
	}

	if (isFilled)
	{
		if (lineStyle.thickness != 0)
			fillcircle(coord.x, coord.y, radius);
		else
			solidcircle(coord.x, coord.y, radius);
	}
	else if (lineStyle.thickness != 0)
		circle(coord.x, coord.y, radius);

	SetWorkingImage(NULL);

	if (pSubCell)
		pSubCell->draw(pDestImg);
}


/******************************************************************************
 * CircleCell::load -- Load from xml node.                                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent -- "Root" node of the cell.                                *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Mustn't pass NULL to strcmp... :(                               *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool CircleCell::load(XMLElement* parent)
{
	parseXMLAttribute(&pos, parent->Attribute("pos"));

	if (!parseXMLAttribute(&radius, parent->Attribute("radius")))
	{
		report(R"(Missing "radius" of circle cell)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&lineColor, parent->Attribute("line-color"));
	parseXMLAttribute(&fillColor, parent->Attribute("fill-color"));
	parseXMLAttribute(&isFilled, parent->Attribute("filled"));
	parseXMLAttribute(&isCentered, parent->Attribute("centered"));
	parseXMLAttribute(&lineStyle.thickness, parent->Attribute("line-thickness"));

	XMLElement* child = parent->FirstChildElement();

	if (child != NULL)
	{
		setSubCell(newDrawCell(child));
		if (pSubCell)
			pSubCell->translate(pos);
	}

	return true;
}



/******************************************************************************
 * RectCell::RectCell -- Constructor of the Rectangle Cell.                   *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   _pos       -- Position of the cell.                               *
 *          _width     -- Width of the rectangle.                             *
 *          _height    -- Height of the rectangle.                            *
 *          _lineColor -- Line color.                                         *
 *          _fillColor -- Fill color.                                         *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
RectCell::RectCell(
	Coord _pos,
	int _width,
	int _height,
	COLORREF _lineColor,
	COLORREF _fillColor)
{
	pos = _pos;
	width = _width;
	height = _height;
	lineColor = _lineColor;
	fillColor = _fillColor;
}


/******************************************************************************
 * RectCell::~RectCell -- Deconstructor of the object.                        *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
RectCell::~RectCell() {}


/******************************************************************************
 * RectCell::draw -- Draw a rectangle.                                        *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   See somewhere above. :)                                           *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *   2022/02/13 Tony : solidrectangle doesn't draw outline...                 *
 *============================================================================*/
void RectCell::draw(IMAGE* pDestImg)
{
	Coord coord;

	SetWorkingImage(pDestImg);
	applyAttribute();

	if (isCentered)
	{
		coord.x = pos.x - (width >> 1);
		coord.y = pos.y - (height >> 1);
	}
	else
		coord = pos;

	if (isFilled)
	{
		if (lineStyle.thickness != 0)
			fillrectangle(coord.x, coord.y, coord.x + width, coord.y + height);
		else
			solidrectangle(coord.x, coord.y, coord.x + width, coord.y + height);
	}
	else if (lineStyle.thickness != 0)
		rectangle(coord.x, coord.y, coord.x + width, coord.y + height);

	SetWorkingImage(NULL);

	if (pSubCell)
		pSubCell->draw(pDestImg);
}


/******************************************************************************
 * RectCell::load -- Load from xml file.                                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool RectCell::load(XMLElement* parent)
{
	parseXMLAttribute(&pos, parent->Attribute("pos"));

	if (!parseXMLAttribute(&width, parent->Attribute("width")))
	{
		report(R"(Missing "width" of rectangle cell)", LOAD_WIDGET);
		return false;
	}
	if (!parseXMLAttribute(&height, parent->Attribute("height")))
	{
		report(R"(Missing "height" of rectangle cell)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&lineColor, parent->Attribute("line-color"));
	parseXMLAttribute(&fillColor, parent->Attribute("fill-color"));
	parseXMLAttribute(&isFilled, parent->Attribute("filled"));
	parseXMLAttribute(&isCentered, parent->Attribute("centered"));
	parseXMLAttribute(&lineStyle.thickness, parent->Attribute("line-thickness"));

	XMLElement* child = parent->FirstChildElement();
	if (child != NULL)
	{
		setSubCell(newDrawCell(child));
		if (pSubCell)
			pSubCell->translate(pos);
	}

	return true;
}


/******************************************************************************
 * RoundRectCell::RoundRectCell -- Constructor of the object.                 *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
RoundRectCell::RoundRectCell(
	Coord _pos,
	int _width,
	int _height,
	int _ellipseWidth,
	int _ellipseHeight,
	COLORREF _lineColor,
	COLORREF _fillColor)
{
	pos = _pos;
	width = _width;
	height = _height;
	ellipseWidth = _ellipseWidth;
	ellipseHeight = _ellipseHeight;
	lineColor = _lineColor;
	fillColor = _fillColor;
}


/******************************************************************************
 * RoundRectCell::~RoundRectCell -- Deconstructor of the object.              *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
RoundRectCell::~RoundRectCell() {}


/******************************************************************************
 * RoundRectCell::setRoundSize -- Set border radius.                          *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   _ellipseWidth                                                     *
 *          _ellipseHeight                                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void RoundRectCell::setRoundSize(int _ellipseWidth, int _ellipseHeight)
{
	ellipseWidth = _ellipseWidth;
	ellipseHeight = _ellipseHeight;
}


/******************************************************************************
 * RoundRectCell::getRoundWidth -- Get width of border radius.                *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
int RoundRectCell::getRoundWidth() const
{
	return ellipseWidth;
}


/******************************************************************************
 * RoundRectCell::getRoundHeight -- Get height of border radius.              *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                               *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
int RoundRectCell::getRoundHeight() const
{
	return ellipseHeight;
}


/******************************************************************************
 * RoundRectCell::Draw -- Draw a round rectangle.                             *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   See somewhere above. ;)                                           *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void RoundRectCell::draw(IMAGE* pDestImg)
{
	Coord coord;

	SetWorkingImage(pDestImg);
	applyAttribute();

	if (isCentered)
	{
		coord.x = pos.x - (width >> 1);
		coord.y = pos.y - (height >> 1);
	}
	else
		coord = pos;

	if (isFilled)
	{
		if (lineStyle.thickness != 0)
			fillroundrect(coord.x, coord.y, coord.x + width, coord.y + height, ellipseWidth, ellipseHeight);
		else
			solidroundrect(coord.x, coord.y, coord.x + width, coord.y + height, ellipseWidth, ellipseHeight);
	}
	else if (lineStyle.thickness != 0)
		roundrect(coord.x, coord.y, coord.x + width, coord.y + height, ellipseWidth, ellipseHeight);

	SetWorkingImage(NULL);

	if (pSubCell)
		pSubCell->draw(pDestImg);
}


/******************************************************************************
 * RoundRectCell::load -- Load from xml element.                              *
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
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool RoundRectCell::load(XMLElement* parent)
{
	parseXMLAttribute(&pos, parent->Attribute("pos"));
	
	if (!parseXMLAttribute(&width, parent->Attribute("width")))
	{
		report(R"(Missing "width" of roundrect cell)", LOAD_WIDGET);
		return false;
	}
	if (!parseXMLAttribute(&height, parent->Attribute("height")))
	{
		report(R"(Missing "height" of roundrect cell)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&ellipseWidth, parent->Attribute("ellipse-width"));
	parseXMLAttribute(&ellipseHeight, parent->Attribute("ellipse-height"));
	parseXMLAttribute(&lineColor, parent->Attribute("line-color"));
	parseXMLAttribute(&fillColor, parent->Attribute("fill-color"));
	parseXMLAttribute(&isFilled, parent->Attribute("filled"));
	parseXMLAttribute(&isCentered, parent->Attribute("centered"));
	parseXMLAttribute(&lineStyle.thickness, parent->Attribute("line-thickness"));

	XMLElement* child = parent->FirstChildElement();
	if (child != NULL)
		setSubCell(newDrawCell(child));

	return true;
}



/******************************************************************************
 * TextCell::TextCell -- Constructor of the object.                           *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   _width  -- Width of the text area.                                *
 *          _height -- Height of the text area.                               *
 *          _pos    -- The text to display.                                   *
 *          _text   -- Position of the text area.                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *   2022/01/10 Tony : Added default property.                                *
 *============================================================================*/
TextCell::TextCell(Coord _pos, int _width, int _height, std::wstring _text)
{
	pos = _pos;
	width = _width;
	height = _height;
	text = _text;

	/*
	** 2022/01/10
	** Changed fontHeight to half of height.
	*/
	fontHeight = height >> 1;

	/*
	** 0 is for automatic fit.
	*/
	fontWidth = 0;

	/*
	** 2022/01/10
	** Added default property.
	*/
	fontColor = WHITE;
	fontFace = L"Consolas";

	/*
	** The text is justified by default.
	*/
	isJustified = true;
}


/******************************************************************************
 * TextCell::~TextCell -- Deconstuctor of the object.                         *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
TextCell::~TextCell() {}


/******************************************************************************
 * TextCell::setText -- Set text to display.                                  *
 *                                                                            *
 *   Just the literal meaning. ;)                                             *
 *                                                                            *
 * INPUT:   _text -- The text to display.                                     *
 *                                                                            *
 * OUTPUT:  Return pointer to current cell.                                   *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
TextCell* TextCell::setText(const std::wstring& _text)
{
	text = _text;

	return this;
}


/******************************************************************************
 * TextCell::setTextStyle -- Set the style of the text.                       *
 *                                                                            *
 *   Only set font size and font family.                                      *
 *                                                                            *
 * INPUT:   _fontHeight  -- ... font height.                                  *
 *          _fontWidth   -- 0 to auto fit the height.                         *
 *          _fontFace    -- ... font face.                                    *
 *          _isJustified -- Whether to display the text at the center.        *
 *                                                                            *
 * OUTPUT:  Return pointer to current cell.                                   *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
TextCell* TextCell::setTextStyle(
	int _fontHeight,
	int _fontWidth,
	COLORREF _fontColor,
	const std::wstring& _fontFace,
	bool _isJustified)
{
	fontHeight = _fontHeight;
	fontWidth = _fontWidth;
	fontColor = _fontColor;
	fontFace = _fontFace;
	isJustified = _isJustified;

	return this;
}


/******************************************************************************
 * TextCell::getText -- Get the text.                                         *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  A reference of the text.                                          *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
std::wstring& TextCell::getText()
{
	return text;
}


/******************************************************************************
 * TextCell::applyAttribute -- Apply font styles.                             *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void TextCell::applyAttribute()
{
	settextcolor(fontColor);
	settextstyle(fontHeight, fontWidth, fontFace.c_str());
}


/******************************************************************************
 * TextCell::draw -- Draw the text.                                           *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   See somewhere abooove.                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void TextCell::draw(IMAGE* pDestImg)
{
	Coord coord;

	SetWorkingImage(pDestImg);
	setbkmode(TRANSPARENT);
	applyAttribute();

	if (isCentered)
	{
		coord.x = pos.x - (width >> 1);
		coord.y = pos.y - (height >> 1);
	}
	else
		coord = pos;

	if (isJustified)
	{
		RECT textArea = { coord.x, coord.y, coord.x + width, coord.y + height };
		drawtext(text.c_str(), &textArea, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
	}
	else
		outtextxy(coord.x, coord.y, text.c_str());

	SetWorkingImage(NULL);

	if (pSubCell)
		pSubCell->draw(pDestImg);
}


/******************************************************************************
 * TextCell::load -- Load from xml element.                                   *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   The text must be placed right after the beginning label!       *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool TextCell::load(XMLElement* parent)
{
	parseXMLAttribute(&pos, parent->Attribute("pos"));
	
	parseXMLAttribute(&width, parent->Attribute("width"));
	parseXMLAttribute(&height, parent->Attribute("height"));
	parseXMLAttribute(&isCentered, parent->Attribute("centered"));

	parseXMLAttribute(&fontHeight, parent->Attribute("font-size"));
	parseXMLAttribute(&fontColor, parent->Attribute("font-color"));
	parseXMLAttribute(&fontFace, parent->Attribute("font"));

	parseXMLAttribute(&isJustified, parent->Attribute("justified"));

	if (!parseXMLAttribute(&text, parent->Attribute("content")))
	{
		report(R"(Missing "content" of text cell)", LOAD_WIDGET);
		return false;
	}


	XMLElement* child = parent->FirstChildElement();
	if (child != NULL)
		setSubCell(newDrawCell(child));

	return true;
}



/******************************************************************************
 * ImageCell::ImageCell -- Constructor of the image cell.                     *
 *                                                                            *
 *   It receive a pointer to a image and generate a copy of it.               *
 *                                                                            *
 * INPUT:   pSrcImg -- The source image.                                      *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
ImageCell::ImageCell(IMAGE* pSrcImg)
{
	if (pSrcImg == nullptr)
		return;

	SetWorkingImage(pSrcImg);
	getimage(&image, 0, 0, pSrcImg->getwidth(), pSrcImg->getheight());
	SetWorkingImage(NULL);
}


/******************************************************************************
 * ImageCell::~ImageCell -- Deconstructor of the image cell.                  *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
ImageCell::~ImageCell() {}


/******************************************************************************
 * ImageCell::setImage -- Set the image to display.                           *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   pSrcImg -- Image to be set.                                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   Remember to adjust size after changing image.                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void ImageCell::setImage(IMAGE* pSrcImg)
{
	image.Resize(pSrcImg->getwidth(), pSrcImg->getheight());

	SetWorkingImage(&image);
	putimage(0, 0, pSrcImg);
	SetWorkingImage(NULL);
}

/******************************************************************************
 * ImageCell::getImage -- Get current image.                                  *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the pointer to current image.                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
IMAGE* ImageCell::getImage()
{
	return &image;
}


/******************************************************************************
 * ImageCell::draweCell -- Constructor of the image cell.                     *
 *                                                                            *
 *   Just the literal meaning...                                              *
 *                                                                            *
 * INPUT:   See sooomewhere abooooove.                                        *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void ImageCell::draw(IMAGE* pDestImg)
{
	Coord coord;

	SetWorkingImage(pDestImg);

	if (isCentered)
	{
		coord.x = pos.x - (width >> 1);
		coord.y = pos.y - (height >> 1);
	}
	else
		coord = pos;

	putTransparentImage(coord.x, coord.y, &image);

	SetWorkingImage(NULL);

	if (pSubCell)
		pSubCell->draw(pDestImg);
}


/******************************************************************************
 * ImageCell::adjustSize -- Adjust to the image size.                         *
 *                                                                            *
 *   To adjust the cell's size to fit the image.                              *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  This should be called every time after the image is changed.    *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void ImageCell::adjustSize()
{
	width = image.getwidth();
	height = image.getheight();
}


/******************************************************************************
 * ImageCell::load -- Load from xml element.                                  *
 *                                                                            *
 *   Many images may be packed in one large image, so some additional info is * 
 *   needed to load image resource.                                           *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
bool ImageCell::load(XMLElement* parent)
{
	std::wstring filename;

	// The origin of the image in the sources image.
	Coord origin;

	IMAGE src;

	parseXMLAttribute(&pos, parent->Attribute("pos"));
	
	parseXMLAttribute(&origin, parent->Attribute("origin"));
	if (!parseXMLAttribute(&width, parent->Attribute("width")))
	{
		report(R"(Missing "width" of image cell)", LOAD_WIDGET);
		return false;
	}
	if (!parseXMLAttribute(&height, parent->Attribute("height")))
	{
		report(R"(Missing "height" of image cell)", LOAD_WIDGET);
		return false;
	}
	if (!parseXMLAttribute(&filename, parent->Attribute("src")))
	{
		report(R"(Missing "src" of image cell)", LOAD_WIDGET);
		return false;
	}

	loadimage(&src, filename.c_str());
	SetWorkingImage(&src);
	getimage(&image, origin.x, origin.y, width, height);
	SetWorkingImage(NULL);

	parseXMLAttribute(&isCentered, parent->Attribute("centered"));


	XMLElement* child = parent->FirstChildElement();
	if (child != NULL)
		setSubCell(newDrawCell(child));

	return true;
}


/******************************************************************************
 * newDrawCell -- Get a draw cell.                                            *
 *                                                                            *
 *   This one get a draw cell through new, and then load it.                  *
 *                                                                            *
 * INPUT:   element -- The root element of the new draw cell.                 *
 *                                                                            *
 * OUTPUT:  Return the new draw cell.                                         *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
DrawCell* newDrawCell(XMLElement* element)
{
	if (element == NULL)
		return nullptr;


	DrawCell* rv;

	const char* childName = element->Name();
	
	if (strcmp(childName, "circle") == 0)
		rv = new CircleCell();
	else if (strcmp(childName, "rectangle") == 0)
		rv = new RectCell();
	else if (strcmp(childName, "roundrect") == 0)
		rv = new RoundRectCell();
	else if (strcmp(childName, "text") == 0)
		rv = new TextCell();
	else if (strcmp(childName, "image") == 0)
		rv = new ImageCell();
	else
		rv = nullptr;

	if (rv)
	{
		if (!rv->load(element))
		{
			delete rv;
			rv = nullptr;
		}
	}
	else
		reportf("Unknown draw cell: %s", childName, "Loading widget");

	return rv;
}



/******************************************************************************
 * Trigger::Trigger -- Constructor of the Trigger.                            *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *   2022/01/07 Tony : Added isCentered.                                      *
 *============================================================================*/
Trigger::Trigger()
{
	isCentered = false;
}


/******************************************************************************
 * Trigger::~Trigger -- Deconstructor of the Trigger.                         *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
Trigger::~Trigger() {}


/******************************************************************************
 * Trigger::setPos -- Set trigger position.                                   *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   _pos                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void Trigger::setPos(const Coord& _pos)
{
	pos = _pos;
}


/******************************************************************************
 * Trigger::translate -- Translate the trigger.                               *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   offset                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
void Trigger::translate(Coord offset)
{
	pos += offset;
}



/******************************************************************************
 * Trigger::makeCenter -- Whether to make center of the position.             *
 *                                                                            *
 *   See in DrawCell. :P                                                      *
 *                                                                            *
 * INPUT:   center                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:   none                                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
void Trigger::makeCenter(bool center)
{
	isCentered = center;
}


/******************************************************************************
 * Trigger::getPos -- Get trigger position.                                   *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
Coord Trigger::getPos() const
{
	return pos;
}



/******************************************************************************
 * CircleTrigger::CircleTrigger -- Constructor of the object.                 *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   _radius - radius of the trigger.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *   2022/01/07 Tony : Circle trigger will center by default.                 *
 *============================================================================*/
CircleTrigger::CircleTrigger(Coord _pos, int _radius)
{
	pos = _pos;
	radius = _radius;

	/*
	** The super constructor is called before this, so
	** it will re-write the old value.
	*/
	isCentered = true;
}


/******************************************************************************
 * CircleTrigger::~CircleTrigger -- Deconstructor of the object.              *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
CircleTrigger::~CircleTrigger() {}


/******************************************************************************
 * CircleTrigger::inRange -- Check if a point is in the trigger.              *
 *                                                                            *
 *   Check if the mouse is in the range of the trigger.                       *
 *                                                                            *
 * INPUT:   target -- Position of the mouse.                                  *
 *                                                                            *
 * OUTPUT:  Return whether in range.                                          *
 *                                                                            *
 * WARNINGS:  Circle trigger's position is its center.                        *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *   2022/01/07 Tony : Added check for isCentered.                            *
 *============================================================================*/
bool CircleTrigger::inRange(const Coord& target)
{
	if (isCentered)
		return (getDistance(pos, target) < (double)radius);

	Coord coord(pos.x + radius, pos.y + radius);
	return (getDistance(coord, target) < (double)radius);
}


/******************************************************************************
 * CircleTrigger::setRadius -- Set radius of the trigger.                     *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void CircleTrigger::setRadius(int _radius)
{
	radius = _radius;
}


/******************************************************************************
 * CircleTrigger::getRadius -- Get radius of the trigger.                     *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the radius of the trigger.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
int CircleTrigger::getRadius() const
{
	return radius;
}


/******************************************************************************
 * CircleTrigger::load -- Load from xml element.                              *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/13 Tony : Created.                                               *
 *============================================================================*/
bool CircleTrigger::load(XMLElement* parent)
{
	parseXMLAttribute(&pos, parent->Attribute("pos"));

	if (!parseXMLAttribute(&radius, parent->Attribute("radius")))
	{
		report(R"(Missing "radius" of circle trigger)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&isCentered, parent->Attribute("centered"));

	return true;
}



/******************************************************************************
 * RectTrigger::RectTrigger -- Constructor of the rectangle trigger.          *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   _width  -- Width of the trigger.                                  *
 *          _height -- Height of the trigger.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
RectTrigger::RectTrigger(Coord _pos, int _width, int _height)
{
	pos = _pos;
	width = _width;
	height = _height;
}


/******************************************************************************
 * RectTrigger::~RectTrigger -- Deconstructor of the rectangle trigger.       *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
RectTrigger::~RectTrigger() {}


/******************************************************************************
 * RectTrigger::inRange -- See above.                                         *
 *                                                                            *
 *   See above. :)                                                            *
 *                                                                            *
 * INPUT:   target                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *   2022/01/07 Tony : Added check for isCentered.                            *
 *   2022/01/10 Tony : Fixed a virable.
 *============================================================================*/
bool RectTrigger::inRange(const Coord& target)
{
	if (isCentered)
		setRectangle(&range, pos.x - (width >> 1), pos.y - (height >> 1), pos.x + (width >> 1), pos.y + (height >> 1));
	else
	{
		/*
		** 2022/01/10
		** pos.y + height... not width.
		*/
		setRectangle(&range, pos.x, pos.y, pos.x + width, pos.y + height);
	}

	return inRectangle(range, target);
}


/******************************************************************************
 * RectTrigger::setSize -- Set rectangle trigger size.                        *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   _width  -- Width of the trigger.                                  *
 *          _height -- Height of the trigger.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void RectTrigger::setSize(int _width, int _height)
{
	width = _width;
	height = _height;
}


/******************************************************************************
 * RectTrigger::getWidth -- Get the width of the trigger.                     *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the width of the trigger.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
int RectTrigger::getWidth() const
{
	return width;
}


/******************************************************************************
 * RectTrigger::getHeight -- Get the height of the trigger.                   *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the height of the trigger.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
int RectTrigger::getHeight() const
{
	return height;
}


/******************************************************************************
 * RectTrigger::load -- Load from xml element.                                *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/13 Tony : Created.                                               *
 *============================================================================*/
bool RectTrigger::load(XMLElement* parent)
{
	parseXMLAttribute(&pos, parent->Attribute("pos"));
	
	if (!parseXMLAttribute(&width, parent->Attribute("width")))
	{
		report(R"(Missing "width" of rectangle trigger)", LOAD_WIDGET);
		return false;
	}
	if (!parseXMLAttribute(&height, parent->Attribute("height")))
	{
		report(R"(Missing "height" of rectangel trigger)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&isCentered, parent->Attribute("centered"));

	return true;
}



/******************************************************************************
 * MaskTrigger::MaskTrigger -- Constructor of the mask trigger.               *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   pSrcImg -- Source of the mask.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *   2022/02/20 Tony : Warning, pSrcImg can be nullptr.                       *
 *============================================================================*/
MaskTrigger::MaskTrigger(Coord _pos, IMAGE* pSrcImg)
{
	pos = _pos;

	if (!pSrcImg)
		return;

	width = pSrcImg->getwidth();
	height = pSrcImg->getheight();

	mask.Resize(width, height);

	SetWorkingImage(&mask);
	putimage(0, 0, pSrcImg);
	SetWorkingImage(NULL);
}


/******************************************************************************
 * MaskTrigger::~MaskTrigger -- Deconstructor of the mask trigger.            *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
MaskTrigger::~MaskTrigger() {}


/******************************************************************************
 * MaskTrigger::inRange -- See above.                                         *
 *                                                                            *
 *   See abooooove. :)                                                        *
 *                                                                            *
 * INPUT:   target                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *   2022/01/07 Tony : Added check for isCentered.                            *
 *============================================================================*/
bool MaskTrigger::inRange(const Coord& target)
{
	if (isCentered)
		setRectangle(&range, pos.x - (width >> 1), pos.y - (height >> 1), pos.x + (width >> 1), pos.y + (height >> 1));
	else
		setRectangle(&range, pos.x, pos.y, pos.x + width, pos.y + width);

	if (inRectangle(range, target))
	{
		DWORD* buffer = GetImageBuffer(&mask);
		return (buffer[(target.y - range.top) * width + (target.x - range.left)] != TRANSPARENT_COLOR);
	}

	return false;
}


/******************************************************************************
 * MaskTrigger::setMask -- Set mask of the trigger.                           *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   pSrcImg -- Source of the mask.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
void MaskTrigger::setMask(IMAGE* pSrcImg)
{
	width = pSrcImg->getwidth();
	height = pSrcImg->getheight();

	mask.Resize(width, height);

	SetWorkingImage(&mask);
	putimage(0, 0, pSrcImg);
	SetWorkingImage(NULL);
}


/******************************************************************************
 * MaskTrigger::getMask -- Get the mask of the trigger.                       *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
IMAGE* MaskTrigger::getMask()
{
	return &mask;
}


/******************************************************************************
 * MaskTrigger::getWidth -- Get the width of the mask trigger.                *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the width of the trigger.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
int MaskTrigger::getWidth() const
{
	return width;
}


/******************************************************************************
 * MaskTrigger::getHeight -- Get the height of the mask trigger.              *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the height of the trigger.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/06 Tony : Created.                                               *
 *============================================================================*/
int MaskTrigger::getHeight() const
{
	return height;
}


/******************************************************************************
 * MaskTrigger::load -- Load from xml element.                                *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/13 Tony : Created.                                               *
 *============================================================================*/
bool MaskTrigger::load(XMLElement* parent)
{
	std::wstring filename;

	// The origin of the image in the sources image.
	Coord origin;

	IMAGE src;

	parseXMLAttribute(&pos, parent->Attribute("pos"));
	parseXMLAttribute(&isCentered, parent->Attribute("centered"));

	parseXMLAttribute(&origin, parent->Attribute("origin"));
	if (!parseXMLAttribute(&width, parent->Attribute("width")))
	{
		report(R"(Missing "width" of mask trigger)", LOAD_WIDGET);
		return false;
	}
	if (!parseXMLAttribute(&height, parent->Attribute("height")))
	{
		report(R"(Missing "height" of mask trigger)", LOAD_WIDGET);
		return false;
	}
	if (!parseXMLAttribute(&filename, parent->Attribute("src")))
	{
		report(R"(Missing "src" of mask trigger)", LOAD_WIDGET);
		return false;
	}

	mask.Resize(width, height);

	loadimage(&src, filename.c_str());
	SetWorkingImage(&src);
	getimage(&mask, origin.x, origin.y, width, height);
	SetWorkingImage(NULL);
	
	return true;
}




/******************************************************************************
 * newTrigger -- Get a new trigger and load it.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   element                                                           *
 *                                                                            *
 * OUTPUT:  Return the new trigger.                                           *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
Trigger* newTrigger(XMLElement* element)
{
	if (element == NULL)
		return nullptr;


	Trigger* rv;
	const char* childName = element->Name();

	// trg is short for trigger
	if (strcmp(childName, "circle-trg") == 0)
		rv = new CircleTrigger();
	else if (strcmp(childName, "rect-trg") == 0)
		rv = new RectTrigger();
	else if (strcmp(childName, "mask-trg") == 0)
		rv = new MaskTrigger();
	else
		rv = nullptr;

	if (rv)
	{
		if (!rv->load(element))
		{
			delete rv;
			rv = nullptr;
		}
	}
	else
		reportf("Unknown trigger: %s", childName, "Loading widget");

	return rv;
}



/******************************************************************************
 * Widget::Widget -- Constructor for the widget object.                       *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Widget::Widget(WidgetType _type) : type(_type)
{
	pos = { 0, 0 };
	isActivated = true;
	isEventable = true;
	layer = 0;
}


/******************************************************************************
 * Widget::~Widget -- Deconstructor for the widget object.                    *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Widget::~Widget() {}


/******************************************************************************
 * Widget::setState -- Set widget state.                                      *
 *                                                                            *
 *   A widget can be seen and respond to user only when it is activated. Or   *
 *   it will not be seen, let alone functioning.                              *
 *                                                                            *
 * INPUT:   _active -- State to be set.                                       *
 *                                                                            *
 * OUTPUT:  Return the pointer to current widget.                             *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Widget* Widget::setState(bool _active)
{
	isActivated = _active;

	return this;
}


/******************************************************************************
 * Widget::setEventable -- Set whether a widget can respond to a event or not.*
 *                                                                            *
 *   Well, widgets are eventable by default, except static widget.            *
 *                                                                            *
 * INPUT:   _eventable -- Whether a eventable.                                *
 *                                                                            *
 * OUTPUT:  Return the pointer to current widget.                             *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Widget* Widget::setEventable(bool _eventable)
{
	isEventable = _eventable;

	return this;
}


/******************************************************************************
 * Widget::setLayer -- Set widget layer.                                      *
 *                                                                            *
 *   Widgets at a lower layer might be shield.                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  A pointer to current widget.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Widget* Widget::setLayer(int _layer)
{
	layer = _layer;

	return this;
}


/******************************************************************************
 * Widget::getType -- Get the type of the widget.                             *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the widget's type.                                         *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
WidgetType Widget::getType() const
{
	return type;
}


/******************************************************************************
 * Widget::getName -- Get the name of the widget.                             *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the widget's name.                                         *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
const std::string& Widget::getName() const
{
	return name;
}


/******************************************************************************
 * Widget::getPos -- Get the position of the widget.                          *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the position of the widget.                                *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Coord Widget::getPos() const
{
	return pos;
}


/******************************************************************************
 * Widget::getState -- Get the widget's state.                                *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether the widget is activated or not.                    *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
bool Widget::getState() const
{
	return isActivated;
}


/******************************************************************************
 * Widget::getEventable -- Get whether the widget is eventable or not.        *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Whether the widget is eventable or not.                           *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
bool Widget::getEventable() const
{
	return isEventable;
}


/******************************************************************************
 * Widget::getLayer -- Get the widget's layer.                                *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the layer of the widget.                                   *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
int Widget::getLayer() const
{
	return layer;
}



/******************************************************************************
 * Button::Button -- Constructor of the button.                               *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to call its super's constructor. And to initialize the *
 *            pointers.                                                       *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Button::Button() : Widget(WidgetType::BUTTON)
{
	pNormalStyle = nullptr;
	pHoverStyle = nullptr;
	pPressedStyle = nullptr;

	pTrigger = nullptr;

	pOnClick = nullptr;

	isHover = false;
	isPressed = false;
}


/******************************************************************************
 * Button::~Button -- Deconstructor of the button.                            *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to delete the pointers.                                *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Button::~Button()
{
	if (pNormalStyle)
		delete pNormalStyle;
	if (pHoverStyle)
		delete pHoverStyle;
	if (pPressedStyle)
		delete pPressedStyle;

	if (pTrigger)
		delete pTrigger;
}


/******************************************************************************
 * Button::setPos -- Set button position.                                     *
 *                                                                            *
 *   Set the position of the button.                                          *
 *                                                                            *
 * INPUT:   _pos                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *   2022/01/10 Tony : Changed position setting.                              *
 *   2022/01/11 Tony : Added behavior to the position setting.                *
 *============================================================================*/
Widget* Button::setPos(const Coord& _pos)
{
	Coord offset = _pos - pos;

	pos = _pos;

	/*
	** 2022/01/10
	** 2022/01/11
	*/
	if (pNormalStyle)
		pNormalStyle->translate(offset);
	if (pHoverStyle)
		pHoverStyle->translate(offset);
	if (pPressedStyle)
		pPressedStyle->translate(offset);

	if (pTrigger)
		pTrigger->translate(offset);

	return this;
}


/******************************************************************************
 * Button::draw -- Draw a button.                                             *
 *                                                                            *
 *   Draw the button on assigned buffer.                                      *
 *                                                                            *
 * INPUT:   pDestImg                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Here, it doesn't check if the three styles are all assigned. So *
 *            they MUST be set before draw.                                   *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *   2022/01/10 Tony : Changed display priority.                              *
 *============================================================================*/
void Button::draw(IMAGE* pDestImg)
{
	/*
	** Widgets won't show up if not activated!
	*/
	if (!isActivated)
		return;

	/*
	** 2022/01/10
	** isPressed should be checked first!
	*/
	if (isPressed)
		pPressedStyle->draw(pDestImg);
	else if (isHover)
		pHoverStyle->draw(pDestImg);
	else
		pNormalStyle->draw(pDestImg);
}


/******************************************************************************
 * Button::onEvent -- The behavior of the button.                             *
 *                                                                            *
 *   What button does if it is on event.                                      *
 *                                                                            *
 * INPUT:   cmd -- User's command containing keyboard and mouse message.      *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
void Button::onEvent(const Command& cmd)
{
	if (!isActivated || !isEventable)
		return;

	/*
	** Buttons only respond when the mouse is up.
	*/
	switch (cmd.eventType)
	{
	case EVT_MOUSE_MOVE:
		if (pTrigger->inRange(cmd.logicalPos))
			isHover = true;
		else
			isHover = false;
		break;
	case EVT_MOUSE_DOWN:
		if (pTrigger->inRange(cmd.logicalPos))
			isPressed = true;
		else
			isPressed = false;
		break;
	case EVT_MOUSE_UP:
		if (isPressed && pTrigger->inRange(cmd.logicalPos) && pOnClick)
			pOnClick();
		isPressed = isHover = false;

		break;
	default:
		break;
	}
}


/******************************************************************************
 * Button::setNormalStyle -- Set button's normal style.                       *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   style -- Style to be set.                                         *
 *                                                                            *
 * OUTPUT:  Return the pointer to the current button.                         *
 *                                                                            *
 * WARNINGS:  Remember to delete the old style.                               *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Button* Button::setNormalStyle(DrawCell* style)
{
	if (pNormalStyle)
		delete pNormalStyle;

	pNormalStyle = style;

	return this;
}


/******************************************************************************
 * Button::setHoverStyle -- Set button's hover style.                         *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   style -- Style to be set.                                         *
 *                                                                            *
 * OUTPUT:  Return the pointer to the current button.                         *
 *                                                                            *
 * WARNINGS:  Remember to delete the old style.                               *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Button* Button::setHoverStyle(DrawCell* style)
{
	if (pHoverStyle)
		delete pHoverStyle;

	pHoverStyle = style;

	return this;
}


/******************************************************************************
 * Button::setPressedStyle -- Set button's pressed style.                     *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   style -- Style to be set.                                         *
 *                                                                            *
 * OUTPUT:  Return the pointer to the current button.                         *
 *                                                                            *
 * WARNINGS:  Remember to delete the old style.                               *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Button* Button::setPressedStyle(DrawCell* style)
{
	if (pPressedStyle)
		delete pPressedStyle;

	pPressedStyle = style;

	return this;
}


/******************************************************************************
 * Button::setTrigger -- Set trigger of the button.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   trigger -- Any kind of a trigger.                                 *
 *                                                                            *
 * OUTPUT:  The pointer to the button.                                        *
 *                                                                            *
 * WARNINGS:  Remember to delete the old trigger.                             *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Button* Button::setTrigger(Trigger* trigger)
{
	if (pTrigger)
		delete pTrigger;

	pTrigger = trigger;

	return this;
}


/******************************************************************************
 * Button::onClick -- Set the callback function of the button.                *
 *                                                                            *
 *    Callback function works after the button is clicked.                    *
 *                                                                            *
 * INPUT:   callback -- The callback function to be called.                   *
 *          param    -- The address of the parameter to the callback.         *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Button* Button::onClick(std::function<void(void)> callback)
{
	/*
	** Both callback and param are not allocated by new.
	*/
	pOnClick = callback;

	return this;
}


/******************************************************************************
 * Button::getNormal -- Get normal style of the button.                       *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the normal style of the button.                            *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DrawCell* Button::getNormalStyle()
{
	return pNormalStyle;
}


/******************************************************************************
 * Button::getHoverStyle -- Get hover style of the button.                    *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the hover style of the button.                             *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DrawCell* Button::getHoverStyle()
{
	return pHoverStyle;
}


/******************************************************************************
 * Button::getPressedStyle -- Get pressed style of the button.                *
 *                                                                            *
 *   Just the literal meaning.                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the pressed style of the button.                           *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DrawCell* Button::getPressedStyle()
{
	return pPressedStyle;
}


/******************************************************************************
 * Button::getTrigger -- Get the button's trigger.                            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the address of the trigger.                                *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
Trigger* Button::getTrigger()
{
	return pTrigger;
}


/******************************************************************************
 * Button::load -- Load from xml element.                                     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool Button::load(XMLElement* parent)
{
	const char* childName;

	if (!parseXMLAttribute(&name, parent->Attribute("name")))
	{
		report(R"(Missing "name" of button)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&pos, parent->Attribute("pos"));
	parseXMLAttribute(&layer, parent->Attribute("layer"));
	
	parseXMLAttribute(&isActivated, parent->Attribute("activated"));
	parseXMLAttribute(&isEventable, parent->Attribute("eventable"));


	XMLElement* child = parent->FirstChildElement();

	while (child != NULL)
	{
		childName = child->Name();
		if (strcmp(childName, "trigger") == 0)
			setTrigger(newTrigger(child->FirstChildElement()));
		else if (strcmp(childName, "normal") == 0)
			setNormalStyle(newDrawCell(child->FirstChildElement()));
		else if (strcmp(childName, "hover") == 0)
			setHoverStyle(newDrawCell(child->FirstChildElement()));
		else if (strcmp(childName, "pressed") == 0)
			setPressedStyle(newDrawCell(child->FirstChildElement()));
		
		child = child->NextSiblingElement();
	}

	if (!pTrigger)
	{
		report(R"(Missing trigger of button)", LOAD_WIDGET);
		return false;
	}
	if ((!pNormalStyle) || (!pHoverStyle) || (!pPressedStyle))
	{
		report(R"(Missing draw cell(s) of button)", LOAD_WIDGET);
		return false;
	}

	pTrigger->translate(pos);
	pNormalStyle->translate(pos);
	pHoverStyle->translate(pos);
	pPressedStyle->translate(pos);

	return true;
}



/******************************************************************************
 * DragBar::DragBar -- Constructor of the object.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to initailizing the pointers.                          *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DragBar::DragBar() : Widget(WidgetType::DRAGBAR)
{
	pBlockNormal = nullptr;
	pBlockPressed = nullptr;
	pBarCell = nullptr;

	pBlockTrigger = nullptr;
	pBarTrigger = nullptr;

	pOnChange = nullptr;
	pOnBlur = nullptr;

	value = 0.0;
	isPressed = false;
}


/******************************************************************************
 * DragBar::~DragBar -- Deconstructor of the object.                          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to delete the pointers.                                *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DragBar::~DragBar()
{
	if (pBlockNormal)
		delete pBlockNormal;
	if (pBlockPressed)
		delete pBlockPressed;
	if (pBarCell)
		delete pBarCell;
	if (pBlockTrigger)
		delete pBlockTrigger;
	if (pBarTrigger)
		delete pBarTrigger;
}


/******************************************************************************
 * DragBar::setPos -- Set position of the drag bar.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _pos                                                              *
 *                                                                            *
 * OUTPUT:  Return the pointer to the Dragbar.                                *
 *                                                                            *
 * WARNINGS:  Notice that, the block of the drag bar should be displayed at   *
 *            the center of the bar.                                          *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *   2022/01/10 Tony : Changed position setting.                              *
 *   2022/01/11 Tony : Added behabior to the setting.                         *
 *============================================================================*/
Widget* DragBar::setPos(const Coord& _pos)
{
	Coord offset = _pos - pos;

	pos = _pos;

	/*
	** 2022/01/10
	** 2022/01/11
	*/
	if (pBarCell)
		pBarCell->translate(offset);
	if (pBarTrigger)
		pBarTrigger->translate(offset);

	return this;
}


/******************************************************************************
 * DragBar::draw -- Draw the drag bar.                                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pDestImg                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
void DragBar::draw(IMAGE* pDestImg)
{
	if (!isActivated)
		return;

	pBarCell->draw(pDestImg);

	/*
	** Here, the block cell is set to center its coordinate.
	*/
	if (isPressed)
	{
		pBlockPressed->setPos({ pos.x + (int)((double)barWidth * value), pos.y + (barHeight >> 1) });
		pBlockPressed->draw(pDestImg);
	}
	else
	{
		pBlockNormal->setPos({ pos.x + (int)((double)barWidth * value), pos.y + (barHeight >> 1) });
		pBlockNormal->draw(pDestImg);
	}
}


/******************************************************************************
 * DragBar::onEvent -- Behavior of the drag bar.                              *
 *                                                                            *
 *    Drag bar... Interesting thing. :|                                       *
 *                                                                            *
 * INPUT:   cmd                                                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
void DragBar::onEvent(const Command& cmd)
{
	if (!isActivated || !isEventable)
		return;

	pBlockTrigger->setPos({ pos.x + (int)((double)barWidth * value), pos.y + (barHeight >> 1) });

	switch (cmd.eventType)
	{
	case EVT_MOUSE_DOWN:
		if (pBlockTrigger->inRange(cmd.logicalPos) || pBarTrigger->inRange(cmd.logicalPos))
		{
			isPressed = true;
			value = (double)(cmd.logicalPos.x - pos.x) / (double)barWidth;
			value = MAX(value, 0.0);
			value = MIN(value, 1.0);

			if (pOnChange)
				pOnChange(value);
		}
		break;
	case EVT_MOUSE_MOVE:
		if (isPressed)
		{
			value = (double)(cmd.logicalPos.x - pos.x) / (double)barWidth;
			value = MAX(value, 0.0);
			value = MIN(value, 1.0);
			if (pOnChange)
				pOnChange((float)value);
		}
		break;
	case EVT_MOUSE_UP:
		if (isPressed && pOnBlur)
			pOnBlur();
		isPressed = false;
		break;
	default:
		break;
	}
}


/******************************************************************************
 * DragBar::setBlockNormal -- Set the normal style of the block.              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   style                                                             *
 *                                                                            *
 * OUTPUT:  The pointer to the drag bar.                                      *
 *                                                                            *
 * WARNINGS:  Remember to delete the old style. And set block cell to center  *
 *            its coordinate.                                                 *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DragBar* DragBar::setBlockNormal(DrawCell* style)
{
	if (pBlockNormal)
		delete pBlockNormal;

	pBlockNormal = style;
	pBlockNormal->makeCenter(true);

	return this;
}


/******************************************************************************
 * DragBar::setBlockPressed -- Set the pressed style of the block.            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   style                                                             *
 *                                                                            *
 * OUTPUT:  The pointer to the drag bar.                                      *
 *                                                                            *
 * WARNINGS:  Remember to delete the old style. And set block cell to center  *
 *            its coordinate.                                                 *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DragBar* DragBar::setBlockPressed(DrawCell* style)
{
	if (pBlockPressed)
		delete pBlockPressed;

	pBlockPressed = style;
	pBlockPressed->makeCenter(true);

	return this;
}


/******************************************************************************
 * DragBar::setBarStyle -- Set the style of the bar.                          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   style                                                             *
 *                                                                            *
 * OUTPUT:  The pointer to the drag bar.                                      *
 *                                                                            *
 * WARNINGS:  Remember to delete the old style. Bar should only be a rectangle*
 *            or a round rectangle.                                           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DragBar* DragBar::setBarStyle(DrawCell* style)
{
	if (pBarCell)
		delete pBarCell;

	pBarCell = style;
	barWidth = dynamic_cast<SizeProperty*>(pBarCell)->getWidth();
	barHeight = dynamic_cast<SizeProperty*>(pBarCell)->getHeight();

	return this;
}


/******************************************************************************
 * DragBar::setBlockTrigger -- Set the trigger for the block.                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   trigger                                                           *
 *                                                                            *
 * OUTPUT:  The pointer to the drag bar.                                      *
 *                                                                            *
 * WARNINGS:  Remember to delete the old trigger. And set the block trigger   *
 *            to center its position.                                         *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DragBar* DragBar::setBlockTrigger(Trigger* trigger)
{
	if (pBlockTrigger)
		delete pBlockTrigger;

	pBlockTrigger = trigger;
	pBlockTrigger->makeCenter(true);

	return this;
}


/******************************************************************************
 * DragBar::setBarTrigger -- Set the trigger for the bar.                     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   trigger                                                           *
 *                                                                            *
 * OUTPUT:  The pointer to the drag bar.                                      *
 *                                                                            *
 * WARNINGS:  Remember to delete the old trigger.                             *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DragBar* DragBar::setBarTrigger(Trigger* trigger)
{
	if (pBarTrigger)
		delete pBarTrigger;

	pBarTrigger = trigger;

	return this;
}


/******************************************************************************
 * DragBar::onChange -- Set the callback function.                            *
 *                                                                            *
 *    Set the callback function to be called when the drag bar is dragged.    *
 *                                                                            *
 * INPUT:   callback                                                          *
 *          param                                                             *
 *                                                                            *
 * OUTPUT:  The pointer to the drag bar.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DragBar* DragBar::onChange(std::function<void(double)> callback)
{
	pOnChange = callback;

	return this;
}


/******************************************************************************
 * DragBar::onBlur -- Set the callback function.                              *
 *                                                                            *
 *    Set the callback function to be called when the drag bar loses focus of *
 *    the user.                                                               *
 *                                                                            *
 * INPUT:   callback                                                          *
 *          param                                                             *
 *                                                                            *
 * OUTPUT:  The pointer to the drag bar.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DragBar* DragBar::onBlur(std::function<void(void)> callback)
{
	pOnBlur = callback;

	return this;
}


/******************************************************************************
 * DragBar::getBlockNormal -- Get the block of the drag bar.                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  The Normal style of the drag bar.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DrawCell* DragBar::getBlockNormal()
{
	return pBlockNormal;
}


/******************************************************************************
 * DragBar::getBlockPressed -- Get the block of the drag bar.                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  The block of the pressed drag bar.                                *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DrawCell* DragBar::getBlockPressed()
{
	return pBlockPressed;
}


/******************************************************************************
 * DragBar::getBar -- Get the bar of the drag bar.                            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  The bar of the drag bar.                                          *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DrawCell* DragBar::getBar()
{
	return pBarCell;
}


/******************************************************************************
 * DragBar::getBlockTrigger -- Get the trigger of the block.                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the block trigger of the drag bar.                         *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
Trigger* DragBar::getBlockTrigger()
{
	return pBlockTrigger;
}


/******************************************************************************
 * DragBar::getBarTrigger -- Get the bar trigger.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the bar trigger of the drag bar.                           *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
Trigger* DragBar::getBarTrigger()
{
	return pBarTrigger;
}


/******************************************************************************
 * DragBar::setValue -- Set the value of the drag bar.                        *
 *                                                                            *
 *    The value of the drag bar is between 0 and 1, and it is directly showed *
 *    by the position it holds on the bar.                                    *
 *                                                                            *
 * INPUT:   _value -- The value to be set.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
void DragBar::setValue(double _value)
{
	value = _value;
}


/******************************************************************************
 * DragBar::setValue -- Set the value of the drag bar.                        *
 *                                                                            *
 *    This one is for callbacks among widgets, because the callbacks... use   *
 *    void* as parameters.                                                    *
 *                                                                            *
 * INPUT:   param -- The address of the value.                                *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
void DragBar::setValue(void* param)
{
	value = *((double*)param);
}


/******************************************************************************
 * DragBar::getValue -- Get the current value of the drag bar.                *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  The value of the drag bar.                                        *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
double DragBar::getValue() const
{
	return value;
}


/******************************************************************************
 * DragBar::load -- Load from xml element.                                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool DragBar::load(XMLElement* parent)
{
	const char* childName;

	if (!parseXMLAttribute(&name, parent->Attribute("name")))
	{
		report(R"(Missing "name" of dragbar)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&pos, parent->Attribute("pos"));
	parseXMLAttribute(&layer, parent->Attribute("layer"));

	parseXMLAttribute(&isActivated, parent->Attribute("activated"));
	parseXMLAttribute(&isEventable, parent->Attribute("eventable"));


	XMLElement* child = parent->FirstChildElement();
	
	while (child != NULL)
	{
		childName = child->Name();
		if (strcmp(childName, "bar") == 0)
			setBarStyle(newDrawCell(child->FirstChildElement()));
		else if (strcmp(childName, "block-normal") == 0)
			setBlockNormal(newDrawCell(child->FirstChildElement()));
		else if (strcmp(childName, "block-pressed") == 0)
			setBlockPressed(newDrawCell(child->FirstChildElement()));
		else if (strcmp(childName, "block-trigger") == 0)
			setBlockTrigger(newTrigger(child->FirstChildElement()));
		else if (strcmp(childName, "bar-trigger") == 0)
			setBarTrigger(newTrigger(child->FirstChildElement()));

		child = child->NextSiblingElement();
	}

	if ((!pBlockTrigger) || (!pBarTrigger))
	{
		report(R"(Missing trigger(s) of dragbar)", LOAD_WIDGET);
		return false;
	}
	if ((!pBlockNormal) || (!pBlockPressed) || (!pBarCell))
	{
		report(R"(Missing draw cell(s) of dragbar)", LOAD_WIDGET);
		return false;
	}

	pBarTrigger->translate(pos);
	pBarCell->translate(pos);

	return true;
}



/******************************************************************************
 * ProgressBar::ProgressBar -- Constructor of the object.                     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to initialize the pointers.                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
ProgressBar::ProgressBar() : Widget(WidgetType::PROGRESSBAR)
{
	pBarCell = nullptr;
	pMaskCell = nullptr;

	value = 0.0;
	padding = 1;
}


/******************************************************************************
 * ProgressBar::~ProgressBar -- Deconstructor of the object.                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to delete the pointers.                                *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
ProgressBar::~ProgressBar()
{
	if (pBarCell)
		delete pBarCell;
	if (pMaskCell)
		delete pMaskCell;
}


/******************************************************************************
 * ProgressBar::setPos -- Set the progress bar's position.                    *
 *                                                                            *
 *    Progress bar is set to not center. It... shouldn't center. :)           *
 *                                                                            *
 * INPUT:   _pos                                                              *
 *                                                                            *
 * OUTPUT:  Pointer to the progress bar.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *   2022/01/10 Tony : Changed position setting.                              *
 *   2022/01/11 Tony : Added behabior to the setting.                         *
 *============================================================================*/
Widget* ProgressBar::setPos(const Coord& _pos)
{
	Coord offset = _pos - pos;

	pos = _pos;

	/*
	** 2022/01/10
	** 2022/01/11
	*/
	if (pBarCell)
		pBarCell->translate(offset);
	if (pMaskCell)
		pMaskCell->translate(offset);

	return this;
}


/******************************************************************************
 * ProgressBar::draw -- Draw the progress bar.                                *
 *                                                                            *
 *    The bar and the mask have the same position and height, but the bar's   *
 *    outline is thicker, so it looks like it has a border. And this is what  *
 *    the padding does.                                                       *
 *                                                                            *
 * INPUT:   pDestImg                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
void ProgressBar::draw(IMAGE* pDestImg)
{
	if (!isActivated)
		return;

	/*
	** Here, since not all draw cells inherit from SizeProperty,
	** and pMask is one of rectangle and roundrectangle... so...
	** just make a cast.
	*/
	dynamic_cast<SizeProperty*>(pMaskCell)->setSize((int)((double)barWidth * value), barHeight);

	pMaskCell->draw(pDestImg);
	pBarCell->draw(pDestImg);
}


/******************************************************************************
 * ProgressBar::onEvent -- Behavior of the progress bar.                      *
 *                                                                            *
 *    In fact... progress bar... don't have interaction with users... :(      *
 *                                                                            *
 * INPUT:   cmd                                                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
void ProgressBar::onEvent(const Command& cmd) {}


/******************************************************************************
 * ProgressBar::setBarStyle -- Set the style of the bar.                      *
 *                                                                            *
 *    The bar of the progress bar can only be rectangle or round rectangel.   *
 *                                                                            *
 * INPUT:   style -- A rectangle cell.                                        *
 *                                                                            *
 * OUTPUT:  Pointer to the progress bar.                                      *
 *                                                                            *
 * WARNINGS:  Remember to delete the old style. And set related styles.       *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
ProgressBar* ProgressBar::setBarStyle(DrawCell* style)
{
	if (pBarCell)
		delete pBarCell;

	pBarCell = style;
	barWidth = dynamic_cast<SizeProperty*>(pBarCell)->getWidth();
	barHeight = dynamic_cast<SizeProperty*>(pBarCell)->getHeight();

	return this;
}


/******************************************************************************
 * ProgressBar::setMaskStyle -- Set mask style.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   style -- Rectangle style.                                         *
 *                                                                            *
 * OUTPUT:  Pointer to the progress bar.                                      *
 *                                                                            *
 * WARNINGS:  Remember to delete the old style.                               *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
ProgressBar* ProgressBar::setMaskStyle(DrawCell* style)
{
	if (pMaskCell)
		delete pMaskCell;

	pMaskCell = style;

	return this;
}


/******************************************************************************
 * ProgressBar::setPadding -- Set the paddings of the progress bar.           *
 *                                                                            *
 *    The padding directly reflect on the outline thickness of the bar, to... *
 *    make it seems to have a padding; ;)                                     *
 *                                                                            *
 * INPUT:   _padding -- Padding of the progress bar.                          *
 *                                                                            *
 * OUTPUT:  Pointer to the progress bar.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
ProgressBar* ProgressBar::setPadding(int _padding)
{
	padding = _padding;

	dynamic_cast<SimpleCell*>(pBarCell)->setLineThickness(padding << 1);

	return this;
}


/******************************************************************************
 * ProgressBar::getBarStyle -- Get the style of the bar.                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the style of the bar.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DrawCell* ProgressBar::getBarStyle()
{
	return pBarCell;
}


/******************************************************************************
 * ProgressBar::getMaskStyle -- Get the style of the mask.                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the style of the mask.                                     *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
DrawCell* ProgressBar::getMaskStyle()
{
	return pMaskCell;
}


/******************************************************************************
 * ProgressBar::setValue -- Set the value.                                    *
 *                                                                            *
 *    Value is between 0 and 1, and is the progress of the progress bar. :]   *
 *                                                                            *
 * INPUT:   _value -- Value to be set.                                        *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
void ProgressBar::setValue(double _value)
{
	value = _value;
}


/******************************************************************************
 * ProgressBar::getValue -- Get the value of the progress bar.                *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the value of the progress bar.                             *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
double ProgressBar::getValue() const
{
	return value;
}


/******************************************************************************
 * ProgressBar::load -- Load from xml element.                                *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool ProgressBar::load(XMLElement* parent)
{
	const char* childName;

	if (!parseXMLAttribute(&name, parent->Attribute("name")))
	{
		report(R"(Missing "name" of progress bar)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&pos, parent->Attribute("pos"));
	parseXMLAttribute(&layer, parent->Attribute("layer"));

	parseXMLAttribute(&isActivated, parent->Attribute("activated"));
	parseXMLAttribute(&isEventable, parent->Attribute("eventable"));


	XMLElement* child = parent->FirstChildElement();
	while (child != NULL)
	{
		childName = child->Name();
		if (strcmp(childName, "mask") == 0)
			setMaskStyle(newDrawCell(child->FirstChildElement()));
		else if (strcmp(childName, "bar") == 0)
			setBarStyle(newDrawCell(child->FirstChildElement()));

		child = child->NextSiblingElement();
	}

	if ((!pBarCell) || (!pMaskCell))
	{
		report(R"(Missing draw cell(s) of progress bar)", LOAD_WIDGET);
		return false;
	}

	pBarCell->translate(pos);
	pMaskCell->translate(pos);

	setPadding(padding);

	return true;
}



/******************************************************************************
 * CheckBox::CheckBox -- Constructor of the object.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember the initializing.                                      *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
CheckBox::CheckBox() : Widget(WidgetType::CHECKBOX)
{
	pNormalStyle = nullptr;
	pSelectedStyle = nullptr;
	pTrigger = nullptr;

	pOnClick = nullptr;

	isSelected = false;
}


/******************************************************************************
 * CheckBox::~CheckBox -- Deconstructor of the object.                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  ...                                                             *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
CheckBox::~CheckBox()
{
	if (pNormalStyle)
		delete pNormalStyle;
	if (pSelectedStyle)
		delete pSelectedStyle;
	if (pTrigger)
		delete pTrigger;
}


/******************************************************************************
 * CheckBox::setPos -- Set the position of the check box.                     *
 *                                                                            *
 *    For a better effect, the check box... oh well, nothing. :)              *
 *                                                                            *
 * INPUT:   _pos                                                              *
 *                                                                            *
 * OUTPUT:  Return the pointer to the check box.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *   2022/01/10 Tony : Changed position setting.                              *
 *   2022/01/11 Tony : Added behabior to the setting.                         *
 *============================================================================*/
Widget* CheckBox::setPos(const Coord& _pos)
{
	Coord offset = _pos - pos;

	pos = _pos;

	/*
	** 2022/01/10
	** 2022/01/11
	*/
	if (pNormalStyle)
		pNormalStyle->translate(offset);
	if (pSelectedStyle)
		pSelectedStyle->translate(offset);
	if (pTrigger)
		pTrigger->translate(offset);

	return this;
}


/******************************************************************************
 * CheckBox::draw -- Draw the check box.                                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pDestImg                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
void CheckBox::draw(IMAGE* pDestImg)
{
	if (!isActivated)
		return;

	if (isSelected)
		pSelectedStyle->draw(pDestImg);
	else
		pNormalStyle->draw(pDestImg);
}


/******************************************************************************
 * CheckBox::onEvent -- Behavior of the check box.                            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cmd                                                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
void CheckBox::onEvent(const Command& cmd)
{
	if (!isActivated || !isEventable)
		return;

	if (cmd.eventType == EVT_MOUSE_DOWN)
	{
		if (pTrigger->inRange(cmd.logicalPos))
		{
			isSelected = !isSelected;
			if (pOnClick)
				pOnClick();
		}
	}
}


/******************************************************************************
 * CheckBox::setNormalStyle -- Set the normal style of the check box.         *
 *                                                                            *
 *    If a check box is not selected, then it disply the normal style.        *
 *                                                                            *
 * INPUT:   style                                                             *
 *                                                                            *
 * OUTPUT:  Return the pointer to the check box.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
CheckBox* CheckBox::setNormalStyle(DrawCell* style)
{
	if (pNormalStyle)
		delete pNormalStyle;

	pNormalStyle = style;

	return this;
}


/******************************************************************************
 * CheckBox::setSelectedStyle -- Set the selected style.                      *
 *                                                                            *
 *    If a check box is selected, then it display the selected style.         *
 *                                                                            *
 * INPUT:   style                                                             *
 *                                                                            *
 * OUTPUT:  Return the pointer to the check box.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
CheckBox* CheckBox::setSelectedStyle(DrawCell* style)
{
	if (pSelectedStyle)
		delete pSelectedStyle;

	pSelectedStyle = style;

	return this;
}


/******************************************************************************
 * CheckBox::setTrigger -- Set the trigger of the check box.                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   trigger                                                           *
 *                                                                            *
 * OUTPUT:  Return the pointer of the check box.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
CheckBox* CheckBox::setTrigger(Trigger* trigger)
{
	if (pTrigger)
		delete pTrigger;

	pTrigger = trigger;

	return this;
}


/******************************************************************************
 * CheckBox::onClick -- Set the call back function.                           *
 *                                                                            *
 *    If the check box is clicked, then it call the callback. :?              *
 *                                                                            *
 * INPUT:   callback                                                          *
 *          param                                                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
CheckBox* CheckBox::onClick(std::function<void(void)> callback)
{
	pOnClick = callback;

	return this;
}


/******************************************************************************
 * CheckBox::getNormalStyle -- Get the normal style.                          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the normal style.                                          *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
DrawCell* CheckBox::getNormalStyle()
{
	return pNormalStyle;
}


/******************************************************************************
 * CheckBox::getSelectedStyle -- Get the selected style.                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the selected style of the check box.                       *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
DrawCell* CheckBox::getSelectedStyle()
{
	return pSelectedStyle;
}


/******************************************************************************
 * CheckBox::getTrigger -- Get the trigger of the check box.                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the trigger.                                               *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
Trigger* CheckBox::getTrigger()
{
	return pTrigger;
}


/******************************************************************************
 * CheckBox::setState -- Set the check box's state.                           *
 *                                                                            *
 *    A check box has two states, selected and not selected.                  *
 *                                                                            *
 * INPUT:   state -- The state to be set.                                     *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
void CheckBox::setState(bool state)
{
	isSelected = state;
}


/******************************************************************************
 * CheckBox::getState -- Get the check box's state.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the state of the check box.                                *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
bool CheckBox::getState() const
{
	return isSelected;
}


/******************************************************************************
 * CheckBox::load -- Load from xml element.                                   *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool CheckBox::load(XMLElement* parent)
{
	const char* childName;

	if (!parseXMLAttribute(&name, parent->Attribute("name")))
	{
		report(R"(Missing "name" of check box)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&pos, parent->Attribute("pos"));
	parseXMLAttribute(&layer, parent->Attribute("layer"));

	parseXMLAttribute(&isActivated, parent->Attribute("activated"));
	parseXMLAttribute(&isEventable, parent->Attribute("eventable"));
	parseXMLAttribute(&isSelected, parent->Attribute("selected"));


	XMLElement* child = parent->FirstChildElement();
	while (child != NULL)
	{
		childName = child->Name();
		if (strcmp(childName, "trigger") == 0)
			setTrigger(newTrigger(child->FirstChildElement()));
		else if (strcmp(childName, "normal") == 0)
			setNormalStyle(newDrawCell(child->FirstChildElement()));
		else if (strcmp(childName, "selected") == 0)
			setSelectedStyle(newDrawCell(child->FirstChildElement()));

		child = child->NextSiblingElement();
	}

	if (!pTrigger)
	{
		report(R"(Missing trigger of check box)", LOAD_WIDGET);
		return false;
	}
	if ((!pNormalStyle) || (!pSelectedStyle))
	{
		report(R"(Missing draw cell(s) of check box)", LOAD_WIDGET);
		return false;
	}

	pTrigger->translate(pos);
	pNormalStyle->translate(pos);
	pSelectedStyle->translate(pos);

	return true;
}



/******************************************************************************
 * TextArea::TextArea -- Constructor of the object.                           *
 *                                                                            *
 *    Here, the cursor and text are added by the input box itself.            *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to... ;)                                               *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
TextArea::TextArea() : Widget(WidgetType::TEXTAREA)
{
	pBoxCell = nullptr;

	pCursorCell = new RectCell();
	pCursorCell->setFillStyle(true);
	pCursorCell->makeCenter(true);

	pTextCell = new TextCell();
	// It is justified by default in the constructor.

	pTrigger = nullptr;

	pOnChange = nullptr;
	pOnBlur = nullptr;

	normalPadding = selectedPadding = 0;
}


/******************************************************************************
 * TextArea::~TextArea() -- Deconstructor of the object.                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember... :x                                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
TextArea::~TextArea()
{
	if (pBoxCell)
		delete pBoxCell;
	if (pCursorCell)
		delete pCursorCell;
	if (pTextCell)
		delete pTextCell;
	if (pTrigger)
		delete pTrigger;
}


/******************************************************************************
 * TextArea::setPos -- Set the position of the input box.                     *
 *                                                                            *
 *    This only set the position of the box, the texts will automatically     *
 *    justify to the center.                                                  *
 *                                                                            *
 * INPUT:   _pos                                                              *
 *                                                                            *
 * OUTPUT:  Return the pointer to the input box.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *   2022/01/10 Tony : Changed position setting.                              *
 *   2022/01/11 Tony : Added behabior to the setting.                         *
 *============================================================================*/
Widget* TextArea::setPos(const Coord& _pos)
{
	Coord offset = _pos - pos;

	pos = _pos;

	/*
	** 2022/01/10
	** 2022/01/11
	*/
	if (pBoxCell)
		pBoxCell->translate(offset);
	if (pTextCell)
		pTextCell->translate(offset);
	if (pTrigger)
		pTrigger->translate(offset);

	return this;
}


/******************************************************************************
 * TextArea::draw -- draw the input box.                                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pDestImg                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
void TextArea::draw(IMAGE* pDestImg)
{
	if (!isActivated)
		return;

	if (isSelected)
		dynamic_cast<SimpleCell*>(pBoxCell)->setLineThickness(selectedPadding);
	else
		dynamic_cast<SimpleCell*>(pBoxCell)->setLineThickness(normalPadding);

	pBoxCell->draw(pDestImg);
	pTextCell->draw(pDestImg);

	if (isSelected && showCursor)
	{
		/*
		** Set cursors' position. Since the cursor is centered, so it is
		** relatively simpler. Sorry for so long. :(
		*/
		pCursorCell->setPos({ pTextCell->getPos().x + (width >> 1) + (textwidth(pTextCell->getText().c_str())) + pCursorCell->getWidth(), pTextCell->getPos().y + (height >> 1) });
		pCursorCell->setSize(2, height - ((isSelected ? selectedPadding : normalPadding) << 1));
		pCursorCell->draw(pDestImg);
	}
	if (isSelected && (GetTickCount() - oldCursorTime > 500))
	{
		showCursor = !showCursor;
		oldCursorTime = GetTickCount();
	}
}


/******************************************************************************
 * TextArea::onEvent -- Behavior of the input box.                            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cmd                                                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
void TextArea::onEvent(const Command& cmd)
{
	if (!isActivated || !isEventable || !pTrigger)
		return;

	std::wstring& str = pTextCell->getText();

	switch (cmd.eventType)
	{
	case EVT_MOUSE_DOWN:
		if (pTrigger->inRange(cmd.logicalPos))
		{
			if (!isSelected)
			{
				lastFilter = filter;
				filter = DISABLE_ALL;
				isSelected = true;
				copy = str;
			}
		}
		else
		{
			if (isSelected)
			{
				if (pOnBlur)
					pOnBlur();
				isSelected = false;
				filter = lastFilter;
			}
		}
		break;
	case EVT_KEY_DOWN:
		if (!isSelected)
			return;

		switch (cmd.keyType)
		{
		case KeyType::KEY_ESC:
			str = copy;
			if (pOnBlur)
				pOnBlur();
			isSelected = false;
			filter = lastFilter;
			break;
		case KeyType::KEY_PRINT:
			str.push_back(cmd.key);
			if (pOnChange)
				pOnChange();
			break;
		case KeyType::KEY_BACKSPC:
			if (!str.empty())
			{
				str.pop_back();
				if (pOnChange)
					pOnChange();
			}
			break;
		case KeyType::KEY_ENTER:
			/*
			** If reaches here, then the input box is
			** sure to be selected.
			*/
			if (pOnBlur)
				pOnBlur();
			isSelected = false;
			filter = lastFilter;
			break;
		default:
			break;
		}	// switch (cmd.keyType)
	default:
		break;
	}	// switch (cmd.commandType)
}


/******************************************************************************
 * TextArea::setText -- Set the text to show in the input box.                *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   str -- A wide string to be set.                                   *
 *                                                                            *
 * OUTPUT:  The pointer to the input box.                                     *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
TextArea* TextArea::setText(const std::wstring& str)
{
	pTextCell->setText(str);

	return this;
}


/******************************************************************************
 * TextArea::getText -- Get the text.                                         *
 *                                                                            *
 *    This is slightly different from the text cell, which we know returns a  *
 *    modifiable reference, here we return a copy.                            *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the text.                                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/07 Tony : Created.                                               *
 *============================================================================*/
std::wstring TextArea::getText() const
{
	return pTextCell->getText();
}


/******************************************************************************
 * TextArea::setCursorColor -- Set the color of the cursor.                   *
 *                                                                            *
 *    Maybe the color can also be set in another way. :)                      *
 *                                                                            *
 * INPUT:   color -- The color to be set.                                     *
 *                                                                            *
 * OUTPUT:  Return the pointer to the input box.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
TextArea* TextArea::setCursorColor(COLORREF color)
{
	pCursorCell->setFillColor(color);
	pCursorCell->setLineColor(color);

	return this;
}


/******************************************************************************
 * TextArea::setPadding -- Set box padding.                                   *
 *                                                                            *
 *    The input box has different paddings depend on whether selected by the  *
 *    user.                                                                   *
 *                                                                            *
 * INPUT:   _normalPadding   -- Padding when not selected.                    *
 *          _selectedPadding -- Padding when selected.                        *
 *                                                                            *
 * OUTPUT:  The pointer to the input box.                                     *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
TextArea* TextArea::setPadding(int _normalPadding, int _selectedPadding)
{
	normalPadding = _normalPadding;
	selectedPadding = _selectedPadding;

	return this;
}


/******************************************************************************
 * TextArea::setInputArea -- Set the style of the input box.                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   style -- The rectangle or round rectangle style.                  *
 *                                                                            *
 * OUTPUT:  The pointer to the input box.                                     *
 *                                                                            *
 * WARNINGS:  The style can only be rectangle or round rectangle. And adjust  *
 *            the text cell's size, we should.
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *   2022/01/10 Tony : Changed position setting.                              *
 *============================================================================*/
TextArea* TextArea::setBoxStyle(DrawCell* style)
{
	if (pBoxCell)
		delete pBoxCell;
	pBoxCell = style;

	width = dynamic_cast<SizeProperty*>(pBoxCell)->getWidth();
	height = dynamic_cast<SizeProperty*>(pBoxCell)->getHeight();

	/*
	** 2022/01/10
	*/
	pTextCell->setPos(style->getPos());
	pTextCell->setSize(width, height);

	return this;
}


/******************************************************************************
 * TextArea::setTextStyle -- Set the text style of the... text. :)            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _fontHeight                                                       *
 *          _fontWidth                                                        *
 *          _fontColor                                                        *
 *          _fontFace                                                         *
 *                                                                            *
 * OUTPUT:  The pointer to the input box.                                     *
 *                                                                            *
 * WARNINGS:  The style can only be rectangle or round rectangle. And adjust  *
 *            the text cell's size, we should.                                *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
TextArea* TextArea::setTextStyle(
	int _fontHeight,
	int _fontWidth,
	COLORREF _fontColor,
	const std::wstring& _fontFace)
{
	pTextCell->setTextStyle(
		_fontHeight,
		_fontWidth,
		_fontColor,
		_fontFace);

	return this;
}


/******************************************************************************
 * TextArea::setTrigger -- Set the trigger of the input box.                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   trigger                                                           *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  ...                                                             *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
TextArea* TextArea::setTrigger(Trigger* trigger)
{
	if (pTrigger)
		delete pTrigger;

	pTrigger = trigger;

	return this;
}


/******************************************************************************
 * TextArea -- onChange -- Set the callback function.                         *
 *                                                                            *
 *    Set the callback function to be called when the text is changed.        *
 *                                                                            *
 * INPUT:   callback                                                          *
 *          param                                                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
TextArea* TextArea::onChange(std::function<void(void)> callback)
{
	pOnChange = callback;

	return this;
}


/******************************************************************************
 * TextArea::onBlur -- Set the callback function.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   callback                                                          *
 *          param                                                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
TextArea* TextArea::onBlur(std::function<void(void)> callback)
{
	pOnBlur = callback;

	return this;
}


/******************************************************************************
 * TextArea::getBoxStyle -- Get the style of the box.                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the style of the box.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
DrawCell* TextArea::getBoxStyle()
{
	return pBoxCell;
}


/******************************************************************************
 * TextArea::load -- Load from xml element.                                   *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool TextArea::load(XMLElement* parent)
{
	const char* childName;

	if (!parseXMLAttribute(&name, parent->Attribute("name")))
	{
		report(R"(Missing "name" of textarea)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&pos, parent->Attribute("pos"));
	parseXMLAttribute(&layer, parent->Attribute("layer"));

	parseXMLAttribute(&isActivated, parent->Attribute("activated"));
	parseXMLAttribute(&isEventable, parent->Attribute("eventable"));

	parseXMLAttribute(&normalPadding, parent->Attribute("normal-padding"));
	parseXMLAttribute(&selectedPadding, parent->Attribute("selected-padding"));

	COLORREF color;
	if (parseXMLAttribute(&color, parent->Attribute("cursor-color")))
		setCursorColor(color);

	std::wstring placeholder;
	if (parseXMLAttribute(&placeholder, parent->Attribute("placeholder")))
		pTextCell->setText(placeholder);

	int fontHeight = parseInt(parent->Attribute("font-size"));	
	COLORREF fontColor = parseColor(parent->Attribute("font-color"));
	std::wstring fontFace;
	if (parseXMLAttribute(&fontFace, parent->Attribute("font")))
		pTextCell->setTextStyle(fontHeight, 0, fontColor, fontFace);
	else
		pTextCell->setTextStyle(fontHeight, 0, fontColor);
	

	XMLElement* child = parent->FirstChildElement();
	while (child != NULL)
	{
		childName = child->Name();
		if (strcmp(childName, "trigger") == 0)
			setTrigger(newTrigger(child->FirstChildElement()));
		else if (strcmp(childName, "box") == 0)
			setBoxStyle(newDrawCell(child->FirstChildElement()));

		child = child->NextSiblingElement();
	}

	if (!pTrigger)
	{
		report(R"(Missing trigger of textarea)", LOAD_WIDGET);
		return false;
	}
	if ((!pBoxCell))
	{
		report(R"(Missing draw cell of textarea)", LOAD_WIDGET);
		return false;
	}

	pTrigger->translate(pos);
	pBoxCell->translate(pos);
	pTextCell->translate(pos);

	return true;
}



/******************************************************************************
* StaticWidget::StaticWidget -- Constructor of the object.                    *
*                                                                             *
*    Just the literal meaning.                                                *
*                                                                             *
* INPUT:   none                                                               *
*                                                                             *
* OUTPUT:  none                                                               *
*                                                                             *
* WARNINGS:  none                                                             *
*                                                                             *
* HISTORY:                                                                    *
*   2022/01/08 Tony : Created.                                                *
*=============================================================================*/
StaticWidget::StaticWidget() : Widget(WidgetType::STATIC)
{
	pDrawCell = nullptr;
}


/******************************************************************************
 * StaticWidget::~StaticWidget -- Deconstructor of the object.                *
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
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
StaticWidget::~StaticWidget()
{
	if (pDrawCell)
		delete pDrawCell;
}


/******************************************************************************
 * StaticWidget::setPos -- Set position of the static widget.                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the pointer to it.                                         *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *   2022/01/10 Tony : Changed position setting.                              *
 *   2022/01/11 Tony : Added behabior to the setting.                         *
 *============================================================================*/
Widget* StaticWidget::setPos(const Coord& _pos)
{
	Coord offset = _pos - pos;

	pos = _pos;

	/*
	** 2022/01/10
	** 2022/01/11
	*/
	if (pDrawCell)
		pDrawCell->translate(offset);

	return this;
}


/******************************************************************************
 * StaticWidget::draw -- Draw the static widget.                              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pDestImg                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
void StaticWidget::draw(IMAGE* pDestImg)
{
	if (!isActivated)
		return;

	if (pDrawCell)
		pDrawCell->draw(pDestImg);
}


/******************************************************************************
 * StaticWidget::onEvent -- Behavior of the static widget.                    *
 *                                                                            *
 *    Err... it seems that it doesn't have any behaviors.                     *
 *                                                                            *
 * INPUT:   cmd                                                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
void StaticWidget::onEvent(const Command& cmd) {}


/******************************************************************************
 * StaticWidget::setStyle -- Set the display style.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   style -- Any kind of draw cell.                                   *
 *                                                                            *
 * OUTPUT:  Return the pointer of it.                                         *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
StaticWidget* StaticWidget::setStyle(DrawCell* style)
{
	if (pDrawCell)
		delete pDrawCell;

	pDrawCell = style;

	return this;
}


/******************************************************************************
 * StaticWidget::getStyle -- Get the widget's style..                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return its style.                                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/08 Tony : Created.                                               *
 *============================================================================*/
DrawCell* StaticWidget::getStyle()
{
	return pDrawCell;
}


/******************************************************************************
 * StaticWidget::load -- Load from xml file.                                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent                                                            *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool StaticWidget::load(XMLElement* parent)
{
	if (!parseXMLAttribute(&name, parent->Attribute("name")))
	{
		report(R"(Missing "name" of static widget)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&pos, parent->Attribute("pos"));
	parseXMLAttribute(&layer, parent->Attribute("layer"));

	parseXMLAttribute(&isActivated, parent->Attribute("activated"));
	parseXMLAttribute(&isEventable, parent->Attribute("eventable"));


	XMLElement* child = parent->FirstChildElement();
	while (child != NULL)
	{
		setStyle(newDrawCell(child));
		child = child->NextSiblingElement();
	}

	if (!pDrawCell)
	{
		report(R"(Missing draw cell of static widget)", LOAD_WIDGET);
		return false;
	}

	pDrawCell->translate(pos);

	return true;
}



/******************************************************************************
 * Detector::Detector -- Constructor of the object.                           *
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
 *   2022/02/20 Tony : Created.                                               *
 *============================================================================*/
Detector::Detector() : Widget(WidgetType::DETECTOR)
{
	mode = 0;
	tarCmdType = CMD_NONE;
	pOnDetect = nullptr;
	isAlwaysActive = false;
}


/******************************************************************************
 * Detector::~Detector -- Deconstructor of the object.                        *
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
 *   2022/02/20 Tony : Created.                                               *
 *============================================================================*/
Detector::~Detector() {}


/******************************************************************************
 * Detector::onEvent -- On event... :)                                        *
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
 *   2022/02/20 Tony : Created.                                               *
 *============================================================================*/
void Detector::onEvent(const Command& cmd)
{
	if (isAlwaysActive && pOnDetect)
	{
		pOnDetect();
		return;
	}

	if (!isActivated || !isEventable)
		return;

	if (!pOnDetect)
		return;

	if (mode == 0)
	{
		if (cmd.commandType & tarCmdType)
			pOnDetect();
	}
	else
	{
		if (cmd.sluggishKey == tarKey)
			pOnDetect();
	}
}


/******************************************************************************
 * Detector::load -- Load the detector.                                       *
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
 *   2022/02/20 Tony : Created.                                               *
 *============================================================================*/
bool Detector::load(XMLElement* parent)
{
	if (!parseXMLAttribute(&name, parent->Attribute("name")))
	{
		report(R"(Missing "name" of static widget)", LOAD_WIDGET);
		return false;
	}

	parseXMLAttribute(&isAlwaysActive, parent->Attribute("always"));
	parseXMLAttribute(&isActivated, parent->Attribute("activated"));
	parseXMLAttribute(&isEventable, parent->Attribute("eventable"));

	return true;
}


/******************************************************************************
 * Detector::setCommand -- Set the command to detect.                         *
 *                                                                            *
 *    This will also set the mode at the same time.                           *
 *                                                                            *
 * INPUT:   cmdType                                                           *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/20 Tony : Created.                                               *
 *============================================================================*/
Detector* Detector::setCommand(unsigned cmdType)
{
	tarCmdType = cmdType;
	mode = 0;

	return this;
}


/******************************************************************************
 * Detector::setKey -- Set the key to detect.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   key                                                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/20 Tony : Created.                                               *
 *============================================================================*/
Detector* Detector::setKey(BYTE key)
{
	tarKey = key;
	mode = 1;

	return this;
}


/******************************************************************************
 * Detector::onDetect -- Set the callback function.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   callback                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/20 Tony : Created.                                               *
 *============================================================================*/
Detector* Detector::onDetect(std::function<void(void)> callback)
{
	pOnDetect = callback;

	return this;
}


/******************************************************************************
 * newWidget -- Get a new widget and load.                                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   element                                                           *
 *                                                                            *
 * OUTPUT:  Return the new widget.                                            *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
Widget* newWidget(XMLElement* element)
{
	if (element == NULL)
		return nullptr;


	const char* childName = element->Name();
	Widget* rv;

	if (strcmp(childName, "static") == 0)
		rv = new StaticWidget();
	else if (strcmp(childName, "button") == 0)
		rv = new Button();
	else if (strcmp(childName, "dragbar") == 0)
		rv = new DragBar();
	else if (strcmp(childName, "checkbox") == 0)
		rv = new CheckBox();
	else if (strcmp(childName, "textarea") == 0)
		rv = new TextArea();
	else if (strcmp(childName, "progressbar") == 0)
		rv = new ProgressBar();
	else if (strcmp(childName, "detector") == 0)
		rv = new Detector();
	else
		rv = nullptr;

	if (rv)
	{
		if (!rv->load(element))
		{
			delete rv;
			rv = nullptr;
		}
	}
	else
		reportf("Unknown widget: %s", childName, "Loading widget");

	return rv;
}



/******************************************************************************
 * WidgetManager::WidgetManager -- Constructor of the object.                 *
 *                                                                            *
 *    The default image is the device.                                        *
 *                                                                            *
 * INPUT:   pDestImg -- The destination image to draw widgets.                *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
WidgetManager::WidgetManager(IMAGE* _pDestImg)
{
	pTargetImage = _pDestImg;
}


/******************************************************************************
 * WidgetManager::~WidgetManager -- Deconstructor of the object.              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to delete widgets. :)                                  *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
WidgetManager::~WidgetManager()
{
	for (auto it = widgetPool.begin(); it != widgetPool.end(); it++)
		delete it->second;
}


/******************************************************************************
 * WidgetManager::setTargetImage -- Set the target imaget to draw widgets.    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pDestImg -- The destination image.                                *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
void WidgetManager::setTargetImage(IMAGE* _pDestImg)
{
	pTargetImage = _pDestImg;
}


/******************************************************************************
 * WidgetManager::draw -- Draw all widgets.                                   *
 *                                                                            *
 *    Draw all widgets to the assigned image.                                 *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
void WidgetManager::draw()
{
	for (auto it = widgetList.begin(); it != widgetList.end(); it++)
		it->second->draw(pTargetImage);
}


/******************************************************************************
 * WidgetManager::processEvent -- Process events.                             *
 *                                                                            *
 *    All user interactions are happening here.                               *
 *                                                                            *
 * INPUT:   cmd -- Command from the user. It will be collected in another     *
 *                 function in another thread. :)                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
void WidgetManager::processEvent(const Command& cmd)
{
	for (auto it = widgetPool.begin(); it != widgetPool.end(); it++)
		it->second->onEvent(cmd);
}


/******************************************************************************
 * WidgetManager::add -- Add a widget to the manager.                         *
 *                                                                            *
 *    Add a widget to the manager. And it will automatically sort them.       *
 *                                                                            *
 * INPUT:   childName   -- The childName of... the widget. LOL                *              *
 *          widget -- What widget to add.                                     *
 *                                                                            *
 * OUTPUT:  Return true if added successfully, false if the widget already    *
 *          exists.                                                           *
 *                                                                            *
 * WARNINGS:  Watch out, the widgets can't have the same childName!           *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
bool WidgetManager::add(const std::string& childName, Widget* widget)
{
	if (widget == nullptr)
		return false;

	// Already exists.
	if (widgetPool.find(childName) != widgetPool.end())
		return false;

	// Insert to widget pool.
	widgetPool[childName] = widget;

	// Insert to the sorted list by layer.
	widgetList.insert(std::make_pair(widget->getLayer(), widget));

	return true;
}


/******************************************************************************
 * WidgetManager::get -- Get a widget from the manager.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   childName -- The childName of the widget to get from the manager. *         *
 *                                                                            *
 * OUTPUT:  Return the required widget. Return nullptr if it doesn't exist.   *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/09 Tony : Created.                                               *
 *============================================================================*/
Widget* WidgetManager::get(const std::string& childName)
{
	if (widgetPool.find(childName) == widgetPool.end())
		return nullptr;

	return widgetPool[childName];
}


/******************************************************************************
 * WidgetManager::load -- Load widgets from xml file.manager.                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent -- The root element of all widgets in a interface.         *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/13 Tony : Created.                                               *
 *============================================================================*/
bool WidgetManager::load(XMLElement* parent)
{
	XMLElement* child;
	Widget* widget;
	bool flag;

	flag = true;
	child = parent->FirstChildElement();
	while (flag && (child != NULL))
	{
		widget = newWidget(child);
		if (widget)
			add(widget->getName(), widget);
		else
			flag = false;

		child = child->NextSiblingElement();
	}

	return flag;
}
		
