/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * team.h
 * Copyright (C) Emil Nathalie Ek
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

#ifndef _TEAM_H
#define _TEAM_H

#include "game/player.h"
#include "game/goal.h"
 
class Team
{
 	public:
 	//Konstruktor
 	Team(Player pl, Goal *gl, std::string n):p(pl), goal(gl), name(n), noGoals(0) 
	{p.setTeam(this);}
 	//Metoder
 	unsigned int getGoals() { return noGoals; }
 	void addGoal() { ++noGoals; }
	void resetGoals() { noGoals = 0; }
	void makeMove() {p.makeMove();}
 	void addPlayer(Player& p);
	Goal *getGoal(){ return goal; }
 	
 	Player* getPlayers();
 	
 	private:
 		//instansvarialber
 		Player p;
 		std::string name;
 		unsigned int noGoals;
 		Goal *goal;
 	
};


#endif