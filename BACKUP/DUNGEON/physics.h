/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : physics.h                                 *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 1, 2022                           *
 *                                                                            *
 *                    Last Update : January 22, 2022                          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 * Over View:                                                                 *
 *   Properties and functions for physics effects.                            *
 * -------------------------------------------------------------------------- *
 * Build Environment:                                                         *
 *   Visual Studio 2022 Community                                             *
 *   EasyX 20220116                                                           *
 *   Windows 11 Pro                                                           *
 ******************************************************************************/

#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "define.h"
#include "auxilliary.h"


 /********************************************************************
** This object provide physical properties to objects that have
** collision or other physical effects.
*/
class PhysicalProperty
{
public:
	/*
	** Here, mass is the actual value of the object, and the
	** Constructor will invert it, but regard 0 as infinite.
	*/
	PhysicalProperty();
	virtual ~PhysicalProperty();

	void setMass(int mass);

	/*
	** This is for the figure, who may carray other objects.
	*/
	void addMass(int mass);

	/*
	** Calculate current acceleration and velocity.
	*/
	void getAcc();
	void getVel();

public:
	/*
	** 2022/01/20
	** Make these public. :(
	*/

	/*
	** m is the actual mass.
	** rm is the reciprocal of the mass, 0.0 means it can't move
	** or be moved.
	*/
	int m;
	double rm;

	/*
	** Fractional coefficient. The Greek letter mu.
	*/
	double mu;

	/*
	** Wind drag coefficient.
	*/
	double drag;

	/*
	** 2022/01/12
	** The strength of the object. It means that when it moves,
	** there will be a force equal to strength to pull it. But
	** it can also be an instant force that only apply for one
	** frame.
	*/
	double strength;

	/*
	** The force it gets, used to calculate the acceleration,
	** and then influence the velocity.
	*/
	Vector f;
	Vector a;
	Vector v;
};

#endif