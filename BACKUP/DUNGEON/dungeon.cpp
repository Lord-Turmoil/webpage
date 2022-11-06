/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : dungeon.cpp                               *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 22, 2022                          *
 *                                                                            *
 *                    Last Update :                                           *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   This is the main process of the game. And there are two modes, the death *
 *   match and the campaign. What's more, there is a launcher to launch the   *
 *   dungeon.                                                                 *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#include <cmath>
#include <vector>

#include "error.h"
#include "config.h"
#include "define.h"
#include "terrain.h"
#include "dungeon.h"
#include "command.h"


extern Command command;

extern Setting setting;


/******************************************************************************
 * Dungeon::Dungeon -- Constructor of the object.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _type -- The type of the dungeon.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
Dungeon::Dungeon(DungeonType _type)
{
	type = _type;

	hero = nullptr;
	brickPool = nullptr;
	pTargetImage = nullptr;

	curSpace = nullptr;

	pOnGenerate = std::bind(&Dungeon::generateBuff, this,
		std::placeholders::_1,
		std::placeholders::_2,
		std::placeholders::_3,
		std::placeholders::_4,
		std::placeholders::_5);
}


/******************************************************************************
 * Dungeon::~Dungeon -- Deconstructor of the object.                          *
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
 *   2022/02/05 Tony : Hero now will be deleted by the launcher.
 *============================================================================*/
Dungeon::~Dungeon() {}


/******************************************************************************
 * Dungeon::getAttribute -- Get the attribute of the dungeon.                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the attribute of the dungeon.                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
DungeonAttribute& Dungeon::getAttribute()
{
	return attribute;
}


/******************************************************************************
 * Dungeon::getState -- Get the state of the dungeon.                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the state of the dungeon.                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/28 Tony : Created.                                               *
 *============================================================================*/
DungeonState& Dungeon::getState()        
{
	return state;
}


/******************************************************************************
 * Dungeon::generateBuff -- Generate buffs.                                   *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   createNum -- The number of create to generate.                    *
 *          ammoNum   -- The number of ammo to generate.                      *
 *          ammoPos   -- The approximate coordinate of the ammo.              *
 *          goldNum   -- The number of gold to generate.                      *
 *          goldPos   -- The approximate coordinate of the gold.              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Dungeon::generateBuff(int createNum, int ammoNum, Coord ammoPos, int goldNum, Coord goldPos)
{
	if (createNum > 0)
		generateCreate(createNum);
	if (ammoNum > 0)
		generateAmmo(ammoNum, ammoPos);
	if (goldNum > 0)
		generateGold(goldNum, goldPos);
}


/******************************************************************************
 * DungeonCampaign::init -- Initialize the dungeon.                           *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _pos          -- Top left of the camera.                          *
 *          _width        -- Width of the camera.                             *
 *          _height       -- Height of the camera.                            *
 *          _hero         -- The hero of the game from select hero interface. *
 *          _difficulty   -- Difficulty of the game.                          *
 *          _pTargetImage -- Hmm... target image of the camera.               *
 *                                                                            *
 * OUTPUT:  Return whether the launch is successful or not.                   *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
bool Dungeon::init(
	Coord _pos,
	int _width,
	int _height,
	Hero* _hero,
	int _difficulty,
	IMAGE* _pTargetImage)
{
	camera.init(_pos, _width, _height, CAM_FAST);
	camera.setTargetImage(_pTargetImage);
	
	command.pRelativeConvert = std::bind(&Camera::convert, &camera, std::placeholders::_1);

	hero = _hero;
	hero->onFire(std::bind(&BulletPool::add, &heroBulletPool, std::placeholders::_1, true));
	hero->update(command);

	attribute.difficulty = _difficulty;

	return true;
}


/******************************************************************************
 * Dungeon::addScore -- Add scores to the game.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   score -- The score to add.                                        *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
void Dungeon::addScore(int score)
{
	attribute.score += score;
}


/******************************************************************************
 * Dungeon::addGold -- Add gold to the game.                                  *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   gold -- The gold to add.                                          *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
void Dungeon::addGold(int gold)
{
	attribute.gold += gold;
}


/******************************************************************************
 * Dungeon::upgrade -- Set the dungeon to levelup.                            *
 *                                                                            *
 *    This only set the levelup flag true, then the dungen upgrade it self.   *
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
void Dungeon::levelup()
{
	state.isLevelup = true;
}


/******************************************************************************
 * Dungeon::generateEnemy -- Generate enemies.                                *
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
void Dungeon::generateEnemy()
{
	int num = 1 + random(0, random(0, attribute.section) + (attribute.difficulty << 1));
	for (int i = 0; i < num; i++)
		generateEnemy(EnemyLevel::ENEMY_PAWN);
	if (curSpace->attribute.hasBoss && (curSpace->attribute.rounds == 0))
		generateEnemy(EnemyLevel::ENEMY_BOSS);
}

void Dungeon::generateEnemy(EnemyLevel level)
{
	Enemy* enemy;
	Weapon* weapon;
	enemy = getEnemy(level);

	if (curSpace->graph.findBlank(curSpace->convert(enemy->width), curSpace->convert(enemy->height)))
	{
		enemy->setPos(curSpace->convert(curSpace->graph.blank, true));
		enemy->onFire(std::bind(&BulletPool::add, &enemyBulletPool, std::placeholders::_1, false));
		enemy->onGenerate(pOnGenerate);
		enemy->onDefeat(std::bind(&Dungeon::addScore, this, std::placeholders::_1));
		auto& weaponList = enemy->getPrimaryWeapon();
		for (auto it = weaponList.begin(); it != weaponList.end(); it++)
		{
			weapon = getWeapon(*it);
			weapon->onPickup(std::bind(&Figure::pickupWeapon, enemy, std::placeholders::_1));
			enemy->pickupWeapon(weapon);
			buffPool.add(weapon);
		}
		enemyPool.add(enemy);
	}
	else
	{
		reportf(NO_BLANK, "Enemy", IN_GAME);
		delete enemy;
	}
}


/******************************************************************************
 * Dungeon::generateCreate -- Generate creates.                               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   num -- How many create to generate.                               *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Dungeon::generateCreate(int num)
{
	Coord target;
	Create* create = new Create();

	create->load(RES_BUFF_CREATE);
	if (curSpace->graph.findBlank(curSpace->convert(create->width), curSpace->convert(create->height)))
	{
		create->setPos(curSpace->convert(curSpace->graph.blank, true));
		create->onOpen(std::bind(&BuffPool::add, &buffPool, std::placeholders::_1));
		buffPool.add(create);
	}
	else
	{
		reportf(NO_BLANK_F, "Create", IN_GAME);
		delete create;
	}
}


/******************************************************************************
 * Dungeon::generateAmmo -- How many ammo to generate.                        *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   num     -- The number of ammo.                                    *
 *          ammoPos -- Ammos will be generated around this coordinate.        *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Dungeon::generateAmmo(int num, Coord ammoPos)
{
	Ammo* buff;
	int radius = (int)sqrt(num) << 2;

	for (int i = 0; i < num; i++)
	{
		buff = new Ammo();
		buff->load(RES_BUFF_AMMO);
		buff->setCenter(randomPos(ammoPos, radius));
		buff->onCollect(std::bind(&Figure::healMp, hero, std::placeholders::_1));
		buffPool.add(buff);
	}
}


/******************************************************************************
 * Dungeon::generateGold -- Generate gold.                                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   num     -- Number of gold.                                        *
 *          goldPos -- Gold will be generated around this coordinate.         *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/14 Tony : Created.                                               *
 *============================================================================*/
void Dungeon::generateGold(int num, Coord goldPos)
{
	Gold* buff;
	int radius = (int)sqrt(num) << 2;

	for (int i = 0; i < num; i++)
	{
		buff = new Gold();
		buff->load(RES_BUFF_GOLD);
		buff->setCenter(randomPos(goldPos, radius));
		buff->onCollect(std::bind(&Dungeon::addGold, this, std::placeholders::_1));
		buffPool.add(buff);
	}
}



/******************************************************************************
**                         Specific mode of the dungeon                      **
*******************************************************************************/


/******************************************************************************
 * DungeonCampaign::DungeonCampaign -- Constructor of the object.             *
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
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
DungeonCampaign::DungeonCampaign() : Dungeon(DungeonType::DUNGEON_CAMPAIGN)
{
	portal = nullptr;
}


/******************************************************************************
 * DungeonCampaign::~DungeonCampaign -- Deconstructor of the object.          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Remember to delete pointers. Emm... But it seems they can all   *
 *            delete themselves automatically and... nothing need to be done. *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
DungeonCampaign::~DungeonCampaign() {}


/******************************************************************************
 * DungeonCampaign::upgrade -- Emm... level up?                               *
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
void DungeonCampaign::upgrade()
{
	state.isLevelup = false;

	attribute.levelup();

	/*
	** Clear remaining items.
	*/
	enemyPool.clear();
	buffPool.clear();
	heroBulletPool.clear();
	enemyBulletPool.clear();

	portal = nullptr;

	if (attribute.isEnd)
	{
		state.isVictorious = true;
		return;
	}

	terrain.generate(
		attribute.stage * SECTION_NUM + attribute.section,
		attribute.difficulty,
		attribute.hasBoss,
		false);

	curSpace = terrain.getCurrentSpace();
	brickPool = curSpace->getBrickPool();

	// Hero
	hero->setCenter(curSpace->getCenter());

	// Camera
	camera.focus(hero->getCenter());
}


/******************************************************************************
 * DungeonCampaign::launch -- Launch the campaign game.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether the launch is successful or not.                   *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
bool DungeonCampaign::launch()
{
	// Terrain.
	terrain.generate(
		attribute.section,
		attribute.difficulty,
		false,
		false);
	curSpace = terrain.getCurrentSpace();
	brickPool = curSpace->getBrickPool();

	// Hero
	std::vector<WeaponType>& weaponList = hero->getPrimaryWeapon();
	Weapon* weapon;
	for (auto it = weaponList.begin(); it != weaponList.end(); it++)
	{
		weapon = getWeapon(*it);
		weapon->onPickup(std::bind(&Figure::pickupWeapon, hero, std::placeholders::_1));

		// These two will be set by the figure who picks the weapon up.
		// weapon->onMove
		// weapon->onFire
		// And weapon state will be set by weaponSlot who picks the weapon up.
		hero->pickupWeapon(weapon);
		buffPool.add(weapon);
	}
	hero->setCenter(curSpace->getCenter());
	hero->setState(HERO_INIT);

	// Camera
	camera.focus(hero->getCenter());

	hero->anim.update(HERO_INIT);

	return true;
}


/******************************************************************************
 * DungeonCampaign::run -- Runs the game.                                     *
 *                                                                            *
 *    The core of the gaming process. It is part of the loop in the game...   *
 *    interface, though. Hmm... Just run once every loop.                     *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  Just... watch out for BUGs!!! :(                                *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
DungeonToken DungeonCampaign::run()
{
	/*
	** Initialize.
	*/
	curSpace = terrain.getCurrentSpace();
	curSpace->graph.clear();
	brickPool = curSpace->getBrickPool();

	/*
	** Draw all stuff, and invalid ones will be deleted in
	** this process.
	*/
	draw();

	/*
	** Some... definitions?
	*/
	auto& enemy_pool = enemyPool.getPool();
	auto& brick_pool = brickPool->getPool();

	/*
	** Entry all figures to the graph.
	** 2022/02/21
	** And obstacles.
	*/
	curSpace->entry();
	curSpace->graph.entry(hero->topLeft(), hero->bottomRight());
	for (auto it = enemy_pool.begin(); it != enemy_pool.end(); it++)
		curSpace->graph.entry((*it)->topLeft(), (*it)->bottomRight());


	/*
	** Update all stuff.
	*/
	Coord coord = hero->getCenter();

	hero->update(command);

	for (auto it = enemy_pool.begin(); it != enemy_pool.end(); it++)
		dynamic_cast<Enemy*>(*it)->update(coord, curSpace);

	heroBulletPool.update(enemyPool);
	heroBulletPool.update(*brickPool);
	heroBulletPool.updateAnim();
	
	enemyBulletPool.update(hero);
	enemyBulletPool.update(*brickPool);
	enemyBulletPool.updateAnim();

	buffPool.update(command, coord);

	camera.follow(getRatioCoord(coord, command.relativePos, 0.7));
	camera.move();

	terrain.update(coord);

	/*
	** Move figures, and... the collision.
	*/
	hero->move();
	for (auto it = enemy_pool.begin(); it != enemy_pool.end(); it++)
		(*it)->move();

	for (auto it = enemy_pool.begin(); it != enemy_pool.end(); it++)
		hero->collide(**it);
	for (auto brick_it = brick_pool.begin(); brick_it != brick_pool.end(); brick_it++)
	{
		hero->collide(**brick_it);
		for (auto enemy_it = enemy_pool.begin(); enemy_it != enemy_pool.end(); enemy_it++)
			(*enemy_it)->collide(**brick_it);
	}

	heroBulletPool.move();
	enemyBulletPool.move();


	/*
	** Check the state of the dungeon.
	*/

	// Game over if the hero dies.
	if (!hero->isValid)
	{
		Sleep(1000);
		state.isLost = true;
		return LOST;
	}


	// Generate enemy.
	if (enemy_pool.size() == 0 && curSpace->attribute.isTrapped)
	{
		curSpace->attribute.rounds--;
		if (curSpace->attribute.rounds >= 0)
			generateEnemy();
	}

	/*
	** 2022/02/19
	** On hold. :(
	if (curSpace->attribute.hasCreate)
	{
		curSpace->attribute.hasCreate = false;
		generateCreate(1);
	}
	*/

	// Check if a portal should be generated.
	if (curSpace->attribute.isEnd && curSpace->attribute.isCompleted)
	{
		if (!portal)
		{
			portal = new Portal();
			portal->load();
			portal->setCenter(curSpace->getCenter());
			portal->onActive(std::bind(&DungeonCampaign::levelup, this));
			buffPool.add(portal);
		}
	}
	
	if (state.isLevelup)
	{
		upgrade();
		return UPGRADE;
	}

	return RUNNING;
}


/******************************************************************************
 * DungeonCampaign::draw -- Draw all elements of the dungeon.                 *
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
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
void DungeonCampaign::draw()
{
	terrain.draw(camera);

	hero->draw(camera);
	enemyPool.draw(camera);

	buffPool.draw(camera);

	heroBulletPool.draw(camera);
	enemyBulletPool.draw(camera);

	camera.develop();
}


/******************************************************************************
 * DungeonDeath::DungeonDeath -- Constructor of the object.                   *
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
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
DungeonDeath::DungeonDeath() : Dungeon(DungeonType::DUNGEON_DEATH) {}


/******************************************************************************
 * DungeonDeath::~DungeonDeath -- Deconstructor of the object.                *
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
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
DungeonDeath::~DungeonDeath() {}


/******************************************************************************
 * DungeonDeath::levelup -- Level up.                                         *
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
 *   2022/02/04 Tony : Created.                                               *
 *============================================================================*/
void DungeonDeath::upgrade()
{
}


/******************************************************************************
 * DungeonDeath::launch -- Launch the dungeon.                                *
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
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
bool DungeonDeath::launch()
{
	// Terrain.
	terrain.generate(
		attribute.stage * SECTION_NUM + attribute.section,
		attribute.difficulty,
		false,
		false);
	Space* curSpace = terrain.getCurrentSpace();
	brickPool = curSpace->getBrickPool();

	// Hero
	std::vector<WeaponType>& weaponList = hero->getPrimaryWeapon();
	Weapon* weapon;
	for (auto it = weaponList.begin(); it != weaponList.end(); it++)
	{
		weapon = getWeapon(*it);
		weapon->onPickup(std::bind(&Figure::pickupWeapon, hero, std::placeholders::_1));
		// These two will be set by the figure who picks the weapon up.
		// weapon->onMove
		// weapon->onFire
		// And weapon state will be set by weaponSlot who picks the weapon up.
		hero->pickupWeapon(weapon);
		buffPool.add(weapon);
	}
	hero->setCenter(curSpace->getCenter());

	// Camera
	camera.focus(MAP_CENTER);
	camera.follow(hero->getCenter());


	return true;
}


/******************************************************************************
 * DungeonDeath::run -- Run the game.                                         *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return dungeon token.                                             *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
DungeonToken DungeonDeath::run()
{
	return RUNNING;
}


/******************************************************************************
 * DungeonDeath::draw -- Just... draw.                                        *
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
 *   2022/02/05 Tony : Created.                                               *
 *============================================================================*/
void DungeonDeath::draw()
{
}



/******************************************************************************
 * Launcher::Launcher -- Constructor of the object.                           *
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
Launcher::Launcher()
{
	pDungeon = nullptr;
	pHero = nullptr;

	pTargetImage = nullptr;
}


/******************************************************************************
 * Launcher::~Deconstructor of the object.                                    *
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
Launcher::~Launcher()
{
	if (pDungeon)
		delete pDungeon;
	if (pHero)
		delete pHero;
}


/******************************************************************************
 * Launcher::setHero -- Set the hero of the game.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _heroType -- The type of hero.                                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
void Launcher::setHero(HeroType _heroType)
{
	// Oh boy, conflict!!!
	pHero = ::getHero(_heroType);
}


/******************************************************************************
 * Launcher::setMode -- Set the mode of the dungeon.                          *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _type     -- The type of the dungeon.                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
void Launcher::setMode(DungeonType _type)
{
	type = _type;

	if (type == DungeonType::DUNGEON_CAMPAIGN)
		pDungeon = new DungeonCampaign();
	else
		pDungeon = new DungeonDeath();
}


/******************************************************************************
 * Launcher::setTargetImage -- Set the target image of the dungeon.           *
 *                                                                            *
 *    This is where the game elements will be displayed.                      *
 *                                                                            *
 * INPUT:   _pTargetImage                                                     *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
void Launcher::setTargetImage(IMAGE* _pTargetImage)
{
	pTargetImage = _pTargetImage;
}


/******************************************************************************
 * Launcher::getHeroCallback -- Get the callback to set hero.                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the callback function.                                     *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
std::function<void(HeroType)> Launcher::getHeroCallback()
{
	return std::bind(&Launcher::setHero, this, std::placeholders::_1);
}


/******************************************************************************
 * Launcher::getModeCallback -- Get the callback to set the mode.             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the callback function.                                     *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
std::function<void(DungeonType)> Launcher::getModeCallback()
{
	return std::bind(&Launcher::setMode, this, std::placeholders::_1);
}


/******************************************************************************
 * Launcher::getHero -- Get the hero of the game.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the hero.                                                  *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
Hero* Launcher::getHero()
{
	return pHero;
}


/******************************************************************************
 * Launcher::getDungeon -- Get the dungeon of the game.                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the dungeon.                                               *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
Dungeon* Launcher::getDungeon()
{
	return pDungeon;
}


/******************************************************************************
 * Launcher::getImage -- Get the image of the camera of the game.             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return the image.                                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
IMAGE* Launcher::getImage()
{
	return pDungeon->camera.getImage();
}


/******************************************************************************
 * Launcher::launch -- Launch the game.                                       *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  Return whether successful or not.                                 *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/12 Tony : Created.                                               *
 *============================================================================*/
bool Launcher::launch()
{
	if ((pHero == nullptr) || (pDungeon == nullptr))
		return false;

	pDungeon->init(
		ORIGIN,
		CANVAS_WIDTH,
		CANVAS_HEIGHT,
		pHero,
		setting.difficulty,
		pTargetImage);

	return pDungeon->launch();
}



/******************************************************************************
 * Launcher::run -- Runs the game.                                            *
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
DungeonToken Launcher::run()
{
	DungeonToken token = (DungeonToken)pDungeon->run();

	if (pDungeon->state.isVictorious)
		return VICTORIOUS;
	
	return token;
}


/******************************************************************************
 * Launcher::draw -- Draws the game.                                          *
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
void Launcher::draw()
{
	pDungeon->draw();
}