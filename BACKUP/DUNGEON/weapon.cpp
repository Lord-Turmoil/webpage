/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : weapon.cpp                                *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 19, 2022                          *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For weapon object. All weapons are the same, but load different resources*
 *   and configs. It is derivated from buff.                                  *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include <easyx.h>
#include <functional>

#include "config.h"
#include "weapon.h"
#include "timing.h"
#include "command.h"
#include "auxilliary.h"


extern Time globalTimer;

extern Resource* gameResource[GAME_RES_NUM];


/******************************************************************************
 * Weapon::Weapon -- Constructor of the object.                               *
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
Weapon::Weapon(WeaponType _weaponType) : Buff(BuffType::BUFF_WEAPON)
{
	weaponType = _weaponType;

	isActivated = true;

	pOnFire = nullptr;
	pOnPickup = nullptr;
	pOnMove = nullptr;

	state = WEAPON_UNPICKUP;

	sym.layer = LAYER_NORMAL + LAYER_WEAPON;

	lastFireTimestamp = globalTimer.getTimestamp();
}


/*****************************************************************************
 * Weapon::~Weapon -- Deconstructor of the object.                            *
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
Weapon::~Weapon() {}


/******************************************************************************
 * Weapon::onFire -- Set the callback function.                               *
 *                                                                            *
 *    This binds the add() function of the bullet pool.                       *
 *                                                                            *
 * INPUT:   callback                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void Weapon::onFire(std::function<void(Bullet*)> callback)
{
	pOnFire = callback;
}


/******************************************************************************
 * Weapon::onPickup -- Set the callback function.                             *
 *                                                                            *
 *    This binds the pickupWeapon function of the hero,                       *
 *                                                                            *
 * INPUT:   callback                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void Weapon::onPickup(std::function<void(Weapon*)> callback)
{
	pOnPickup = callback;
}


/******************************************************************************
 * Weapon::onMove -- Set the callback function.                               *
 *                                                                            *
 *    This binds the figure's getPos() function to change the position of the *
 *    weapon.                                                                 *
 *                                                                            *
 * INPUT:   callback                                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void Weapon::onMove(std::function<Coord(void)> callback)
{
	pOnMove = callback;
}


/******************************************************************************
 * Weapon::getWeaponType -- Get the type of the weapon.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the type of the weapon.                                    *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
WeaponType Weapon::getWeaponType() const
{
	return weaponType;
}


/******************************************************************************
 * Weapon::getState -- Get the state of the weapon.                           *
 *                                                                            *
 *    Perhaps it doesn't need to exist.                                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the state of the weapon.                                   *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
WeaponState Weapon::getState() const
{
	return state;
}


/******************************************************************************
 * Weapon::getBulletType -- Get the type of the bullet.                       *
 *                                                                            *
 *    Hmm... Perhaps... we don't need this, neither.                          *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the bullet type of the weapon.                             *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
BulletType Weapon::getBulletType() const
{
	return bulletType;
}


/******************************************************************************
 * Weapon::getCost -- Get the cost of the weapon.                             *
 *                                                                            *
 *    Hmm... Perhaps... we don't need this, neither.                          *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the cost of the weapon.                                    *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/17 Tony : Created.                                               *
 *============================================================================*/
int Weapon::getCost() const
{
	return cost;
}


/******************************************************************************
 * Weapon::load -- Load weapon resources.                                     *
 *                                                                            *
 *    All the weapons share the same code, only differ in their resources.    *
 *                                                                            *
 * INPUT:   resId                                                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void Weapon::load(GameResourceId resId)
{
	WeaponRes* res = dynamic_cast<WeaponRes*>(gameResource[resId]);

	name = res->name;
	coolingTime = res->coolingTime;
	cost = res->cost;
	offset = res->offset;
	muzzleOffset = res->muzzleOffset;

	auto pos = BULLET_TYPE_MAP.find(res->bulletType);
	if (pos != BULLET_TYPE_MAP.end())
		bulletType = pos->second;

	pFrame = &(res->frame);
	anim.load(pFrame);

	width = res->width;
	height = res->height;
	imgOffset = res->imgOffset;

	radius = offset.y - muzzleOffset.y;
	bulletOffset = muzzleOffset - offset;

	anim.update();
	sym.img = anim.getFrame();
	sym.offset = imgOffset - offset;
}


/******************************************************************************
 * Weapon::update -- Update the weapon.                                       *
 *                                                                            *
 *    The weapon can be picked up by heroes, and need to change the direction *
 *    if equipped. Well... this will update the symbol by the way.            *
 *                                                                            *
 * INPUT:   cmd   -- Command from the user.                                   *
 *          coord -- The coordinate of the hero.                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void Weapon::update(const Command& cmd, const Coord& coord)
{
	/*
	** If the weapon is not picked up yet... well, it can't react to
	** the hero, it can only be picked up. :)
	*/
	if (state == WEAPON_UNPICKUP)
	{
		if ((cmd.commandType & CMD_ACTIVATE) && (this->hit(coord)))
			pOnPickup(this);
		else
			return;
	}

	Coord center = pOnMove();
	setCenter(center);
	Coord dir = target - center;

	facing = (int)(dir.x < 0);
	
	sym.radian = getRadian(dir, radius, true);

	anim.update(WEAPON_MOTION_MAP[state]);
	updateState();
}


/******************************************************************************
 * Weapon::draw -- Draw the weapon.                                           *
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
 *============================================================================*/
void Weapon::draw(Camera& cam)
{
	if (!isActivated || isHidden || !isValid)
		return;
	
	if (state == WEAPON_UNEQUIPPED)
		return;

	sym.img = anim.getFrame(facing);
	sym.pos = pOnMove();

	cam.capture(sym);
}


/******************************************************************************
 * Weapon::setState -- Set the state of the object.                           *
 *                                                                            *
 *    I'm not really sure about this one. Perhaps it should be a private one. *
 *                                                                            *
 * INPUT:   _state -- The state to be set.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void Weapon::setState(WeaponState _state)
{
	state = WEAPON_STATE_MACHINE[state][_state];
}


/******************************************************************************
 * Weapon::updateState -- Update the state of the weapon.                     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _state -- The new state of the weapon.                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *   2022/01/23 Tony : Only check for animation state.                        *
 *============================================================================*/
void Weapon::updateState()
{
	if ((state == WEAPON_ONFIRE) && anim.over())
	{
		lastFireTimestamp = globalTimer.getTimestamp();
		setState(WEAPON_END);
	}

	if (state == WEAPON_COOLING)
	{
		if (globalTimer.getTimestamp() - lastFireTimestamp > coolingTime)
			setState(WEAPON_END);
	}
}


/******************************************************************************
 * Weapon::aim -- Aim the target.                                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   target -- The coordinate of the target... The hero or the mouse.  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
void Weapon::aim(const Coord& _target)
{
	target = _target;
}


/******************************************************************************
 * Weapon::fire -- Open FIRE!!!                                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   target -- The coordinate of the target... The hero or the mouse.  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
bool Weapon::fire()
{
	if (state != WEAPON_READY)
		return false;

	Coord center = getCenter();
	Coord src;
	double radian = getRadian(target - center, radius, true);
	if (facing == 0)
		src = center + rotate(bulletOffset, radian);
	else
		src = center + rotate(-bulletOffset, radian);

	pOnFire(getBullet(bulletType, src, target - center));

	setState(WEAPON_ONFIRE);

	return true;
}


/******************************************************************************
 * Weapon::move -- Move the weapon.                                           *
 *                                                                            *
 *    Hmm... weapon doesn't move.                                             *
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
void Weapon::move() {}



/******************************************************************************
 * getWeapon -- Get a weapon from the type.                                   *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   type -- The type of the desired weapon.                           *
 *                                                                            *
 * OUTPUT:  Return a new weapon in the heap.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Weapon* getWeapon(WeaponType type)
{
	Weapon* weapon = new Weapon(type);

	switch (type)
	{
	case WEAPON_PISTOL:
		weapon->load(RES_WEAPON_PISTOL);
		break;
	case WEAPON_RIFLE:
		weapon->load(RES_WEAPON_RIFLE);
		break;
	case WEAPON_FLAME:
		weapon->load(RES_WEAPON_FLAME);
		break;
	case WEAPON_FLAMEX:
		weapon->load(RES_WEAPON_FLAMEX);
		break;
	default:
		delete weapon;
		weapon = nullptr;
		break;
	}

	return weapon;
}



/******************************************************************************
 * WeaponSlot::WeaponSlot -- Constructor of the object.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _capacity -- The capacity of the weapon slot.                     *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
WeaponSlot::WeaponSlot(int _capacity)
{
	capacity = _capacity;
	curWeapon = -1;
}


/******************************************************************************
 * WeaponSlot::~WeaponSlot -- Deconstructor of the object.                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  All the weapons are stored in buff pool, so there's no need to  *
 *            delete them here. But drop them, we must.                       *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
WeaponSlot::~WeaponSlot() {}


/******************************************************************************
 * WeaponSlot::setCapacity -- Set the capacity of the weapon slot.            *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _capacity -- The capacity of the weapon slot.                     *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void WeaponSlot::setCapacity(int _capacity)
{
	capacity = _capacity;

	if (capacity == 0)
	{
		weaponList.clear();
		curWeapon = -1;
		return;
	}
	if (weaponList.size() > capacity)
	{
		curWeapon = capacity - 1;
		while (weaponList.size() > capacity)
			weaponList.pop_back();
	}
}


/******************************************************************************
 * WeaponSlot::update -- Update all weapons.                                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cmd    -- Command from the user.                                  *
 *          target -- The target of the weapon.                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
void WeaponSlot::update(const Command& cmd, Coord target)
{
	if (curWeapon != -1)
		weaponList[curWeapon]->update(cmd, target);
}


/******************************************************************************
 * WeaponSlot::draw -- Draw the weapon.                                       *
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
 *============================================================================*/
void WeaponSlot::draw(Camera& cam)
{
	if (curWeapon != -1)
		weaponList[curWeapon]->draw(cam);
}


/******************************************************************************
 * WeaponSlot::pickup -- Pick up a weapon.                                    *
 *                                                                            *
 *    To pick up a weapon and add it to the slot. However, this may drop old  *
 *    weapon and the current weapon is the first choice.                      *
 *                                                                            *
 * INPUT:   weapon -- The weapon to pick up.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *   2022/01/22 Tony : Changed the way the weapon is picked up.               *
 *   2022/02/18 Tony : Fixed the failure of the first weapon.                 *
 *============================================================================*/
void WeaponSlot::pickup(Weapon* weapon)
{
	if (capacity == 0)
		return;

	weapon->setState(WEAPON_READY);

	// Check for the first one.
	if (weaponList.size() == 0)
	{
		weaponList.push_back(weapon);
		curWeapon = 0;
		return;
	}
	
	// The weapon slot is full or not.
	if (weaponList.size() == capacity)
	{
		weaponList[curWeapon]->setState(WEAPON_UNPICKUP);
		weaponList[curWeapon] = weapon;
	}
	else
	{
		weaponList[curWeapon]->setState(WEAPON_UNEQUIPPED);
		weaponList.push_back(weapon);
		curWeapon = (int)(weaponList.size() - 1);
	}
}



/******************************************************************************
 * WeaponSlot::switchWeapon -- Switch weapon.                                 *
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
void WeaponSlot::switchWeapon()
{
	if ((capacity == 0) || weaponList.empty())
		return;

	if (weaponList.size() == 1)
		return;

	static clock_t lastTime = 0;
	if (clock() - lastTime < 200)
		return;
	
	lastTime = clock();

	weaponList[curWeapon]->setState(WEAPON_UNEQUIPPED);
	curWeapon++;
	if (curWeapon == weaponList.size())
		curWeapon = 0;
	weaponList[curWeapon]->setState(WEAPON_READY);
}


/******************************************************************************
 * WeaponSlot::aim -- Aim the target.                                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   target -- The target of the firing.                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
void WeaponSlot::aim(const Coord& target)
{
	if (curWeapon != -1)
		weaponList[curWeapon]->aim(target);
}


/******************************************************************************
 * WeaponSlot::fire -- Make current weapon fire.                              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   target      -- The target of the firing.                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
bool WeaponSlot::fire()
{
	if (curWeapon != -1)
		return weaponList[curWeapon]->fire();

	return false;
}


/******************************************************************************
 * WeaponSlot::fire -- Make current weapon fire.                              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   target      -- The target of the firing.                          *
 *          mp          -- The mp of the figure.                              *
 *          collisionId -- The collision id of the bullet.                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/19 Tony : Created.                                               *
 *============================================================================*/
bool WeaponSlot::fire(int& mp)
{
	if (curWeapon != -1)
	{
		if (mp > weaponList[curWeapon]->cost)
		{
			if (weaponList[curWeapon]->fire())
			{
				mp -= weaponList[curWeapon]->cost;
				return true;
			}
		}
	}

	return false;
}


/******************************************************************************
 * WeaponSlot::hide -- Hide the weapon.                                       *
 *                                                                            *
 *    It just hide the current weapon temporarily.                            *
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
void WeaponSlot::hide()
{
	if (curWeapon != -1)
		weaponList[curWeapon]->isHidden = true;
}


 /******************************************************************************
  * WeaponSlot::reveal -- Reveal the weapon.                                   *
  *                                                                            *
  *    It just reveal the current weapon.                                      *
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
void WeaponSlot::reveal()
{
	if (curWeapon != -1)
		weaponList[curWeapon]->isHidden = false;
}


/******************************************************************************
 * WeaponSlot::clear -- Clear the weapons in the slot.                        *
 *                                                                            *
 *    It doesn't actually delete the weapon, it just drop them and then they  *
 *    will be handled by the buff pool.                                       *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/24 Tony : Created.                                               *
 *   2022/02/12 Tony : Changed set invalid to just drop them.                 *
 *   2022/02/18 Tony : 
 *============================================================================*/
void WeaponSlot::clear()
{
	for (auto it = weaponList.begin(); it != weaponList.end(); it++)
	{
		(*it)->setState(WeaponState::WEAPON_UNPICKUP);
		(*it)->isValid = false;
	}
	weaponList.clear();
}
