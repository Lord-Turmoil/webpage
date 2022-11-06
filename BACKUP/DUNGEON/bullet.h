/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : bullet.h                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 13, 2022                          *
 *                                                                            *
 *                    Last Update : February 18, 2022                         *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For bullet object. It is derived from Physical object.                   *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 * -------------------------------------------------------------------------- *
 * Comments:                                                                  *
 *   This is terrible. :(                                                     *
 ******************************************************************************/

#ifndef _BULLET_H_
#define _BULLET_H_

#include <ctime>
#include <easyx.h>

#include "define.h"
#include "object.h"
#include "config.h"


/********************************************************************
** A struct for bullet's damage.
*/
struct Damage
{
	/*
	** The source of the damage.
	*/
	Coord source;

	/*
	** The blow force of the damage. It will apply to the figure.
	*/
	double blowForce;

	/*
	** During the shock time, the figure can't move by himself.
	*/
	clock_t shockTime;

	/*
	** The damage caused to the figure.
	*/
	int value;

	/*
	** The range of the damage, for explode damage.
	*/
	int range;
};



/********************************************************************
** Bullet state.
**   0 1 2 3
** 0 0 1 0 3
** 1 1 1 3 3
** 2 3 3 3 3
** 3 3 3 3 3
*/
enum BulletState
{
	BULLET_FLY = 0,
	BULLET_EXPLODE,
	BULLET_END,
	BULLET_INVALID,
	BULLET_STATE_NUM
};

const BulletState BULLET_STATE_MACHINE[BULLET_STATE_NUM][BULLET_STATE_NUM] = {
	{ BULLET_FLY,		BULLET_EXPLODE,	BULLET_FLY,		BULLET_INVALID },
	{ BULLET_EXPLODE,	BULLET_EXPLODE,	BULLET_INVALID,	BULLET_INVALID },
	{ BULLET_INVALID,	BULLET_INVALID,	BULLET_INVALID,	BULLET_INVALID },
	{ BULLET_INVALID,	BULLET_INVALID,	BULLET_INVALID,	BULLET_INVALID } };

const int BULLET_MOTION_MAP[BULLET_STATE_NUM] = { 0, 1, -1, -1 };


/********************************************************************
** Bullet object.
*/
class Bullet : public PhysicalObject
{
public:
	Bullet(BulletType _bulletType, const Coord& _pos, const Coord& _dir);
	~Bullet();

	BulletType getBulletType() const;

	/*
	** Bullets' update only need the object pool to check whether
	** hit the target.
	*/
	void update(PhysicalObject* object);
	void update(PhysicalObjectPool& pool);
	void updateAnim();

	virtual void load(GameResourceId resId);
	virtual void draw(Camera& cam);

	virtual void move();

private:
	void setState(BulletState _state);
	void updateState();
	

	BulletType bulletType;

	BulletState state;

	/*
	** The damage of the bullet.
	*/
	Damage damage;

	Coord dir;
	double speed;
};


/********************************************************************
** Bullet pool takes hold of all bullets.
*/
class BulletPool
{
public:
	BulletPool();
	~BulletPool();

	void add(Bullet* bullet, bool isGood);

	void update(PhysicalObject* object);
	void update(PhysicalObjectPool& objectPool);
	void updateAnim();
	void move();

	void draw(Camera& cam);
	void clear();

private:
	

	std::vector<Bullet*> pool;
};


/********************************************************************
** New a bullet.
*/
Bullet* getBullet(BulletType type, const Coord& pos, const Coord& dir);

#endif