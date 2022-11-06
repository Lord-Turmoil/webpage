/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : figure.cpp                                *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 23, 2022                          *
 *                                                                            *
 *                    Last Update : February 18, 2022                         *
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

#include <easyx.h>
#include <functional>

#include "figure.h"
#include "timing.h"
#include "auxilliary.h"

extern Time globalTimer;

extern Resource* gameResource[GAME_RES_NUM];


/******************************************************************************
 * Figure::Figure -- Constructor of the object.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _figureType -- The type of the figure.                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
Figure::Figure(FigureType _figureType) : PhysicalObject(ObjectType::FIGURE)
{
	figureType = _figureType;

	pOnFire = nullptr;

	pFrame = nullptr;

	hpGap[0] = mpGap[0] = amorGap[0] = chiGap[0] = globalTimer.getTimestamp();

	facing = 0;

	sym.layer = LAYER_NORMAL;
	/*
	** Others will be initialized in load().
	*/
}


/******************************************************************************
 * Figure::~Figure -- Deconstructor of the object.                            *
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
 *   2022/01/24 Tony : Figure will now clear his... or her weapon slot.       *
 *   2022/02/18 Tony : Hero will not clear his weapon slot.
 *============================================================================*/
Figure::~Figure() {}


/******************************************************************************
 * Figure::onFire -- Set the callback function.                               *
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
void Figure::onFire(std::function<void(Bullet*)> callback)
{
	pOnFire = callback;
}


/******************************************************************************
 * Figure::getPrimaryWeapon -- Get the primary weapon list.                   *
 *                                                                            *
 *    Since all figures have their primary weapon which is/are carried when   *
 *    they are created, so there should be such a function to get that... or  *
 *    those. :)                                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the figure's primary weapon list.                          *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/25 Tony : Created.                                               *
 *============================================================================*/
std::vector<WeaponType>& Figure::getPrimaryWeapon()
{
	return primaryWeaponList;
}


/******************************************************************************
 * Figure::pickupWeapon -- When figure picks up a weapon.                     *
 *                                                                            *
 *    Well, all the weapons are first added to the buff pool, and then just   *
 *    have a copy in the figure's weapon slot.                                *
 *                                                                            *
 * INPUT:   weapon -- The weapon to be picked up.                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Figure::pickupWeapon(Weapon* weapon)
{
	weapon->isActivated = true;
	weapon->onFire(pOnFire);
	weapon->onMove(std::bind(&Figure::getWeaponPos, this));
	weaponSlot.pickup(weapon);
}


/******************************************************************************
 * Figure::getWeaponPos -- Get the position of the weapon.                    *
 *                                                                            *
 *    Well, to get the center of the weapon.                                  *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the coordinate of the weapon.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/16 Tony : Created.                                               *
 *============================================================================*/
Coord Figure::getWeaponPos() const
{
	return pos + weaponOffset;
}


/******************************************************************************
 * Figure::draw -- Draw the figure.  alth.                                    *
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
 *   2022/01/23 Tony : Created.                                               *
 *============================================================================*/
void Figure::draw(Camera& cam)
{
	if (isHidden || !isValid)
		return;

	sym.img = anim.getFrame(facing);
	sym.pos = getCenter();

	cam.capture(sym);
}


/******************************************************************************
 * Figure::healHp -- Regenerate some health.                                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val -- The health to regain.                                      *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void Figure::healHp(int val)
{
	hp[0] += val;
	hp[0] = MIN(hp[0], hp[1]);
}


/******************************************************************************
 * Figure::healMp -- Regenerate some ammo.                                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   val -- The ammo to add.                                           *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
void Figure::healMp(int val)
{
	mp[0] += val;
	mp[0] = MIN(mp[0], mp[1]);
}


/******************************************************************************
 * Figure::move -- The figure moves.                                          *
 *                                                                            *
 *    Well, the figure can move, and then comes the collision part.           *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *   2022/02/07 Tony : Fixed that no acc or vel is got.                       *
 *============================================================================*/
void Figure::move()
{
	prevPos = pos;

	getAcc();
	getVel();

	pos.x += (int)(v.x * globalTimer.getDeltaTime() * VEL_COF);
	pos.y += (int)(v.y * globalTimer.getDeltaTime() * VEL_COF);
	sym.pos = pos + imgOffset;

	/*
	** The external force should be cleared after each move, for
	** they are all instant force.
	*/
	this->f = ZERO_VECTOR;
}


/******************************************************************************
 * Figure::autoHeal -- Auto regenerate properties.                            *
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
void Figure::autoHeal()
{
	clock_t curTimestamp = globalTimer.getTimestamp();

	if ((hpGap[1] != 0) && (hp[0] < hp[1]))
	{
		if (curTimestamp - hpGap[0] >= hpGap[1])
		{
			hpGap[0] = curTimestamp;
			hp[0]++;
		}
	}
	if ((mpGap[1] != 0) && (mp[0] < mp[1]))
	{
		if (curTimestamp - mpGap[0] >= mpGap[1])
		{
			mpGap[0] = curTimestamp;
			mp[0]++;
		}
	}
	if ((amorGap[1] != 0) && (amor[0] < amor[1]))
	{
		if (curTimestamp - amorGap[0] >= amorGap[1])
		{
			amorGap[0] = curTimestamp;
			amor[0]++;
		}
	}
	if ((chiGap[1] != 0) && (chi[0] < chi[1]))
	{
		if (curTimestamp - chiGap[0] >= chiGap[1])
		{
			chiGap[0] = curTimestamp;
			chi[0]++;
		}
	}
}



/******************************************************************************
 * Hero::Hero -- Constructor of the object.                                   *
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
 *   2022/01/23 Tony : Created.                                               *
 *============================================================================*/
Hero::Hero() : Figure(FigureType::HERO)
{
	state = HERO_INIT;
	collId = CollisionId::COLL_HERO;
}


/******************************************************************************
 * Hero::~Hero -- Deconstructor of the object.                                *
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
 *   2022/01/23 Tony : Created.                                               *
 *============================================================================*/
Hero::~Hero() {}


/******************************************************************************
 * Hero::update -- Update the hero.                                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   cmd -- The hero follows only the player's command.                *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/23 Tony : Created.                                               *
 *============================================================================*/
void Hero::update(Command& cmd)
{
	autoHeal();

	pShowHp((double)hp[0] / (double)hp[1]);
	pShowAmor((double)amor[0] / (double)amor[1]);
	pShowMp((double)mp[0] / (double)mp[1]);

	updateState();
	anim.update(HERO_MOTION_MAP[state]);

	facing = (cmd.relativePos.x < getCenter().x);

	if (!HERO_CONTROLLABLE[state])
		return;

	/*
	** Since picking up buffs is hecked by buffs, here we only need
	** to... well control the hero's moving and firing.
	*/
	Vector motiveForce;

	if (cmd.commandType & CMD_LEFT)
		motiveForce -= UNIT_X;
	if (cmd.commandType & CMD_RIGHT)
		motiveForce += UNIT_X;
	if (cmd.commandType & CMD_UP)
		motiveForce -= UNIT_Y;
	if (cmd.commandType & CMD_DOWN)
		motiveForce += UNIT_Y;

	if (cmd.commandType & CMD_SKILL)
	{
		skill();
		cmd.commandType = CMD_NONE;
	}
	if (cmd.commandType & CMD_SWITCH)
	{
		weaponSlot.switchWeapon();
		cmd.commandType = CMD_NONE;
	}

	weaponSlot.aim(cmd.relativePos);
	if (cmd.commandType & CMD_FIRE)
		weaponSlot.fire(mp[0]);

	f += getUnit(motiveForce) * strength;
}


/******************************************************************************
 * Hero::load -- Load hero.                                                   *
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
 *   2022/02/16 Tony : Created.                                               *
 *============================================================================*/
void Hero::load(GameResourceId resId)
{
	HeroRes* res = dynamic_cast<HeroRes*>(gameResource[resId]);

	offset = res->offset;

	hp[0] = hp[1] = res->maxHp;
	hpGap[1] = res->hpGap;
	mp[0] = mp[1] = res->maxMp;
	mpGap[1] = res->mpGap;
	amor[0] = amor[1] = res->maxAmor;
	amorGap[1] = res->amorGap;
	chi[0] = chi[1] = res->maxChi;
	chiGap[1] = res->chiGap;

	pFrame = &(res->frame);
	anim.load(pFrame);

	weaponSlot.setCapacity(res->slotCapacity);

	// const map does not support []... :(
	for (auto it = res->primaryWeaponList.begin(); it != res->primaryWeaponList.end(); it++)
	{
		auto pos = WEAPON_TYPE_MAP.find(*it);
		if (pos != WEAPON_TYPE_MAP.end())
			primaryWeaponList.push_back(pos->second);
	}

	width = res->width;
	height = res->height;
	weaponOffset = res->weaponOffset;
	imgOffset = res->imgOffset;

	setMass(res->m);
	mu = res->mu;
	drag = res->drag;
	strength = res->strength;

	sym.offset = imgOffset - offset;
	anim.update();
}


/******************************************************************************
 * Hero::hurt -- Get hurt.                                                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   damage -- The damage of the bullet.                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/23 Tony : Created.                                               *
 *============================================================================*/
void Hero::hurt(const Damage& damage)
{
	if (state == HERO_INIT)
		return;

	Coord dir = pos + offset - damage.source;
	Vector force((double)dir.x, (double)dir.y);

	force = getUnit(force) * damage.blowForce;
	this->f += force;

	if (amor[0] > damage.value)
		amor[0] -= damage.value;
	else
	{
		amor[0] = 0;
		hp[0] -= (damage.value - amor[0]);
	}

	if (hp[0] > 0)
		setState(HERO_HURT);
	else
	{
		hp[0] = 0;
		setState(HERO_DEAD);
	}

	hpGap[0] = mpGap[0] = amorGap[0] = chiGap[0] = globalTimer.getTimestamp();
}


/******************************************************************************
 * Hero::setState -- Set the hero's state.                                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _state                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  It must be called after primary weapon is loaded.               *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/23 Tony : Created.                                               *
 *   2022/02/18 Tony : Added a detail to hide weapon.                         *
 *============================================================================*/
void Hero::setState(HeroState _state)
{
	state = HERO_STATE_MACHINE[state][_state];
	if (state == HERO_INIT)
		weaponSlot.hide();
	else if (state == HERO_DEAD)
	{
		weaponSlot.hide();
		collId = COLL_VACUUM;
	}
	else if (state == HERO_INVALID)
	{
		weaponSlot.clear();
		isValid = false;
	}
}


/******************************************************************************
 * Hero::onShow -- Set the callback functions to show properties.             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   pShowHp   |                                                       *
 *          pShowAmor |- The callback functions to show hero's property.      *
 *          pShowMp   |                                                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
void Hero::onShow(
	std::function<void(double)> _pShowHp,
	std::function<void(double)> _pShowAmor,
	std::function<void(double)> _pShowMp)
{
	pShowHp = _pShowHp;
	pShowAmor = _pShowAmor;
	pShowMp = _pShowMp;
}


/******************************************************************************
 * Hero::updateState -- Update the hero's state.                              *
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
 *   2022/01/23 Tony : Created.                                               *
 *============================================================================*/
void Hero::updateState()
{
	if (state == HERO_INVALID)
		return;

	if (anim.over())
	{
		if (state == HERO_INIT)
			weaponSlot.reveal();
		setState(HERO_END);
	}

	if (state == HERO_DEAD)
		return;

	if ((getModule(v) < 1.0) && (f == ZERO_VECTOR))
	{
		v = ZERO_VECTOR;
		setState(HERO_STAND);
	}
	else
		setState(HERO_MOVE);
}


/******************************************************************************
 * Hero::switchWeapon -- Hmm... switch the weapon. :)                         *
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
 *   2022/01/23 Tony : Created.                                               *
 *============================================================================*/
void Hero::switchWeapon()
{
	weaponSlot.switchWeapon();
}



/******************************************************************************
 * Enemy::Enemy -- Constructor of the object.                                 *
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
 *   2022/01/24 Tony : Created.                                               *
 *============================================================================*/
Enemy::Enemy() : Figure(FigureType::ENEMY)
{
	pOnDefeat = nullptr;
	pOnGenerate = nullptr;

	state = ENEMY_INIT;

	patrolRadius = 0;

	collId = CollisionId::COLL_ENEMY;
}


/******************************************************************************
 * Enemy::~Enemy -- Deconstructor of the object.                              *
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
 *   2022/01/24 Tony : Created.                                               *
 *============================================================================*/
Enemy::~Enemy() {}


/******************************************************************************
 * Enemy::onDeafeat -- Set the callback function.                             *
 *                                                                            *
 *    This will add score to the game.                                        *
 *                                                                            *
 * INPUT:   callback -- Of the Dungeon, to add scores.                        *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/24 Tony : Created.                                               *
 *============================================================================*/
void Enemy::onDefeat(std::function<void(int)> callback)
{
	pOnDefeat = callback;
}


/******************************************************************************
 * Enemy::onGenerate -- Generate buff after being defeated.                   *
 *                                                                            *
 *    This is the function of the Dungeon, a little redundancy though.        *
 *                                                                            *
 * INPUT:   callback -- generateBuff of the Dungeon.                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/24 Tony : Created.                                               *
 *============================================================================*/
void Enemy::onGenerate(std::function<void(int, int, Coord, int, Coord)> callback)
{
	pOnGenerate = callback;
}


/******************************************************************************
 * Enemy::setPos -- Set the position of the enemy.                            *
 *                                                                            *
 *    This will also set the target pos together.                             *
 *                                                                            *
 * INPUT:   _pos                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
void Enemy::setPos(const Coord& _pos)
{
	prevPos = pos = _pos;
	tarPos = getCenter();
}


/******************************************************************************
 * Enemy::setCenter -- Set the center of the enemy.                           *
 *                                                                            *
 *    This will also set the target pos together.                             *
 *                                                                            *
 * INPUT:   center                                                            *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
void Enemy::setCenter(const Coord& center)
{
	prevPos = pos = center - offset;
	tarPos = center;
}


/******************************************************************************
 * Enemy::update -- Update the enemy.                                         *
 *                                                                            *
 *    Move towards the target position.                                       *
 *                                                                            *
 * INPUT:   target -- The hero's center coordinate.                           *
 *          space  -- The current space.                                      *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/24 Tony : Created.                                               *
 *   2022/01/28 Tony : Changed brickMatrix to space.                          *
 *============================================================================*/
void Enemy::update(Coord target, Space* space)
{
	autoHeal();

	updateState();
	anim.update(ENEMY_MOTION_MAP[state]);

	if (!ENEMY_CONTROLLABLE[state])
		return;

	Coord center = pos + offset;	
	facing = (int)(target.x < center.x);

	if (getManhattanDistance(center, target) > patrolRadius)
	{
		if (space->graph.advance(space->convert(center), space->convert(target)))
			tarPos = space->convert(space->graph.next, true);
	}
	else
	{
		if (random(0, 10) == 0)
		{
			if (space->graph.retreat(space->convert(center), space->convert(target)))
				tarPos = space->convert(space->graph.next, true);
		}
	}

	Vector motiveForce((double)(tarPos.x - center.x), (double)(tarPos.y - center.y));
	this->f += getUnit(motiveForce) * strength;

	weaponSlot.aim(target);
	if (space->graph.inSight(space->convert(center), space->convert(target)))
		weaponSlot.fire(mp[0]);
}


/******************************************************************************
 * Figure::load -- Load figure.                                               *
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
 *   2022/02/16 Tony : Created.                                               *
 *============================================================================*/
void Enemy::load(GameResourceId resId)
{
	EnemyRes* res = dynamic_cast<EnemyRes*>(gameResource[resId]);

	offset = res->offset;

	hp[0] = hp[1] = res->maxHp;
	hpGap[1] = res->hpGap;
	mp[0] = mp[1] = res->maxMp;
	mpGap[1] = res->mpGap;
	amor[0] = amor[1] = res->maxAmor;
	amorGap[1] = res->amorGap;
	chi[0] = chi[1] = res->maxChi;
	chiGap[1] = res->chiGap;

	patrolRadius = res->patrolRadius;
	price = res->price;

	pFrame = &(res->frame);
	anim.load(pFrame);

	// const map does not support []... :(
	for (auto it = res->primaryWeaponList.begin(); it != res->primaryWeaponList.end(); it++)
	{
		auto pos = WEAPON_TYPE_MAP.find(*it);
		if (pos != WEAPON_TYPE_MAP.end())
			primaryWeaponList.push_back(pos->second);
	}

	width = res->width;
	height = res->height;
	weaponOffset = res->weaponOffset;
	imgOffset = res->imgOffset;

	setMass(res->m);
	mu = res->mu;
	drag = res->drag;
	strength = res->strength;

	sym.offset = imgOffset - offset;
	anim.update();
}


/******************************************************************************
 * Enemy::move -- Move the enemy.                                             *
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
 *   2022/01/28 Tony : Created.                                               *
 *============================================================================*/
void Enemy::move()
{
	double dist;
	double step;
	Coord center = pos + offset;
	double k = globalTimer.getDeltaTime() * VEL_COF;

	prevPos = pos;

	getAcc();
	getVel();

	dist = getDistance(center, tarPos);
	step = getModule(v) * k;

	// Close enough.
	if (step > dist)
		pos = tarPos - offset;
	else
	{
		pos.x += (int)(v.x * k);
		pos.y += (int)(v.y * k);
	}

	sym.pos = pos + imgOffset;

	/*
	** The external force should be cleared after each move, for
	** they are all instant force.
	*/
	this->f = ZERO_VECTOR;
}


/******************************************************************************
 * Enemy::hurt -- The enemy gets hurtf the enemy.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   damage -- The damage from the bullet.                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/24 Tony : Created.                                               *
 *============================================================================*/
void Enemy::hurt(const Damage& damage)
{
	if (state == ENEMY_INIT)
		return;

	Coord dir = pos + offset - damage.source;
	Vector force((double)dir.x, (double)dir.y);

	force = getUnit(force) * damage.blowForce;
	this->f += force;

	if (amor[0] > damage.value)
		amor[0] -= damage.value;
	else
	{
		amor[0] = 0;
		hp[0] -= (damage.value - amor[0]);
	}

	if (hp[0] > 0)
		setState(ENEMY_HURT);
	else
	{
		hp[0] = 0;
		setState(ENEMY_DEAD);
	}

	hpGap[0] = mpGap[0] = amorGap[0] = chiGap[0] = globalTimer.getTimestamp();
}


/******************************************************************************
 * Enemy::setState -- Set the state of the enemy.                             *
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
void Enemy::setState(EnemyState _state)
{
	state = ENEMY_STATE_MACHINE[state][_state];
	if (state == ENEMY_INIT)
		weaponSlot.hide();
	else if (state == ENEMY_DEAD)
	{
		weaponSlot.hide();
		collId = COLL_VACUUM;
	}
	else if (state == ENEMY_INVALID && isValid)
	{
		weaponSlot.clear();
		isValid = false;
		
		perish();
	}
}


/******************************************************************************
 * Enemy::updateState -- Update the state of the enemy.                       *
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
 *   2022/01/24 Tony : Created.                                               *
 *   2022/02/19 Tony : Prevent "dying". :(                                    *
 *============================================================================*/
void Enemy::updateState()
{
	if (anim.over())
	{
		if (state == ENEMY_INIT)
			weaponSlot.reveal();
		setState(ENEMY_END);
	}

	if (state == ENEMY_DEAD)
	{
		/*
		** 2022/02/19
		** Notice that, if the enemy is dead, then for a 
		** little period, his state will always be DEAD. :(
		*/

		return;
	}

	if (getModule(v) < 1.0)
		setState(ENEMY_STAND);
	else
		setState(ENEMY_MOVE);
}




/******************************************************************************
**                            Specific Heroes                                **
* --------------------------------------------------------------------------- *
* Yony -- The basic hero, nothing special but his name.                       *
*******************************************************************************/


/******************************************************************************
 * BLANK                                                                      *
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
 *   2022/01/25 Tony : Created.                                               *
 *============================================================================*/
Yony::Yony()
{
	heroType = HERO_YONY;
}


/******************************************************************************
 * Yony::Yony -- Constructor of the object.                                   *
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
 *   2022/01/25 Tony : Created.                                               *
 *============================================================================*/
Yony::~Yony() {}



void Yony::skill()
{
	/*
	** On hold.
	*/
}


/******************************************************************************
 * Yony::perish -- The thing to do after perish.                              *
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
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
void Yony::perish() {}



/******************************************************************************
*                             Specific Enemies                                *
* --------------------------------------------------------------------------- *
* Pawn -- The basic enemy, nothing special but... nothing. :)                 *
*******************************************************************************/


/******************************************************************************
 * Pawn::Pawn -- Constructor of the object.                                   *
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
 *   2022/01/25 Tony : Created.                                               *
 *============================================================================*/
Pawn::Pawn()
{
	weaponSlot.setCapacity(1);
}


/******************************************************************************
 * Pawn::~Pawn -- Deconstructor of the object.                                *
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
 *   2022/01/25 Tony : Created.                                               *
 *============================================================================*/
Pawn::~Pawn() {}


/******************************************************************************
 * Pawn::skill -- The pawn's skill...                                         *
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
 *   2022/01/25 Tony : Created.                                               *
 *============================================================================*/
void Pawn::skill() {}


/******************************************************************************
 * Pawn::perish -- The thing to do after perish.                              *
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
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
void Pawn::perish()
{
	if (pOnDefeat)
		pOnDefeat(price);
	if (pOnGenerate)
		pOnGenerate(0, random(0, 3), getCenter(), random(0, 3), getCenter());
}


Boss::Boss()
{
	weaponSlot.setCapacity(2);
}
Boss::~Boss() {}

void Boss::update(Coord target, Space* space)
{
	autoHeal();

	updateState();
	anim.update(ENEMY_MOTION_MAP[state]);

	if (!ENEMY_CONTROLLABLE[state])
		return;

	if (hp[0] < (hp[1] >> 1))
		skill();

	Coord center = pos + offset;
	facing = (int)(target.x < center.x);

	if (getManhattanDistance(center, target) > patrolRadius)
	{
		if (space->graph.advance(space->convert(center), space->convert(target)))
			tarPos = space->convert(space->graph.next, true);
	}
	else
	{
		if (random(0, 5) == 0)
		{
			if (space->graph.retreat(space->convert(center), space->convert(target)))
				tarPos = space->convert(space->graph.next, true);
		}
	}

	Vector motiveForce((double)(tarPos.x - center.x), (double)(tarPos.y - center.y));
	this->f += getUnit(motiveForce) * strength;

	weaponSlot.aim(target);
	if (space->graph.inSight(space->convert(center), space->convert(target)))
		weaponSlot.fire();
}

void Boss::skill()
{
	if (chi[0] > 0)
	{
		weaponSlot.switchWeapon();
		chi[0] = 0;
	}
}

void Boss::perish()
{
	if (pOnDefeat)
		pOnDefeat(price);
	if (pOnGenerate)
		pOnGenerate(0, random(0, 3), getCenter(), random(0, 3), getCenter());
}








/******************************************************************************
**                           Other Functions                                 **
*******************************************************************************/


/******************************************************************************
 * getHero -- Get a hero.                                                     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   type -- The type of the hero.                                     *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
Hero* getHero(HeroType type)
{
	Hero* hero;

	switch (type)
	{
	case HERO_YONY:
		hero = new Yony();
		hero->load(RES_HERO_YONY);
		break;
	default:
		hero = nullptr;
		break;
	}

	return hero;
}


/******************************************************************************
 * getEnemy -- Get an enemy.                                                  *
 *                                                                            *
 *    This only decide the level of the enemy, then specific function will    *
 *    generate the enemy.                                                     *
 *                                                                            *
 * INPUT:   level -- The level of the enemy.                                  *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
Enemy* getEnemy(EnemyLevel level)
{
	switch (level)
	{
	case ENEMY_PAWN:
		return getPawn();
	case ENEMY_BOSS:
		return getBoss();
	default:
		return nullptr;
	}

	return nullptr;
}

Pawn* getPawn()
{
	Pawn* rv = new Pawn();

	if (!random(0, 10))
		rv->load(RES_ENEMY_SQUAREX);
	else
		rv->load(RES_ENEMY_SQUARE);

	return rv;
}

Boss* getBoss()
{
	Boss* rv = new Boss();

	rv->load(RES_ENEMY_MEGA);

	return rv;
}