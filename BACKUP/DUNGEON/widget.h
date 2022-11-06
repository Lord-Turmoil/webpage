/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : widget.h                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 4, 2022                           *
 *                                                                            *
 *                    Last Update : February 20, 2022                         *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For UI widgets. Based on EasyUI.                                         *
 * -------------------------------------------------------------------------- *
 * Reference:                                                                 *
 *   https://codebus.cn/contributor/zhurong-easyui                            *
 *   Many many many... thanks! :)                                             *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <map>
#include <ctime>
#include <string>
#include <easyx.h>
#include <functional>

#include "define.h"
#include "tinyxml.h"
#include "command.h"

/******************************************************************************
**                               Draw Cell                                   **
*******************************************************************************/
#pragma region DrawCell

/********************************************************************
** Base class of drawing componenets. They only draw certain images,
** and interaction are for triggers.
*/
class DrawCell
{
public:
	DrawCell();
	virtual ~DrawCell();

	/*
	** The position to draw.
	*/
	void setPos(const Coord& _pos);
	void translate(Coord offset);

	void makeCenter(bool center);

	Coord getPos() const;

	/*
	** Sub draw cell. Here return the sub cell to do ths
	** continuously, just like cin, cout.
	*/
	DrawCell* setSubCell(DrawCell* cell);
	DrawCell* getSubCell();

	/*
	** Draw contents to assigned buffer. This buffer will
	** be provided by UI widget manager.
	** 2022/01/05
	** If makeCenter is true, then the draw cell will try to
	** adjust its position to make top-right position to its
	** center.
	** 2022/01/07
	** Removed makeCenter, and added it as a member.
	*/
	virtual void draw(IMAGE* pDestImg) = 0;

	/*
	** Load draw cell from certain xml node.
	*/
	virtual bool load(XMLElement* parent) = 0;

protected:
	Coord pos;

	/*
	** 2022/01/07
	** Once makeCenter in the draw...
	*/
	bool isCentered;

	/*
	** Sub cell will be drawn on a higher layer.
	*/
	DrawCell* pSubCell;
};


/********************************************************************
** To draw simple shapes.
*/
class SimpleCell : public DrawCell
{
public:
	SimpleCell();
	virtual ~SimpleCell();

	/*
	** Set shape properties. Return itself to apply them
	** in a row.
	*/
	SimpleCell* setFillStyle(bool fill);
	SimpleCell* setLineColor(COLORREF color);
	SimpleCell* setFillColor(COLORREF color);
	SimpleCell* setLineStyle(const LINESTYLE& style);
	SimpleCell* setLineThickness(int thickness);

	bool getFill() const;
	COLORREF getLineColor() const;
	COLORREF getFillColor() const;
	LINESTYLE* getLineStyle();
	FILLSTYLE* getFillStyle();

	virtual void draw(IMAGE* pDestImg) = 0;

	virtual bool load(XMLElement* parent) = 0;

protected:
	/*
	** Apply current style.
	*/
	void applyAttribute();

	bool		isFilled;
	COLORREF	lineColor;
	COLORREF	fillColor;
	LINESTYLE	lineStyle;
	FILLSTYLE	fillStyle;
};


/********************************************************************
** Size properties of draw cell.
*/
class SizeProperty
{
public:
	SizeProperty();
	virtual ~SizeProperty();

	/*
	** If width or height is not assigned, then it keeps its
	** original value.
	*/
	void setSize(int _width = 0, int _height = 0);

	int getWidth() const;
	int getHeight() const;

protected:
	int width;
	int	height;
};


/********************************************************************
** To draw a circle.
*/
class CircleCell : public SimpleCell
{
public:
	CircleCell(
		Coord _pos = { 0, 0 },
		int _radius = 0,
		COLORREF _lineColor = WHITE,
		COLORREF _fillColor = WHITE);
	~CircleCell();

	void setRadius(int _radius);
	int getRadius() const;

	virtual void draw(IMAGE* pDestImg);

	virtual bool load(XMLElement* parent);

private:
	int radius;
};


/********************************************************************
** To draw a rectangle
*/
class RectCell : public SimpleCell, public SizeProperty
{
public:
	RectCell(
		Coord _pos = { 0, 0 },
		int _width = 0,
		int _height = 0,
		COLORREF _lineColor = WHITE,
		COLORREF _fillColor = WHITE);
	~RectCell();

	virtual void draw(IMAGE* pDestImg);

	virtual bool load(XMLElement* parent);

private:
};


/********************************************************************
** To draw a round-rectangle.
*/
class RoundRectCell : public SimpleCell, public SizeProperty
{
public:
	RoundRectCell(
		Coord _pos = { 0, 0 },
		int _width = 0,
		int _height = 0,
		int _ellipseWidth = 0,
		int _ellipseHeight = 0,
		COLORREF _lineColor = WHITE,
		COLORREF _fillColor = WHITE);
	~RoundRectCell();

	/*
	** If not assigned, then it remains unchanged.
	*/
	void setRoundSize(int _ellipseWidth = 0, int _ellipseHeight = 0);

	int getRoundWidth() const;
	int getRoundHeight() const;

	virtual void draw(IMAGE* pDestImg);

	virtual bool load(XMLElement* parent);

private:
	int	ellipseWidth;
	int	ellipseHeight;
};


/********************************************************************
** To draw text.
*/
class TextCell : public DrawCell, public SizeProperty
{
public:
	TextCell(Coord _pos = { 0, 0 }, int _width = 0, int _height = 0, std::wstring _text = L"");
	~TextCell();

	TextCell* setText(const std::wstring& _text);
	TextCell* setTextStyle(
		int _fontHeight = 0,
		int _fontWidth = 0,
		COLORREF _fontColor = WHITE,
		const std::wstring& _fontFace = L"Consolas",
		bool _isJustified = true);

	std::wstring& getText();

	virtual void draw(IMAGE* pDestImg);

	virtual bool load(XMLElement* parent);

private:
	void applyAttribute();

	std::wstring text;

	int fontHeight;
	int fontWidth;
	COLORREF fontColor;
	std::wstring fontFace;

	/*
	** Whether to center the text in the rectangle or not.
	*/
	bool isJustified;
};


/********************************************************************
** To draw an image. Here we use transparent image.
*/
class ImageCell : public DrawCell, public SizeProperty
{
public:
	ImageCell(IMAGE* pSrcImg = nullptr);
	~ImageCell();

	/*
	** This will make a copy of the src image.
	*/
	void setImage(IMAGE* pSrcImg);
	IMAGE* getImage();

	virtual void draw(IMAGE* pDestImg);

	virtual bool load(XMLElement* parent);

private:
	/*
	** Adjust size to the image size. This will be called after
	** setImage or valid constructor automatically.
	*/
	void adjustSize();

	IMAGE image;
};


/********************************************************************
** Create a new draw cell and load from xml.
*/
DrawCell* newDrawCell(XMLElement* element);

// End of DrawCell
#pragma endregion




/******************************************************************************
**                               Trigger                                     **
*******************************************************************************/
#pragma region Trigger

/********************************************************************
** Interact with the user.
*/
class Trigger
{
public:
	Trigger();
	virtual ~Trigger();

	/*
	** Check whether a point is detected by the trigger.
	*/
	virtual bool inRange(const Coord& target) = 0;

	/*
	** Set trigger position.
	*/
	void setPos(const Coord& _pos);
	void translate(Coord offset);

	void makeCenter(bool center);

	Coord getPos() const;

	virtual bool load(XMLElement* parent) = 0;

protected:
	Coord pos;

	/*
	** 2022/01/07
	** The same as the one in draw cell.
	*/
	bool isCentered;
};


/********************************************************************
** A trigger that looks like a circle. Be aware that only circle has
** its center as the coordinate.
*/
class CircleTrigger : public Trigger
{
public:
	CircleTrigger(Coord _pos = { 0, 0 }, int _radius = 0);
	~CircleTrigger();

	virtual bool inRange(const Coord& target);

	void setRadius(int _radius);
	int getRadius() const;

	virtual bool load(XMLElement* parent);

private:
	int radius;
};


/********************************************************************
** A trigger that looks like a rectangle.
*/
class RectTrigger : public Trigger
{
public:
	RectTrigger(Coord _pos = { 0, 0 }, int _width = 0, int height = 0);
	~RectTrigger();

	virtual bool inRange(const Coord& target);

	/*
	** If width or height is not assigned, then it keeps
	** its original value.
	*/
	void setSize(int _width = 0, int _height = 0);

	int getWidth() const;
	int getHeight() const;

	virtual bool load(XMLElement* parent);

private:
	int width;
	int height;

	/*
	** The valid trigger area.
	*/
	RECT range;
};


/********************************************************************
** A trigger that use a image as a mask. This should work better
** with ImageCell.
*/
class MaskTrigger : public Trigger
{
public:
	MaskTrigger(Coord _pos = { 0, 0 }, IMAGE* pSrcImg = nullptr);
	~MaskTrigger();

	virtual bool inRange(const Coord& target);

	/*
	** It will also have a copy of the image. And here, the same
	** as the transparent image, the area with TRANSPARENT_COLOR
	** will be regarded as invalid.
	*/
	void setMask(IMAGE* pSrcImg);
	IMAGE* getMask();

	int getWidth() const;
	int getHeight() const;

	virtual bool load(XMLElement* parent);

private:
	IMAGE mask;
	int width;
	int height;

	/*
	** The valid trigger area.
	*/
	RECT range;
};


Trigger* newTrigger(XMLElement* element);

// End of Trigger
#pragma endregion



/******************************************************************************
**                                Widget                                     **
*******************************************************************************/
#pragma region Widget

/********************************************************************
** UI widget types.
*/
enum class WidgetType {
	STATIC,
	BUTTON,
	DRAGBAR,
	CHECKBOX,
	TEXTAREA,
	DETECTOR,
	PROGRESSBAR,

	WIDGET_NUM,

	UNKNOW = 0
};

/********************************************************************
** Base calss of UI widgets.
*/
class Widget
{
public:
	Widget(WidgetType _type);
	virtual ~Widget();

	/*
	** This will automatically set draw cells and triggers'
	** position.
	*/
	virtual Widget* setPos(const Coord& _pos) = 0;

	Widget* setState(bool _active);
	Widget* setEventable(bool _eventable);
	Widget* setLayer(int _layer);

	WidgetType getType() const;
	const std::string& getName() const;
	Coord getPos() const;
	bool getState() const;
	bool getEventable() const;
	int getLayer() const;

	virtual void draw(IMAGE* pDestImg) = 0;
	virtual void onEvent(const Command& cmd) = 0;

	virtual bool load(XMLElement* parent) = 0;

protected:
	WidgetType type;

	std::string name;

	Coord pos;

	/*
	** Whether a widget is activated for use or not.
	** if is not activated, then user simply can't
	** see it, let alone have interaction with it.
	*/
	bool isActivated;

	/*
	** Whether a widget can interact with user or not.
	** if is not eventable, then users can see it, but
	** it won't have any reactions.
	*/
	bool isEventable;

	/*
	** Widget's layer, to display in multiple layer and may
	** shield each other.
	*/
	int layer;
};


/********************************************************************
** A ordinary button.
*/
class Button : public Widget
{
public:
	Button();
	~Button();

	virtual Widget* setPos(const Coord& _pos);

	virtual void draw(IMAGE* pDestImg);
	virtual void onEvent(const Command& cmd);

	/*
	** How to draw the button. Button has three states,
	** normal, hover and pressed.
	*/
	Button* setNormalStyle(DrawCell* style);
	Button* setHoverStyle(DrawCell* style);
	Button* setPressedStyle(DrawCell* style);

	/*
	** How the button responds.
	*/
	Button* setTrigger(Trigger* trigger);

	/*
	** The callback function. It's a little tricky. :(
	** It will be called after a click. Since I'm not sure
	** what it should be, I made it void*. :)
	*/
	Button* onClick(std::function<void(void)> callback);

	DrawCell* getNormalStyle();
	DrawCell* getHoverStyle();
	DrawCell* getPressedStyle();
	Trigger* getTrigger();
	
	virtual bool load(XMLElement* parent);

private:
	/*
	** Three states.
	*/
	DrawCell* pNormalStyle;
	DrawCell* pHoverStyle;
	DrawCell* pPressedStyle;

	/*
	** The trigger binded to it.
	*/
	Trigger* pTrigger;

	/*
	** Callback function. And perhaps param is... the parameter?
	** I hope that the call back function can make change to the
	** parameter. :(
	** 2022/01/09
	** Notice that if the param is void*, then it will no longer
	** compatible for the widgets themselves!!! :(
	** 2022/02/14
	** Changed back to void(void).
	*/
	std::function<void(void)> pOnClick;

	/*
	** Current mouse state. If not pressed or hover, then
	** nothing happens.
	*/
	bool isHover;
	bool isPressed;
};


/********************************************************************
** A fancy drag bar. To set volume or else.
*/
class DragBar : public Widget
{
public:
	DragBar();
	~DragBar();

	virtual Widget* setPos(const Coord& _pos);

	virtual void draw(IMAGE* pDestImg);
	virtual void onEvent(const Command& cmd);

	/*
	** Drag bar consists of a block and a bar. Be aware that the
	** block's position is its center.
	*/
	DragBar* setBlockNormal(DrawCell* style);
	DragBar* setBlockPressed(DrawCell* style);
	DragBar* setBarStyle(DrawCell* style);

	DragBar* setBlockTrigger(Trigger* trigger);
	DragBar* setBarTrigger(Trigger* trigger);

	/*
	** When the block is dragged, or the bar is pressed(not clicked).
	*/
	DragBar* onChange(std::function<void(double)> callback);

	/*
	** When the drag bar loses user's focus.
	*/
	DragBar* onBlur(std::function<void(void)> callback);

	DrawCell* getBlockNormal();
	DrawCell* getBlockPressed();
	DrawCell* getBar();
	Trigger* getBlockTrigger();
	Trigger* getBarTrigger();

	void setValue(double _value);

	/*
	** 2022/01/09
	** This is used for callbacks among widgets. :(
	*/
	void setValue(void* param);

	double getValue() const;

	virtual bool load(XMLElement* parent);

private:
	DrawCell* pBlockNormal;
	DrawCell* pBlockPressed;
	DrawCell* pBarCell;

	Trigger* pBlockTrigger;
	Trigger* pBarTrigger;

	std::function<void(double)> pOnChange;
	std::function<void(void)> pOnBlur;

	int barWidth;
	int barHeight;

	/*
	** value is between 0 and 1.
	*/
	double value;

	bool isPressed;
};


/********************************************************************
** The most fancy progress bar.
*/
class ProgressBar : public Widget
{
public:
	ProgressBar();
	~ProgressBar();

	virtual Widget* setPos(const Coord& _pos);

	virtual void draw(IMAGE* pDestImg);
	virtual void onEvent(const Command& cmd);

	/*
	** A progress bar is composed of a bar and a mask.
	*/
	ProgressBar* setBarStyle(DrawCell* style);
	ProgressBar* setMaskStyle(DrawCell* style);
	ProgressBar* setPadding(int _padding);

	DrawCell* getBarStyle();
	DrawCell* getMaskStyle();

	void setValue(double _value);
	double getValue() const;

	virtual bool load(XMLElement* parent);

private:
	DrawCell* pBarCell;
	DrawCell* pMaskCell;

	double value;

	int barWidth;
	int barHeight;

	/*
	** Horizontal padding and vertical padding.
	** 2022/01/07
	** Changed two paddings to be the same.
	*/
	int padding;
};


/********************************************************************
** Check box... Check box. :)
*/
class CheckBox : public Widget
{
public:
	CheckBox();
	~CheckBox();


	virtual Widget* setPos(const Coord& _pos);

	virtual void draw(IMAGE* pDestImg);
	virtual void onEvent(const Command& cmd);

	CheckBox* setNormalStyle(DrawCell* style);
	CheckBox* setSelectedStyle(DrawCell* style);

	CheckBox* setTrigger(Trigger* trigger);

	CheckBox* onClick(std::function<void(void)> callback);

	DrawCell* getNormalStyle();
	DrawCell* getSelectedStyle();

	Trigger* getTrigger();

	void setState(bool state);
	bool getState() const;

	virtual bool load(XMLElement* parent);

private:
	DrawCell* pNormalStyle;
	DrawCell* pSelectedStyle;

	Trigger* pTrigger;

	std::function<void(void)> pOnClick;

	bool isSelected;
};


/********************************************************************
** Input box. Only support single line... :(
** 2022/01/08
** ... InputBox is a class name in EasyX... >_<
** So... change it to TextArea...
*/
class TextArea : public Widget
{
public:
	TextArea();
	~TextArea();

	virtual Widget* setPos(const Coord& _pos);

	virtual void draw(IMAGE* pDestImg);
	virtual void onEvent(const Command& cmd);

	TextArea* setText(const std::wstring& str);
	std::wstring getText() const;

	TextArea* setCursorColor(COLORREF color);
	TextArea* setPadding(int _normalPadding, int _selectedPadding);

	/*
	** Although here is... DrawCell, but only support rectangle
	** and round rectangle. :[
	*/
	TextArea* setBoxStyle(DrawCell* style);

	/*
	** Here we removed the choice for justified. :}
	*/
	TextArea* setTextStyle(
		int _fontHeight = 0,
		int _fontWidth = 0,
		COLORREF _fontColor = WHITE,
		const std::wstring& _fontFace = L"Consolas");

	TextArea* setTrigger(Trigger* trigger);

	TextArea* onChange(std::function<void(void)> callback);
	TextArea* onBlur(std::function<void(void)> callback);

	DrawCell* getBoxStyle();

	virtual bool load(XMLElement* parent);

private:
	DrawCell* pBoxCell;

	/*
	** Cursor cell and text cell are generated by
	** the class itself.
	*/
	RectCell* pCursorCell;
	TextCell* pTextCell;

	Trigger* pTrigger;

	std::function<void(void)> pOnChange;
	std::function<void(void)> pOnBlur;

	int width;
	int height;

	/*
	** If is selected, then it will have a slightly different
	** style. :P
	*/
	int normalPadding;
	int selectedPadding;

	/*
	** Last time when the cursor change its visibility.
	*/
	clock_t oldCursorTime;

	bool isSelected;

	/*
	** Whether to show the cursor or not. This is for the
	** blink effect.
	*/
	bool showCursor;

	/*
	** Copy of the str in case unwanted change is discarded.
	*/
	std::wstring copy;

	CommandFilter lastFilter;
};


/********************************************************************
** Static Widgets.
*/
class StaticWidget : public Widget
{
public:
	StaticWidget();
	~StaticWidget();

	virtual Widget* setPos(const Coord& _pos);

	virtual void draw(IMAGE* pDestImg);
	virtual void onEvent(const Command& cmd);

	StaticWidget* setStyle(DrawCell* style);
	DrawCell* getStyle();

	virtual bool load(XMLElement* parent);

private:
	/*
	** Static widget can only be seen.
	*/
	DrawCell* pDrawCell;
};


/********************************************************************
** Command widget. This only check for command, and no physical
** form. Usually as a linker.
*/
class Detector : public Widget
{
public:
	Detector();
	~Detector();

	virtual Widget* setPos(const Coord& _pos) { return this; }
	virtual void draw(IMAGE* pDestImg) {}
	virtual void onEvent(const Command& cmd);
	virtual bool load(XMLElement* parent);

	Detector* setCommand(unsigned cmdType);
	Detector* setKey(BYTE key);
	Detector* onDetect(std::function<void(void)> callback);

private:
	/*
	** 0 for command type, 1 for virtual key.
	*/
	int mode;
	bool isAlwaysActive;

	union
	{
		unsigned tarCmdType;
		BYTE tarKey;
	};

	std::function<void(void)> pOnDetect;
};


Widget* newWidget(XMLElement* element);

// End of Widget
#pragma endregion


/********************************************************************
** UI widget manager.
*/
class WidgetManager
{
public:
	WidgetManager(IMAGE* _pDestImg = nullptr);
	~WidgetManager();

	void setTargetImage(IMAGE* _pDestImg);

	/*
	** Draw all UI widget to the assigned buffer.
	*/
	void draw();

	/*
	** Process all events.
	*/
	void processEvent(const Command& cmd);

	/*
	** Here, we use a map to store all widgets. So we should
	** provide a key and a value.
	*/
	bool add(const std::string& name, Widget* widget);

	Widget* get(const std::string& name);

	virtual bool load(XMLElement* parent);

	Widget* operator[](const std::string& name)
	{
		return widgetPool[name];
	}

private:
	IMAGE* pTargetImage;

	/*
	** widgtePool stores all widgets, but not sorted. It is
	** only for add and search.
	*/
	std::map<std::string, Widget*> widgetPool;

	/*
	** widgetList stores all widgets sorted by layers. It will
	** refresh after a widget is added to the widgetPool.
	*/
	std::multimap<int, Widget*> widgetList;
};


#endif