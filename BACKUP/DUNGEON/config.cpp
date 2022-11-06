/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : config.cpp                                *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 11, 2022                          *
 *                                                                            *
 *                    Last Update : February 12, 2022                         *
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

#include <sstream>
#ifndef _DEBUG
#include <Windows.h>
#endif

#include "straw.h"
#include "error.h"
#include "config.h"
#include "auxilliary.h"


/********************************************************************
** Game settings.
*/
Setting setting;


/******************************************************************************
 * Setting::load -- Load settings.                                            *
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
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
void Setting::load()
{
	Straw straw(FILE_SETTING, L"Setting");

	difficulty = straw.suckInt(L"difficulty");
	difficulty = MAX(difficulty, 0);

	musicVolume = straw.suckDouble(L"music");
	musicVolume = MIN(musicVolume, 1.0);
	musicVolume = MAX(musicVolume, 0.0);

	soundVolume = straw.suckDouble(L"sound");
	soundVolume = MIN(soundVolume, 1.0);
	soundVolume = MAX(soundVolume, 0.0);
	
	int fps = straw.suckInt(L"fps");
	if (fps != 0)
		delay = (int)(1000.0 / (double)fps);
}


/******************************************************************************
 * Setting::save -- Save settings.                                            *
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
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
void Setting::save()
{
	Straw straw(FILE_SETTING, L"Setting");

	straw.exhale(difficulty, L"difficulty");
	straw.exhale(musicVolume, L"music");
	straw.exhale(soundVolume, L"sound");
}


/********************************************************************
** Global resource.
*/
Resource* gameResource[GAME_RES_NUM];


/******************************************************************************
**                          Specific Resources                               **
*******************************************************************************/

/******************************************************************************
 * HeroRes                                                                    *
 *                                                                            *
 *    Take hold of the properties of the figure.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/07 Tony : Created.                                               *
 *============================================================================*/
// Constructor called automatically.
static HeroRes heroResource[HERO_NUM];

HeroRes::HeroRes()
{
	token.file = FILE_FIGURE;
}

HeroRes::HeroRes(const std::wstring& section) : HeroRes()
{
	token.section = section;
	load();
}

bool HeroRes::load()
{
	return load(token.section);
}

bool HeroRes::load(const std::wstring& section)
{
	Straw straw(token.file, section);
	std::wstring value;
	Coord cp;

	// Figure properties.
	cp = straw.suckCoord(L"hp");
	maxHp = cp.x;
	hpGap = cp.y;
	cp = straw.suckCoord(L"mp");
	maxMp = cp.x;
	mpGap = cp.y;
	cp = straw.suckCoord(L"amor");
	maxAmor = cp.x;
	amorGap = cp.y;
	cp = straw.suckCoord(L"chi");
	maxChi = cp.x;
	chiGap = cp.y;

	offset = straw.suckCoord(L"offset");

	weaponOffset = straw.suckCoord(L"weaponOffset");

	value = straw.suckString(L"frame", L"no");
	if (value != L"no")
	{
		if (!frame.load(FILE_FRAME, value))
		{
			wreportf(FAILED_AT_FW, section.c_str(), LOAD_FRAME_W);
			return false;
		}
	}
	else
	{
		wreportf(LR"(Missing "frame" of %s)", section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	slotCapacity = straw.suckInt(L"slotCapacity");
	extractString(straw.suckString(L"weapon"), primaryWeaponList);

	// Object properties.
	width = straw.suckInt(L"width");
	height = straw.suckInt(L"height");
	imgOffset = straw.suckCoord(L"imgOffset");

	// Physical properties
	m = straw.suckInt(L"mass");
	mu = straw.suckDouble(L"mu");
	drag = straw.suckDouble(L"drag");
	strength = straw.suckDouble(L"strength");

	if (!straw.good())
	{
		wreportf(FAILED_AT_FW, section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	return true;	
}



/******************************************************************************
 * EnemyRes                                                                   *
 *                                                                            *
 *    Take hold of the properties of the figure.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/07 Tony : Created.                                               *
 *============================================================================*/
 // Constructor called automatically.
static EnemyRes enemyResource[ENEMY_NUM];

EnemyRes::EnemyRes()
{
	token.file = FILE_FIGURE;
}

EnemyRes::EnemyRes(const std::wstring& section) : EnemyRes()
{
	token.section = section;
	load();
}

bool EnemyRes::load()
{
	return load(token.section);
}

bool EnemyRes::load(const std::wstring& section)
{
	Straw straw(token.file, section);
	std::wstring value;
	Coord cp;

	// These properties can be omitted
	cp = straw.suckCoord(L"mp");
	maxMp = cp.x;
	mpGap = cp.y;
	cp = straw.suckCoord(L"amor");
	maxAmor = cp.x;
	amorGap = cp.y;
	cp = straw.suckCoord(L"chi");
	maxChi = cp.x;
	chiGap = cp.y;
	straw.clear();


	// Figure properties.
	cp = straw.suckCoord(L"hp");
	maxHp = cp.x;
	hpGap = cp.y;

	patrolRadius = straw.suckInt(L"patrol");
	price = straw.suckInt(L"price");

	offset = straw.suckCoord(L"offset");

	weaponOffset = straw.suckCoord(L"weaponOffset");

	value = straw.suckString(L"frame", L"no");
	if (value != L"no")
	{
		if (!frame.load(FILE_FRAME, value))
		{
			wreportf(FAILED_AT_FW, section.c_str(), LOAD_FRAME_W);
			return false;
		}
	}
	else
	{
		wreportf(LR"(Missing "frame" of %s)", section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	extractString(straw.suckString(L"weapon"), primaryWeaponList);

	// Object properties.
	width = straw.suckInt(L"width");
	height = straw.suckInt(L"height");
	imgOffset = straw.suckCoord(L"imgOffset");

	// Physical properties
	m = straw.suckInt(L"mass");
	mu = straw.suckDouble(L"mu");
	drag = straw.suckDouble(L"drag");
	strength = straw.suckDouble(L"strength");

	if (!straw.good())
	{
		wreportf(FAILED_AT_FW, section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	return true;
}



/******************************************************************************
 * WeaponRes                                                                  *
 *                                                                            *
 *    Take hold of the properties of the weapon.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/07 Tony : Created.                                               *
 *============================================================================*/
static WeaponRes weaponResource[WEAPON_NUM];

WeaponRes::WeaponRes()
{
	token.file = FILE_WEAPON;
}

WeaponRes::WeaponRes(const std::wstring& section) : WeaponRes()
{
	token.section = section;
	load();
}

bool WeaponRes::load()
{
	return load(token.section);
}

bool WeaponRes::load(const std::wstring& section)
{
	Straw straw(token.file, section);
	std::wstring value;

	name = straw.suckString(L"name");
	coolingTime = straw.suckInt(L"cooling");
	bulletType = straw.suckString(L"bullet");

	cost = straw.suckInt(L"cost");

	offset = straw.suckCoord(L"offset");
	muzzleOffset = straw.suckCoord(L"muzzleOffset");
	value = straw.suckString(L"frame", L"no");
	if (value != L"no")
	{
		if (!frame.load(FILE_FRAME, value))
		{
			wreportf(FAILED_AT_FW, section.c_str(), LOAD_FRAME_W);
			return false;
		}
	}
	else
	{
		wreportf(LR"(Missing "frame" of %s)", section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	width = straw.suckInt(L"width");
	height = straw.suckInt(L"height");
	imgOffset = straw.suckCoord(L"imgOffset");

	if (!straw.good())
	{
		wreportf(FAILED_AT_FW, section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	return true;
}



/******************************************************************************
 * BulletRes                                                                  *
 *                                                                            *
 *    Take hold of the properties of the bullet.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
static BulletRes bulletResource[BULLET_NUM];

BulletRes::BulletRes()
{
	token.file = FILE_BULLET;
}

BulletRes::BulletRes(const std::wstring& section) : BulletRes()
{
	token.section = section;
	load();
}

bool BulletRes::load()
{
	return load(token.section);
}

bool BulletRes::load(const std::wstring& section)
{
	Straw straw(token.file, section);
	std::wstring val;	// value will conflict with a member.

	speed = straw.suckDouble(L"speed");

	val = straw.suckString(L"frame", L"no");
	if (val != L"no")
	{
		if (!frame.load(FILE_FRAME, val))
		{
			wreportf(FAILED_AT_FW, section.c_str(), LOAD_FRAME_W);
			return false;
		}
	}
	else
	{
		wreportf(LR"(Missing "frame" of %s)", section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	blowForce = straw.suckDouble(L"blowForce");
	shockTime = straw.suckInt(L"shockTime");
	value = straw.suckInt(L"value");
	range = straw.suckInt(L"range");

	offset = straw.suckCoord(L"offset");

	width = straw.suckInt(L"width");
	height = straw.suckInt(L"height");
	imgOffset = straw.suckCoord(L"imgOffset");

	if (!straw.good())
	{
		wreportf(FAILED_AT_FW, section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	return true;
};



/******************************************************************************
 * BuffRes                                                                    *
 *                                                                            *
 *    Take hold of the properties of the buff.                                *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/08 Tony : Created.                                               *
 *============================================================================*/
static BuffRes buffResource[BUFF_NUM];

BuffRes::BuffRes()
{
	token.file = FILE_BUFF;
}

BuffRes::BuffRes(const std::wstring& section) : BuffRes()
{
	token.section = section;
	load();
}

bool BuffRes::load()
{
	return load(token.section);
}

bool BuffRes::load(const std::wstring& section)
{
	Straw straw(token.file, section);
	std::wstring val;

	speed = straw.suckDouble(L"speed");
	value = straw.suckInt(L"value");
	straw.clear();

	name = straw.suckString(L"name");

	val = straw.suckString(L"frame", L"no");
	if (val != L"no")
	{
		if (!frame.load(FILE_FRAME, val))
		{
			wreportf(FAILED_AT_FW, section.c_str(), LOAD_FRAME_W);
			return false;
		}
	}
	else
	{
		wreportf(LR"(Missing "frame" of %s)", section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	width = straw.suckInt(L"width");
	height = straw.suckInt(L"height");
	offset = straw.suckCoord(L"offset");
	imgOffset = straw.suckCoord(L"imgOffset");
	
	if (!straw.good())
	{
		wreportf(FAILED_AT_FW, section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	return true;
}



/******************************************************************************
 * BrickRes                                                                   *
 *                                                                            *
 *    Take hold of the properties of the brick.                               *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/09 Tony : Created.                                               *
 *============================================================================*/
static BrickRes brickResource[BRICK_NUM];

BrickRes::BrickRes()
{
	token.file = FILE_TERRAIN;
}

BrickRes::BrickRes(const std::wstring& section) : BrickRes()
{
	token.section = section;
	load();
}

bool BrickRes::load()
{
	return load(token.section);
}

bool BrickRes::load(const std::wstring& section)
{
	Straw straw(token.file, section);
	std::wstring value;

	value = straw.suckString(L"image", L"no");
	if (value != L"no")
	{
		if (!fetchImage(&image, FILE_FRAME, value))
		{
			wreportf(FAILED_AT_FW, section.c_str(), LOAD_FRAME_W);
			return false;
		}
	}

	value = straw.suckString(L"frame", L"no");
	if (value != L"no")
	{
		if (!frame.load(FILE_FRAME, value))
		{
			wreportf(FAILED_AT_FW, section.c_str(), LOAD_FRAME_W);
			return false;
		}
	}
	straw.clear();

	width = straw.suckInt(L"width");
	height = straw.suckInt(L"height");
	offset = straw.suckCoord(L"offset");
	imgOffset = straw.suckCoord(L"imgOffset");

	if (!straw.good())
	{
		wreportf(FAILED_AT_FW, section.c_str(), LOAD_RESOURCE_W);
		return false;
	}

	return true;
}





/******************************************************************************
 * fetchImage -- Fetch a image from a certain ini file.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   imge    -- The image to fetch.                                    *
 *          file    -- The .ini file.                                         *
 *          section -- The section of the image.                              *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/09 Tony : Created.                                               *
 *============================================================================*/
bool fetchImage(IMAGE* img, std::wstring file, std::wstring section)
{
	static IMAGE tempImage;

	Straw straw(file, section);

	int width = straw.suckInt(L"width");
	int height = straw.suckInt(L"height");
	Coord start = straw.suckCoord(L"start");
	std::wstring src = straw.suckString(L"src", L"no");

	if (src == L"no")
		return false;

	src = PATH_IMAGE + src;
	if (!isAccessible(src.c_str()))
		return false;

	loadimage(&tempImage, src.c_str());
	SetWorkingImage(&tempImage);
	getimage(img, start.x, start.y, width, height);
	SetWorkingImage(NULL);

	return true;
}


/******************************************************************************
 * loadResource -- Load all resources.                                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return status. 0 means successful.                                *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/11 Tony : Created.                                               *
 *============================================================================*/
int loadResource()
{
	setting.load();

	// Hero resource.
	if (!heroResource[HERO_YONY].load(L"Yony"))
	{
		reportf(FAILED_TO_LOAD_F, "Yony", LOAD_RESOURCE);
		return RES_HERO_YONY;
	}
	gameResource[RES_HERO_YONY] = &heroResource[HERO_YONY];


	// Enemy resource.
	if (!enemyResource[ENEMY_SQUARE].load(L"Square"))
	{
		reportf(FAILED_TO_LOAD_F, "Square", LOAD_RESOURCE);
		return RES_ENEMY_SQUARE;
	}
	if (!enemyResource[ENEMY_SQUAREX].load(L"SquareX"))
	{
		reportf(FAILED_TO_LOAD_F, "SquareX", LOAD_RESOURCE);
		return RES_ENEMY_SQUAREX;
	}
	if (!enemyResource[ENEMY_MEGA].load(L"Mega"))
	{
		reportf(FAILED_TO_LOAD_F, "Mega", LOAD_RESOURCE);
		return RES_ENEMY_MEGA;
	}

	gameResource[RES_ENEMY_SQUARE] = &enemyResource[ENEMY_SQUARE];
	gameResource[RES_ENEMY_SQUAREX] = &enemyResource[ENEMY_SQUAREX];
	gameResource[RES_ENEMY_MEGA] = &enemyResource[ENEMY_MEGA];



	// Weapon resource.
	if (!weaponResource[WEAPON_PISTOL].load(L"Pistol"))
	{
		reportf(FAILED_TO_LOAD_F, "Pistol", LOAD_RESOURCE);
		return RES_WEAPON_PISTOL;
	}
	if (!weaponResource[WEAPON_RIFLE].load(L"Rifle"))
	{
		reportf(FAILED_TO_LOAD_F, "Rifle", LOAD_RESOURCE);
		return RES_WEAPON_RIFLE;
	}
	if (!weaponResource[WEAPON_FLAME].load(L"Flame"))
	{
		reportf(FAILED_TO_LOAD_F, "Flame", LOAD_RESOURCE);
		return RES_WEAPON_FLAME;
	}
	if (!weaponResource[WEAPON_FLAMEX].load(L"FlameX"))
	{
		reportf(FAILED_TO_LOAD_F, "FlameX", LOAD_RESOURCE);
		return RES_WEAPON_FLAME;
	}

	gameResource[RES_WEAPON_PISTOL] = &weaponResource[WEAPON_PISTOL];
	gameResource[RES_WEAPON_RIFLE] = &weaponResource[WEAPON_RIFLE];
	gameResource[RES_WEAPON_FLAME] = &weaponResource[WEAPON_FLAME];
	gameResource[RES_WEAPON_FLAMEX] = &weaponResource[WEAPON_FLAMEX];


	// Buffs resource.
	if (!buffResource[BUFF_CREATE].load(L"Create"))
	{
		reportf(FAILED_TO_LOAD_F, "Create", LOAD_RESOURCE);
		return RES_BUFF_CREATE;
	}
	if (!buffResource[BUFF_GOLD].load(L"Gold"))
	{
		reportf(FAILED_TO_LOAD_F, "Gold", LOAD_RESOURCE);
		return RES_BUFF_GOLD;
	}
	if (!buffResource[BUFF_AMMO].load(L"Ammo"))
	{
		reportf(FAILED_TO_LOAD_F, "Ammo", LOAD_RESOURCE);
		return RES_BUFF_AMMO;
	}
	if (!buffResource[BUFF_PORTAL].load(L"Portal"))
	{
		reportf(FAILED_TO_LOAD_F, "Portal", LOAD_RESOURCE);
		return RES_BUFF_PORTAL;
	}

	gameResource[RES_BUFF_CREATE] = &buffResource[BUFF_CREATE];
	gameResource[RES_BUFF_GOLD] = &buffResource[BUFF_GOLD];
	gameResource[RES_BUFF_AMMO] = &buffResource[BUFF_AMMO];
	gameResource[RES_BUFF_PORTAL] = &buffResource[BUFF_PORTAL];


	// Bricks resource
	if (!brickResource[BRICK_FLOOR].load(L"Floor"))
	{
		reportf(FAILED_TO_LOAD_F, "Floor", LOAD_RESOURCE);
		return RES_BRICK_FLOOR;
	}
	if (!brickResource[BRICK_WALL].load(L"Wall"))
	{
		reportf(FAILED_TO_LOAD_F, "Wall", LOAD_RESOURCE);
		return RES_BRICK_WALL;
	}
	if (!brickResource[BRICK_GATE].load(L"Gate"))
	{
		reportf(FAILED_TO_LOAD_F, "", LOAD_RESOURCE);
		return RES_BRICK_GATE;
	}

	gameResource[RES_BRICK_FLOOR] = &brickResource[BRICK_FLOOR];
	gameResource[RES_BRICK_WALL] = &brickResource[BRICK_WALL];
	gameResource[RES_BRICK_GATE] = &brickResource[BRICK_GATE];


	// Bullet resource
	if (!bulletResource[BULLET_PEPPER].load(L"Pepper"))
	{
		reportf(FAILED_TO_LOAD_F, "Pepper", LOAD_RESOURCE);
		return RES_BULLET_PEPPER;
	}
	if (!bulletResource[BULLET_FIRE].load(L"Fire"))
	{
		reportf(FAILED_TO_LOAD_F, "Fire", LOAD_RESOURCE);
		return RES_BULLET_FIRE;
	}

	gameResource[RES_BULLET_PEPPER] = &bulletResource[BULLET_PEPPER];
	gameResource[RES_BULLET_FIRE] = &bulletResource[BULLET_FIRE];

#ifndef _DEBUG
	Sleep(1000);
#endif

	return 0;
}



/******************************************************************************
 * load -- Load all things of the game.                                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return status. 0 means successful.                                *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/11 Tony : Created.                                               *
 *============================================================================*/
int load()
{
	return loadResource();
}