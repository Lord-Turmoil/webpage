/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : interface.h                               *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 19, 2022                          *
 *                                                                            *
 *                    Last Update : February 10, 2022                         *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For the interface of the game. :(                                        *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <map>
#include <easyx.h>
#include <functional>

#include "audio.h"
#include "define.h"
#include "widget.h"
#include "tinyxml.h"
#include "dungeon.h"


/********************************************************************
** Type of interface. INTF is short for interface.
*/
enum InterfaceType
{
	INTF_UNKNOWN = 0,

	INTF_WIN,
	INTF_LOSE,
	INTF_LOAD,
	INTF_MAIN,
	INTF_HELP,
	INTF_GAME,
	INTF_PLAIN,
	INTF_STORE,
	INTF_PAUSE,
	INTF_OPTIONS,
	INTF_CREDITS,
	INTF_SELECT_MODE,
	INTF_ACHIEVENTMEN,
	INTF_INGAME_OPTIONS,
	INTF_SELECT_CHARACTER,

	INTF_NUM
};
	

/********************************************************************
** The base class of all interfaces.
*/
class Interface
{
public:
	Interface(InterfaceType _type = INTF_PLAIN);
	virtual ~Interface();

	void setTargetImage(IMAGE* _pTargetImage);

	InterfaceType getType() const;
	const std::string& getName() const;

	/*
	** Get the callback function of launch and terminate.
	*/
	std::function<void(void)> getLaunch();
	std::function<void(void)> getTerminate();

	/*
	** Launch the interface. This includes initialization and run.
	** To make it compatible with the widgets, here is a void*
	** parameter, but doesn't function.
	*/
	virtual void launch();

	/*
	** Terminate the interface.
	*/
	virtual void terminate();

	/*
	** Run the interface, and all its contents.
	*/
	virtual void run();

	virtual void draw();

	virtual bool load(XMLElement* parent);

	WidgetManager* getWidget();

	Widget* operator[](const std::string& name)
	{
		return widgetManager[name];
	};
	

protected:
	/*
	** For the transition between different interfaces.
	*/
	virtual void transitIn();
	virtual void transitOut();

	virtual void initialize();
	virtual void perish();
	virtual void process();

	InterfaceType type;
	std::string name;

	IMAGE* pTargetImage;

	/*
	** Manage all UI components.
	*/
	WidgetManager widgetManager;

	/*
	** The background image of the interface. Most of them are...
	** the last frame of the previous interface.
	*/
	IMAGE background;

	bool hasBackground;
	
	/*
	** Whether the interface is currently on. If a sub-interface
	** is activated, then its parent interface is still active until
	** terminate() is called.
	*/
	bool isActive;

	/*
	** The time that transit in and out take.
	*/
	TransitStyle inStyle;
	TransitStyle outStyle;

public:
	Interface* pPrevInterface;
	Interface* pNextInterface;

	MusicList musicList;

	std::function<void(void)> onUnLoad;
};


class GameInterface : public Interface
{
public:
	GameInterface();
	~GameInterface();

	virtual void draw();

	Launcher* getLauncher();
	GameInterface* setVictory(Interface* intf);
	GameInterface* setLost(Interface* intf);

private:
	virtual void process();
	virtual void initialize();

	Launcher launcher;
	Interface* pVictoryInterface;
	Interface* pLostInterface;
};


class TaskInterface : public Interface
{
public:
	TaskInterface();
	~TaskInterface();

	void setTask(std::function<int(void)> _pTask, bool abort = true);

	virtual void launch();

private:
	virtual void initialize();
	virtual void process();

	// Here, task must return 0 if successful.
	std::function<int(void)> pTask;
	int state;

	bool isOnce;
};


class PauseInterface : public Interface
{
public:
	PauseInterface() {}
	~PauseInterface() {}

private:
	virtual void initialize();
	virtual void perish();
};


Interface* newInterface(XMLElement* element);


class InterfaceManager
{
public:
	InterfaceManager();
	~InterfaceManager();

	bool add(const std::string& key, Interface* intf);
	Interface* get(const std::string& key);

	void setTargetImage(IMAGE* _pTargetImage);

	void launch();

	bool load(const char* file);
	bool unload();

	Interface* operator[](const std::string& key)
	{
		return interfacePool[key];
	};

private:
	std::map<std::string, Interface*> interfacePool;

	Interface* startup;

	IMAGE* pTargetImage;
};


#endif