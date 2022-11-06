/******************************************************************************
 ***                   N E W  D E S I R E  S T U D I O S                    ***
 ******************************************************************************
 *                   Project Name : Dungeon                                   *
 *                                                                            *
 *                      File Name : physics.cpp                               *
 *                                                                            *
 *                     Programmer : Tony Skywalker                            *
 *                                                                            *
 *                     Start Date : January 22, 2022                          *
 *                                                                            *
 *                    Last Update :                                           *
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

#include "timing.h"
#include "physics.h"

#define IS_STATIC

extern Time globalTimer;


/******************************************************************************
 * PhysicalProperty::PhysicalProperty -- Constructor of the object.           *
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
PhysicalProperty::PhysicalProperty()
{
	m = 0;
	f = a = v = ZERO_VECTOR;
}


/******************************************************************************
 * PhysicalProperty::~PhysicalProperty -- Deconstructor of the object.        *
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
PhysicalProperty::~PhysicalProperty() {}


/******************************************************************************
 * PhysicalProperty::setMass -- Set mass.                                     *
 *                                                                            *
 *    Just the literal meaning.                                               *
 *                                                                            *
 * INPUT:   mass -- The mass to be set.                                       *
 *                                                                            *
 * OUTPUT:  none                                                              *
 *                                                                            *
 * WARNINGS:  none                                                            *
 *                                                                            *
 * HISTORY:                                                                   *
 *   2022/01/22 Tony : Created.                                               *
 *============================================================================*/
void PhysicalProperty::setMass(int mass)
{
	m = mass;
	if (m != 0)
		rm = 1.0 / m;
}


/******************************************************************************
 * PhysicalProperty::addMass -- Add mass to the object.                       *
 *                                                                            *
 *    The mass can be negative.                                               *
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
void PhysicalProperty::addMass(int mass)
{
	m += mass;

	if (m != 0)
		rm = 1.0 / m;
}


/******************************************************************************
 * PhysicalProperty::getAcc -- Get current acceleration.                      *
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
void PhysicalProperty::getAcc()
{
	double fraction = mu * m * G;
	if (IS_ZERO(getModule(v)))
	{
		if (getModule(f) > fraction)
			a = (f - getUnit(f) * fraction) * rm;
		else
			a = ZERO_VECTOR;
	}
	else
		a = (f - getUnit(f) * fraction - drag * v * v * getUnit(v)) * rm;
}


/******************************************************************************
 * PhysicalProperty::getVel -- Get current velocity.                          *
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
void PhysicalProperty::getVel()
{
	double nv;
	double fraction = mu * m * G;
	Vector unit_v = getUnit(v);
	double k = globalTimer.getDeltaTime() * 100.0;

	nv = v.x + a.x * k;
	if (IS_OPPOSITE(v.x, nv))
	{
		if (ABS(f.x) < fraction * unit_v.x)
			v.x = 0.0;
		else
			v.x = nv;
	}
	else
		v.x = nv;

	nv = v.y + a.y * k;
	if (IS_OPPOSITE(v.y, nv))
	{
		if (ABS(f.y) < fraction * unit_v.y)
			v.y = 0.0;
		else
			v.y = nv;
	}
	else
		v.y = nv;
}