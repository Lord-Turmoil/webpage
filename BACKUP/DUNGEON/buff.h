/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : buff.h                                    *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 11, 2022                          *
 *                                                                            *
 *                    Last Update : January 12, 2022                          *
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

#ifndef _BUFF_H_
#define _BUFF_H_

#include <ctime>
#include <vector>
#include <easyx.h>
#include <functional>

#include "camera.h"
#include "object.h"
#include "command.h"
#include "animation.h"


/********************************************************************
** Base class of all buffs.
*/
class Buff : public Object
{
public:
	Buff(BuffType _type);
	virtual ~Buff();

	std::wstring getName() const;
	BuffType getBuffType() const;

	virtual void load(GameResourceId resId = RES_VOID) = 0;

	/*
	** All buffs need command and hero's coordinate.
	*/
	virtual void update(const Command& cmd, const Coord& target) = 0;

	virtual void draw(Camera& cam);

	virtual void move();

	bool isActivated;

protected:

	BuffType buffType;

	/*
	** The name of the buff.
	*/
	std::wstring name;
};

class Weapon;

/********************************************************************
** For create. A create contains many buffs. It creates them, save a
** copy of them and hand them to the buff pool of the game after
** setting them to hidden. Then, when it is activated, it set them
** to visible through the copies, and set itself to invalid. :)
** The contents are randomly generated based on a few combinations.
*/
enum CreateState
{
	CREATE_CLOSED = 0,
	CREATE_OPENING,
	CREATE_OPEN,
	CREATE_END,			// a motion ends
	CREATE_STATE_NUM,
};


/********************************************************************
** Create state machine.
**   0 1 2 3 4
** 0 0 1 1 0 0
** 1 3 1 1 3 2
** 2 3 2 2 3 2
** 3 3 1 1 3 0
** 4 4 4 4 4 4
*/
const CreateState CREATE_STATE_MACHINE[CREATE_STATE_NUM][CREATE_STATE_NUM] = {
	{ CREATE_CLOSED,	CREATE_OPENING,	CREATE_OPENING,	CREATE_CLOSED },
	{ CREATE_CLOSED,	CREATE_OPENING,	CREATE_OPENING,	CREATE_OPEN },
	{ CREATE_CLOSED,	CREATE_OPEN,	CREATE_OPEN,	CREATE_OPEN } };

const int CREATE_MOTION_MAP[CREATE_STATE_NUM] = { 0, 1, 2, -1};

class Create : public Buff
{
public:
	Create();
	~Create();

	void onOpen(std::function<void(Buff*)> callback);

	virtual void load(GameResourceId resId = RES_VOID);

	virtual void update(const Command& cmd, const Coord& target);

private:
	void setState(CreateState _state);
	void updateState();
	bool inRange(const Coord& target);
	void fill();

	bool isOpen;

	CreateState state;

	Weapon* content;

	/*
	** When the create is open, it call this function to add
	** its buffs to the buffpool. The function belongs to the
	** buff pool.
	*/
	std::function<void(Buff*)> pOnOpen;
};


/********************************************************************
** For gold. When coins are collected, it should have a callback to
** add scores.
*/
const double GOLD_SPEED_COF = 0.0001;

class Gold : public Buff
{
public:
	Gold();
	~Gold();

	/*
	** Here we sshould bind the game info to it.
	*/
	void onCollect(std::function<void(int)> callback);

	virtual void load(GameResourceId res = RES_VOID);

	virtual void update(const Command& cmd, const Coord& target);

private:

	/*
	** The function called after being collected by the
	** hero. It is the games add score.
	*/
	std::function<void(int)> pOnCollect;

	double speed;
	int value;
};


/********************************************************************
** Ammo are used to add mp to the hero. It flies after the hero.
*/
const double AMMO_SPEED_COF = 0.0001;

class Ammo : public Buff
{
public:
	Ammo();
	~Ammo();

	void onCollect(std::function<void(int)> callback);

	virtual void load(GameResourceId res = RES_VOID);

	virtual void update(const Command& cmd, const Coord& target);

private:

	/*
	** The function to be called after being collected by
	** hero. The function it bind is to heal hero's mp.
	*/
	std::function<void(int)> pOnCollect;

	double speed;
	int value;
};



/********************************************************************
** Portal is the pathway to the next level.
** When it is activated, it tells the game via game info to go next
** level. :) It is owned by the game, but there is a copy in the
** object list.
*/
enum PortalState
{
	PORTAL_INIT,
	PORTAL_OPEN,
	PORTAL_END,

	PORTAL_STATE_NUM
};

const PortalState PORTAL_STATE_MACHINE[PORTAL_STATE_NUM][PORTAL_STATE_NUM] = {
	{ PORTAL_INIT, PORTAL_INIT, PORTAL_OPEN },
	{ PORTAL_INIT, PORTAL_OPEN, PORTAL_OPEN } };

const int PORTAL_MOTION_MAP[PORTAL_STATE_NUM] = { 0, 1, -1 };

class Portal : public Buff
{
public:
	Portal();
	~Portal();

	void onActive(std::function<void(void)> callback);

	virtual void load(GameResourceId resId = RES_VOID);

	virtual void update(const Command& cmd, const Coord& target);

private:
	void setState(PortalState _state);
	void updateState();

	PortalState state;

	/*
	** The function called when activated. It set the
	** game to go next level.
	*/
	std::function<void(void)> pOnActivate;
};



/********************************************************************
** Buff pool is used to take hold of all buffs. :?
*/
class BuffPool
{
public:
	BuffPool();
	~BuffPool();

	void add(Buff* buff);
	void clear(bool remove = false);
	void update(const Command& cmd, const Coord& target);
	void draw(Camera& cam);

private:
	std::vector<Buff*> pool;
};


/********************************************************************
** new a buff. This can also... get a weapon through getWeapon in
** weapon.h.
*/
Buff* getBuff(BuffType type);

#endif