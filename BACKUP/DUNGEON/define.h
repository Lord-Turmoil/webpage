/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : define.h                                  *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 2, 2022                           *
 *                                                                            *
 *                    Last Update : February 7, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   Define global constants, and custom types.                               *
 * -------------------------------------------------------------------------- *
 * Functions:                                                                 *
 ******************************************************************************/

#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <map>
#include <string>


// To control the precision of double.
const double EPSILON = 0.001;


// Physical quantity.
const double PI = 3.1415926;
const double G = 10.0;

// The ratio of velocity after and before the elastic collision.
const double ENERGY_RATIO = 0.8;

const int FPS = 60;
const int DELAY = (int)(1000.0 / (double)FPS);


/******************************************************************************
**                          Coordinate And Vector                            **
*******************************************************************************/

/********************************************************************
** Coordinate of elements.
*/
struct Coord
{
	int x;
	int y;

	Coord() : x(0), y(0) {}
	Coord(int _x, int _y) : x(_x), y(_y) {}
	Coord(const Coord& obj) : x(obj.x), y(obj.y) {}
	Coord(const Coord&& obj) : x(obj.x), y(obj.y) {}

	Coord& operator=(const Coord& obj)
	{
		this->x = obj.x;
		this->y = obj.y;

		return *this;
	};
	Coord operator+(const Coord& obj) const
	{
		return { this->x + obj.x, this->y + obj.y };
	};
	Coord operator-(const Coord& obj) const
	{
		return { this->x - obj.x, this->y - obj.y };
	};
	Coord operator-() const
	{
		return { -this->x, -this->y };
	};
	Coord& operator+=(const Coord& obj)
	{
		this->x += obj.x;
		this->y += obj.y;

		return *this;
	};
	Coord& operator-=(const Coord& obj)
	{
		this->x -= obj.x;
		this->y -= obj.y;

		return *this;
	};
	bool operator==(const Coord& obj) const
	{
		return (this->x == obj.x) && (this->y == obj.y);
	}
	bool operator!=(const Coord& obj) const
	{
		return (this->x != obj.x) || (this->y != obj.y);
	}

	friend Coord operator*(const int& k, const Coord& coord)
	{
		return { coord.x * k, coord.y * k };
	};
	friend Coord operator*(const int&& k, const Coord& coord)
	{
		return { coord.x * k, coord.y * k };
	};
	friend Coord operator*(const Coord& coord, const int& k)
	{
		return { coord.x * k, coord.y * k };
	};
	friend Coord operator*(const Coord& coord, const int&& k)
	{
		return { coord.x * k, coord.y * k };
	};

	Coord& operator*=(const int& k)
	{
		*this = *this * k;
		return *this;
	};
	Coord& operator*=(const int&& k)
	{
		*this = *this * k;
		return *this;
	};
};

struct CompareCoord
{
	bool operator()(const Coord& c1, const Coord& c2) const
	{
		if (c1.x == c2.x)
			return c1.y < c2.y;
		else
			return c1.x < c2.x;
	};
};



/********************************************************************
** Vector, for speed, damage .etc.
*/
struct Vector
{
	double x;
	double y;

	Vector() : x(0.0), y(0.0) {}
	Vector(double _x, double _y) : x(_x), y(_y) {}
	Vector(const Vector& obj) : x(obj.x), y(obj.y) {}

	bool operator==(const Vector& obj) const
	{
		/*
		** WARNING!!!
		** Here, I'm too lazy to use a precision to compare two
		** double numbers. If it doesn't run properly, just
		** make a little change to it. :)
		*/
		return (this->x == obj.x) && (this->y == obj.y);
	};
	Vector& operator=(const Vector& obj)
	{
		this->x = obj.x;
		this->y = obj.y;

		return *this;
	};
	Vector operator+(const Vector& obj) const
	{
		return { this->x + obj.x, this->y + obj.y };
	};
	Vector operator-(const Vector& obj) const
	{
		return { this->x - obj.x, this->y - obj.y };
	};
	Vector operator-() const
	{
		return { -this->x, -this->y };
	};
	Vector& operator+=(const Vector& obj)
	{
		this->x += obj.x;
		this->y += obj.y;

		return *this;
	};
	Vector& operator-=(const Vector& obj)
	{
		this->x -= obj.x;
		this->y -= obj.y;

		return *this;
	}
	/*
	** 2022/01/20
	** Here... it is the inner product. :(
	*/
	double operator*(const Vector& obj)
	{
		return this->x * obj.x + this->y * obj.y;
	};
	friend Vector operator*(const double& k, const Vector& obj)
	{
		return { k * obj.x, k * obj.y };
	};
	friend Vector operator*(const double&& k, const Vector& obj)
	{
		return { k * obj.x, k * obj.y };
	};
	friend Vector operator*(const Vector& obj, const double& k)
	{
		return { k * obj.x, k * obj.y };
	};
	friend Vector operator*(const Vector& obj, const double&& k)
	{
		return { k * obj.x, k * obj.y };
	};
	friend Vector operator/(const Vector& obj, const double& k)
	{
		return { obj.x / k, obj.y / k };
	};
	friend Vector operator/(const Vector& obj, const double&& k)
	{
		return { obj.x / k, obj.y / k };
	};
};


// Default coordinate.
const Coord ZERO_COORD = { 0, 0 };
const Coord ORIGIN = { 0, 0 };

// Unit vector.
const Vector UNIT_X = { 1.0, 0.0 };
const Vector UNIT_Y = { 0.0, 1.0 };

const Vector ZERO_VECTOR = { 0.0, 0.0 };



/******************************************************************************
**                             Type of Elements                              **
*******************************************************************************/

/********************************************************************
** Figure types.
*/
enum HeroType
{
	HERO_YONY = 0,

	HERO_NUM
};

enum EnemyType
{
	ENEMY_SQUARE = 0,
	ENEMY_SQUAREX,
	ENEMY_MEGA,

	ENEMY_NUM
};


/********************************************************************
** Weapon type.
*/
enum WeaponType
{
	WEAPON_PISTOL = 0,
	WEAPON_RIFLE,
	WEAPON_FLAME,
	WEAPON_FLAMEX,

	WEAPON_NUM,

	WEAPON_UNKNOWN
};

const std::map<std::wstring, WeaponType> WEAPON_TYPE_MAP = {
	{ L"Pistol", WEAPON_PISTOL },
	{ L"Rifle", WEAPON_RIFLE },
	{ L"Flame", WEAPON_FLAME },
	{ L"FlameX", WEAPON_FLAMEX } };


/********************************************************************
** Bullet type.
*/
enum BulletType
{
	BULLET_PEPPER = 0,
	BULLET_FIRE,

	BULLET_NUM,

	BULLET_UNKNOWN
};

const std::map<std::wstring, BulletType> BULLET_TYPE_MAP = {
	{ L"Pepper", BULLET_PEPPER },
	{ L"Fire", BULLET_FIRE } };


/********************************************************************
** Buff type.
*/
enum BuffType
{
	BUFF_WEAPON,
	BUFF_CREATE,
	BUFF_GOLD,
	BUFF_AMMO,
	BUFF_PORTAL,

	BUFF_NUM
};

const std::map<std::wstring, BuffType> BUFF_TYPE_MAP = {
	{ L"Weapon", BUFF_WEAPON },
	{ L"Create", BUFF_CREATE },
	{ L"Gold", BUFF_GOLD },
	{ L"Ammo", BUFF_AMMO },
	{ L"Portal", BUFF_PORTAL } };


/********************************************************************
** Brick Type.
*/
enum BrickType
{
	BRICK_FLOOR = 0,
	BRICK_WALL,
	BRICK_GATE,

	BRICK_NUM
};

const std::map<std::wstring, BrickType> BRICK_TYPE_MAP = {
	{ L"Floor", BRICK_FLOOR },
	{ L"Wall", BRICK_WALL },
	{ L"Gate", BRICK_GATE } };



/********************************************************************
** Type of transition.
*/
enum TransitType
{
	TRANS_NONE = 0,
	TRANS_COVER,
	TRANS_DARKEN
};

const std::map < std::string, TransitType> TRANSIT_TYPE_MAP = {
	{ "none", TRANS_NONE },
	{ "cover", TRANS_COVER },
	{ "darken", TRANS_DARKEN } };

struct TransitStyle
{
	TransitType type;
	int duration;

	TransitStyle() : type(TRANS_NONE), duration(0) {}
};


#endif