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

#ifndef _GAME_H_
#define _GAME_H_

#include "math/vector2D.h"
#include "game/team.h"
#include "game/puck.h"
#include "game/rink.h"
#include "game/clock.h"

class Player;

typedef unsigned short int usint;

class Game
{
	public:
		// Constructors
		Game();

		// The main loop of the game
		usint play();
		
		// Function for retrieving the puck position
		Math::Vector2D<double> getPuckPosition(){ return puck.getPosition(); }
		void setPuckVelocity(Math::Vector2D<double> v){ puck.setVelocity(v); }
		
		// Function for retrieveing players
		Player* getHomeTeamPlayers() { return homeTeam.getPlayers(); }
		Player* getAwayTeamPlayers() { return awayTeam.getPlayers(); }

		// Get goals for each team
		unsigned int getHomeScore() { return homeTeam.getGoals(); }
		unsigned int getAwayScore() { return awayTeam.getGoals(); }
		
		// Retrieving functions for teams
		Team* getHomeTeam() { return &homeTeam; }
		Team* getAwayTeam() { return &awayTeam; }

		// Get the period
		usint getPeriod() { return period; }

		// Get the clock
		std::string getClock() { return gameClock.printTime(); }

		void reset();

		static Game* instance();
		static Player * getPuckHolder() { return puckHolder; }
		static void setPuckHolder(Player *p) { puckHolder = p; }

		unsigned int getRinkCenterX() {return rink.CENTERX; }
		unsigned int getRinkCenterY() {return rink.CENTERY; }

		Rink* getRink() { return &rink; }

		Player *getNearestOpponent(Team *, Player *);
		
		// Class constants
		static const int FACEOFF, RUNNING, HOME_TEAM, AWAY_TEAM;

	private:
		Team homeTeam, awayTeam;
		Clock gameClock;
		Puck puck;
		usint period;
		Rink rink;
		int state;
		static Player *puckHolder;

		static Game* inst;

		// Functions
		void dropPuck();
		void faceOff();
		int goal();
		void checkPuckCollision();
		void checkPlayerCollisions();
		unsigned int gameTime();

};

#endif // _GAME_H_
