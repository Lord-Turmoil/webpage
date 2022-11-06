/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : weapon.h                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 13, 2022                          *
 *                                                                            *
 *                    Last Update : January 25, 2022                          *
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


#ifndef _WEAPON_H_
#define _WEAPON_H_


#include <map>
#include <string>
#include <vector>
#include <easyx.h>
#include <functional>

#include "buff.h"
#include "define.h"
#include "bullet.h"


/********************************************************************
** Weapon's state.
**   0 1 2 3 4 5
** 0 0 1 2 0 0 0
** 1 0 1 2 1 1 1
** 2 0 1 2 3 2 2
** 3 0 1 3 3 3 4
** 4 0 1 4 4 4 2
** 5 0 1 5 5 5 5
*/
enum WeaponState
{
	WEAPON_UNPICKUP = 0,
	WEAPON_UNEQUIPPED,
	WEAPON_READY,
	WEAPON_ONFIRE,
	WEAPON_COOLING,
	WEAPON_END,

	WEAPON_STATE_NUM,
};

const WeaponState WEAPON_STATE_MACHINE[WEAPON_STATE_NUM][WEAPON_STATE_NUM] = {
	{ WEAPON_UNPICKUP,	WEAPON_UNEQUIPPED,	WEAPON_READY,	WEAPON_UNPICKUP,	WEAPON_UNPICKUP,	WEAPON_UNPICKUP },
	{ WEAPON_UNPICKUP,	WEAPON_UNEQUIPPED,	WEAPON_READY,	WEAPON_UNEQUIPPED,	WEAPON_UNEQUIPPED,	WEAPON_UNEQUIPPED },
	{ WEAPON_UNPICKUP,	WEAPON_UNEQUIPPED,	WEAPON_READY,	WEAPON_ONFIRE,		WEAPON_READY,		WEAPON_READY },
	{ WEAPON_UNPICKUP,	WEAPON_UNEQUIPPED,	WEAPON_ONFIRE,	WEAPON_ONFIRE,		WEAPON_ONFIRE,		WEAPON_COOLING },
	{ WEAPON_UNPICKUP,	WEAPON_UNEQUIPPED,	WEAPON_COOLING,	WEAPON_COOLING,		WEAPON_COOLING,		WEAPON_READY } };

const int WEAPON_MOTION_MAP[WEAPON_STATE_NUM] = { -1, -1, 0, 1, 0, -1 };

class Weapon : public Buff
{
public:
	Weapon(WeaponType _weaponType);
	~Weapon();

	void setState(WeaponState _state);
	void onFire(std::function<void(Bullet*)> callback);
	void onPickup(std::function<void(Weapon*)> callback);
	void onMove(std::function<Coord(void)> callback);

	WeaponType getWeaponType() const;
	WeaponState getState() const;
	BulletType getBulletType() const;
	int getCost() const;

	virtual void load(GameResourceId resId);

	virtual void update(const Command& cmd, const Coord& target);
	virtual void draw(Camera& cam);

	void aim(const Coord& _target);
	bool fire();

private:
	friend class WeaponSlot;

	void updateState();

	virtual void move();

	WeaponType weaponType;
	WeaponState state;

	clock_t coolingTime;
	clock_t lastFireTimestamp;

	BulletType bulletType;

	Coord target;

	int cost;

	/*
	** 2022/02/18
	** The offset to the muzzle. :(
	*/
	Coord muzzleOffset;
	
	/*
	** This is from center to muzzle.
	*/
	Coord bulletOffset;

	int facing;

	/*
	** 2022/02/18
	** The rotation radius of the weapon. For better aiming.
	*/
	int radius;

	/*
	** The callback function to call when open fire, to
	** add bullet(s) to  the bullet pool.
	*/
	std::function<void(Bullet*)> pOnFire;

	/*
	** 2022/01/19
	** This is for the hero to pick up weapon.
	*/
	std::function<void(Weapon*)> pOnPickup;

	/*
	** 2022/01/19
	** This one binds the figure's getPos() function, to
	** adjust coordinate.
	*/
	std::function<Coord(void)> pOnMove;
};


/********************************************************************
** new a weapon base on the weapon type.
*/
Weapon* getWeapon(WeaponType type);


/********************************************************************
** Weapon slot is the... slot of weapon for the figures.
*/
class WeaponSlot
{
public:
	WeaponSlot(int _capacity = 0);
	~WeaponSlot();

	void setCapacity(int _capacity);
	void update(const Command& cmd, Coord target);
	void draw(Camera& cam);
	void pickup(Weapon* weapon);
	void switchWeapon();
	void aim(const Coord& target);
	bool fire();
	bool fire(int& mp);

	// Hide or reveal the weapon temporarily.
	void hide();
	void reveal();
	
	/*
	** 2022/01/24
	** Clear all weapons by setting them invalid, and then
	** they will be deleted by the buff pool.
	** 2022/02/12
	** Clear all weapons by... drop them...
	*/
	void clear();

private:
	int capacity;
	std::vector<Weapon*> weaponList;
	int curWeapon;
};

#endif