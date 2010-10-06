/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * roboHockey
 * Copyright (C) Albert Cervin 2010 <albert@nat0.se>
 * 
 * roboHockey is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * roboHockey is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "game/goal.h"

Goal::Goal(unsigned int lX, unsigned int fY, 
		     unsigned int bY, unsigned int rX) :
leftX(lX),
frontY(fY),
backY(bY),
rightX(rX)
{}

bool Goal::isGoal(Math::Vector2D<double> &position)
{
	unsigned int x = floor(position.x); unsigned int y = floor(position.y);
	
	if (x > leftX && x < rightX && y < frontY && y > backY)
		return true;
	else if (x > leftX && x < rightX && y > frontY && y < backY)
		return true;
	else
		return false;
}