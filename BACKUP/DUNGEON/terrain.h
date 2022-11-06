/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : terrain.h                                 *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 13, 2022                          *
 *                                                                            *
 *                    Last Update : February 4, 2022                          *
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

#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <vector>
#include <easyx.h>
#include <functional>

#include "graph.h"
#include "image.h"
#include "define.h"
#include "object.h"
#include "config.h"


/********************************************************************
** Brick's size. For the floor, it is BRICK_WIDH * BRICK_WIDTH, but
** for the bricks that have height, it is BRICK_WIDTH * BRICK_HEIGHT.
*/
const int BRICK_WIDTH = 40;
const int BRICK_HEIGHT = 60;


/********************************************************************
** Bricks are the basic elements of the terrain.
*/
class Brick : public PhysicalObject
{
public:
	Brick(BrickType _type);
	virtual ~Brick();

	BrickType getBrickType() const;

	virtual void setPos(const Coord& _pos);

	/*
	** 2022/01/14
	** Initialize the symbol's property.
	*/
	void initSymbol();

	/*
	** Update brick info. In fact, only Door have properties to
	** update. If the room is in fire, then the door locks.
	*/
	virtual void update() = 0;

	virtual void load(GameResourceId resId) = 0;
	virtual void draw(Camera& cam) = 0;
protected:
	virtual void move();

	BrickType brickType;
};


/********************************************************************
** Floor is a... Brick. :?
*/
class Floor : public Brick
{
public:
	Floor();
	~Floor();

	/*
	** Return its' image, for the game to make a large background
	** floor.
	*/
	IMAGE* getImage();

	virtual void update();

	virtual void load(GameResourceId resId);
	virtual void draw(Camera& cam);

private:
	IMAGE* pImage;
};


/********************************************************************
** Wall is the boundary of the room. It can also work as barriers.
** Nothing special.
*/
class Wall : public Brick
{
public:
	Wall();
	~Wall();

	virtual void update();

	virtual void load(GameResourceId resId);
	virtual void draw(Camera& cam);

private:
	IMAGE* pImage;
};


/********************************************************************
** Gate is a quite special brick for it can open and close. So it
** has four motions. :)
*/
enum GateState
{
	GATE_CLOSED = 0,
	GATE_OPENING,
	GATE_OPEN,
	GATE_CLOSING,
	GATE_END,			// a motion ends

	GATE_STATE_NUM,
};


/********************************************************************
** Gate state machine is for the state transform. The row is the 
** former state.
*/
const GateState GATE_STATE_MACHINE[GATE_STATE_NUM][GATE_STATE_NUM] = {
	{ GATE_CLOSED,	GATE_OPENING,	GATE_OPENING,	GATE_CLOSED,	GATE_CLOSED	},
	{ GATE_CLOSING,	GATE_OPENING,	GATE_OPENING,	GATE_CLOSING,	GATE_OPEN	},
	{ GATE_CLOSING,	GATE_OPEN,		GATE_OPEN,		GATE_CLOSING,	GATE_OPEN	},
	{ GATE_CLOSING,	GATE_OPENING,	GATE_OPENING,	GATE_CLOSING,	GATE_CLOSED	} };


const int GATE_MOTION_MAP[GATE_STATE_NUM] = { 0, 1, 2, 3, -1 };

class Gate : public Brick
{
public:
	Gate();
	~Gate();

	/*
	** 2022/01/17
	*/
	void lock();
	void unlock();

	virtual void update();

	virtual void load(GameResourceId resId);
	virtual void draw(Camera& cam);

private:
	void setState(GateState _state);
	void updateState();

	GateState state;
};



/********************************************************************
** Space is the base class of the area, including rooms for firing
** and bridges that connect the rooms. And it has the callback to
** generate enemies and buffs.
*/

const int GATE_WIDTH = 6;

// Type of space.
enum SpaceType
{
	VACANT = 0,	// nothing.
	ARENA,
	BRIDGE
};

// Space state.
struct SpaceAttribute
{
	/*
	** How many rounds of firing the space left.
	*/
	int rounds;

	/*
	** Whether discovered yet.
	*/
	bool isDiscovered : 1;

	/*
	** Whether the firing is over.
	*/
	bool isCompleted : 1;

	/*
	** Whether the space should generate a create or not.
	*/
	bool hasCreate : 1;

	/*
	** If the space has boss.
	*/
	bool hasBoss : 1;

	/*
	** Whether the space is the end of a level.
	*/
	bool isEnd : 1;

	/*
	** 2022/01/18
	** Whether is the current space.
	*/
	bool isCurrent : 1;

	/*
	** 2022/02/19
	** Whether the hero is trapped or not. Once trapped,
	** it will only end after completing the arena.
	*/
	bool isTrapped : 1;

	SpaceAttribute()
		: rounds(0), isDiscovered(false), isCompleted(false), hasCreate(false),
		hasBoss(false), isEnd(false), isCurrent(false), isTrapped(false) {}

	void init()
	{
		rounds = 0;
		isDiscovered = false;
		isCompleted = false;
		hasCreate = false;
		hasBoss = false;
		isEnd = false;
		isCurrent = false;
		isTrapped = false;
	}
	
	void update()
	{
		/*
		** 2022/02/19
		** If rounds is 0, the last round is still hanging around.
		*/
		if ((rounds == -1) && (!isCompleted))
		{
			isCompleted = true;
			hasCreate = true;
			isTrapped = false;
		}
	}
};

// Directions.
enum Direction : unsigned
{
	DIR_NONE	= 0,
	DIR_LEFT	= 1,
	DIR_RIGHT	= 2,
	DIR_UP		= 4,
	DIR_DOWN	= 8
};

// Role of the space.
enum SpaceRole : unsigned
{
	SPACE_NONE	= 0,
	SPACE_START	= 1,
	SPACE_END	= 2
};


// This records every bricks info for the enemy to find path.
typedef std::vector<std::vector<BrickType>> BrickMatrix;

class Space
{
public:
	Space(SpaceType _type);
	virtual ~Space();

	SpaceType getType() const;
	PhysicalObjectPool* getBrickPool();

	Coord getCenter() const;

	/*
	** Convert between absolute position and relative position.
	** And the relative position is actually... the index of the
	** brick matrix.
	*/
	Coord convert(Coord coord, bool invert = false);

	/*
	** Convert the length to unit length for the subscription.
	*/
	int convert(int length);

	/*
	** Check if the point is in the space.
	*/
	bool isInside(Coord target);

	virtual void entry() = 0;
	virtual void update(const Coord& target) = 0;

	/*
	** When the space is roughly generated by the Terrain, the
	** space calls this one to complete the generation.
	*/
	virtual void generate() = 0;

	void draw(Camera& cam);

	/*
	** Draw mini space on the mini map.
	*/
	void drawMiniSpace(IMAGE* pDestImage);

	/*
	** 2022/01/27
	** To find path.
	*/
	Graph graph;

	SpaceAttribute attribute;

protected:
	SpaceType type;

	int width;
	int height;

	Coord pos;		// top-left coordinate
	Coord center;	// center coordinate
	Coord offset;	// offset for pos-center convert

	PhysicalObjectPool brickPool;

	/*
	** Piece together all floors.
	*/
	IMAGE floorImage;
	Symbol floor;

public:
	/*
	** Some function needed in generating the map.
	*/
	void setUnitPos(Coord _unitPos);
	void setSubscript(Coord _subscript);
	void setUnitSize(int _unitWidth, int _unitHeight);
	void setGateSide(unsigned side);
	void setRole(unsigned role);

	Coord getUnitPos() const;
	Coord getSubscript() const;
	int getUnitWidth() const;
	int getUnitHeight() const;

	bool addNeighbor(Space* neighbor);

protected:
	/*
	** Some members needed in generate the map.
	*/
	Coord unitPos;
	Coord subscript;
	int unitWidth;
	int unitHeight;
	
	unsigned gateSide;
	unsigned spaceRole;

	/*
	** 2022/02/19
	** The neighboring spaces. The neighbors of the
	** current space will be discovered.
	*/
	std::vector<Space*> neighborList;
};


/********************************************************************
** Arena is the place where the firing takes place.
*/
class Arena : public Space
{
public:
	Arena();
	~Arena();

	virtual void entry();
	virtual void update(const Coord& target);
	virtual void generate();

private:
	/*
	** Check if the hero is totally in the arena.
	*/
	bool inTrap(const Coord& target);

	/*
	** To lock or unlock the gate of the arena.
	*/
	void lock();
	void unlock();

	/*
	** 2022/01/17
	** Added gate list to simplify the process of lock and
	** unlock the arena.
	*/
	std::vector<Gate*> gateList;

	/*
	** 2022/02/21
	** Keep obstacles for the graph to find path.
	*/
	std::vector<Coord> obstacleList;

	bool isLocked;
};


/********************************************************************
** Bridge connects arenas.
*/
class Bridge : public Space
{
public:
	Bridge();
	~Bridge();

	virtual void entry() {}
	virtual void update(const Coord& target);
	virtual void generate();

private:

};


/********************************************************************
** Edge is used in prim.
*/
struct Edge
{
	int from;		// start point of an edge
	int to;			// ending point of an edge
	int weight;		// the random weight of the edge
	int dir;		// direction of the ending to the start
	int next;		// next edge
};


/********************************************************************
** PrimToken is also used in prim, and record info.
*/
struct PrimToken
{
	int weight;		// weight of the edge
	int vertex;		// ending point of the edge
	int edgeId;		// id of the edge
};

struct ComparePrimToken
{
	bool operator()(const PrimToken& t1, const PrimToken& t2) const
	{
		// decreasing
		return t1.weight > t2.weight;
	};
};


/********************************************************************
** Some constants needed in prim.
*/
const int MAX_EDGE_WEIGHT = 200;

const int MAP_SIZE = 3;

const int MIN_SPACE_SIZE = 15;
const int MAX_SPACE_SIZE = 20;
const int WRAPPER_SIZE = 30;	// Spaces are in the wrapper.

const int LARGE_MAP_SIZE = MAP_SIZE * WRAPPER_SIZE * BRICK_WIDTH;
const int MINI_MAP_SIZE = 100;
const float ASPECT_RATIO = (float)MINI_MAP_SIZE / (float)LARGE_MAP_SIZE;

const Coord MAP_CENTER = { LARGE_MAP_SIZE >> 1, LARGE_MAP_SIZE >> 1 };

/********************************************************************
** Terrain takes hold of the map of the game.
*/
class Terrain
{
public:
	Terrain();
	~Terrain();

	/*
	** To generate a map of certain properties.
	*/
	void generate(int level, int difficulty, bool _hasBoss = false, bool _isDeath = false);

	Space* getCurrentSpace();

	void update(const Coord& target);
	void draw(Camera& cam);

private:
	void generateMiniMap();
	void generateCampaign(int level, int difficulty);
	void generateDeath(int level, int difficulty);

	IMAGE miniMapImage;
	Symbol miniMap;

	bool isDeath;

	bool hasBoss;

private:
	/*
	** Static members for map generation.
	*/
	static void addEdge(int from, int to, unsigned direction);
	static void initPrim();
	static void randomPrim(int num);
	static void generateSpace();

	static bool vertexFlag[9];
	static bool edgeFlag[30];

	static Edge edgeList[30];
	static int headList[9];
	static int distList[9];
	static int edgestamp;

	static std::priority_queue<PrimToken, std::vector<PrimToken>, ComparePrimToken> primHeap;


	/*
	** 2022/01/18
	** These can't be as non-static member. :(
	*/

	/*
	** All spaces of a level's map.
	*/
	static std::vector<Space*> spacePool;

	/*
	** The current space that the hero is in.
	*/
	static Space* curSpace;

	/*
	** The start space is the space hero is in when a
	** level starts.
	*/
	static Space* startSpace;

	/*
	** The end space is the space that is the end of a
	** level.
	*/
	static Space* endSpace;
};

#endif