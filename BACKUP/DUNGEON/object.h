/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : object.h                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 1, 2022                           *
 *                                                                            *
 *                    Last Update : January 28, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For Object class, base class of elements that has size, and is derivated *
 *   ones with physical effects.                                              *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>

#include "camera.h"
#include "define.h"
#include "config.h"
#include "physics.h"
#include "animation.h"


/********************************************************************
** Type of object.
*/
enum class ObjectType
{
	UNKNOWN,

	// Physical objects.
	FIGURE,
	BULLET,
	BRICK,

	// Normal Objects.
	BUFF
};


/********************************************************************
** Base class of all objects. Elements that have a position
** and a size.
*/
class Object
{
public:
	Object(ObjectType _type = ObjectType::UNKNOWN);
	virtual ~Object();

	void init(Coord _pos, int _width, int _height, Coord _imgOffset);

	ObjectType getType() const;

	virtual void setPos(const Coord& _pos);
	virtual void setCenter(const Coord& center);
	void setSize(int _width, int _height);
	void setValid(bool _isValid);
	void setHidden(bool _isHidden);

	Coord getCenter() const;

	/*
	** Check if two object hit each other.
	*/
	bool hit(const Object& obj);

	/*
	** 2022/01/19
	** Well... A overload version. :?
	*/
	bool hit(const Coord& coord);
	
	/*
	** 2022/01/13
	** Load the object's resources.
	*/
	virtual void load(GameResourceId resId = RES_VOID) = 0;

	virtual void draw(Camera& cam) = 0;

	virtual void move() = 0;

/*
** 2022/01/22
** Just make them public
** protected:
*/

	ObjectType type;

	/*
	** pos is the object's absolute position. It is
	** the center of the object. :)
	** 2022/01/22
	** Let pos be the top left. It is just the collision area's
	** top left coordinate.
	*/
	Coord pos;
	
	/*
	** 2022/01/11
	** The offset for the top-left coordinate.
	** 2022/01/22
	** For the center.
	*/
	Coord offset;
	
	int width;
	int height;

	/*
	** Since every object has its image whose position is not
	** exacty the same, so here I use img_pos for the relative
	** position to pos.
	*/
	Coord imgOffset;

	/*
	** 2022/01/13
	** The animation of the object.
	*/
	Frame* pFrame;
	Animation anim;

	/*
	** A symbol is needed when we draw an object to the camera.
	*/
	Symbol sym;

	/*
	** 2022/01/04
	** Whether valid or not. If an object is no longer valid,
	** such as died or activated, then it is invalid and will
	** be removed by object pool.
	*/
	bool isValid;

	/*
	** 2022/01/11
	** Whether is hidden or not. If an object is hidden, then it
	** is invisible to the player and doesn't have interactions.
	*/
	bool isHidden;
};


/********************************************************************
** Collision types and their relation map.
** Coll is short for collision.
*/
enum CollisionId
{
	// bricks
	COLL_WALL = 0,
	COLL_GATE_CLOSED,
	COLL_GATE_OPEN,

	// figure
	COLL_HERO,
	COLL_HERO_SHOCKED,
	COLL_ENEMY,
	COLL_ENEMY_SHOCKED,

	// Buffs are not physical object. :)

	// bullets
	COLL_BULLET_HERO,
	COLL_BULLET_ENEMY,

	// vaccuum
	COLL_VACUUM,

	COLL_NUM,

	COLL_UNKNOWN
};

enum CollisionType
{
	COLL_NONE = 0,
	COLL_CHECK,		// only check collision
	COLL_INELASTIC,	// no bounce
	COLL_ELASTIC,	// bounce

	COLL_TYPE_NUM
};


const CollisionType COLLISION_MAP[COLL_NUM][COLL_NUM] = {
	{ COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_INELASTIC,		COLL_ELASTIC,		COLL_INELASTIC,		COLL_ELASTIC,		COLL_INELASTIC,		COLL_INELASTIC,	COLL_NONE },
	{ COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_INELASTIC,		COLL_ELASTIC,		COLL_INELASTIC,		COLL_ELASTIC,		COLL_INELASTIC,		COLL_INELASTIC,	COLL_NONE },
	{ COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_INELASTIC,		COLL_ELASTIC,		COLL_INELASTIC,		COLL_INELASTIC,	COLL_NONE },
	{ COLL_INELASTIC,		COLL_INELASTIC,		COLL_NONE,			COLL_ELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_NONE,			COLL_INELASTIC,	COLL_NONE },
	{ COLL_ELASTIC,			COLL_ELASTIC,		COLL_NONE,			COLL_ELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_NONE,			COLL_INELASTIC,	COLL_NONE },
	{ COLL_INELASTIC,		COLL_INELASTIC,		COLL_INELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_INELASTIC,		COLL_NONE,		COLL_NONE },
	{ COLL_ELASTIC,			COLL_ELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_ELASTIC,		COLL_INELASTIC,		COLL_NONE,		COLL_NONE },
	{ COLL_INELASTIC,		COLL_INELASTIC,		COLL_INELASTIC,		COLL_NONE,			COLL_NONE,			COLL_INELASTIC,		COLL_INELASTIC,		COLL_NONE,			COLL_NONE,		COLL_NONE },
	{ COLL_INELASTIC,		COLL_INELASTIC,		COLL_INELASTIC,		COLL_INELASTIC,		COLL_INELASTIC,		COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_NONE,		COLL_NONE },
	{ COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_NONE,			COLL_NONE,		COLL_NONE } };



/********************************************************************
** Objects that has physical properties.
*/
class PhysicalObject : public Object, public PhysicalProperty
{
public:
	PhysicalObject(ObjectType _type = ObjectType::UNKNOWN);
	virtual ~PhysicalObject();

	Coord topLeft(bool prev = false) const;
	Coord topRight(bool prev = false) const;
	Coord bottomLeft(bool prev = false) const;
	Coord bottomRight(bool prev = false) const;
	
	/*
	** Calculate the result of the collision between two objects
	** with physical properties.
	*/
	bool collide(PhysicalObject& obj);

	virtual void setPos(const Coord& _pos);
	virtual void setCenter(const Coord& center);

	virtual void load(GameResourceId resId) = 0;
	virtual void draw(Camera& cam) = 0;

	virtual void move();

/*
** 2022/01/22
** Just... make them public. :(
** protected:
*/

	Coord prevPos; 

	/*
	** 2022/01/11
	** This is used for the type of effect when two object collide.
	** There will be a matrix showing the relations among them. :)
	*/
	CollisionId collId;
};


/********************************************************************
** A pool contains all physical objects. It is not well designed so
** far, so... when updates, it return the pool and... then get them
** updated manually (> <). We are really sorry about this. :(
** To be specific, it includes Hero, Enemy and Brick.
*/
class PhysicalObjectPool
{
public:
	PhysicalObjectPool();
	~PhysicalObjectPool();

	void add(PhysicalObject* obj);
	size_t size() const;

	/*
	** 2022/01/17
	** This one is suitable for all objects.
	*/
	void draw(Camera& cam);

	void clear();

	std::vector<PhysicalObject*>& getPool();

private:
	std::vector<PhysicalObject*> pool;
};


/********************************************************************
** For the collision check of two objects. Here we regard obj2 as
** still. The rest are the same.
*/
bool checkCollision(const PhysicalObject& obj1, const PhysicalObject& obj2);


/********************************************************************
** For the inelastic collision between two objects.
*/
bool inelasticCollide(PhysicalObject& obj1, PhysicalObject& obj2);


/********************************************************************
** For the elastic collision between two objects.
*/
bool elasticCollide(PhysicalObject& obj1, PhysicalObject& obj2);

#endif