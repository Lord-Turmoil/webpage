/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : object.cpp                                *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 20, 2022                          *
 *                                                                            *
 *                    Last Update : January 28, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For Object class, base class of elements that has size, and is derivated *
 *   ones with physical effects.                                              *
 * -------------------------------------------------------------------------- *
 * Functions:                                                                 *
 ******************************************************************************/

#include <easyx.h>

#include "object.h"
#include "timing.h"
#include "auxilliary.h"


extern Time globalTimer;


/******************************************************************************
 * Object::Object -- Constructor of the object.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _type -- The type of the object.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
Object::Object(ObjectType _type) : type(_type)
{
	pos = { 0, 0 };
	offset = { 0, 0 };

	width = height = 0;

	imgOffset = { 0, 0 };

	pFrame = nullptr;

	isValid = true;
	isHidden = false;
}


/******************************************************************************
 * Object::~Object -- Deconstructor of the object.                            *
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
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
Object::~Object() {}


/******************************************************************************
 * Object::init -- Initialize the object.                                     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _pos       -- The coordinate of the object.                       *
 *          _width     -- The width of the object.                            *
 *          _height    -- The height of the object.                           *
 *          _imgOffset -- The image offset of the object.                     *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
void Object::init(Coord _pos, int _width, int _height, Coord _imgOffset)
{
	pos = _pos;

	width = _width;
	height = _height;

	offset = { width >> 1, height >> 1 };
	imgOffset = _imgOffset;
}


/******************************************************************************
 * Object::getType -- Get the type of the object.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the type of the object.                                    *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
ObjectType Object::getType() const
{
	return type;
}


/******************************************************************************
 * Object::setPos -- Set the object's position.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _pos -- The coordinate to be set.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to change all positions needed.                        *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
void Object::setPos(const Coord& _pos)
{
	pos = _pos;
}


/******************************************************************************
 * Object::setCenter -- Set the center of the object.                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   center -- The center of the object.                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Object::setCenter(const Coord& center)
{
	pos = center - offset;
}


/******************************************************************************
 * Object::setSize -- Set the size of the object.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _width                                                            *
 *          _height                                                           *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
void Object::setSize(int _width, int _height)
{
	width = _width;
	height = _height;

	offset = { width >> 1, height >> 1 };
}


/******************************************************************************
 * Object::setValid -- Set the valid state of the object.                     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _isValid -- Whether is valid or not.                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
void Object::setValid(bool _isValid)
{
	isValid = _isValid;
}


/******************************************************************************
 * Object::setHidden -- Set the hidden state of the object.                   *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _isHidden -- Whether is hidden or not.                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
void Object::setHidden(bool _isHidden)
{
	isHidden = _isHidden;
}


/******************************************************************************
 * Object::getCenter -- Get the center of the object.                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the center of the object.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/23 Tony : Created.                                               *
 *============================================================================*/
Coord Object::getCenter() const
{
	return pos + offset;
}


/******************************************************************************
 * Object::hit -- Check whether two object hits or not.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   obj -- The other object to be checked.                            *
 *                                                                            *
 * OUTPUT:  Return whether two objects hit each other or not.                 *
 *                                                                            *
 * WARNINGS:  Here, about the margin... I didn't use equal.                   *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
bool Object::hit(const Object& obj)
{
	Coord diff = obj.pos - pos;
	Coord dist = { (obj.width + width) >> 1, (obj.height + height) >> 1 };

	return (ABS(diff.x) < dist.x) && (ABS(diff.y) < dist.y);
}


/******************************************************************************
 * Object::hit -- Check whether a object hits a point or not.                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   coord -- The point to be checked.                                 *
 *                                                                            *
 * OUTPUT:  Return whether the object hits the point or not.                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
bool Object::hit(const Coord& coord)
{
	RECT range{ pos.x, pos.y, pos.x + width, pos.y + height };

	return inRectangle(range, coord);
}



/******************************************************************************
 * PhysicalObject::PhysicalObject -- Constructor of the object.               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _type -- Type of the object... That Object.                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
PhysicalObject::PhysicalObject(ObjectType _type)
	: Object(_type)
{
	strength = 0.0;
	collId = COLL_UNKNOWN;
}


/******************************************************************************
 * PhysicalObject::~PhysicalObject -- Deconstructor of the object.            *
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
 *   2022/01/20 Tony : Created.                                               *
 *============================================================================*/
PhysicalObject::~PhysicalObject() {}


/******************************************************************************
 * PhysicalObject::topLeft -- Get top left coordinate.                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   prev -- Whether to get previous one or not.                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
Coord PhysicalObject::topLeft(bool prev) const
{
	if (prev)
		return prevPos;
	else
		return pos;
}


/******************************************************************************
 * PhysicalObject::topRight -- Get top right coordinate.                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   prev -- Whether to get previous one or not.                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
Coord PhysicalObject::topRight(bool prev) const
{
	if (prev)
		return { prevPos.x + width, prevPos.y };
	else
		return { pos.x + width, pos.y };
}


/******************************************************************************
 * PhysicalObject::bottomLeft -- Get bottom left coordinate.                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   prev -- Whether to get previous one or not.                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
Coord PhysicalObject::bottomLeft(bool prev) const
{
	if (prev)
		return { prevPos.x, prevPos.y + height };
	else
		return { pos.x, pos.y + height };
}


/******************************************************************************
 * PhysicalObject::bottomRight -- Get bottom right coordinate.                *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   prev -- Whether to get previous one or not.                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
Coord PhysicalObject::bottomRight(bool prev) const
{
	if (prev)
		return { prevPos.x + width, prevPos.y + height };
	else
		return { pos.x + width, pos.y + height };
}


/******************************************************************************
 * PhysicalObject::collide -- The collision of two physical object.           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   obj -- The physical object to collide.                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/20 Tony : Created.                                               *
 *   2022/01/22 Tony : Removed elastic collision.                             *
 *============================================================================*/
bool PhysicalObject::collide(PhysicalObject& obj)
{
	CollisionType collType = COLLISION_MAP[collId][obj.collId];

	switch (collType)
	{
	case COLL_NONE:
		return false;
	case COLL_CHECK:
		return checkCollision(*this, obj);
	case COLL_INELASTIC:
		return inelasticCollide(*this, obj);
	case COLL_ELASTIC:
		return elasticCollide(*this, obj);
	default:
		return false;
	}

	return false;
}


/******************************************************************************
 * PhysicalObject::setPos -- Set the coordinate of the physical object.       *
 *                                                                            *
 *    This is the top left coordinate.                                        *
 *                                                                            *
 * INPUT:   _pos -- The new coordinate to be set.                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void PhysicalObject::setPos(const Coord& _pos)
{
	prevPos = pos = _pos;
}


/******************************************************************************
 * PhysicalObject::setCenter -- Set the center of the physical object.        *
 *                                                                            *
 *    This is the top left coordinate.                                        *
 *                                                                            *
 * INPUT:   center -- The center of the object.                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void PhysicalObject::setCenter(const Coord& center)
{
	prevPos = pos = center - offset;
}


/******************************************************************************
 * PhysicalObject::move -- Move the object.                                   *
 *                                                                            *
 *    This just use the force to move.                                        *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void PhysicalObject::move()
{
	// The object with infinite mass can't move.
	if (m == 0)
		return;

	getAcc();
	getVel();

	prevPos = pos;
	pos.x += (int)(v.x * globalTimer.getDeltaTime() * 100.0);
	pos.y += (int)(v.y * globalTimer.getDeltaTime() * 100.0);
	sym.pos = pos;
}



/******************************************************************************
 * PhysicalObjectPool::PhysicalObjectPool -- Constructor.                     *
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
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
PhysicalObjectPool::PhysicalObjectPool() {}


/******************************************************************************
 * PhysicalObjectPool::~PhysicalObjectPool -- Deconstructor.                  *
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
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
PhysicalObjectPool::~PhysicalObjectPool()
{
	for (auto it = pool.begin(); it != pool.end(); it++)
		delete (*it);
}


/******************************************************************************
 * PhysicalObjectPool::add -- Add a physical object to the pool.              *
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
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void PhysicalObjectPool::add(PhysicalObject* obj)
{
	pool.push_back(obj);
}


/******************************************************************************
 * PhysicalObjectPool::size -- Get the size of the pool.                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the size of the physical object pool.                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/28 Tony : Created.                                               *
 *============================================================================*/
size_t PhysicalObjectPool::size() const
{
	return pool.size();
}


/******************************************************************************
 * PhysicalObjectPool::draw -- Draw all objects.                              *
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
 *   2022/01/22 Tony : Created.                                               *
 *   2022/02/04 Tony : Now this may remove invalid ones.                      *
 *============================================================================*/
void PhysicalObjectPool::draw(Camera& cam)
{
	auto it = pool.begin();
	while (it != pool.end())
	{
		if (!((*it)->isValid))
		{
			delete (*it);
			it = pool.erase(it);
			continue;
		}
		(*it)->draw(cam);
		it++;
	}
}


/******************************************************************************
 * PhysicalObjectPool::clear -- Clear the pool.                               *
 *                                                                            *
 *    This will delete all items in the pool.                                 *
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
void PhysicalObjectPool::clear()
{
	for (auto it = pool.begin(); it != pool.end(); it++)
		delete (*it);
	pool.clear();
}


/******************************************************************************
 * PhysicalObjectPool::getPool -- Get the pool.                               *
 *                                                                            *
 *    This is not well designed. Since different objects have different ways  *
 *    to update... not good. :(                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
std::vector<PhysicalObject*>& PhysicalObjectPool::getPool()
{
	return pool;
}



/******************************************************************************
 * checkCollision -- Check collision between two physical objects.            *
 *                                                                            *
 *    Only check for the collision between two objects.                       *
 *                                                                            *
 * INPUT:   obj1 -- Active object.                                            *
 *          obj2 -- Passive object.                                           *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
bool checkCollision(const PhysicalObject& obj1, const PhysicalObject& obj2)
{
	bool rv = false;
	Coord p[4];
	Coord q[2];
	int delta;

	/*
	** Y-axis.
	*/
	delta = obj1.pos.y - obj1.prevPos.y;
	if (delta != 0)
	{
		if (delta > 0)
		{
			p[0] = obj1.bottomLeft(true);
			p[1] = obj1.bottomRight(true);
			p[2] = obj1.bottomLeft();
			p[3] = obj1.bottomRight();

			q[0] = obj2.topLeft();
			q[1] = obj2.topRight();

			if ((p[0].y <= q[0].y) && (q[0].y <= p[2].y))
			{
				/*
				** x = (y - y1)(x1 - x3) / (y1 - y3) + x1,
				** x = (y - y2)(x2 - x4) / (y2 - y4) + x2,
				** t = (y - y1)(x1 - x3) / (y1 - y3)
				*/
				int t = (int)((q[0].y - p[0].y) * (p[0].x - p[2].x) / (double)(p[0].y - p[2].y));
				int x1 = t + p[0].x;
				int x2 = t + p[1].x;

				if (!((x2 < q[0].x) || (x1 > q[1].x)))
					rv = true;
			}
		}
		else
		{
			p[0] = obj1.topLeft(true);
			p[1] = obj1.topRight(true);
			p[2] = obj1.topLeft();
			p[3] = obj1.topRight();

			q[0] = obj2.bottomLeft();
			q[1] = obj2.bottomRight();

			if ((p[0].y >= q[0].y) && (q[0].y >= p[2].y))
			{
				/*
				** x = (y - y1)(x1 - x3) / (y1 - y3) + x1,
				** x = (y - y2)(x2 - x4) / (y2 - y4) + x2,
				** t = (y - y1)(x1 - x3) / (y1 - y3)
				*/
				int t = (int)((q[0].y - p[0].y) * (p[0].x - p[2].x) / (double)(p[0].y - p[2].y));
				int x1 = t + p[0].x;
				int x2 = t + p[1].x;

				if (!((x2 < q[0].x) || (x1 > q[1].x)))
					rv = true;
			}
		}
	}

	/*
	** X-axis.
	*/
	delta = obj1.pos.x - obj1.prevPos.x;
	if (delta != 0)
	{
		if (delta > 0)
		{
			p[0] = obj1.topRight(true);
			p[1] = obj1.bottomRight(true);
			p[2] = obj1.topRight();
			p[3] = obj1.bottomRight();

			q[0] = obj2.topLeft();
			q[1] = obj2.bottomLeft();

			if ((p[0].x <= q[0].x) && (q[0].x <= p[2].x))
			{

				/*
				** y = (y1 - y3)(x - x1) / (x1 - x3) + y1
				** t = (y1 - y3)(x - x1) / (x1 - x3)
				*/
				int t = (int)((p[0].y - p[2].y) * (q[0].x - p[0].x) / (double)(p[0].x - p[2].x));
				int y1 = t + p[0].y;
				int y2 = t + p[1].y;

				if (!((y2 < q[0].y) || (y1 > q[1].y)))
					rv = true;
			}
		}
		else
		{
			p[0] = obj1.topLeft(true);
			p[1] = obj1.bottomLeft(true);
			p[2] = obj1.topLeft();
			p[3] = obj1.bottomLeft();

			q[0] = obj2.topRight();
			q[1] = obj2.bottomRight();

			if ((p[0].x >= q[0].x) && (q[0].x >= p[2].x))
			{

				/*
				** y = (y1 - y3)(x - x1) / (x1 - x3) + y1
				** t = (y1 - y3)(x - x1) / (x1 - x3)
				*/
				int t = (int)((p[0].y - p[2].y) * (q[0].x - p[0].x) / (double)(p[0].x - p[2].x));
				int y1 = t + p[0].y;
				int y2 = t + p[1].y;

				if (!((y2 < q[0].y) || (y1 > q[1].y)))
					rv = true;
			}
		}
	}

//	if (!rv)
//	{
//		Coord diff = obj1.pos - obj2.pos;
//		Coord dist = { (obj1.width + obj2.width) >> 1, (obj1.height + obj2.height) >> 1 };
//
//		return (ABS(diff.x) < dist.x) && (ABS(diff.y) < dist.y);
//	}

	return rv;
}


/******************************************************************************
 * inelasticCollide -- Perform inelastic collision.                           *
 *                                                                            *
 *    Here, we take obj2 as un-movable.                                       *
 *                                                                            *
 * INPUT:   obj1                                                              *
 *          obj2                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
bool inelasticCollide(PhysicalObject& obj1, PhysicalObject& obj2)
{
	bool rv = false;
	Coord p[4];
	Coord q[2];
	int delta;

	/*
	** Y-axis.
	*/
	delta = obj1.pos.y - obj1.prevPos.y;
	if (delta != 0)
	{
		if (delta > 0)
		{
			p[0] = obj1.bottomLeft(true);
			p[1] = obj1.bottomRight(true);
			p[2] = obj1.bottomLeft();
			p[3] = obj1.bottomRight();

			q[0] = obj2.topLeft();
			q[1] = obj2.topRight();

			if ((p[0].y <= q[0].y) && (q[0].y < p[2].y))
			{
				/*
				** x = (y - y1)(x1 - x3) / (y1 - y3) + x1,
				** x = (y - y2)(x2 - x4) / (y2 - y4) + x2,
				** t = (y - y1)(x1 - x3) / (y1 - y3)
				*/
				int t = (int)((q[0].y - p[0].y) * (p[0].x - p[2].x) / (double)(p[0].y - p[2].y));
				int x1 = t + p[0].x;
				int x2 = t + p[1].x;

				if (!((x2 <= q[0].x) || (x1 >= q[1].x)))
				{
					rv = true;
					obj1.pos.y = q[0].y - obj1.height;
					obj1.sym.pos.y = obj1.pos.y;
					obj1.v.y = 0.0;
				}
			}
		}
		else
		{
			p[0] = obj1.topLeft(true);
			p[1] = obj1.topRight(true);
			p[2] = obj1.topLeft();
			p[3] = obj1.topRight();

			q[0] = obj2.bottomLeft();
			q[1] = obj2.bottomRight();

			if ((p[0].y >= q[0].y) && (q[0].y > p[2].y))
			{
				/*
				** x = (y - y1)(x1 - x3) / (y1 - y3) + x1,
				** x = (y - y2)(x2 - x4) / (y2 - y4) + x2,
				** t = (y - y1)(x1 - x3) / (y1 - y3)
				*/
				int t = (int)((q[0].y - p[0].y) * (p[0].x - p[2].x) / (double)(p[0].y - p[2].y));
				int x1 = t + p[0].x;
				int x2 = t + p[1].x;

				if (!((x2 <= q[0].x) || (x1 >= q[1].x)))
				{
					rv = true;
					obj1.pos.y = q[0].y;
					obj1.sym.pos.y = obj1.pos.y;
					obj1.v.y = 0.0;
				}
			}
		}
	}

	/*
	** X axis
	*/
	delta = obj1.pos.x - obj1.prevPos.x;
	if (delta != 0)
	{
		if (delta > 0)
		{
			p[0] = obj1.topRight(true);
			p[1] = obj1.bottomRight(true);
			p[2] = obj1.topRight();
			p[3] = obj1.bottomRight();

			q[0] = obj2.topLeft();
			q[1] = obj2.bottomLeft();

			if ((p[0].x <= q[0].x) && (q[0].x < p[2].x))
			{

				/*
				** y = (y1 - y3)(x - x1) / (x1 - x3) + y1
				** t = (y1 - y3)(x - x1) / (x1 - x3)
				*/
				int t = (int)((p[0].y - p[2].y) * (q[0].x - p[0].x) / (double)(p[0].x - p[2].x));
				int y1 = t + p[0].y;
				int y2 = t + p[1].y;

				if (!((y2 <= q[0].y) || (y1 >= q[1].y)))
				{
					rv = true;
					obj1.pos.x = q[0].x - obj1.width;
					obj1.sym.pos.x = obj1.pos.x;
					obj1.v.x = 0.0;
				}
			}
		}
		else
		{
			p[0] = obj1.topLeft(true);
			p[1] = obj1.bottomLeft(true);
			p[2] = obj1.topLeft();
			p[3] = obj1.bottomLeft();

			q[0] = obj2.topRight();
			q[1] = obj2.bottomRight();

			if ((p[0].x >= q[0].x) && (q[0].x > p[2].x))
			{

				/*
				** y = (y1 - y3)(x - x1) / (x1 - x3) + y1
				** t = (y1 - y3)(x - x1) / (x1 - x3)
				*/
				int t = (int)((p[0].y - p[2].y) * (q[0].x - p[0].x) / (double)(p[0].x - p[2].x));
				int y1 = t + p[0].y;
				int y2 = t + p[1].y;

				if (!((y2 <= q[0].y) || (y1 >= q[1].y)))
				{
					rv = true;
					obj1.pos.x = q[0].x;
					obj1.sym.pos.x = obj1.pos.x;
					obj1.v.x = 0.0;
				}
			}
		}
	}

	return rv;
}

/******************************************************************************
 * inelasticCollide -- Perform inelastic collision.                           *
 *                                                                            *
 *    Here, we take obj2 as un-movable. If collision occurs, just reverse the *
 *    velocity of obj1 and make a little degragation to it.                   *
 *                                                                            *
 * INPUT:   obj1                                                              *
 *          obj2                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
bool elasticCollide(PhysicalObject& obj1, PhysicalObject& obj2)
{
	bool rv = false;
	Coord p[4];
	Coord q[2];
	int delta;

	/*
	** Y-axis.
	*/
	delta = obj1.pos.y - obj1.prevPos.y;
	if (delta != 0)
	{
		if (delta > 0)
		{
			p[0] = obj1.bottomLeft(true);
			p[1] = obj1.bottomRight(true);
			p[2] = obj1.bottomLeft();
			p[3] = obj1.bottomRight();

			q[0] = obj2.topLeft();
			q[1] = obj2.topRight();

			if ((p[0].y <= q[0].y) && (q[0].y < p[2].y))
			{
				/*
				** x = (y - y1)(x1 - x3) / (y1 - y3) + x1,
				** x = (y - y2)(x2 - x4) / (y2 - y4) + x2,
				** t = (y - y1)(x1 - x3) / (y1 - y3)
				*/
				int t = (int)((q[0].y - p[0].y) * (p[0].x - p[2].x) / (double)(p[0].y - p[2].y));
				int x1 = t + p[0].x;
				int x2 = t + p[1].x;

				if (!((x2 <= q[0].x) || (x1 >= q[1].x)))
				{
					rv = true;
					obj1.pos.y = q[0].y - obj1.height;
					obj1.sym.pos.y = obj1.pos.y;
					obj1.v.y = -obj1.v.y * ENERGY_RATIO;
				}
			}
		}
		else
		{
			p[0] = obj1.topLeft(true);
			p[1] = obj1.topRight(true);
			p[2] = obj1.topLeft();
			p[3] = obj1.topRight();

			q[0] = obj2.bottomLeft();
			q[1] = obj2.bottomRight();

			if ((p[0].y >= q[0].y) && (q[0].y > p[2].y))
			{
				/*
				** x = (y - y1)(x1 - x3) / (y1 - y3) + x1,
				** x = (y - y2)(x2 - x4) / (y2 - y4) + x2,
				** t = (y - y1)(x1 - x3) / (y1 - y3)
				*/
				int t = (int)((q[0].y - p[0].y) * (p[0].x - p[2].x) / (double)(p[0].y - p[2].y));
				int x1 = t + p[0].x;
				int x2 = t + p[1].x;

				if (!((x2 <= q[0].x) || (x1 >= q[1].x)))
				{
					rv = true;
					obj1.pos.y = q[0].y;
					obj1.sym.pos.y = obj1.pos.y;
					obj1.v.y = -obj1.v.y * ENERGY_RATIO;
				}
			}
		}
	}

	/*
	** X axis
	*/
	delta = obj1.pos.x - obj1.prevPos.x;
	if (delta != 0)
	{
		if (delta > 0)
		{
			p[0] = obj1.topRight(true);
			p[1] = obj1.bottomRight(true);
			p[2] = obj1.topRight();
			p[3] = obj1.bottomRight();

			q[0] = obj2.topLeft();
			q[1] = obj2.bottomLeft();

			if ((p[0].x <= q[0].x) && (q[0].x < p[2].x))
			{

				/*
				** y = (y1 - y3)(x - x1) / (x1 - x3) + y1
				** t = (y1 - y3)(x - x1) / (x1 - x3)
				*/
				int t = (int)((p[0].y - p[2].y) * (q[0].x - p[0].x) / (double)(p[0].x - p[2].x));
				int y1 = t + p[0].y;
				int y2 = t + p[1].y;

				if (!((y2 <= q[0].y) || (y1 >= q[1].y)))
				{
					rv = true;
					obj1.pos.x = q[0].x - obj1.width;
					obj1.sym.pos.x = obj1.pos.x;
					obj1.v.x = -obj1.v.x * ENERGY_RATIO;
				}
			}
		}
		else
		{
			p[0] = obj1.topLeft(true);
			p[1] = obj1.bottomLeft(true);
			p[2] = obj1.topLeft();
			p[3] = obj1.bottomLeft();

			q[0] = obj2.topRight();
			q[1] = obj2.bottomRight();

			if ((p[0].x >= q[0].x) && (q[0].x > p[2].x))
			{

				/*
				** y = (y1 - y3)(x - x1) / (x1 - x3) + y1
				** t = (y1 - y3)(x - x1) / (x1 - x3)
				*/
				int t = (int)((p[0].y - p[2].y) * (q[0].x - p[0].x) / (double)(p[0].x - p[2].x));
				int y1 = t + p[0].y;
				int y2 = t + p[1].y;

				if (!((y2 <= q[0].y) || (y1 >= q[1].y)))
				{
					rv = true;
					obj1.pos.x = q[0].x;
					obj1.sym.pos.x = obj1.pos.x;
					obj1.v.x = -obj1.v.x * ENERGY_RATIO;
				}
			}
		}
	}

	return rv;
}