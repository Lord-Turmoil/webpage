/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : bullet.cpp                                *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 18, 2022                          *
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
 ******************************************************************************/

#include <deque>
#include <vector>

#include "figure.h"
#include "bullet.h"
#include "timing.h"
#include "auxilliary.h"


extern Time globalTimer;

extern Resource* gameResource[GAME_RES_NUM];


/******************************************************************************
 * Bullet::Bullet -- Constructor of the object.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _bulletType -- Type of the bullet.                                *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *   2022/01/19 Tony : Changed dir to Coord.                                  *
 *============================================================================*/
Bullet::Bullet(BulletType _bulletType, const Coord& _pos, const Coord& _dir)
	: PhysicalObject(ObjectType::BULLET)
{
	bulletType = _bulletType;
	prevPos = pos = _pos;

	dir = _dir;

	sym.layer = LAYER_NORMAL;
	sym.radian = getRadian(dir);

	state = BULLET_FLY;

	if (dir == ZERO_COORD)
		isValid = false;
}


/******************************************************************************
 * Bullet::~Bullet -- Deconstructor of the object.                            *
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
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
Bullet::~Bullet() {}


/******************************************************************************
 * Bullet::getBulletType -- Get the type of the bullet.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the type of the bullet.                                    *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
BulletType Bullet::getBulletType() const
{
	return bulletType;
}


/******************************************************************************
 * Bullet::update -- Update the state of the bullet.                          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   object -- The object to check.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
void Bullet::update(PhysicalObject* object)
{
	if (state != BULLET_FLY)
		return;

	if (!collide(*object))
		return;

	setState(BULLET_EXPLODE);
	damage.source = pos;

	if (object->getType() != ObjectType::BRICK)
		dynamic_cast<Figure*>(object)->hurt(damage);
}


/******************************************************************************
 * Bullet::update -- Update the state of the bullet.                          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pool -- The current physical object pool.                         *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *   2022/01/21 Tony : Fixed that no collision might happen.                  *
 *============================================================================*/
void Bullet::update(PhysicalObjectPool& pool)
{
	if (state != BULLET_FLY)
		return;

	auto& objPool = pool.getPool();
	PhysicalObject* obj = nullptr;

	for (auto it = objPool.begin(); it != objPool.end(); it++)
	{
		if (collide(**it))
		{
			setState(BULLET_EXPLODE);
			obj = *it;
			break;
		}
	}

	/*
	** 2022/01/21
	** Collide with nothing. :)
	*/
	if (obj == nullptr)
		return;

	damage.source = pos;
	if (obj->getType() != ObjectType::BRICK)
		dynamic_cast<Figure*>(obj)->hurt(damage);

	if (damage.range == 0)
		return;

	// Explosion damage.
	double dist;
	double k;
	Damage tempDamage;

	tempDamage.source = pos;
	for (auto it = objPool.begin(); it != objPool.end(); it++)
	{
		if (((*it)->getType() == ObjectType::BRICK) || (*it == obj))
			continue;

		dist = getDistance(pos, (*it)->pos);
		if (dist < (double)damage.range)
		{
			k = (dist - (double)damage.range) / dist;
			tempDamage.blowForce = damage.blowForce * k;
			tempDamage.shockTime = (clock_t)(damage.shockTime * k);
			tempDamage.value = (int)(damage.value * k);

			dynamic_cast<Figure*>(*it)->hurt(tempDamage);
		}
	}
}


/******************************************************************************
 * Bullet::updateAnim -- Oh man... update the state and animation...          *
 *                                                                            *
 *    This is bad... So bad... :(                                             *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/18 Tony : Created.                                               *
 *============================================================================*/
void Bullet::updateAnim()
{
	sym.img = anim.getFrame();
	sym.pos = getCenter();

	updateState();
	anim.update(BULLET_MOTION_MAP[state]);
}


/******************************************************************************
 * Bullet::load -- Load bullet resources.                                     *
 *                                                                            *
 *    All bullets are only different in their resources.                      *
 *                                                                            *
 * INPUT:   resId                                                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
void Bullet::load(GameResourceId resId)
{
	BulletRes* res = dynamic_cast<BulletRes*>(gameResource[resId]);

	offset = res->offset;

	speed = res->speed;

	pFrame = &(res->frame);
	anim.load(pFrame);

	damage.blowForce = res->blowForce;
	damage.shockTime = res->shockTime;
	damage.value = res->value;
	damage.range = res->range;

	width = res->width;
	height = res->height;
	imgOffset = res->imgOffset;

	anim.update();
	sym.img = anim.getFrame();
	sym.offset = imgOffset - offset;

	v = getUnit({ (double)dir.x, (double)dir.y }) * speed;
}


/******************************************************************************
 * Bullet::draw -- Draw the bullet.                                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cam                                                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
void Bullet::draw(Camera& cam)
{
	if (isHidden || !isValid)
		return;

	cam.capture(sym);
}


/******************************************************************************
 * Bullet::setState -- Set the state of the bullet.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _state -- The new state.                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
void Bullet::setState(BulletState _state)
{
	state = BULLET_STATE_MACHINE[state][_state];
}


/******************************************************************************
 * Bullet::updateState -- Update bullet state.                                *
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
 *   2022/01/18 Tony : Created.                                               *
 *   2022/01/23 Tony : Only check for animation state.                        *
 *============================================================================*/
void Bullet::updateState()
{
	if (anim.over())
		state = BULLET_STATE_MACHINE[state][BULLET_END];
	
	if (state == BULLET_INVALID)
		isValid = false;
}


/******************************************************************************
 * Bullet::move -- Move the bullet.                                           *
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
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
void Bullet::move()
{
	if (state != BULLET_FLY)
		return;

	Vector step = v * globalTimer.getDeltaTime() * VEL_COF;

	prevPos = pos;

	pos.x += (int)step.x;
	pos.y += (int)step.y;
}



/******************************************************************************
 * BulletPool::BulletPool -- Constructor of the object.                       *
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
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
BulletPool::BulletPool() {}


/******************************************************************************
 * BulletPool::Deconstructor of the object.                                   *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to delete bullets.                                     *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
BulletPool::~BulletPool()
{
	for (auto it = pool.begin(); it != pool.end(); it++)
		delete (*it);
}


/******************************************************************************
 * BulletPool::add -- Add bullets to the pool.                                *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   bullet -- The bullet to be added.                                 *
 *          isGood -- Whether the bullet is good.
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void BulletPool::add(Bullet* bullet, bool isGood)
{
	if (isGood)
		bullet->collId = COLL_BULLET_HERO;
	else
		bullet->collId = COLL_BULLET_ENEMY;

	pool.push_back(bullet);
}


/******************************************************************************
 * BulletPool::update -- Update bullets in the pool                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   object -- The target.                                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
void BulletPool::update(PhysicalObject* object)
{
	for (auto it = pool.begin(); it != pool.end(); it++)
		(*it)->update(object);
}


/******************************************************************************
 * BulletPool::update -- Update bullets in the pool                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   objectPool -- The game's physical object pool.                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void BulletPool::update(PhysicalObjectPool& objectPool)
{
	for (auto it = pool.begin(); it != pool.end(); it++)
		(*it)->update(objectPool);
}


/******************************************************************************
 * BulletPool::updateAnim -- Update bullets' animation.                       *
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
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void BulletPool::updateAnim()
{
	for (auto it = pool.begin(); it != pool.end(); it++)
		(*it)->updateAnim();
}

/******************************************************************************
 * BulletPool::move -- Move all bullets.                                      *
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
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void BulletPool::move()
{
	for (auto it = pool.begin(); it != pool.end(); it++)
		(*it)->move();
}


/******************************************************************************
 * BulletPool::draw -- Draw all the bullets.                                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cam                                                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *   2022/02/18 Tony : This will remove invalid bullets.                      *
 *============================================================================*/
void BulletPool::draw(Camera& cam)
{
	auto it = pool.begin();
	while (it != pool.end())
	{
		if (!((*it)->isValid))
		{
			it = pool.erase(it);
			continue;
		}
		(*it)->draw(cam);
		it++;
	}
}


/******************************************************************************
 * BulletPool::clear -- Clear the bullet pool.                                *
 *                                                                            *
 *    This simply delete all the bullets in the pool.                         *
 *                                                                            *
 * INPUT:   cam                                                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
void BulletPool::clear()
{
	for (auto it = pool.begin(); it != pool.end(); it++)
		delete (*it);
	pool.clear();
}



/******************************************************************************
 * getBullet -- Get a bullet.                                                 *
 *                                                                            *
 *    This function return a bullet in the heap by the type of the bullet.    *
 *                                                                            *
 * INPUT:   type -- Type of the bullet.                                       *
 *          pos  -- Position of the bullet.                                   *
 *          dir  -- Direction of the bullet.                                  *
 *                                                                            *
 * OUTPUT:  Return a new bullet in the heap.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
Bullet* getBullet(BulletType type, const Coord& pos, const Coord& dir)
{
	Bullet* bullet = new Bullet(type, pos, dir);
	
	switch (type)
	{
	case BULLET_PEPPER:
		bullet->load(RES_BULLET_PEPPER);
		break;
	case BULLET_FIRE:
		bullet->load(RES_BULLET_FIRE);
		break;
	default:
		delete bullet;
		bullet = nullptr;
		break;
	}

	return bullet;
}
