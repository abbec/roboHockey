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

#ifndef _PUCK_H_
#define _PUCK_H_

#include "math/vector2D.h"

class Puck
{
	public:
		
		Math::Vector2D<double>& getPosition() { return position; }
		Math::Vector2D<double>& getVelocity() { return velocity; }

		void setPosition(int x, int y) { position.x = x; position.y = y; }
		inline void setPosition(Math::Vector2D<double> pos) { position = pos; }
		inline void setVelocity(Math::Vector2D<double> vel) { velocity = vel; }
		void move() { position += velocity; velocity = velocity*0.99; }
		
	private:
		Math::Vector2D<double> position;
		Math::Vector2D<double> velocity;

};

#endif // _PUCK_H_
