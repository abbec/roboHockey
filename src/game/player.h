/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * roboHockey
 * Copyright (C) Emil Brissman <>
 * 
 * splat is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * splat is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "math/vector2D.h"
#include "game/skills.h"
#include <string>

class Team;

class Player
{
	public:
 		// Constructor
 		Player(std::string n, bool g, Skills s);
 	
 		// Functions
 		inline Math::Vector2D<double>& getPosition() { return position; }
		inline Math::Vector2D<double>& getVelocity() { return velocity; }
		
	 	inline void setVelocity(Math::Vector2D<double> vel) { velocity = vel; }
		inline void setPosition(unsigned int x, unsigned int y) { position.x = x; position.y = y; }
		inline void setTeam(Team *t) { team = t; }
		inline void setLock(int v) { lock = (v > 0 ? v : 0); velocity = Math::Vector2D<double>(0,0);}
		Skills * getSkills() { return &skills; }
		std::string getName() { return name; }
	 	void move();

		// AI methods
		void makeMove();
 	
 	private:
	 	// Data members
	 	std::string name;
	 	bool gender; // true = woman, false = man
	 	Math::Vector2D<double> position;
	 	Math::Vector2D<double> velocity;
		Skills skills;
		int lock;

		Team *team;
		
		void makeDefensiveMove();
		void makeOffensiveMove();
		
		void tackle();
		void shoot();
 		
};


#endif