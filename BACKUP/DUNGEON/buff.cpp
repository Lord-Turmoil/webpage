/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : buff.cpp                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 22, 2022                          *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For buffs in game, including weapon, create, coin, ammo, stair.          *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include "buff.h"
#include "weapon.h"
#include "config.h"
#include "define.h"
#include "timing.h"


extern Time globalTimer;

extern Resource* gameResource[GAME_RES_NUM];

/******************************************************************************
 * Buff::Buff -- Constructor of the object.                                   *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _type                                                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
Buff::Buff(BuffType _type) : Object(ObjectType::BUFF)
{
	buffType = _type;
	isActivated = false;
}


/******************************************************************************
 * Buff::~Buff -- Deconstructor of the object.                                *
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
Buff::~Buff() {}


/******************************************************************************
 * Buff::getName -- Get the name of the buff.                                 *
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
std::wstring Buff::getName() const
{
	return name;
}


/******************************************************************************
 * Buff::getBuffType -- Get the type of the buff.                             *
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
BuffType Buff::getBuffType() const
{
	return buffType;
}


/******************************************************************************
 * Buff::draw -- Draw the buff.                                               *
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
 *   2022/01/24 Tony : Created.                                               *
 *============================================================================*/
void Buff::draw(Camera& cam)
{
	if (!isActivated || isHidden)
		return;

	sym.img = anim.getFrame();
	sym.pos = getCenter();

	cam.capture(sym);
}


/******************************************************************************
 * Buff::move -- Buff doesn't move.                                           *
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
void Buff::move() {}



/******************************************************************************
 * Create::Create -- Constructor of the object.                               *
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
Create::Create() : Buff(BuffType::BUFF_CREATE)
{
	pOnOpen = nullptr;
	isOpen = false;
	isActivated = true;
	state = CREATE_CLOSED;

	content = nullptr;

	sym.layer = LAYER_NORMAL - 1;
}


/******************************************************************************
 * Create::~Create -- Deconstructor of the object.                            *
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
Create::~Create()
{
	/*
	** If the create is not open, then its contents are not added to
	** the buff list, so they should be deleted here.
	*/
	if (content)
		delete content;
}


/******************************************************************************
 * Create::onOpen -- Set the callback function.                               *
 *                                                                            *
 *    This is called when the create is opened by the hero.                   *
 *                                                                            *
 * INPUT:   callback                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Create::onOpen(std::function<void(Buff*)> callback)
{
	pOnOpen = callback;
}


/******************************************************************************
 * Create::load -- Load resouce.                                              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   resId                                                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Create::load(GameResourceId resId)
{
	BuffRes* res = dynamic_cast<BuffRes*>(gameResource[RES_BUFF_CREATE]);

	offset = res->offset;

	name = res->name;
	
	pFrame = &(res->frame);
	anim.load(pFrame);

	width = res->width;
	height = res->height;
	imgOffset = res->imgOffset;

	sym.offset = imgOffset - offset;
	anim.update();
}


/******************************************************************************
 * Create::update -- Update the create.                                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cmd    -- Command from the player.                                *
 *          target -- Coordinate of the hero.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Create::update(const Command& cmd, const Coord& target)
{
	if (state == CREATE_OPEN)
	{
		if (content)
		{
			content->setHidden(false);
			pOnOpen(content);
			content = nullptr;
		}

		return;
	}

	if ((cmd.commandType & CMD_ACTIVATE) && inRange(target))
	{
		isOpen = true;
		setState(CREATE_OPEN);
		fill();
	}

	anim.update(CREATE_MOTION_MAP[state]);
	updateState();
}



/******************************************************************************
 * Create::setState -- Set the state of the create.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _state -- New state.                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Create::setState(CreateState _state)
{
	state = CREATE_STATE_MACHINE[state][_state];
}


/******************************************************************************
 * Create::updateState -- Update create state.                                *
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
 *   2022/01/23 Tony : Only check for animation state.                        *
 *============================================================================*/
void Create::updateState()
{
	if (anim.over())
		setState(CREATE_END);
}


/******************************************************************************
 * Create::inRange -- Check if target is in range.                            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   target                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
bool Create::inRange(const Coord& target)
{
	return (getDistance(target, getCenter()) < (double)(width + height));
}


/******************************************************************************
 * Create::fill -- Fill the create.                                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   target                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
void Create::fill()
{
	content = getWeapon(WEAPON_PISTOL);
	content->setHidden(true);
	content->setCenter(getCenter());
}


/******************************************************************************
 * Gold::Gold -- Constructor of the object.                                   *
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
Gold::Gold() : Buff(BuffType::BUFF_GOLD)
{
	pOnCollect = nullptr;
	isActivated = true;
	sym.layer = LAYER_HIGH;
}


/******************************************************************************
 * Gold::~Gold -- Deconstructor of the object.                                *
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
Gold::~Gold() {}


/******************************************************************************
 * Gold::onCollect -- Set the callback function.                              *
 *                                                                            *
 *    This will not be called until the gold is collected by the hero.        *
 *                                                                            *
 * INPUT:   callback                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Gold::onCollect(std::function<void(int)> callback)
{
	pOnCollect = callback;
}


/******************************************************************************
 * Gold::load -- Load the gold.                                               *
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
void Gold::load(GameResourceId resId)
{
	BuffRes* res = dynamic_cast<BuffRes*>(gameResource[RES_BUFF_GOLD]);

	offset = res->offset;

	name = res->name;
	
	pFrame = &(res->frame);
	anim.load(pFrame);
	
	speed = res->speed;
	value = res->value;

	width = res->width;
	height = res->height;
	imgOffset = res->imgOffset;

	
	sym.layer = LAYER_NORMAL;
	sym.offset = imgOffset - offset;
}


/******************************************************************************
 * Gold::update -- Update the gold.                                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cmd    -- Command from the player.                                *
 *          target -- The coordinate of the hero.                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Gold::update(const Command& cmd, const Coord& target)
{
	if (!isActivated)
		return;

	Coord center = pos + offset;
	double dist = getDistance(center, target);
	double step;

	step = speed * globalTimer.getDeltaTime() * dist * dist * GOLD_SPEED_COF;
	step = MAX(step, 5.0);

	// Already very close.
	if (step > dist)
	{
		center = target;
		pos = center - offset;
		pOnCollect(value);
		isValid = false;
		return;
	}

	Coord dir = target - center;
	Vector vec;

	vec.x = (double)dir.x;
	vec.y = (double)dir.y;

	vec = getUnit(vec) * step;
	center.x += (int)vec.x;
	center.y += (int)vec.y;
	pos = center - offset;

	anim.update();
}




/******************************************************************************
 * Ammo::Ammo -- Constructor of the object.                                   *
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
Ammo::Ammo() : Buff(BuffType::BUFF_AMMO)
{
	pOnCollect = nullptr;
	isActivated = true;
	sym.layer = LAYER_HIGH;
}


/******************************************************************************
 * Ammo::~Ammo -- Deconstructor of the object.                                *
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
Ammo::~Ammo() {}


/******************************************************************************
 * Ammo::onCollet -- Set the callback function.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   callback                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Ammo::onCollect(std::function<void(int)> callback)
{
	pOnCollect = callback;
}


/******************************************************************************
 * Ammo::load -- Load the resource.                                           *
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
void Ammo::load(GameResourceId resId)
{
	BuffRes* res = dynamic_cast<BuffRes*>(gameResource[RES_BUFF_AMMO]);
	
	offset = res->offset;

	name = res->name;

	pFrame = &(res->frame);
	anim.load(pFrame);
	
	speed = res->speed;
	value = res->value;

	width = res->width;
	height = res->height;
	imgOffset = res->imgOffset;


	sym.offset = imgOffset - offset;
	anim.update();
}


/******************************************************************************
 * Ammo::update -- Update ammo state.                                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cmd                                                               *
 *          target                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Ammo::update(const Command& cmd, const Coord& target)
{
	if (!isActivated)
		return;

	Coord center = pos + offset;
	double dist = getDistance(center, target);
	double step;

	step = speed * globalTimer.getDeltaTime() * dist * dist * AMMO_SPEED_COF;
	step = MAX(step, 5);

	// Already very close.
	if (step > dist)
	{
		center = target;
		pos = center - offset;
		pOnCollect(value);
		isValid = false;
		return;
	}

	Coord dir = target - center;
	Vector vec;

	vec.x = (double)dir.x;
	vec.y = (double)dir.y;

	vec = getUnit(vec) * step;
	center.x += (int)vec.x;
	center.y += (int)vec.y;
	pos = center - offset;

	anim.update();
}



/******************************************************************************
 * Portal::Portal -- Constructor of the object.                               *
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
Portal::Portal() : Buff(BuffType::BUFF_PORTAL)
{
	isActivated = true;
	pOnActivate = nullptr;

	sym.layer = LAYER_NORMAL - 1;
}


/******************************************************************************
 * Portal::~Portal -- Deconstructor of the object.                            *
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
Portal::~Portal() {}


/******************************************************************************
 * Portal::onActive -- Set the callback function.                             *
 *                                                                            *
 *    This will be called when the hero triggers the stair.                   *
 *                                                                            *
 * INPUT:   callback                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Portal::onActive(std::function<void(void)> callback)
{
	pOnActivate = callback;
}


/******************************************************************************
 * Portal::load -- Load stair resource.                                       *
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
void Portal::load(GameResourceId resId)
{
	BuffRes* res = dynamic_cast<BuffRes*>(gameResource[RES_BUFF_PORTAL]);
	
	offset = res->offset;

	name = res->name;

	pFrame = &(res->frame);
	anim.load(pFrame);

	width = res->width;
	height = res->height;
	imgOffset = res->imgOffset;

	sym.offset = imgOffset - offset;
	anim.update();
}


/******************************************************************************
 * Portal::update -- Update the stair.                                        *
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
void Portal::update(const Command& cmd, const Coord& target)
{
	if (!isActivated)
		return;

	if ((cmd.commandType & CMD_ACTIVATE) && hit(target) && (state == PORTAL_OPEN))
	{
		isActivated = true;
		pOnActivate();
		isValid = false;
		return;
	}

	anim.update(PORTAL_MOTION_MAP[state]);
	updateState();
}


/******************************************************************************
 * Portal::setState -- Set the portal's state.                                *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _state                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void Portal::setState(PortalState _state)
{
	state = PORTAL_STATE_MACHINE[state][_state];
}


/******************************************************************************
 * Portal::updateState -- Update the state of portal.                         *
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
void Portal::updateState()
{
	if (anim.over())
		setState(PORTAL_END);
}



/******************************************************************************
 * BuffPool::BuffPool -- Constructor of the object.                           *
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
BuffPool::BuffPool() {}


/******************************************************************************
 * BuffPool::~BuffPool -- Deconstructor of the object.                        *
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
BuffPool::~BuffPool()
{
	for (auto it = pool.begin(); it != pool.end(); it++)
		delete (*it);
}



void BuffPool::add(Buff* buff)
{
	pool.push_back(buff);
}


/******************************************************************************
 * BuffPool::clear -- Clear the buffPool.                                     *
 *                                                                            *
 *    If remove is false, then it will keep all weapons that is picked up.    *
 *                                                                            *
 * INPUT:   remove -- Whether remove all items.                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  This must be called after all figures are deconstructed, because*
 *            it may only delete weapons that not picked up by figures.       *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/23 Tony : Created.                                               *
 *============================================================================*/
void BuffPool::clear(bool remove)
{
	if (remove)
	{
		for (auto it = pool.begin(); it != pool.end(); it++)
			delete (*it);
		pool.clear();
	}
	else
	{
		auto it = pool.begin();
		while (it != pool.end())
		{
			if ((*it)->getBuffType() == BuffType::BUFF_WEAPON)
			{
				// only delete unpicked-up weapons
				if (dynamic_cast<Weapon*>(*it)->getState() == WeaponState::WEAPON_UNPICKUP)
				{
					delete (*it);
					it = pool.erase(it);
					continue;
				}
			}
			else
			{
				delete (*it);
				it = pool.erase(it);
				continue;
			}
			it++;
		}
	}
}


/******************************************************************************
 * BuffPool::update -- Update all buffs in the pool.                          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cmd    -- Command from the player.                                *
 *          target -- Coordinate of the hero.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void BuffPool::update(const Command& cmd, const Coord& target)
{
	for (auto it = pool.begin(); it != pool.end(); it++)
		(*it)->update(cmd, target);
}


/******************************************************************************
 * BuffPool::draw -- Draw all buffs in the pool.                              *
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
void BuffPool::draw(Camera& cam)
{
	auto it = pool.begin();
	while (it != pool.end())
	{
		if (!(*it)->isValid)
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
 * getBuff -- Get a buff.                                                     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the desired buff.                                          *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
Buff* getBuff(BuffType type)
{
	Buff* buff;

	switch (type)
	{
	case BUFF_AMMO:
		buff = new Ammo();
		break;
	case BUFF_GOLD:
		buff = new Gold();
		break;
	default:
		buff = nullptr;
		break;
	}

	if (buff)
		buff->load();

	return buff;
}