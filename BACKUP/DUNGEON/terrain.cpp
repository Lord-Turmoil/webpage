/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : terrain.cpp                               *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 14, 2022                          *
 *                                                                            *
 *                    Last Update : January 18, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For the Dungeon's terrain. Or just the map of the game.                  *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include <ctime>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include "config.h"
#include "terrain.h"


extern Resource* gameResource[GAME_RES_NUM];


/******************************************************************************
 * Brick::Brick -- Constructor of the object.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _type -- The type of the brick.                                   *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Brick::Brick(BrickType _type) : PhysicalObject(ObjectType::BRICK)
{
	brickType = _type;

	m = 0;
}


/******************************************************************************
 * Brick::~Brick -- Deconstructor of the object.                              *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Brick::~Brick() {}


/******************************************************************************
 * Brick::getBrickType -- Get the type of the brick.                          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the type of the brick.                                     *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
BrickType Brick::getBrickType() const
{
	return brickType;
}


/******************************************************************************
 * Brick::setPos -- Set the position of the brick.                            *
 *                                                                            *
 *    This is slightly different since it also modify symbol at the same time.*
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/17 Tony : Created.                                               *
 *============================================================================*/
void Brick::setPos(const Coord& _pos)
{
	prevPos = pos = _pos;
	sym.pos = pos + offset;
}


/******************************************************************************
 * Brick::initSymbol -- Initialize the symbol's property.                     *
 *                                                                            *
 *    Since the bricks can's move, so their symbol doesn't change much.       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Brick::initSymbol()
{
	sym.layer = LAYER_NORMAL;
	sym.pos = pos;
	sym.radian = 0.0;
}


/******************************************************************************
 * Brick::move -- Move the brick.                                             *
 *                                                                            *
 *    Infact, all bricks can't move. :)                                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Brick::move() {}



/******************************************************************************
 * Floor::Floor -- Constructor of the object.                                 *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Floor::Floor() : Brick(BrickType::BRICK_FLOOR) {}


/******************************************************************************
 * Floor::~Floor -- Deconstructor of the object.                              *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Floor::~Floor() {}


/******************************************************************************
 * Floor::getImage -- Get the image of the floor.                             *
 *                                                                            *
 *    ... This one hand the floor's image to the space to... piece a larger   *
 *    background.                                                             *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the image of the floor.                                    *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
IMAGE* Floor::getImage()
{
	return pImage;
}


/******************************************************************************
 * Floor::update -- Update the floor.                                         *
 *                                                                            *
 *    Infact... After handing its image to the space... the floor is just...  *
 *    useless.                                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Floor::update() {}


/******************************************************************************
 * Floor::load -- Load resource from given resourece id.                      *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   resId -- The resource id.                                         *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
void Floor::load(GameResourceId resId)
{
	BrickRes* res = dynamic_cast<BrickRes*>(gameResource[RES_BRICK_FLOOR]);

	pImage = &(res->image);

	offset = res->offset;

	width = res->width;
	height = res->height;
	imgOffset = res->imgOffset;
}


/******************************************************************************
 * Floor::draw -- Draw the floor.                                             *
 *                                                                            *
 *    Emm... In fact... Err... Maybe sorry for the floors. :(                 *
 *                                                                            *
 * INPUT:   Cam -- Camera of the game.                                        *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Floor::draw(Camera& cam) {}


/******************************************************************************
 * Wall::Wall -- Constructor of the object.                                   *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Wall::Wall() : Brick(BrickType::BRICK_WALL)
{
	collId = COLL_WALL;
}


/******************************************************************************
 * Wall::~Wall -- Deconstructor of the object.                                *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Wall::~Wall() {}


/******************************************************************************
 * Wall::update -- Update the wall state.                                     *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Wall::update() {}


/******************************************************************************
 * Wall::load -- Load wall image.                                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   resId -- See above.                                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
void Wall::load(GameResourceId resId)
{
	BrickRes* res = dynamic_cast<BrickRes*>(gameResource[RES_BRICK_WALL]);
	
	pImage = &(res->image);

	offset = res->offset;

	width = res->width;
	height = res->height;
	imgOffset = res->imgOffset;

	// A little initialization.
	sym.img = pImage;
	sym.offset = imgOffset - offset;
	sym.layer = LAYER_NORMAL;
}


/******************************************************************************
 * Wall::draw -- Draw the wall.                                               *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Wall::draw(Camera& cam)
{
	cam.capture(sym);
}


/******************************************************************************
 * Gate::Gate -- Constructor of the object.                                   *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Gate::Gate() : Brick(BrickType::BRICK_GATE)
{
	collId = COLL_GATE_OPEN;
	state = GATE_OPEN;
}


/******************************************************************************
 * Gate::~Gate -- Deconstructor of the object.                                *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Gate::~Gate() {}


/******************************************************************************
 * Gate::lock/unlock -- Lock or unlock the gate.                              *
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
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
void Gate::lock()
{
	setState(GATE_CLOSED);
}

void Gate::unlock()
{
	setState(GATE_OPEN);
}


/******************************************************************************
 * Gate::update -- Update the gate state.                                     *
 *                                                                            *
 *    This one DOES works! It updates its animation and decide which state to *
 *    go into.                                                                *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Gate::update()
{
	updateState();
	anim.update(GATE_MOTION_MAP[state]);
}


/******************************************************************************
 * Gate::load -- Load gate resources.                                         *
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
void Gate::load(GameResourceId resId)
{
	BrickRes* res = dynamic_cast<BrickRes*>(gameResource[RES_BRICK_GATE]);

	pFrame = &(res->frame);
	anim.load(pFrame);

	offset = res->offset;

	width = res->width;
	height = res->height;
	imgOffset = res->imgOffset;
	
	sym.offset = imgOffset - offset;
	sym.layer = LAYER_NORMAL;

	anim.update(state);
}


/******************************************************************************
 * Gate::draw -- Draw the gate.                                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cam -- See above.                                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Gate::draw(Camera& cam)
{
	sym.img = anim.getFrame();
	cam.capture(sym);
}


/******************************************************************************
 * Gate::setState -- Set the state of the gate.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _state -- The state to be set.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/24 Tony : Created.                                               *
 *============================================================================*/
void Gate::setState(GateState _state)
{
	state = GATE_STATE_MACHINE[state][_state];
}


/******************************************************************************
 * Gate::updateState -- Update the gate's state.                              *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Gate::updateState()
{
	if (anim.over())
		state = GATE_STATE_MACHINE[state][GATE_END];

	if (state == GATE_OPEN)
	{
		collId = COLL_GATE_OPEN;
		sym.layer = LAYER_BACK;
	}
	else
	{
		collId = COLL_GATE_CLOSED;
		sym.layer = LAYER_NORMAL;
	}
}



/******************************************************************************
 * Space::Space -- Constructor of the object.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _type -- The type of the space.                                   *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
Space::Space(SpaceType _type)
{
	type = _type;

	attribute.init();

	gateSide = DIR_NONE;
	spaceRole = SPACE_NONE;
}


/******************************************************************************
 * Space::~Space -- Deconstructor of the object.                              *
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
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
Space::~Space() {}


/******************************************************************************
 * Space::getType -- Get the type of the space.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the type of the space.                                     *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
SpaceType Space::getType() const
{
	return type;
}


/******************************************************************************
 * Space::getObjectPool -- Get the object pool of the space.                  *
 *                                                                            *
 *    The game's object pool actually belongs to these spaces, and the game   *
 *    just have a pointer to them.                                            *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the address of the object pool.                            *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
PhysicalObjectPool* Space::getBrickPool()
{
	return &brickPool;
}


/******************************************************************************
 * Space::getCenter -- Get the center of the space.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the center coordinate of the space.                        *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
Coord Space::getCenter() const
{
	return center;
}


/******************************************************************************
 * Space::convert -- Convert coordinates to or from subscript.                *
 *                                                                            *
 *    Convert coordinate of the whole terrain to or from the subscript of     *
 *    current space.                                                          *
 *                                                                            *
 * INPUT:   coord  -- The coordinate to convert.                              *
 *          invert -- Whether invert the process (convert from subscript).    *
 *                                                                            *
 * OUTPUT:  Return the converted coordinate.                                  *
 *                                                                            *
 * WARNINGS:  The 2D array and the device have different axis direction.      *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
Coord Space::convert(Coord coord, bool invert)
{
	Coord rv;

	if (invert)
	{
		// Convert from subscript to coordinate.
		rv.x = pos.x + coord.y * BRICK_WIDTH;
		rv.y = pos.y + coord.x * BRICK_WIDTH;
	}
	else
	{
		// Convert from coordinate to subscript.
		rv.x = (coord.y - pos.y) / BRICK_WIDTH;
		rv.y = (coord.x - pos.x) / BRICK_WIDTH;
	}

	return rv;
}


/******************************************************************************
 * Space::convert -- Convert length to unit length for subscription.          *
 *                                                                            *
 *    Just for the space's graph to find blank...                             *
 *                                                                            *
 * INPUT:   length -- The original length.                                    *
 *                                                                            *
 * OUTPUT:  Return the converted length.                                      *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/28 Tony : Created.                                               *
 *============================================================================*/
int Space::convert(int length)
{
	return 1 + length / BRICK_WIDTH;
}


/******************************************************************************
 * Space::isInside -- Whether a coordinate is in a space or not.              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   target -- The coordinate to be checked.                           *
 *                                                                            *
 * OUTPUT:  Return whether the target is in the space or not.                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
bool Space::isInside(Coord target)
{
	return ((pos.x <= target.x) && (target.x <= pos.x + width) \
		&& (pos.y < target.y) && (target.y <= pos.y + height));
}


/******************************************************************************
 * Space::draw -- Draw the space.                                             *
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
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
void Space::draw(Camera& cam)
{
	cam.capture(floor);
	brickPool.draw(cam);
}


/******************************************************************************
 * Space::drawMiniSpace -- Draw a mini space on the map                       *
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
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
void Space::drawMiniSpace(IMAGE* pDestImage)
{
	SetWorkingImage(pDestImage);

	if (attribute.isDiscovered)
	{
		if (attribute.isCurrent)
		{
			if (attribute.isCompleted)
				setfillcolor(0x00C9EE);
			else
				setfillcolor(0x9EB7CD);
		}
		else if (attribute.isCompleted)
			setfillcolor(0x00FC7C);
		else
			setfillcolor(0x6B7D8B);
		solidrectangle(pos.x, pos.y, pos.x + width, pos.y + height);

		if (attribute.hasBoss)
		{
			setfillcolor(0x0000EE);
			solidcircle(center.x, center.y, (int)(MIN(width, height) * 0.4));
		}
		else if (attribute.isEnd)
		{
			setfillcolor(0x00FFFF);
			solidcircle(center.x, center.y, (int)(MIN(width, height) * 0.4));
		}
	}
}


/******************************************************************************
 * Space::setUnitPos -- Set unit position of the space.                       *
 *                                                                            *
 *    The unit position is based on a larger grid, or in other words, is the  *
 *    subscript of the brick in the whole terrain.                            *
 *                                                                            *
 * INPUT:   _unitPos -- The unit coordinate to be set.                        *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
void Space::setUnitPos(Coord _unitPos)
{
	unitPos = _unitPos;
}


/******************************************************************************
 * Space::setSubscript -- Set the subscript of the space in the terrain.      *
 *                                                                            *
 *    This is based on the 3 * 3 grid of the terrain.                         *
 *                                                                            *
 * INPUT:   _subscript -- The subscript to be set.                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
void Space::setSubscript(Coord _subscript)
{
	subscript = _subscript;
}


/******************************************************************************
 * Space::setUnitSize -- Set the unit size of the space.                      *
 *                                                                            *
 *    This is how many bricks there are in the width or height.               *
 *                                                                            *
 * INPUT:   _unitWidth                                                        *
 *          _unitHeight                                                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
void Space::setUnitSize(int _unitWidth, int _unitHeight)
{
	unitWidth = _unitWidth;
	unitHeight = _unitHeight;
}


/******************************************************************************
 * Space::setGateSide -- Set the door side of the space.                      *
 *                                                                            *
 *    With the gate side, the arena or bridge can generate gate or vacant     *
 *    bricks.                                                                 *
 *                                                                            *
 * INPUT:   side -- The side of the gate.                                     *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
void Space::setGateSide(unsigned side)
{
	gateSide |= side;
}


/******************************************************************************
 * Space::setRole -- Set the space's role.                                    *
 *                                                                            *
 *    The space can play a role like the start or the ending.                 *
 *                                                                            *
 * INPUT:   role -- The role of the space.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
void Space::setRole(unsigned role)
{
	spaceRole |= role;
}


/******************************************************************************
 * Space::getUnitPos -- Get the unit coordinate of the space.                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the unit coordinate of the space.                          *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
Coord Space::getUnitPos() const
{
	return unitPos;
}


/******************************************************************************
 * Space::getSubscript -- Get the... just the literal meaning...              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the subscript of the space.                                *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
Coord Space::getSubscript() const
{
	return subscript;
}


/******************************************************************************
 * Space::getUnitWidth -- Get the unit width.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the unit width of the space.                               *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
int Space::getUnitWidth() const
{
	return unitWidth;
}


/******************************************************************************
 * Space::getUnitHeight -- Get the unit height of the space.                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the unit height of the space.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
int Space::getUnitHeight() const
{
	return unitHeight;
}


/******************************************************************************
 * Space::addNeighbor -- Add neighbor to the space.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   neighbor -- The neighbor to add.                                  *
 *                                                                            *
 * OUTPUT:  If the space already the neighbor, return false.                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
bool Space::addNeighbor(Space* neighbor)
{
	for (auto it = neighborList.begin(); it != neighborList.end(); it++)
	{
		if (*it == neighbor)
			return false;
	}

	neighborList.push_back(neighbor);
	return true;
}


/******************************************************************************
 * Arena::Arena -- Constructor of the object.                                 *
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
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
Arena::Arena() : Space(SpaceType::ARENA) {}


 /******************************************************************************
  * Arena::~Arena -- Deconstructor of the object.                              *
  *                                                                            *
  *    Just the literal meaning.                                               *
  *                                                                            *
  * INPUT:   none                                                              *
  *                                                                            *
  * OUTPUT:  none                                                              *
  *                                                                            *
  * WARNINGS:  The pointers in gateList will finally be deleted by the object  *
  *            pool.                                                           *
  *                                                                            *
  * HISTORY:                                                                   *
  *   2022/01/17 Tony : Created.                                               *
  *============================================================================*/
Arena::~Arena() {}


/******************************************************************************
 * Arena::entry -- Entry obstacles to the graph.                              *
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
 *   2022/02/21 Tony : Created.                                               *
 *============================================================================*/
void Arena::entry()
{
	for (auto it = obstacleList.begin(); it != obstacleList.end(); it++)
		graph.entry(*it);
}


/******************************************************************************
 * Arena::update -- Update the arena.                                         *
 *                                                                            *
 *    This will only update the gate.                                         *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
void Arena::update(const Coord& target)
{
	if (inTrap(target) && !attribute.isCompleted)
	{
		attribute.isTrapped = true;
		lock();
	}
	if (attribute.isCompleted)
		unlock();

	for (auto it = gateList.begin(); it != gateList.end(); it++)
		(*it)->update();

	attribute.update();
	if (attribute.isCurrent)
	{
		for (auto it = neighborList.begin(); it != neighborList.end(); it++)
			(*it)->attribute.isDiscovered = true;
	}
}


/******************************************************************************
 * Arena::generate -- Generate the arena from the result of the prim.         *
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
 *   2022/01/17 Tony : Created.                                               *
 *   2022/02/17 Tony : Init the gate at creation.                             *
 *============================================================================*/
void Arena::generate()
{
	pos.x = unitPos.x * BRICK_WIDTH;
	pos.y = unitPos.y * BRICK_WIDTH;

	width = unitWidth * BRICK_WIDTH;
	height = unitHeight * BRICK_WIDTH;

	offset = { width >> 1, height >> 1 };
	center = pos + offset;

	Floor tempFloor;

	tempFloor.load(RES_BRICK_FLOOR);

	floorImage.Resize(width, height);
	SetWorkingImage(&floorImage);
	for (int i = 0; i < width; i += BRICK_WIDTH)
	{
		for (int j = 0; j < height; j += BRICK_WIDTH)
			putimage(i, j, tempFloor.getImage());
	}
	SetWorkingImage(NULL);

	floor.img = &floorImage;
	floor.layer = LAYER_BACK;
	floor.pos = pos;
	floor.radian = 0.0;
	floor.offset = { 0, 0 };

	// Generate brick matrix.
	BrickMatrix brickMatrix;
	brickMatrix.resize(unitHeight, std::vector<BrickType>(unitWidth));

	Coord unitCenter = { unitHeight >> 1, unitWidth >> 1 };
	for (int i = 0; i < unitHeight; i++)
	{
		for (int j = 0; j < unitWidth; j++)
		{
			if ((i == 0) || (i == unitHeight - 1) || (j == 0) || (j == unitWidth - 1))
				brickMatrix[i][j] = BRICK_WALL;
			else
			{
				if ((i == 1) || (i == unitHeight - 2) || (j == 1) || (j == unitWidth - 2))
				{
					/*
					** 2022/02/22
					** Do not block the gate.
					*/
					brickMatrix[i][j] = BRICK_FLOOR;
				}
				else if ((!random(0, 20)) && (getManhattanDistance({ i, j }, unitCenter) > 2))
				{
					brickMatrix[i][j] = BRICK_WALL;
					obstacleList.push_back({ i, j });
				}
				else
					brickMatrix[i][j] = BRICK_FLOOR;
			}
		}
	}

	int k;
	if (gateSide & DIR_LEFT)
	{
		k = (unitHeight - GATE_WIDTH) >> 1;
		for (int i = 0; i < GATE_WIDTH; i++)
			brickMatrix[k + i][0] = BRICK_GATE;
	}
	if (gateSide & DIR_RIGHT)
	{
		k = (unitHeight - GATE_WIDTH) >> 1;
		for (int i = 0; i < GATE_WIDTH; i++)
			brickMatrix[k + i][unitWidth - 1] = BRICK_GATE;
	}
	if (gateSide & DIR_UP)
	{
		k = (unitWidth - GATE_WIDTH) >> 1;
		for (int i = 0; i < GATE_WIDTH; i++)
			brickMatrix[0][k + i] = BRICK_GATE;
	}
	if (gateSide & DIR_DOWN)
	{
		k = (unitWidth - GATE_WIDTH) >> 1;
		for (int i = 0; i < GATE_WIDTH; i++)
			brickMatrix[unitHeight - 1][k + i] = BRICK_GATE;
	}

	// Add bricks to the object pool.
	Brick* tempBrick;
	gateList.clear();
	for (int i = 0; i < unitHeight; i++)
	{
		for (int j = 0; j < unitWidth; j++)
		{
			if (brickMatrix[i][j] == BRICK_FLOOR)
				continue;

			if (brickMatrix[i][j] == BRICK_WALL)
			{
				tempBrick = new Wall();
				tempBrick->load(RES_BRICK_WALL);
				tempBrick->setPos({ pos.x + j * BRICK_WIDTH, pos.y + i * BRICK_WIDTH });
				brickPool.add(tempBrick);
			}
			else
			{
				tempBrick = new Gate();
				tempBrick->load(RES_BRICK_GATE);
				tempBrick->setPos({ pos.x + j * BRICK_WIDTH, pos.y + i * BRICK_WIDTH });

				brickPool.add(tempBrick);
				gateList.push_back(dynamic_cast<Gate*>(tempBrick));
			}
		}
	}

	graph.init(unitWidth, unitHeight);
}


/******************************************************************************
 * Arena::inTrap -- Check if the hero is totally in the arena.                *
 *                                                                            *
 *    This is to prevent the closing of the gate when the hero is still... on *
 *    the open gate.                                                          *
 *                                                                            *
 * INPUT:   target -- The center of the hero.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
bool Arena::inTrap(const Coord& target)
{
	int margin = BRICK_WIDTH << 2;

	return ((pos.x + margin < target.x) && (target.x + margin < pos.x + width) \
		&& (pos.y + margin < target.y) && (target.y + margin < pos.y + height));
}


/******************************************************************************
 * Arena::lock/unlock -- Lock or unlock the arena.                            *
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
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
void Arena::lock()
{
	if (isLocked)
		return;

	isLocked = true;
	for (auto it = gateList.begin(); it != gateList.end(); it++)
		(*it)->lock();
}
void Arena::unlock()
{
	if (!isLocked)
		return;

	isLocked = false;
	for (auto it = gateList.begin(); it != gateList.end(); it++)
		(*it)->unlock();
}


/******************************************************************************
 * Bridge::Bridge -- Constructor of the object.                               *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Bridge::Bridge() : Space(SpaceType::BRIDGE) {}


/******************************************************************************
 * Bridge::~Bridge -- Deconstructor of the object.                            *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Bridge::~Bridge() {}


/******************************************************************************
 * Bridge::update -- Update the bridge.                                       *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Bridge::update(const Coord& target) {}


/******************************************************************************
 * Bridge::generate -- Generate the bridge from the result of the prim.       *
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
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Bridge::generate()
{
	pos.x = unitPos.x * BRICK_WIDTH;
	pos.y = unitPos.y * BRICK_WIDTH;

	width = unitWidth * BRICK_WIDTH;
	height = unitHeight * BRICK_WIDTH;

	offset = { width >> 1, height >> 1 };
	center = pos + offset;

	Floor tempFloor;

	tempFloor.load(RES_BRICK_FLOOR);

	floorImage.Resize(width, height);
	SetWorkingImage(&floorImage);
	for (int i = 0; i < width; i += BRICK_WIDTH)
	{
		for (int j = 0; j < height; j += BRICK_WIDTH)
			putimage(i, j, tempFloor.getImage());
	}
	SetWorkingImage(NULL);

	floor.img = &floorImage;
	floor.layer = LAYER_BACK;
	floor.pos = pos;
	floor.radian = 0.0;

	// Generate brick matrix.
	BrickMatrix brickMatrix;
	brickMatrix.resize(unitHeight, std::vector<BrickType>(unitWidth));

	for (int i = 0; i < unitHeight; i++)
	{
		for (int j = 0; j < unitWidth; j++)
		{
			if ((i == 0) || (i == unitHeight - 1) || (j == 0) || (j == unitWidth - 1))
				brickMatrix[i][j] = BRICK_WALL;
			else
				brickMatrix[i][j] = BRICK_FLOOR;
		}
	}

	int k;
	if (gateSide & DIR_LEFT)
	{
		k = (unitHeight - GATE_WIDTH) >> 1;
		for (int i = 0; i < GATE_WIDTH; i++)
			brickMatrix[k + i][0] = BRICK_FLOOR;
	}
	if (gateSide & DIR_RIGHT)
	{
		k = (unitHeight - GATE_WIDTH) >> 1;
		for (int i = 0; i < GATE_WIDTH; i++)
			brickMatrix[k + i][unitWidth - 1] = BRICK_FLOOR;
	}
	if (gateSide & DIR_UP)
	{
		k = (unitWidth - GATE_WIDTH) >> 1;
		for (int i = 0; i < GATE_WIDTH; i++)
			brickMatrix[0][k + i] = BRICK_FLOOR;
	}
	if (gateSide & DIR_DOWN)
	{
		k = (unitWidth - GATE_WIDTH) >> 1;
		for (int i = 0; i < GATE_WIDTH; i++)
			brickMatrix[unitHeight - 1][k + i] = BRICK_FLOOR;
	}

	// Add bricks to the object pool.
	Wall* tempWall;
	for (int i = 0; i < unitHeight; i++)
	{
		for (int j = 0; j < unitWidth; j++)
		{
			if (brickMatrix[i][j] == BRICK_FLOOR)
				continue;
			else
			{
				tempWall = new Wall();
				tempWall->load(RES_BRICK_WALL);
				tempWall->setPos({ pos.x + j * BRICK_WIDTH, pos.y + i * BRICK_WIDTH });
				brickPool.add(tempWall);
			}
		}
	}

	graph.init(unitWidth, unitHeight);
}



/******************************************************************************
 * Terrain::Terrain -- Constructor of the object.                             *
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
 *   2022/01/17 Tony : Created.                                               *
 *============================================================================*/
Terrain::Terrain()
{
	curSpace = nullptr;
	startSpace = nullptr;
	endSpace = nullptr;

	miniMapImage.Resize(MINI_MAP_SIZE, MINI_MAP_SIZE);
	SetWorkingImage(&miniMapImage);
	setbkcolor(TRANSPARENT_COLOR);
	setaspectratio(ASPECT_RATIO, ASPECT_RATIO);
	cleardevice();
	SetWorkingImage(NULL);

	miniMap.img = &miniMapImage;
	miniMap.layer = LAYER_HIGH;
	miniMap.radian = 0.0;
	miniMap.pos = { CANVAS_WIDTH - MINI_MAP_SIZE - 10, 10 };
}


/******************************************************************************
 * Terrain::~Terrain -- Deconstructor of the object.                          *
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
Terrain::~Terrain()
{
	for (auto it = spacePool.begin(); it != spacePool.end(); it++)
	{
		delete (*it);
	}
}


/******************************************************************************
 * Terrain::generate -- Generate the terrain.                                 *
 *                                                                            *
 *    This will generate the terrain based on some given parameters.          *
 *                                                                            *
 * INPUT:   level      -- The level of the game.                              *
 *          difficulty -- The difficulty of the game.                         *
 *          hasBoss    -- Whether the level have a boss or not.               *
 *          isDeath    -- The mode of the game.                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *   2022/02/12 Tony : Clear the space pool first.                            *
 *============================================================================*/
void Terrain::generate(int level, int difficulty, bool _hasBoss, bool _isDeath)
{
	for (auto it = spacePool.begin(); it != spacePool.end(); it++)
		delete (*it);
	spacePool.clear();


	hasBoss = _hasBoss;
	isDeath = _isDeath;

	initPrim();

	if (isDeath)
		generateDeath(level, difficulty);
	else
		generateCampaign(level, difficulty);

	generateSpace();

	// Death mode doesn't need to consider the following.
	if (isDeath)
		return;

	for (auto it = spacePool.begin(); it != spacePool.end(); it++)
	{
		(*it)->generate();
		if (*it == startSpace)
		{
			startSpace->attribute.isDiscovered = true;
			startSpace->attribute.isCurrent = true;
			startSpace->attribute.isCompleted = true;

			continue;
		}
		else if (*it == endSpace)
		{
			endSpace->attribute.isEnd = true;
			if (hasBoss)
			{
				(*it)->attribute.rounds = 1;
				(*it)->attribute.hasBoss = true;
			}
			else
				(*it)->attribute.rounds = 1 + random(0, level) + difficulty;
		}
		else if ((*it)->getType() != SpaceType::BRIDGE)
		{
			(*it)->attribute.rounds = 1 + random(0, level >> 1) + difficulty;
			(*it)->attribute.isCompleted = false;
		}
	}
}


/******************************************************************************
 * Terrain::getCurrentSpace -- Get the current space.                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the current space.                                         *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
Space* Terrain::getCurrentSpace()
{
	return curSpace;
}


/******************************************************************************
 * Terrain::update -- Update the terrain, and check for the current space.    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   target -- Coordinate of the hero.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
void Terrain::update(const Coord& target)
{
	if (!curSpace->isInside(target))
	{
		curSpace->attribute.isCurrent = false;
		for (auto it = spacePool.begin(); it != spacePool.end(); it++)
		{
			if ((*it)->isInside(target))
			{
				curSpace = *it;
				curSpace->attribute.isCurrent = true;
				curSpace->attribute.isDiscovered = true;
				break;
			}
		}
	}

	curSpace->update(target);

	generateMiniMap();
}


/******************************************************************************
 * Terrain::draw -- Draw the terrain.                                         *
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
void Terrain::draw(Camera& cam)
{	
	for (auto it = spacePool.begin(); it != spacePool.end(); it++)
		(*it)->draw(cam);
	cam.captureStatic(miniMap);
}


/******************************************************************************
 * Terrain::generateMiniMap -- Generate the mini map.                         *
 *                                                                            *
 *    The mini map will be displayed at the corner of the screen to show      *
 *    space info.
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
void Terrain::generateMiniMap()
{
	SetWorkingImage(&miniMapImage);
	cleardevice();
	SetWorkingImage(NULL);
	for (auto it = spacePool.begin(); it != spacePool.end(); it++)
		(*it)->drawMiniSpace(&miniMapImage);
}


/******************************************************************************
 * Terrain::generateCampaign -- Generate the map of campaign mode.            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   level      -- See above.                                          *
 *          difficulty -- See above.                                          *
 *          hasBoss    -- See above.                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
void Terrain::generateCampaign(int level, int difficulty)
{
	int spaceNum = 2 + random(0, MIN((MAX(level, 3) + (level >> 1) + difficulty), 9));

	randomPrim(spaceNum);
}


/******************************************************************************
 * Terrain::generateDeath -- Generate the map of the death mode.              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   level      -- See above.                                          *
 *          difficulty -- See above.
 *          hasBoss    -- See above.
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
void Terrain::generateDeath(int level, int difficulty)
{
	// On hold
}


/******************************************************************************
 * Terrain::addEdge -- Add edge to the graph.                                 *
 *                                                                            *
 *    This construct a graph with edges with random weight.                   *
 *                                                                            *
 * INPUT:   from      -- The start point of the edge.                         *
 *          to        -- The ending point of the edge.                        *
 *          direction -- The direction of the edge.                           *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
void Terrain::addEdge(int from, int to, unsigned direction)
{
	edgeList[++edgestamp].from = from;
	edgeList[edgestamp].to = to;
	edgeList[edgestamp].weight = random(0, MAX_EDGE_WEIGHT);
	edgeList[edgestamp].dir = direction;
	edgeList[edgestamp].next = headList[from];
	headList[from] = edgestamp;
}


/******************************************************************************
 * Terrain::initPrim -- Initialize the prim.                                  *
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
void Terrain::initPrim()
{
	memset(vertexFlag, 0, sizeof(vertexFlag));
	memset(edgeFlag, 0, sizeof(edgeFlag));

	memset(headList, 0, sizeof(headList));
	memset(distList, 0x3f, sizeof(distList));

	while (!primHeap.empty())
		primHeap.pop();

	for (auto it = spacePool.begin(); it != spacePool.end(); it++)
		delete (*it);
	spacePool.clear();

	edgestamp = 0;
	for (int i = 0; i < 7; i += 3)
	{
		addEdge(i, i + 1, DIR_RIGHT);
		addEdge(i + 1, i, DIR_LEFT);
		addEdge(i + 1, i + 2, DIR_RIGHT);
		addEdge(i + 2, i + 1, DIR_LEFT);
	}
	for (int i = 0; i < 3; i++)
	{
		addEdge(i, i + 3, DIR_DOWN);
		addEdge(i + 3, i, DIR_UP);
		addEdge(i + 3, i + 6, DIR_DOWN);
		addEdge(i + 6, i + 3, DIR_UP);
	}
}


/******************************************************************************
 * Terrain::randomPrim -- Perform the prim.                                   *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   start -- The starting point. The root of the tree.                *
 *          num   -- The number of nodes that is wanted.                      *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/18 Tony : Created.                                               *
 *============================================================================*/
void Terrain::randomPrim(int num)
{
	int start = random(0, num - 1);

	int cnt;
	int u, v, w, id;
	PrimToken token;

	distList[start] = 0;
	token.weight = distList[start];
	token.vertex = start;
	token.edgeId = -1;

	primHeap.push(token);

	cnt = 0;
	while (!primHeap.empty())
	{
		token = primHeap.top();
		u = token.vertex;
		w = token.weight;
		id = token.edgeId;
		primHeap.pop();

		if (vertexFlag[u])
			continue;
		vertexFlag[u] = true;
		cnt++;
		if (id != -1)
			edgeFlag[id] = true;
		if (cnt == num)
			break;

		for (int i = headList[u]; i != 0; i = edgeList[i].next)
		{
			v = edgeList[i].to;
			w = edgeList[i].weight;
			if (distList[v] > w)
			{
				distList[v] = w;
				token.weight = w;
				token.vertex = v;
				token.edgeId = i;
				primHeap.push(token);
			}
		}
	}
}


/******************************************************************************
 * Terrain::generateSpace -- Generate space list.                             *
 *                                                                            *
 *    This only roughly generates the spaces, and then we need the spaces'    *
 *    own method to finish the generation.                                    *
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
void Terrain::generateSpace()
{
	Arena* arena;
	Bridge* bridge;
	Arena* arenaList[9];
	int deg[9] = { 0 };

	std::vector<int> vertexList;

	int x, y;
	int posx, posy;
	int width, height;

	int u, v;

	for (int i = 0; i < 9; i++)
	{
		arenaList[i] = nullptr;
		if (!vertexFlag[i])
			continue;
		arena = new Arena();

		// subscript
		x = i / MAP_SIZE;
		y = i % MAP_SIZE;
		arena->setSubscript({ x, y });

		// width height
		width = randomEven(MIN_SPACE_SIZE, MAX_SPACE_SIZE);
		height = randomEven(MIN_SPACE_SIZE, MAX_SPACE_SIZE);
		arena->setUnitSize(width, height);

		// pos
		posx = y * WRAPPER_SIZE + ((WRAPPER_SIZE - width) >> 1);
		posy = x * WRAPPER_SIZE + ((WRAPPER_SIZE - height) >> 1);
		arena->setUnitPos({ posx, posy });

		arenaList[i] = arena;
		vertexList.push_back(i);
	}

	for (int i = 1; i <= edgestamp; i++)
	{
		if (!edgeFlag[i])
			continue;

		bridge = new Bridge();

		u = edgeList[i].from;
		v = edgeList[i].to;

		deg[u]++;
		deg[v]++;

		if (edgeList[i].dir == DIR_LEFT)
		{
			// arenaList[v] is on the left of arenaList[u]

			// door way
			arenaList[u]->setGateSide(DIR_LEFT);
			arenaList[v]->setGateSide(DIR_RIGHT);
			bridge->setGateSide(DIR_LEFT | DIR_RIGHT);

			// pos
			Coord pos1 = arenaList[u]->getUnitPos();
			Coord pos2 = arenaList[v]->getUnitPos();
			x = pos2.x + arenaList[v]->getUnitWidth();
			y = pos2.y + (arenaList[v]->getUnitHeight() >> 1) - 4;
			bridge->setUnitPos({ x, y });

			// size
			width = pos1.x - x;
			height = GATE_WIDTH + 2;
			bridge->setUnitSize(width, height);
		}
		else if (edgeList[i].dir == DIR_RIGHT)
		{
			// arenaList[v] is on the right of arenaList[u]

			// door way
			arenaList[u]->setGateSide(DIR_RIGHT);
			arenaList[v]->setGateSide(DIR_LEFT);
			bridge->setGateSide(DIR_LEFT | DIR_RIGHT);

			// pos
			Coord pos1 = arenaList[u]->getUnitPos();
			Coord pos2 = arenaList[v]->getUnitPos();
			x = pos1.x + arenaList[u]->getUnitWidth();
			y = pos1.y + (arenaList[u]->getUnitHeight() >> 1) - 4;
			bridge->setUnitPos({ x, y });

			// size
			width = pos2.x - x;
			height = GATE_WIDTH + 2;;
			bridge->setUnitSize(width, height);
		}
		else if (edgeList[i].dir == DIR_UP)
		{
			// arenaList[v] is on the up of arenaList[u]

			// door way
			arenaList[u]->setGateSide(DIR_UP);
			arenaList[v]->setGateSide(DIR_DOWN);
			bridge->setGateSide(DIR_UP | DIR_DOWN);

			// pos
			Coord pos1 = arenaList[u]->getUnitPos();
			Coord pos2 = arenaList[v]->getUnitPos();
			x = pos2.x + (arenaList[v]->getUnitWidth() >> 1) - 4;
			y = pos2.y + arenaList[v]->getUnitHeight();
			bridge->setUnitPos({ x, y });

			// size
			width = GATE_WIDTH + 2;
			height = pos1.y - y;
			bridge->setUnitSize(width, height);
		}
		else
		{
			// arenaList[v] is on the down of arenaList[u]

			// door way
			arenaList[u]->setGateSide(DIR_DOWN);
			arenaList[v]->setGateSide(DIR_UP);
			bridge->setGateSide(DIR_UP | DIR_DOWN);

			// pos
			Coord pos1 = arenaList[u]->getUnitPos();
			Coord pos2 = arenaList[v]->getUnitPos();
			x = pos1.x + (arenaList[u]->getUnitWidth() >> 1) - 4;
			y = pos1.y + arenaList[u]->getUnitHeight();
			bridge->setUnitPos({ x, y });

			// size
			width = GATE_WIDTH + 2;
			height = pos2.y - y;
			bridge->setUnitSize(width, height);
		}

		arenaList[u]->addNeighbor(arenaList[v]);
		arenaList[u]->addNeighbor(bridge);
		arenaList[v]->addNeighbor(arenaList[u]);
		arenaList[v]->addNeighbor(bridge);

		spacePool.push_back(bridge);
	}

	std::random_shuffle(vertexList.begin(), vertexList.end());
	auto it = vertexList.begin();
	while (it != vertexList.end())
	{
		if (deg[*it] == 1)
		{
			arenaList[*it]->setRole(SPACE_START);
			curSpace = startSpace = arenaList[*it];

			break;
		}
		it++;
	}
	if (vertexList.size() != 1)
		it++;
	while (it != vertexList.end())
	{
		if (deg[*it] == 1)
		{
			arenaList[*it]->setRole(SPACE_END);
			endSpace = arenaList[*it];

			break;
		}
		it++;
	}

	for (int i = 0; i < 9; i++)
	{
		if (arenaList[i])
			spacePool.push_back(arenaList[i]);
	}
}


/********************************************************************
** Static members of terrain.
*/
bool Terrain::vertexFlag[9];
bool Terrain::edgeFlag[30];
Edge Terrain::edgeList[30];
int Terrain::headList[9];
int Terrain::distList[9];
int Terrain::edgestamp;

std::priority_queue<PrimToken, std::vector<PrimToken>, ComparePrimToken> Terrain::primHeap;
std::vector<Space*> Terrain::spacePool;

Space* Terrain::curSpace;
Space* Terrain::startSpace;
Space* Terrain::endSpace;