/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : graph.h                                   *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 27, 2022                          *
 *                                                                            *
 *                    Last Update : February 20, 2022                         *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   For the enemies' path finding. Here we specific the graph to be a closed *
 *   space. And algorithms in the graph.                                      *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _ASTAR_H_
#define _ASTAR_H_

#include <queue>
#include <vector>

#include "define.h"
#include "auxilliary.h"

 /********************************************************************
 ** The direction of each move, and their corresponding costs.
 */
const Coord DIR[8] = {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1},
	{-1, 1}, {-1, -1}, {1, -1}, {1, 1} };

const int DIR_COST[8] = { 2, 2, 2, 2, 3, 3, 3, 3 };

const int INF_COST = 0x3f3f3f;


/********************************************************************
** Here we use the grid to represent the graph.
*/
enum class GridType
{
	NONE,
	BRICK_WALL,

	/*
	** BLOCK is the temporary obstacle in the space. perhaps
	** the hero, the other enemies or past bricks.
	*/
	BLOCK
};


struct Grid
{
	GridType type;
	int cost;
	Coord father;

	Grid() : cost(INF_COST), father({ 0, 0 }), type(GridType::NONE) {}
	void reset()
	{
		cost = INF_COST;
		father = ZERO_COORD;
		type = GridType::NONE;
	}
};


/********************************************************************
** This is the info needed for the sorting in A*.
*/
struct AStarToken
{
	// Subscription of the grid.
	Coord sub;

	// Cost and heuritics.
	int priority;

	AStarToken(Coord _sub = { 0, 0 }, int _priority = 0) : sub(_sub), priority(_priority) {}
};

// For shortest path heap.
struct GreaterAStarToken
{
	bool operator()(const AStarToken& t1, const AStarToken& t2) const 
	{
		return t1.priority > t2.priority;
	};
};

// For long path heap.
struct LessAStarToken
{
	bool operator()(const AStarToken& t1, const AStarToken& t2) const
	{
		return t1.priority < t2.priority;
	};
};


/********************************************************************
** A class for A* algorithm. This should work with Space for it
** needs the conversion between actual coordinate and subscript of
** each individual space.
*/
typedef std::vector<std::vector<Grid>> GridMatrix;

class Graph
{
public:
	Graph();
	~Graph();

	/*
	** Initialize the map with assigned size, and then 
	** call the generate() to be a enclosed space.
	*/
	void init(int _width, int _height);

	/*
	** Clear everything in the map except the walls.
	*/
	void clear();

	/*
	** Entry a block or a lot of blocks to the map.
	*/
	void entry(const Coord& coord);
	void entry(const Coord& leftTop, const Coord& bottomRight);

	/*
	** De-entry a block or a lot of blocks to the map.
	** I'm not sure there is a "de-entry" or not. :)
	*/
	void deEntry(const Coord& coord);
	void deEntry(const Coord& leftTop, const Coord& bottomRight);

	/*
	** Find a path and if there has, store the next
	** move int next.
	*/
	bool advance(const Coord& src, const Coord& dest);
	bool retreat(const Coord& src, const Coord& dest);

	/*
	** Find a blank position in the graph.
	*/
	bool findBlank(int _width, int _height);

	/*
	** Check if the src can see the dest or not.
	*/
	bool inSight(const Coord& src, const Coord& dest);

	/*
	** The next move.
	*/
	Coord next;

	/*
	** The blank position.
	*/
	Coord blank;

private:
	/*
	** Check if the subscription is valid or not.
	*/
	bool isLegal(const Coord& coord);
	bool isLegalStrict(const Coord& coord);

	/*
	** To calculate the heuristic value.
	*/
	int heuristic(const Coord& pos1, const Coord& pos2);

	/*
	** Generate the graph to be a enclosed space.
	*/
	void generate();

	/*
	** Clear the previous path to ready for the next roll.
	*/
	void clearPath();


	/*
	** Width and height are all unit ones of the space.
	*/
	int width;
	int height;

	/*
	** The graph.
	*/
	GridMatrix graph;
};

#endif
