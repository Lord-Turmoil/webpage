/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : config.h                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 11, 2022                          *
 *                                                                            *
 *                    Last Update : February 18, 2022                         *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For the whole game's configuration. Constants related to resources.      *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _CONFIG_H_     
#define _CONFIG_H_      

#include <ctime>
#include <vector>
#include <string>
#include <climits>
#include <easyx.h>
#include <Windows.h>

#include "define.h"
#include "animation.h"
#include "auxilliary.h"


/******************************************************************************
*                             File Sturcture                                  *
* --------------------------------------------------------------------------- *
* res\         -- Game resources.                                             *
*   images\      -- Images.                                                   *
*   sounds\      -- Sounds.                                                   *
* data\        -- Game data.                                                  *
*   figure.ini   -- Figure's resource property.                               *
*   weapon.ini   -- Weapon's resource property.                               *
*   bullet.ini   -- Bullet's resource property.                               *
*   buff.ini     -- Buff's resource property.                                 *
*   terrain.ini  -- Terrain's resource property.                              *
*   custom.ini   -- Modified data, player's progress.                         *
*   setting.ini  -- Game settings.                                            *
*   frame.ini    -- Frame image info.                                         *
*   ui.xml       -- Game UI layout.                                           *
* save\        -- Saved progress(on hold).                                    *
*   info.ini     -- Saving slots' state.                                      *
*   story.sav    -- Story mode save.                                          *
*   death.sav    -- Death mode save.                                          *
* screenshot\  -- In game screen shots.                                       *
*******************************************************************************/

// Default paths.
const std::wstring PATH_RES		= L".\\res\\";
const std::wstring PATH_DATA	= L".\\data\\";
const std::wstring PATH_SAVE	= L".\\save\\";
const std::wstring PATH_SCREEN	= L".\\screenshot\\";

const std::wstring PATH_IMAGE	= PATH_RES + L"images\\";
const std::wstring PATH_SOUND	= PATH_RES + L"sounds\\";

// Default files.
const std::wstring FILE_FIGURE		= PATH_DATA + L"figure.ini";
const std::wstring FILE_WEAPON		= PATH_DATA + L"weapon.ini";
const std::wstring FILE_BULLET		= PATH_DATA + L"bullet.ini";
const std::wstring FILE_BUFF		= PATH_DATA + L"buff.ini";
const std::wstring FILE_TERRAIN		= PATH_DATA + L"terrain.ini";
const std::wstring FILE_CUSTOM		= PATH_DATA + L"custom.ini";
const std::wstring FILE_SETTING		= PATH_DATA + L"setting.ini";
const std::wstring FILE_FRAME		= PATH_DATA + L"frame.ini";
// const std::wstring FILE_UI		= PATH_DATA + L"ui.xml";
// tinyxml doesn't support unicode...
const std::string FILE_UI			= ".\\data\\ui.xml";

const std::wstring FILE_INFO	= PATH_SAVE + L"info.ini";
const std::wstring FILE_STORY	= PATH_SAVE + L"story.sav";
const std::wstring FILE_DEATH	= PATH_SAVE + L"death.sav";



/********************************************************************
** Game settings.
*/
const int MAX_DIFFICULTY = 3;

const std::wstring DIFFICULTY_TEXT[MAX_DIFFICULTY] = {
	L"Normal",
	L"Hard",
	L"Insane" };

struct Setting
{
	int difficulty;

	/*
	** The volume of the background music.
	*/
	double musicVolume;

	/*
	** The volume of the sounds such as bullet's explosion.
	*/
	double soundVolume;

	int delay;

	Setting() : delay(DELAY) {}

	void setDifficulty(int dif)
	{
		difficulty = dif;
	}

	void setMusicVolume(double volume)
	{
		musicVolume = volume;
	}

	void setSoundVolume(double volume)
	{
		soundVolume = volume;
	}

	void addDifficulty()
	{
		difficulty++;
		if (difficulty >= MAX_DIFFICULTY)
			difficulty = 0;
	}
	
	void minusDifficulty()
	{
		difficulty--;
		if (difficulty < 0)
			difficulty = MAX_DIFFICULTY - 1;
	}

	void load();
	void save();
};



/********************************************************************
** Resource ids.
*/
enum GameResourceId : unsigned
{
	RES_UNKNOWN = 0,

	// Heroes.
	RES_HERO_YONY,

	// Enemies.
	RES_ENEMY_SQUARE,
	RES_ENEMY_SQUAREX,
	RES_ENEMY_MEGA,
	
	// Weapons.
	RES_WEAPON_PISTOL,
	RES_WEAPON_RIFLE,
	RES_WEAPON_FLAME,
	RES_WEAPON_FLAMEX,

	// Buffs.
	RES_BUFF_CREATE,
	RES_BUFF_GOLD,
	RES_BUFF_AMMO,
	RES_BUFF_PORTAL,

	// Bricks.
	RES_BRICK_FLOOR,
	RES_BRICK_WALL,
	RES_BRICK_GATE,

	// Bullets.
	RES_BULLET_PEPPER,
	RES_BULLET_FIRE,

	GAME_RES_NUM,

	/*
	** 2022/01/25
	** Well, this is for those really specific objects which
	** don't need a resId to be assigned.
	*/
	RES_VOID
};


/********************************************************************
** Resource struct. Include .ini filename, section name, and address
** of the resource image.
*/
struct ResourceToken
{
	std::wstring file;
	std::wstring section;
};


struct Resource
{
	ResourceToken token;

	virtual bool load() = 0;
	virtual bool load(const std::wstring& section) = 0;
};


/********************************************************************
** Hero's resources.
*/
struct HeroRes : public Resource
{
	HeroRes();
	HeroRes(const std::wstring& section);

	virtual bool load();
	virtual bool load(const std::wstring& section);

	// Figure properties.
	int maxHp;
	clock_t hpGap;
	int maxMp;
	clock_t mpGap;
	int maxAmor;
	clock_t amorGap;
	int maxChi;
	clock_t chiGap;

	Coord offset;

	Frame frame;

	int slotCapacity;
	std::vector<std::wstring> primaryWeaponList;

	Coord weaponOffset;

	// Object properties.
	int width;
	int height;
	Coord imgOffset;

	// Physical properties
	int m;
	double mu;
	double drag;
	double strength;
};


/********************************************************************
** Enemy's resource.
*/
struct EnemyRes : public Resource
{
	EnemyRes();
	EnemyRes(const std::wstring& section);

	virtual bool load();
	virtual bool load(const std::wstring& section);

	// Figure properties.
	int maxHp;
	clock_t hpGap;
	int maxMp;
	clock_t mpGap;
	int maxAmor;
	clock_t amorGap;
	int maxChi;
	clock_t chiGap;

	int patrolRadius;
	int price;

	Coord offset;

	Frame frame;

	std::vector<std::wstring> primaryWeaponList;

	Coord weaponOffset;

	// Object properties.
	int width;
	int height;
	Coord imgOffset;

	// Physical properties
	int m;
	double mu;
	double drag;
	double strength;
};


/********************************************************************
** Weapon resources.
*/
struct WeaponRes : public Resource
{
	WeaponRes();
	WeaponRes(const std::wstring& section);

	virtual bool load();
	virtual bool load(const std::wstring& section);

	std::wstring name;
	clock_t coolingTime;
	std::wstring bulletType;

	int cost;

	Frame frame;

	Coord offset;
	Coord muzzleOffset;

	int width;
	int height;
	Coord imgOffset;
};


/********************************************************************
** Bullet's resource.
*/
struct BulletRes : Resource
{
	BulletRes();
	BulletRes(const std::wstring& section);

	virtual bool load();
	virtual bool load(const std::wstring& section);

	// bullet property
	double speed;

	Coord offset;

	Frame frame;

	// damage
	double blowForce;
	clock_t shockTime;
	int value;
	int range;

	int width;
	int height;
	Coord imgOffset;
};


/********************************************************************
** Buff's resource.
*/
struct BuffRes : public Resource
{
	BuffRes();
	BuffRes(const std::wstring& section);

	virtual bool load();
	virtual bool load(const std::wstring& section);

	std::wstring name;

	Coord offset;

	Frame frame;

	double speed;
	int value;

	int width;
	int height;
	Coord imgOffset;
};


/********************************************************************
** Brick's resouces.
*/
struct BrickRes : public Resource
{
	BrickRes();
	BrickRes(const std::wstring& section);

	virtual bool load();
	virtual bool load(const std::wstring& section);

	Coord offset;

	IMAGE image;	// only for floor
	Frame frame;

	int width;
	int height;
	Coord imgOffset;
};



/********************************************************************
** To fetch a image from FILE_FRAME.
*/
bool fetchImage(IMAGE* img, std::wstring file, std::wstring section);


/********************************************************************
** Load all resources.
*/
int loadResource();

int load();

#endif