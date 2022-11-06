/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : interface.h                               *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : February 10, 2022                         *
 *                                                                            *
 *                    Last Update :                                           *
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

#include <easyx.h>
#include <cstring>
#include <functional>

#include "image.h"
#include "error.h"
#include "config.h"
#include "timing.h"
#include "command.h"
#include "tinyxml.h"
#include "interface.h"


extern Canvas canvas;

extern Time globalTimer;
extern FPSTimer fpsTimer;
extern HPTimer hpTimer;

extern Command command;

extern Setting setting;

extern MusicManager musicPanel;


/******************************************************************************
 * Interface::Interface -- Constructor of the object.                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _type -- The type of the interface.                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/10 Tony : Created.                                               *
 *============================================================================*/
Interface::Interface(InterfaceType _type)
{
	type = _type;
	pTargetImage = nullptr;
	isActive = false;

	hasBackground = false;

	pPrevInterface = nullptr;
	pNextInterface = nullptr;

	onUnLoad = nullptr;
}


/******************************************************************************
 * Interface::~Interface -- Deconstructor of the object.                      *
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
 *   2022/02/10 Tony : Created.                                               *
 *============================================================================*/
Interface::~Interface() {}


/******************************************************************************
 * Interface::setTargetImage -- Set the target image of the UI widget.        *
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
 *   2022/02/10 Tony : Created.                                               *
 *============================================================================*/
void Interface::setTargetImage(IMAGE* _pTargetImage)
{
	pTargetImage = _pTargetImage;
	widgetManager.setTargetImage(pTargetImage);
}


/******************************************************************************
 * Interface::getType -- Get the type of the interface.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the type of the interface.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/10 Tony : Created.                                               *
 *============================================================================*/
InterfaceType Interface::getType() const
{
	return type;
}


/******************************************************************************
 * Interface::getName -- Get the name of the interface.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the name of the interface.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
const std::string& Interface::getName() const
{
	return name;
}


/******************************************************************************
 * Interface::getLaunch -- Get the callback of launch().                      *
 *                                                                            *
 *    This returns the callback function of launch(), making the link more    *
 *    easily.                                                                 *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/10 Tony : Created.                                               *
 *============================================================================*/
std::function<void(void)> Interface::getLaunch()
{
	return std::bind(&Interface::launch, this);
}


/******************************************************************************
 * Interface::getTerminate -- Get the callback of terminate().                *
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
 *   2022/02/10 Tony : Created.                                               *
 *============================================================================*/
std::function<void(void)> Interface::getTerminate()
{
	return std::bind(&Interface::terminate, this);
}


/******************************************************************************
 * Interface::launch -- Launch the interface.                                 *
 *                                                                            *
 *    This will be called at the start of the interface, including the        *
 *    transition-in process, and it will be active until terminate is called. *
 *                                                                            *
 * INPUT:   dummy -- Emm... dummy param.                                      *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/10 Tony : Created.                                               *
 *============================================================================*/
void Interface::launch()
{
	initialize();

	transitIn();

	isActive = true;
	run();

	transitOut();

	perish();

	if (pNextInterface)
		pNextInterface->launch();
}


/******************************************************************************
 * Interface::terminate -- Terminate the interface.                           *
 *                                                                            *
 *    This will end the main loop of the interface by setting the avtive flag *
 *    to false.                                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/10 Tony : Created.                                               *
 *============================================================================*/
void Interface::terminate()
{
	isActive = false;
}


/******************************************************************************
 * Interface::run -- Runs the interface.                                      *
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
 *   2022/02/11 Tony : Created.                                               *
 *============================================================================*/
void Interface::run()
{
	while (isActive)
	{
		draw();

		musicPanel.update();

		process();

		canvas.draw();

		hpTimer.delay(setting.delay);
	}
}


/******************************************************************************
 * Interface::draw - Draw the interface.                                      *
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
 *   2022/02/11 Tony : Created.                                               *
 *============================================================================*/
void Interface::draw()
{
	canvas.clear();

	if (hasBackground)
	{
		SetWorkingImage(pTargetImage);
		putimage(0, 0, &background);
		SetWorkingImage(NULL);
	}

	widgetManager.draw();
}


/******************************************************************************
 * Interface::load -- Load the interface from xml element.                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   parent -- xml element.                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
bool Interface::load(XMLElement* parent)
{
	if (parent == NULL)
		return false;

	if (!parseXMLAttribute(&name, parent->Attribute("name")))
	{
		report(R"(Missing "name" of interface)", LOAD_INTF);
		return false;
	}

	std::wstring src;
	if (parseXMLAttribute(&src, parent->Attribute("background")))
	{
		if (isAccessible(src.c_str()))
		{
			loadimage(&background, src.c_str());
			hasBackground = true;
		}
	}
	parseXMLAttribute(&inStyle, parent->Attribute("in-style"));
	parseXMLAttribute(&outStyle, parent->Attribute("out-style"));


	XMLElement* child = parent->FirstChildElement();
	const char* childName;
	while (child != NULL)
	{
		childName = child->Name();
		if (strcmp(childName, "music-list") == 0)
		{
			if (!musicList.load(child))
			{
				reportf("Failed to load music of %s", name.c_str(), LOAD_INTF);
				return false;
			}
		}
		else if (strcmp(childName, "widget") == 0)
		{
			if (!widgetManager.load(child))
			{
				reportf("Failed to load %s", parent->Name(), LOAD_INTF);
				return false;
			}
		}

		child = child->NextSiblingElement();
	}

	return true;
}


/******************************************************************************
 * Interface::getWidget -- Get the widget manager of the interface.           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the widget manager.                                        *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
WidgetManager* Interface::getWidget()
{
	return &widgetManager;
}


/******************************************************************************
 * Interface::transitIn -- Transit in effect.                                 *
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
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
void Interface::transitIn()
{
	switch (inStyle.type)
	{
	case TRANS_NONE:
		return;
	case TRANS_DARKEN:
		canvas.darken(inStyle.duration >> 1);
		draw();
		canvas.brighten(inStyle.duration >> 1);
		break;
	default:
		break;
	}
}


/******************************************************************************
 * Interface::transitOut -- Transit out effect.                               *
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
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
void Interface::transitOut()
{
	switch (outStyle.type)
	{
	case TRANS_NONE:
		return;
	case TRANS_DARKEN:
		if (pPrevInterface)
		{
			canvas.darken(outStyle.duration >> 1);
			pPrevInterface->draw();
			canvas.brighten(outStyle.duration >> 1);
		}
		else
			canvas.darken(outStyle.duration);
		break;
	default:
		break;
	}
}


/******************************************************************************
 * Interface::initialize -- Initialize the interface.                         *
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
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
void Interface::initialize()
{
	if (musicList.size() != 0)
	{
		musicPanel.push(&musicList);
		musicPanel.getList()->play();
	}
}


/******************************************************************************
 * Interface::perish -- Things to do at the end.                              *
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
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
void Interface::perish()
{
	if (musicList.size() != 0)
		musicPanel.pop();
	if (onUnLoad)
		onUnLoad();
}


/******************************************************************************
 * Interface::process -- Process event.                                       *
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
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
void Interface::process()
{
	getCommand();

	widgetManager.processEvent(command);

	switch (command.commandType)
	{
	case CMD_ESCAPE:
		command.commandType = CMD_NONE;
		isActive = false;
		break;
	case CMD_FULLSCREEN:
		canvas.switchSize();
		break;
	case CMD_PRINTSCREEN:
		canvas.snip();
		break;
	default:
		break;
	}
}



GameInterface::GameInterface() : Interface(InterfaceType::INTF_GAME)
{
	pVictoryInterface = nullptr;
	pLostInterface = nullptr;
}

GameInterface::~GameInterface() {}

void GameInterface::draw()
{
	canvas.clear();

	if (hasBackground)
	{
		SetWorkingImage(pTargetImage);
		putimage(0, 0, &background);
		SetWorkingImage(NULL);
	}

	launcher.draw();
	widgetManager.draw();

	// fps calculating.
#ifdef _DEBUG
	double fps;
	if (fpsTimer.getFPS(&fps))
		printf("%6.1f FPS\r", fps);
#endif
}

void GameInterface::process()
{
	// Timing
	globalTimer.update();
	fpsTimer.update();

	// Initialize.
	getCommand();

	// UI widgets.
	widgetManager.processEvent(command);

	switch (command.commandType)
	{
	case CMD_ESCAPE:
		command.commandType = CMD_NONE;
		isActive = false;
		break;
	case CMD_FULLSCREEN:
		canvas.switchSize();
		break;
	case CMD_PRINTSCREEN:
		canvas.snip();
		break;
	default:
		break;
	}

	// Gaming process.
	DungeonToken token = launcher.run();

	switch (token)
	{
	case VICTORIOUS:
		terminate();
		outStyle.type = TransitType::TRANS_NONE;
		pVictoryInterface->launch();
		break;
	case LOST:
		terminate();
		outStyle.type = TransitType::TRANS_NONE;
		pLostInterface->launch();
		break;
	case UPGRADE:
		transitIn();
		break;
	case RUNNING:
		break;
	default:
		break;
	}
}


/******************************************************************************
 * GameInterface::getLauncher -- Get the launcher of the game.                *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the launcher.                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
Launcher* GameInterface::getLauncher()
{
	return &launcher;
}

void GameInterface::initialize()
{
	if (musicList.size() != 0)
		musicPanel.push(&musicList);

	launcher.setHero(HeroType::HERO_YONY);
	launcher.getHero()->onShow(
		std::bind(&ProgressBar::setValue, dynamic_cast<ProgressBar*>(widgetManager["hp"]), std::placeholders::_1),
		std::bind(&ProgressBar::setValue, dynamic_cast<ProgressBar*>(widgetManager["amor"]), std::placeholders::_1),
		std::bind(&ProgressBar::setValue, dynamic_cast<ProgressBar*>(widgetManager["mp"]), std::placeholders::_1));
	launcher.setMode(DungeonType::DUNGEON_CAMPAIGN);
	launcher.setTargetImage(pTargetImage);
	launcher.launch();

	widgetManager.setTargetImage(launcher.getImage());
}

GameInterface* GameInterface::setVictory(Interface* intf)
{
	pVictoryInterface = intf;

	return this;
}

GameInterface* GameInterface::setLost(Interface* intf)
{
	pLostInterface = intf;

	return this;
}



TaskInterface::TaskInterface() : Interface(InterfaceType::INTF_LOAD)
{
	pTask = nullptr;
	state = 0;
	isOnce = true;
}

TaskInterface::~TaskInterface() {}

void TaskInterface::initialize()
{
	if (musicList.size() != 0)
	{
		musicPanel.push(&musicList);
		musicPanel.getList()->play();
	}

	command.commandType = CMD_NONE;
}

void TaskInterface::launch()
{
	initialize();

	transitIn();

	isActive = true;
	run();

	transitOut();

	if (state != 0)
	{
		reportf("Error: %s", std::to_string(state).c_str(), "Task interface");
		return;
	}

	command.commandType = CMD_NONE;

	if (pNextInterface)
		pNextInterface->launch();
}


/******************************************************************************
 * TaskInterface::setTask -- Set the task of the load interface.              *
 *                                                                            *
 *    Load interface will automatically end itself after the task.            *
 *                                                                            *
 * INPUT:   _pTask -- The task to perform.                                    *
 *          abort  -- Whether abort after task.                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
void TaskInterface::setTask(std::function<int(void)> _pTask, bool abort)
{
	pTask = _pTask;
	isOnce = abort;
}

void TaskInterface::process()
{
	if (pTask)
	{
		state = pTask();
		pTask = nullptr;
	}
	if (isOnce)
		isActive = false;

	getCommand();

	widgetManager.processEvent(command);

	switch (command.commandType)
	{
	case CMD_ESCAPE:
		command.commandType = CMD_NONE;
		isActive = false;
		break;
	case CMD_FULLSCREEN:
		canvas.switchSize();
		break;
	case CMD_PRINTSCREEN:
		canvas.snip();
		break;
	default:
		break;
	}

	widgetManager.processEvent(command);
}



void PauseInterface::initialize()
{
	if (musicList.size() != 0)
	{
		musicPanel.push(&musicList);
		musicPanel.getList()->play();
	}

	globalTimer.pause();
	command.commandType = CMD_NONE;
}

void PauseInterface::perish()
{
	if (onUnLoad)
		onUnLoad();
	globalTimer.cont();
}



/******************************************************************************
 * newInterface -- New a interface from a xml element.                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   element -- The xml element.                                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
Interface* newInterface(XMLElement* element)
{
	if (element == NULL)
		return nullptr;


	const char* childName = element->Name();
	Interface* rv;

	if (strcmp(childName, "intf") == 0)
		rv = new Interface();
	else if (strcmp(childName, "game-intf") == 0)
		rv = new GameInterface();
	else if (strcmp(childName, "task-intf") == 0)
		rv = new TaskInterface();
	else if (strcmp(childName, "pause-intf") == 0)
		rv = new PauseInterface();
	else
		rv = nullptr;

	if (!rv)
	{
		reportf("Unknown interface: %s", childName, "Loading interface");
		return nullptr;
	}


	if (!rv->load(element))
	{
		delete rv;
		rv = nullptr;
	}

	return rv;
}



/******************************************************************************
 * InterfaceManager::InterfaceManager -- Constructor of the object.           *
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
 *   2022/02/11 Tony : Created.                                               *
 *============================================================================*/
InterfaceManager::InterfaceManager()
{
	pTargetImage = nullptr;
	startup = nullptr;
}


/******************************************************************************
 * InterfaceManager::~InterfaceManager -- Deconstructor of the object.        *
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
 *   2022/02/11 Tony : Created.                                               *
 *============================================================================*/
InterfaceManager::~InterfaceManager()
{
	for (auto it = interfacePool.begin(); it != interfacePool.end(); it++)
		delete it->second;
}


/******************************************************************************
 * InterfaceManager::add -- Add an interface to the manager.                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   key  -- The key of the interface.                                 *
 *          intf -- The interface to add.                                     *
 *                                                                            *
 * OUTPUT:  If the intf already exist,                                        *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/11 Tony : Created.                                               *
 *============================================================================*/
bool InterfaceManager::add(const std::string& key, Interface* intf)
{
	if (intf == nullptr)
		return false;

	if (interfacePool.find(key) != interfacePool.end())
		return false;

	interfacePool[key] = intf;

	return true;
}


/******************************************************************************
 * InterfaceManager::get -- Get an interface.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   key -- The key of the interface to get.                           *
 *                                                                            *
 * OUTPUT:  Return the desired interface.                                     *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/11 Tony : Created.                                               *
 *============================================================================*/
Interface* InterfaceManager::get(const std::string& key)
{
	if (interfacePool.find(key) == interfacePool.end())
		return nullptr;

	return interfacePool[key];
}


/******************************************************************************
 * InterfaceManager::setTargetImage -- Set the target image.                  *
 *                                                                            *
 *    This will set all interfaces' target image. Call it before rendering.   *
 *                                                                            *
 * INPUT:   _pTargetImage                                                     *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
void InterfaceManager::setTargetImage(IMAGE* _pTargetImage)
{
	pTargetImage = _pTargetImage;
	for (auto it = interfacePool.begin(); it != interfacePool.end(); it++)
		(it->second)->setTargetImage(pTargetImage);
}


/******************************************************************************
 * InterfaceManager::launch -- Launch the startup interface.                  *
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
 *   2022/02/11 Tony : Created.                                               *
 *============================================================================*/
void InterfaceManager::launch()
{
	startup->launch();
}


/******************************************************************************
 * InterfaceManager::load -- Load all the interfaces.                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   file -- xml file name.                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
bool InterfaceManager::load(const char* file)
{
	XMLDoc doc;
	int ret = doc.LoadFile(file);

	if (ret != 0)
	{
		reportf(R"(Cannot open "data\ui.xml" - ERROR CODE: %s)", std::to_string(ret).c_str(), LOAD_INTF);
		return false;
	}

	XMLElement* root = doc.RootElement();
	XMLElement* child = root->FirstChildElement();
	Interface* intf;
	bool isStartup = false;

	while (child != NULL)
	{
		intf = newInterface(child);
		if (intf)
		{
			if (parseXMLAttribute(&isStartup, child->Attribute("startup")))
			{
				if (isStartup)
				{
					// No multiple start up interfaces.
					if (startup)
					{
						report("Multiple startup", LOAD_INTF);
						return false;
					}
					startup = intf;
				}
			}
			add(intf->getName(), intf);
		}
		else
			return false;

		child = child->NextSiblingElement();
	}

	if (!startup)
	{
		report("No startup", LOAD_INTF);
		return false;
	}

	return true;
}

bool InterfaceManager::unload()
{
	for (auto it = interfacePool.begin(); it != interfacePool.end(); it++)
		it->second->musicList.clear();

	return true;
}