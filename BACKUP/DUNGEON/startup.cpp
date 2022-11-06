/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : startup.cpp                               *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : February 15, 2022                         *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For the pre-process and start up of the programme.                       *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include <ctime>
#include <cstdlib>
#include <Windows.h>

#include "error.h"
#include "image.h"
#include "config.h"
#include "startup.h"
#include "command.h"
#include "interface.h"


extern Canvas canvas;
extern Command command;

extern Setting setting;

static InterfaceManager interfaceManager;


/******************************************************************************
 * initialize -- Initialize global ones.                                      *
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
bool initialize()
{
	srand((unsigned)time(NULL));

	canvas.create(CANVAS_WIDTH, CANVAS_HEIGHT);
	command.pLogicalConvert = std::bind(&Canvas::convert, &canvas, std::placeholders::_1);

	if (!initAudio())
		return false;

	setting.load();

	return true;
}

bool close()
{
	return closeAudio();
}


/******************************************************************************
 * render -- Render all interfaces.                                           *
 *                                                                            *
 *    Load all interfaces, and then inter-connect the widgets in them. Hmm... *
 *    manually. :(                                                            *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether succeeded or not.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
bool render()
{
	if (!interfaceManager.load(FILE_UI.c_str()))
	{
		reportf(FAILED_TO_LOAD_F, FILE_UI.c_str(), "Loading interface");
		return false;
	}

	interfaceManager.setTargetImage(canvas.getImage());

	Interface* intf;
	WidgetManager* mgr;
	Widget* w;

	auto delay = [](int milliseconds)->int { Sleep(milliseconds); return 0; };

	/*
	** Render load interface.
	*/
	intf = interfaceManager.get("load");
	if (!intf)
	{
		report("Missing load interface", RENDER_INTF);
		return false;
	}
	dynamic_cast<TaskInterface*>(intf)->setTask(std::bind(&load));

	/*
	** Render main interface.
	*/
	intf = interfaceManager.get("main");
	if (!intf)
	{
		report("Missing main interface", RENDER_INTF);
		return false;
	}
	mgr = intf->getWidget();

	w = mgr->get("play");
	if (!w)
	{
		report(R"(Missing "play" button in main)", RENDER_INTF);
		return false;
	}
	w = mgr->get("help");
	if (!w)
	{
		report(R"(Missing "help" button in main)", RENDER_INTF);
		return false;
	}
	w = mgr->get("exit");
	if (!w)
	{
		report(R"(Missing "exit" button in main)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Button*>(w)->onClick(intf->getTerminate());


	/*
	** Render help interface.
	*/
	intf = interfaceManager.get("help");
	if (!intf)
	{
		report("Missing help interface", RENDER_INTF);
		return false;
	}
	mgr = intf->getWidget();

	w = mgr->get("back");
	if (!w)
	{
		report(R"(Missing "back" button in help)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Button*>(w)->onClick(intf->getTerminate());


	/*
	**Render game interface.
	*/
	intf = interfaceManager.get("game");
	if (!intf)
	{
		report("Missing game interface", RENDER_INTF);
		return false;
	}
	mgr = intf->getWidget();

	w = mgr->get("board");
	if (!w)
	{
		report(R"(Missing "board" board in game)", RENDER_INTF);
		return false;
	}
	w = mgr->get("hp");
	if (!w)
	{
		report(R"(Missing "hp" progress bar in game)", RENDER_INTF);
		return false;
	}
	w = mgr->get("amor");
	if (!w)
	{
		report(R"(Missing "amor" progress bar in game)", RENDER_INTF);
		return false;
	}
	w = mgr->get("mp");
	if (!w)
	{
		report(R"(Missing "hp" progress bar in game)", RENDER_INTF);
		return false;
	}


	/*
	** Render options interface.
	*/
	intf = interfaceManager.get("options");
	if (!intf)
	{
		report(R"(Missing "version" interface)", RENDER_INTF);
		return false;
	}
	intf->onUnLoad = std::bind(&Setting::save, &setting);

	mgr = intf->getWidget();

	w = mgr->get("back");
	if (!w)
	{
		report(R"(Missing "back" button in options)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Button*>(w)->onClick(intf->getTerminate());

	w = mgr->get("minus");
	if (!w)
	{
		report(R"(Missing "minus" button in options)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Button*>(w)->onClick(std::bind(&Setting::minusDifficulty, &setting));
	w = mgr->get("plus");
	if (!w)
	{
		report(R"(Missing "plus" button in options)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Button*>(w)->onClick(std::bind(&Setting::addDifficulty, &setting));
	
	w = mgr->get("text");
	if (!w)
	{
		report(R"(Missing "text" textarea in options)", RENDER_INTF);
		return false;
	}
	auto setText = std::bind(&TextArea::setText, dynamic_cast<TextArea*>(w), std::placeholders::_1);
	auto changeText = [=]()->void { setText(DIFFICULTY_TEXT[setting.difficulty]); };
	changeText();

	w = mgr->get("link");
	if (!w)
	{
		report(R"(Missing "link" detector in options)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Detector*>(w)->onDetect(changeText);

	w = mgr->get("volume");
	if (!w)
	{
		report(R"(Missing "volume" dragbar in options)", RENDER_INTF);
		return false;
	}
	dynamic_cast<DragBar*>(w)
		->onChange(std::bind(&Setting::setMusicVolume, &setting, std::placeholders::_1))
		->setValue(setting.musicVolume);

	/*
	** Render in-game options.
	*/
	intf = interfaceManager.get("in-options");
	if (!intf)
	{
		report(R"(Missing "in-options" interface)", RENDER_INTF);
		return false;
	}
	mgr = intf->getWidget();

	w = mgr->get("back");
	if (!w)
	{
		report(R"(Missing "back" button in ingame-options)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Button*>(w)->onClick(intf->getTerminate());

	w = mgr->get("text");
	if (!w)
	{
		report(R"(Missing "text" textarea in ingame-options)", RENDER_INTF);
		return false;
	}
	auto setText2 = std::bind(&TextArea::setText, dynamic_cast<TextArea*>(w), std::placeholders::_1);
	auto changeText2 = [=]()->void { setText2(DIFFICULTY_TEXT[setting.difficulty]); };
	changeText2();

	w = mgr->get("link");
	if (!w)
	{
		report(R"(Missing "link" detector in ingame-options)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Detector*>(w)->onDetect(changeText2);

	w = mgr->get("volume");
	if (!w)
	{
		report(R"(Missing "volume" dragbar in ingame-options)", RENDER_INTF);
		return false;
	}
	dynamic_cast<DragBar*>(w)
		->onChange(std::bind(&Setting::setMusicVolume, &setting, std::placeholders::_1))
		->setValue(setting.musicVolume);


	/*
	** Render version interface.
	*/
	intf = interfaceManager.get("version");
	if (!intf)
	{
		report(R"(Missing "version" interface)", RENDER_INTF);
		return false;
	}
	mgr = intf->getWidget();

	w = mgr->get("back");
	if (!w)
	{
		report(R"(Missing "back" button in version)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Button*>(w)->onClick(intf->getTerminate());


	/*
	** Render pause interface.
	*/
	intf = interfaceManager.get("pause");
	if (!intf)
	{
		report(R"(Missing "pause" interface)", RENDER_INTF);
		return false;
	}
	mgr = intf->getWidget();

	w = mgr->get("back");
	if (!w)
	{
		report(R"(Missing "back" button in pause)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Button*>(w)->onClick(intf->getTerminate());
	w = mgr->get("detector");
	if (!w)
	{
		report(R"(Missing "detector" detector in pause)", RENDER_INTF);
		return false;
	}
	dynamic_cast<Detector*>(w)->setCommand(CMD_PAUSE)->onDetect(intf->getTerminate());
	w = mgr->get("options");
	if (!w)
	{
		report(R"(Missing "options" button in pause)", RENDER_INTF);
		return false;
	}

	/*
	** Render victory interface.
	*/
	intf = interfaceManager.get("victory");
	if (!intf)
	{
		report(R"(Missing "victory" interface)", RENDER_INTF);
		return false;
	}
	dynamic_cast<TaskInterface*>(intf)->setTask(std::bind(delay, 3000));


	/*
	** Render lost interface.
	*/
	intf = interfaceManager.get("lost");
	if (!intf)
	{
		report(R"(Missing "lost" interface)", RENDER_INTF);
		return false;
	}
	dynamic_cast<TaskInterface*>(intf)->setTask(std::bind(delay, 3000));

	return true;
}


/******************************************************************************
 * arrange -- Arrange all interfaces.                                         *
 *                                                                            *
 *    This one connects all interfaces.                                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether succeeded or not.                                  *
 *                                                                            *
 * WARNINGS:  This MUST be called after render to make sure that all the      *
 *            interfaces and widgets are valid.                               *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
bool arrange()
{
	InterfaceManager& mgr = interfaceManager;

	// At load
	mgr["load"]->pNextInterface = mgr["main"];

	// At main
	dynamic_cast<Button*>((*mgr["main"])["help"])->onClick(mgr["help"]->getLaunch());
	dynamic_cast<Button*>((*mgr["main"])["play"])->onClick(mgr["game"]->getLaunch());
	dynamic_cast<Button*>((*mgr["main"])["options"])->onClick(mgr["options"]->getLaunch());
	dynamic_cast<Button*>((*mgr["main"])["version"])->onClick(mgr["version"]->getLaunch());
	
	// At help
	mgr["help"]->pPrevInterface = mgr["main"];

	// At game
	mgr["game"]->pPrevInterface = mgr["main"];
	dynamic_cast<GameInterface*>(mgr["game"])
		->setVictory(mgr["victory"])
		->setLost(mgr["lost"]);
	dynamic_cast<Detector*>((*mgr["game"])["pause"])
		->setCommand(CMD_PAUSE)
		->onDetect(mgr["pause"]->getLaunch());

	// At options
	mgr["options"]->pPrevInterface = mgr["main"];

	// At Version
	mgr["version"]->pPrevInterface = mgr["main"];

	// At pause
	mgr["pause"]->pPrevInterface = mgr["game"];
	dynamic_cast<Button*>((*mgr["pause"])["options"])->onClick(mgr["in-options"]->getLaunch());

	// At in-options
	mgr["in-options"]->pPrevInterface = mgr["pause"];

	// At victory
	mgr["victory"]->pPrevInterface = mgr["main"];

	// At lost
	mgr["lost"]->pPrevInterface = mgr["main"];

	return true;
}


/******************************************************************************
 * load -- Load every thing of the game.                                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether succeeded or not.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/15 Tony : Created.                                               *
 *============================================================================*/
bool loadInterface()
{
	if (!render())
		return false;

	if (!arrange())
		return false;

	return true;
}

bool unloadInterface()
{
	interfaceManager.unload();

	return true;
}

/******************************************************************************
 * launch -- Launch the whole game.                                           *
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
void launch()
{
	interfaceManager.launch();

	canvas.close();
}