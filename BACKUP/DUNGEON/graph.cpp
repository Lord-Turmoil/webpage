/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : graph.cpp                                 *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 28, 2022                          *
 *                                                                            *
 *                    Last Update :                                           *
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

#include <map>
#include <queue>
#include <vector>

#include "graph.h"
#include "define.h"
#include "auxilliary.h"


/******************************************************************************
 * Graph::Graph -- Constructor of the object.                                 *
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
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
Graph::Graph() : width(0), height(0), next({ 0, 0 }) {}


/******************************************************************************
 * Graph::Deconstructor of the object.                                        *
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
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
Graph::~Graph() {}


/******************************************************************************
 * Graph::init -- Initialize the graph.                                       *
 *                                                                            *
 *    Here, the graph is specific to be just like the enclosed space. This    *
 *    function make the out-bound of the graph to be wall.                    *
 *    PS: Later may init more complicated graph.                              *
 *                                                                            *
 * INPUT:   _width  -- Width of the graph.                                    *
 *          _height -- Height of the graph.                                   *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  The minimum width and height is 3!                              *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
void Graph::init(int _width, int _height)
{
	graph.clear();

	width = _width;
	height = _height;

	graph.resize(height, std::vector<Grid>(width));

	generate();
}


/******************************************************************************
 * Graph::clear -- Clear the graph.                                           *
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
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
void Graph::clear()
{
	for (int i = height - 2; i > 0; i--)
	{
		for (int j = width - 2; j > 0; j--)
			graph[i][j].reset();
	}
}


/******************************************************************************
 * Graph::isLegal -- Check if the subscription is legal or not.               *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   sub -- Subscription of the grid.                                  *
 *                                                                            *
 * OUTPUT:  Return true if is legal.                                          *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
bool Graph::isLegal(const Coord& sub)
{
	return ((0 <= sub.x) && (sub.x < height) && (0 <= sub.y) && (sub.y < width));
}
bool Graph::isLegalStrict(const Coord& sub)
{
	return ((2 <= sub.x) && (sub.x < height - 2) && (2 <= sub.y) && (sub.y < width - 2));
}

/******************************************************************************
 * Graph::entry -- Entry a block to the graph.                                *
 *                                                                            *
 *    This is for, well, the enemy, perhaps later the bullet also.            *
 *                                                                            *
 * INPUT:   coord -- The coordinate to entry.                                 *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
void Graph::entry(const Coord& coord)
{
	if (isLegal(coord))
		graph[coord.x][coord.y].type = GridType::BLOCK;
}


/******************************************************************************
 * Graph::entry -- Entry blocks to the graph.                                 *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   topLeft     -- Top left of the entry area.                        *
 *          bottomRight -- Bottom right of the entry area.                    *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
void Graph::entry(const Coord& topLeft, const Coord& bottomRight)
{
	if ((!isLegal(topLeft)) || (!isLegal(bottomRight)))
		return;

	for (int i = topLeft.x; i <= bottomRight.x; i++)
	{
		for (int j = topLeft.y; j <= topLeft.y; j++)
			graph[i][j].type = GridType::BLOCK;
	}
}


/******************************************************************************
 * Graph::deEntry -- Justo opposite to the entry.                             *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   coord                                                             *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
void Graph::deEntry(const Coord& coord)
{
	if (isLegal(coord))
		graph[coord.x][coord.y].type = GridType::NONE;
}



/******************************************************************************
 * Graph::deEntry -- Just opposite to the entry.                              *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   topLeft                                                           *
 *          bottomRight                                                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
void Graph::deEntry(const Coord& topLeft, const Coord& bottomRight)
{
	if ((!isLegal(topLeft)) || (!isLegal(bottomRight)))
		return;

	for (int i = topLeft.x; i <= bottomRight.x; i++)
	{
		for (int j = topLeft.y; j <= topLeft.y; j++)
			graph[i][j].type = GridType::BLOCK;
	}
}


/******************************************************************************
 * Graph::heuristic -- Calculate the heuristic value.                         *
 *                                                                            *
 *    Here we simply use the Manhattan distance.                              *
 *                                                                            *
 * INPUT:   pos1 -- A coordinate.                                             *
 *          pos2 -- Another coordinate.                                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
int Graph::heuristic(const Coord& pos1, const Coord& pos2)
{
	return getManhattanDistance(pos1, pos2);
}


/******************************************************************************
 * Graph::advance -- Find the shortest path.                                  *
 *                                                                            *
 *    This one find the shortest path to the target and then keep the next    *
 *    step to go.                                                             *
 *                                                                            *
 * REFERENCE:                                                                 *
 *          https://www.redblobgames.com/pathfinding/a-star/introduction.html *
 *                                                                            *
 * INPUT:   src  -- Source of the finding.                                    *
 *          dest -- Destination.                                              *
 *                                                                            *
 * OUTPUT:  Return whether a path exists.                                     *
 *                                                                            *
 * WARNINGS:  Remember to clear the path after finding.                       *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
bool Graph::advance(const Coord& src, const Coord& dest)
{
	if (src == dest)
		return false;

	std::priority_queue<AStarToken, std::vector<AStarToken>, GreaterAStarToken> frontier;
	AStarToken current;
	Coord sub;
	int new_cost;
	bool has_path = false;

	graph[src.x][src.y].cost = 0;
	graph[src.x][src.y].father = src;

	frontier.push(AStarToken(src, 0));

	while (!frontier.empty())
	{
		current = frontier.top();
		frontier.pop();

		if (current.sub == dest)
		{
			has_path = true;
			break;
		}

		for (int d = 0; d < 8; d++)
		{
			sub = current.sub + DIR[d];

			if (!isLegal(sub))
				continue;
			if (graph[sub.x][sub.y].type != GridType::NONE)
				continue;

			new_cost = graph[current.sub.x][current.sub.y].cost + DIR_COST[d];

			if (new_cost < graph[sub.x][sub.y].cost)
			{
				graph[sub.x][sub.y].father = current.sub;
				graph[sub.x][sub.y].cost = new_cost;
				frontier.push(AStarToken(sub, new_cost + heuristic(sub, dest)));
			}
			else if (new_cost == graph[sub.x][sub.y].cost)
			{
				if (random(0, 1))
					graph[sub.x][sub.y].father = current.sub;
			}
		}
	}

	if (!has_path)
	{
		clearPath();
		
		return false;
	}

	sub = dest;
	while (graph[sub.x][sub.y].father != src)
		sub = graph[sub.x][sub.y].father;
	next = sub;

	// Prepare for the next find.
	clearPath();

	return true;
}


/******************************************************************************
 * Graph::retreat -- Find the path to retreat.                                *
 *                                                                            *
 *    This one only search one step and choose the "worst" one to go, which   *
 *    looks like a retreat.                                                   *
 *                                                                            *
 * REFERENCE:                                                                 *
 *          https://www.redblobgames.com/pathfinding/a-star/introduction.html *
 *                                                                            *
 * INPUT:   src  -- Source of the finding.                                    *
 *          dest -- Destination.                                              *
 *                                                                            *
 * OUTPUT:  Return whether a choice exists.                                   *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/02/19 Tony : Created.                                               *
 *============================================================================*/
bool Graph::retreat(const Coord& src, const Coord& dest)
{
	if (src == dest)
		return false;

	std::priority_queue<AStarToken, std::vector<AStarToken>, LessAStarToken> frontier;
	AStarToken current(src, 0);
	Coord sub;
	int new_cost;

	graph[src.x][src.y].cost = 0;

	for (int d = 0; d < 8; d++)
	{
		sub = current.sub + DIR[d];

		if (!isLegalStrict(sub))
			continue;
		if (graph[sub.x][sub.y].type != GridType::NONE)
			continue;

		new_cost = graph[current.sub.x][current.sub.y].cost + DIR_COST[d];

		if (new_cost < graph[sub.x][sub.y].cost)
			frontier.push(AStarToken(sub, new_cost + heuristic(sub, dest)));
	}

	// Here, only one grid changes.
	graph[src.x][src.y].reset();

	if (frontier.empty())
		return false;

	next = frontier.top().sub;

	return true;
}


/******************************************************************************
 * Graph::findBlank -- Find a blank position in the graph.                    *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   _width  -- The width needed.                                      *
 *          _height -- The height needed.                                     *
 *                                                                            *
 * OUTPUT:  Return whether is blank or not.                                   *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
bool Graph::findBlank(int _width, int _height)
{
	std::queue<Coord> candidate;
	std::map<Coord, int, CompareCoord> visited;
	Coord current;
	int max_x = height - 1 - _height;
	int max_y = width - 1 - _width;
	bool flag = false;

	if ((max_x < 1) || (max_y < 1))
		return false;


	candidate.push({ random(1, max_x), random(1, max_y) });
	while (!candidate.empty())
	{
		current = candidate.front();
		candidate.pop();
		if (visited.find(current) != visited.end())
			continue;
		visited[current] = 1;

		flag = true;
		for (int i = _height - 1; (i >= 0) && flag; i--)
		{
			for (int j = _width - 1; (j >= 0) && flag; j--)
			{
				if (graph[current.x + i][current.y + j].type != GridType::NONE)
					flag = false;
				else
				{
					if (!((current.x + i > max_x) || (current.y + j > max_y)))
						candidate.push({ current.x + i, current.y + j });
				}
			}
		}
		if (flag)
		{
			blank = current;
			break;
		}

		if (current.x - _height > 0)
			candidate.push({ current.x - _height, current.y });
		if (current.y - _width > 0)
			candidate.push({ current.x, current.y - _width });
		if (current.x + _height <= max_x)
			candidate.push({ current.x + _height, current.y });
		if (current.y + _width <= max_y)
			candidate.push({ current.x, current.y + _width });
	}

	return flag;
}


/******************************************************************************
 * Graph::inSight -- Check if dest is in sight of src.                        *
 *                                                                            *
 *    This function works by drawing a line between two points and see if any *
 *    block blocks it.                                                        *
 *                                                                            *
 * REFERENCE:  https://www.redblobgames.com/grids/line-drawing.html           *
 *                                                                            *
 * INPUT:   _width  -- The width needed.                                      *
 *          _height -- The height needed.                                     *
 *                                                                            *
 * OUTPUT:  Return whether is blank or not.                                   *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/28 Tony : Created.                                               *
 *============================================================================*/
bool Graph::inSight(const Coord& src, const Coord& dest)
{
	Coord diff = dest - src;
	Coord p = src;
	int dx = SIGN(diff.x);
	int dy = SIGN(diff.y);
	int decision;

	diff.x = ABS(diff.x);
	diff.y = ABS(diff.y);

	for (int ix = 0, iy = 0; (ix < diff.x) || (iy < diff.y);)
	{
		decision = (1 + 2 * iy) * diff.x - (1 + 2 * ix) * diff.y;
		if (decision == 0)
		{
			// diagonal
			p.x += dx;
			p.y += dy;
			ix++;
			iy++;
		}
		else if (decision < 0)
		{
			// horizontal
			p.y += dy;
			iy++;
		}
		else
		{
			// vertical
			p.x += dx;
			ix++;
		}
		if (graph[p.x][p.y].type != GridType::NONE)
			return false;
	}

	return true;
}


/******************************************************************************
 * Graph::generate -- Generate the map.                                       *
 *                                                                            *
 *    Currently, just generate an enclosed one.                               *
 *                                                                            *
 * INPUT:   none                                                              *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
void Graph::generate()
{
	for (int i = 0; i < width; i++)
	{
		graph[0][i].type = GridType::BRICK_WALL;
		graph[height - 1][i].type = GridType::BRICK_WALL;
	}
	for (int i = height - 2; i > 0; i--)
	{
		graph[i][0].type = GridType::BRICK_WALL;
		graph[i][width - 1].type = GridType::BRICK_WALL;
	}
}


/******************************************************************************
 * Graph::clearPath -- Clear only the path.                                   *
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
 *   2022/01/27 Tony : Created.                                               *
 *============================================================================*/
void Graph::clearPath()
{
	for (int i = height - 2; i > 0; i--)
	{
		for (int j = width - 2; j > 0; j--)
		{
			if (graph[i][j].type == GridType::NONE)
				graph[i][j].reset();
		}
	}
}