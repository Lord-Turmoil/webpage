/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : dungeon.h                                 *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 20, 2022                          *
 *                                                                            *
 *                    Last Update : January 28, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   This is the main process of the game. And there are two modes, the death *
 *   match and the campaign. What's more, there is a launcher to launch the   *
 *   dungeon.                                                                 *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include <easyx.h>
#include <functional>

#include "buff.h"
#include "camera.h"
#include "figure.h"
#include "weapon.h"
#include "terrain.h"
#include "auxilliary.h"


/********************************************************************
** Some constant info.
*/

/*
** Different stages should have different styles, and contains
** some sections.
*/
const int STAGE_NUM = 1;

/*
** Each stage contains several sections, and each section is
** one level.
*/
const int SECTION_NUM = 5;

// The final level, pass this and win.
const int FINAL_LEVEL = STAGE_NUM * SECTION_NUM;


/********************************************************************
** The mode of the dungeon.
*/
enum class DungeonType
{
	DUNGEON_CAMPAIGN,
	DUNGEON_DEATH,

	DUNGEON_NUM
};


/********************************************************************
** The state of the game, or, the state of the dungeon. :)
*/
struct DungeonState
{
	bool isVictorious : 1;
	bool isLost : 1;

	/*
	** If isLevelup, then the dungeon's level will... up. :)
	** It will then be set to false immediately.
	*/
	bool isLevelup : 1;

	DungeonState()
		: isVictorious(false), isLost(false), isLevelup(false) {}
};


/********************************************************************
** The attribute of the dungeon. Well... some properties, I guess.
*/
struct DungeonAttribute
{
	int stage;
	int section;
	int difficulty;
	int score;
	int gold;

	bool isEnd : 1;
	bool hasBoss : 1;

	DungeonAttribute() : stage(1), section(1), difficulty(0), score(0), gold(0), isEnd(false), hasBoss(false) {}

	void set(int _stage = 1, int _section = 1, int _difficulty = 0, int _score = 0, int _gold = 0)
	{
		stage = _stage;
		section = _section;
		difficulty = _difficulty;
		score = _score;
		gold = _gold;
	}

	void levelup()
	{
		section++;
		stage = section / SECTION_NUM;
		section %= SECTION_NUM;

		isEnd = (stage >= STAGE_NUM) ? true : false;
		hasBoss = (section == SECTION_NUM - 1) ? true : false;

		score += stage * 100;
	}
};

enum DungeonToken
{
	RUNNING,
	LOST,
	VICTORIOUS,
	UPGRADE
};

/********************************************************************
** Dungeon is the base class of the game.
*/
class Dungeon
{
public:
	Dungeon(DungeonType _type);
	~Dungeon();

	DungeonAttribute& getAttribute();
	DungeonState& getState();

	void generateBuff(
		int createNum = 0,
		int ammoNum = 0,
		Coord ammoPos = { 0, 0 },
		int goldNum = 0,
		Coord goldPos = { 0, 0 });

	bool init(
		Coord _pos,
		int _width,
		int _height,
		Hero* _hero,
		int _difficulty,
		IMAGE* _pTargetImage);

	void addScore(int score);
	void addGold(int gold);

	void levelup();

	virtual bool launch() = 0;

	virtual DungeonToken run() = 0;
	virtual void draw() = 0;

protected:
	friend class Launcher;

	virtual void upgrade() = 0;

	void generateEnemy();
	void generateEnemy(EnemyLevel level);

	void generateCreate(int num);
	void generateAmmo(int num, Coord ammoPos);
	void generateGold(int num, Coord goldPos);

	DungeonType type;
	DungeonState state;
	DungeonAttribute attribute;
	
	/*
	** The player of the game.
	*/
	Hero* hero;

	Space* curSpace;

	/*
	** This will point to the current space's brick
	** pool.
	*/
	PhysicalObjectPool* brickPool;

	PhysicalObjectPool enemyPool;
	BuffPool buffPool;
	BulletPool heroBulletPool;
	BulletPool enemyBulletPool;

	Terrain terrain;

	/*
	** Some members related to drawing.
	*/
	Camera camera;
	IMAGE* pTargetImage;

	/*
	** Some callbacks...
	*/
	std::function<void(int, int, Coord, int, Coord)> pOnGenerate;
};


/********************************************************************
** The campaign mode has a lot of spaces to fight.
*/
class DungeonCampaign : public Dungeon
{
public:
	DungeonCampaign();
	~DungeonCampaign();

	virtual bool launch();
	virtual DungeonToken run();
	virtual void draw();

private:
	friend class Launcher;
	
	virtual void upgrade();

	Portal* portal;
};


/********************************************************************
** The death match mode only has one arena and the hero will fight
** till death.
*/
class DungeonDeath : public Dungeon
{
public:
	DungeonDeath();
	~DungeonDeath();

	virtual bool launch();
	virtual DungeonToken run();
	virtual void draw();

private:
	friend class Launcher;

	virtual void upgrade();
};


/********************************************************************
** The launcher will first collect some info like which hero is 
** selected and the mode of the game, and then launch the game.
*/
class Launcher
{
public:
	Launcher();
	~Launcher();

	void setHero(HeroType _heroType);
	void setMode(DungeonType _type);
	void setTargetImage(IMAGE* _pTargetImage);

	std::function<void(HeroType)> getHeroCallback();
	std::function<void(DungeonType)> getModeCallback();

	Hero* getHero();
	Dungeon* getDungeon();

	/*
	** 2022/02/19
	** The machanism to draw image differs between the camera
	** and UI widget, so UI cannot display on higher layer than
	** the camera if it use the same target image with the
	** camera.
	** Get the image of the camera of the game, for UI widgets
	** to show on it.
	*/
	IMAGE* getImage();

	bool launch();

	DungeonToken run();
	void draw();

private:
	DungeonType type;

	Dungeon* pDungeon;
	Hero* pHero;

	IMAGE* pTargetImage;
};

#endif