/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : figure.h                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 11, 2022                          *
 *                                                                            *
 *                    Last Update : February 17, 2022                         *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For game figures. Including hero, enemy and the boss.                    *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <ctime>
#include <easyx.h>
#include <functional>

#include "config.h"
#include "bullet.h"
#include "weapon.h"
#include "camera.h"
#include "define.h"
#include "object.h"
#include "command.h"
#include "terrain.h"
#include "animation.h"


/********************************************************************
** Type of the figures.
*/
enum class FigureType
{
	HERO,
	ENEMY
};


/********************************************************************
** Base class of all figures. Well, the function to open fire is 
** binded with the weapon, not the figure.
*/
class Figure : public PhysicalObject
{
public:
	Figure(FigureType _figureType);
	virtual ~Figure();
	
	void onFire(std::function<void(Bullet*)> callback);

	std::vector<WeaponType>& getPrimaryWeapon();
	void pickupWeapon(Weapon* weapon);

	Coord getWeaponPos() const;

	/*
	** Load a figure from pre-loaded info.
	*/
	virtual void load(GameResourceId resId = RES_VOID) = 0;

	virtual void draw(Camera& cam);

	virtual void hurt(const Damage& damage) = 0;
	
	void healHp(int val);
	void healMp(int val);

	virtual void move();

protected:

	virtual void skill() = 0;
	virtual void autoHeal();

	/*
	** Well... this is done when the figure is died.
	*/
	virtual void perish() = 0;

	FigureType figureType;

	/*
	** Properties:
	** [0] is the current hp(mp, ...),
	** [1] is the max hp(mp, ...),
	** xxGap[0] is the last timestamp of the regeneration.
	** xxGap[1] is the regenerating gap, how many ms to regain 1 point,
	**      0 means no auto regain.
	*/
	int hp[2];
	clock_t hpGap[2];
	int mp[2];
	clock_t mpGap[2];
	int amor[2];
	clock_t amorGap[2];
	int chi[2];
	clock_t chiGap[2];

	/*
	** 2022/01/23
	** The facing of the figure. 0 is for right.
	*/
	int facing;

	/*
	** The function to call when open fire. To add bullets to
	** the bullet pool.
	*/
	std::function<void(Bullet*)> pOnFire;

	WeaponSlot weaponSlot;
	Coord weaponOffset;

	/*
	** The primary weapon of the figure, which is possessed at
	** the very beginning.
	*/
	std::vector<WeaponType> primaryWeaponList;
};


/********************************************************************
** Base class of heroes.
*/
enum HeroState
{
	HERO_INIT = 0,
	HERO_STAND,
	HERO_MOVE,
	HERO_HURT,
	HERO_DEAD,
	HERO_INVALID,
	HERO_END,

	HERO_STATE_NUM,
};

const HeroState HERO_STATE_MACHINE[HERO_STATE_NUM][HERO_STATE_NUM] = {
	{ HERO_INIT,	HERO_INIT,		HERO_INIT,		HERO_INIT,		HERO_INIT,		HERO_INVALID,	HERO_STAND	},
	{ HERO_INIT,	HERO_STAND,		HERO_MOVE,		HERO_HURT,		HERO_DEAD,		HERO_INVALID,	HERO_STAND	},
	{ HERO_INIT,	HERO_STAND,		HERO_MOVE,		HERO_HURT,		HERO_DEAD,		HERO_INVALID,	HERO_MOVE	},
	{ HERO_INIT,	HERO_HURT,		HERO_HURT,		HERO_HURT,		HERO_DEAD,		HERO_INVALID,	HERO_STAND	},
	{ HERO_INIT,	HERO_DEAD,		HERO_DEAD,		HERO_DEAD,		HERO_DEAD,		HERO_INVALID,	HERO_INVALID },
	{ HERO_INIT,	HERO_INVALID,	HERO_INVALID,	HERO_INVALID,	HERO_INVALID,	HERO_INVALID,	HERO_INVALID } };

const int HERO_MOTION_MAP[HERO_STATE_NUM] = { 0, 1, 2, 3, 4, -1, -1 };

/*
** Hero can only react in specific states.
*/
const bool HERO_CONTROLLABLE[HERO_STATE_NUM] = { false, true, true, false, false, false, false };

class Hero : public Figure
{
public:
	Hero();
	virtual ~Hero();

	/*
	** Hero's update, the following parameters are needed:
	** user command           -- Command from the player,
	*/
	virtual void update(Command& cmd);
	virtual void load(GameResourceId resId);

	void setState(HeroState _state);

	/*
	** These show the properties of the hero, which is connected
	** to the progress bar of the UI.
	*/
	void onShow(
		std::function<void(double)> _pShowHp,
		std::function<void(double)> _pShowAmor,
		std::function<void(double)> _pShowMp);

protected:
	virtual void hurt(const Damage& damage);

	virtual void skill() = 0;
	virtual void perish() = 0;

	/*
	** There's a little difference between these two, as
	** setState does not check the animation's state while
	** updateState only check the animation's state.
	*/
	void updateState();

	void switchWeapon();

	HeroType heroType;
	HeroState state;

	std::function<void(double)> pShowHp;
	std::function<void(double)> pShowAmor;
	std::function<void(double)> pShowMp;
};



/********************************************************************
** Base class for enemies.
*/
enum EnemyState
{
	ENEMY_INIT = 0,
	ENEMY_STAND,
	ENEMY_MOVE,
	ENEMY_HURT,
	ENEMY_DEAD,
	ENEMY_INVALID,
	ENEMY_END,

	ENEMY_STATE_NUM,
};

const EnemyState ENEMY_STATE_MACHINE[ENEMY_STATE_NUM][ENEMY_STATE_NUM] = {
	{ ENEMY_INIT,	ENEMY_INIT,		ENEMY_INIT,		ENEMY_INIT,		ENEMY_INIT,		ENEMY_INVALID,	ENEMY_STAND	},
	{ ENEMY_INIT,	ENEMY_STAND,	ENEMY_MOVE,		ENEMY_HURT,		ENEMY_DEAD,		ENEMY_INVALID,	ENEMY_STAND	},
	{ ENEMY_INIT,	ENEMY_STAND,	ENEMY_MOVE,		ENEMY_HURT,		ENEMY_DEAD,		ENEMY_INVALID,	ENEMY_MOVE	},
	{ ENEMY_INIT,	ENEMY_HURT,		ENEMY_HURT,		ENEMY_HURT,		ENEMY_DEAD,		ENEMY_INVALID,	ENEMY_STAND	},
	{ ENEMY_INIT,	ENEMY_DEAD,		ENEMY_DEAD,		ENEMY_DEAD,		ENEMY_DEAD,		ENEMY_INVALID,	ENEMY_INVALID },
	{ ENEMY_INIT,	ENEMY_INVALID,	ENEMY_INVALID,	ENEMY_INVALID,	ENEMY_INVALID,	ENEMY_INVALID,	ENEMY_INVALID } };

const int ENEMY_MOTION_MAP[ENEMY_STATE_NUM] = { 0, 1, 2, 3, 4, -1, -1 };

const bool ENEMY_CONTROLLABLE[ENEMY_STATE_NUM] = { false, true, true, false, false, false, false };


class Enemy : public Figure
{
public:
	Enemy();
	virtual ~Enemy();

	void onDefeat(std::function<void(int)> callback);
	void onGenerate(std::function<void(int, int, Coord, int, Coord)> callback);

	virtual void setPos(const Coord& _pos);
	virtual void setCenter(const Coord& center);

	/*
	** Enemies' update, the following parameters are needed:
	** hero's info            -- To target hero.
	** terrain info           -- For AI (perhaps) algorithm. :)
	*/
	virtual void update(Coord target, Space* space);

	virtual void load(GameResourceId resId);

	/*
	** Enemy's move is slightly different from the hero, since he may
	** directly stop at some points.
	*/
	virtual void move();

	void updateState();

protected:
	virtual void hurt(const Damage& damage);
	virtual void skill() = 0;

	virtual void perish() = 0;

	void setState(EnemyState _state);
	

	Coord tarPos;

	/*
	** The function to be called when the figure is defeated.
	*/
	std::function<void(int)> pOnDefeat;

	/*
	** 2022/01/20
	** Used when the enemy dies and generate buffs.
	*/
	std::function<void(int, int, Coord, int, Coord)> pOnGenerate;

	EnemyState state;

	/*
	** 2022/01/28
	** The enemy will keep a distance from the hero. Here just use
	** Manhattan distance.
	*/
	int patrolRadius;

	int price;
};



/********************************************************************
** Yony is the basic hero. :)
*/
class Yony : public Hero
{
public:
	Yony();
	~Yony();

private:
	virtual void skill();
	virtual void perish();
};


enum EnemyLevel
{
	ENEMY_PAWN = 0,
	ENEMY_BOSS
};


/********************************************************************
** Pawn is the basic enemy.
*/
class Pawn : public Enemy
{
public:
	Pawn();
	~Pawn();

private:
	virtual void skill();
	virtual void perish();
};


class Boss : public Enemy
{
public:
	Boss();
	~Boss();

	/*
	** Enemies' update, the following parameters are needed:
	** hero's info            -- To target hero.
	** terrain info           -- For AI (perhaps) algorithm. :)
	*/
	virtual void update(Coord target, Space* space);

private:
	virtual void skill();
	virtual void perish();
};


/********************************************************************
** Well, this one generates a hero.
*/
Hero* getHero(HeroType type);


/********************************************************************
** Hmm, this one generates an enemy.
*/
Enemy* getEnemy(EnemyLevel level);
Pawn* getPawn();
Boss* getBoss();


#endif