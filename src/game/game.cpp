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

#include <iostream>
#include <cstdlib>
#include "app/roboHockey.h"
#include "game/game.h"

Player* Game::puckHolder = NULL;
Game* Game::inst = NULL;

const int Game::AWAY_TEAM = 0;
const int Game::HOME_TEAM = 1;
const int Game::FACEOFF = 2;
const int Game::RUNNING = 3;

Game::Game() : 
gameClock(Clock(20,0)), 
puck(Puck()), 
period(1),
state(FACEOFF),
// Set up the teams
homeTeam(Player("Nathalie Ek", true, Skills(80, 60, 50, 80)),
         rink.getAwayGoal(), "Nathalie Rangers"),
awayTeam(Player("Emil Brissman", false, Skills(70, 90, 80, 50)),
         rink.getHomeGoal(), "Emil Blackhawks")
{
	faceOff();
}

Game* Game::instance()
{
	if (inst == NULL)
		inst = new Game();

	return inst;
}

usint Game::play()
{
	// Set game clock
	if (gameClock.isEnd())
		gameClock.reset();

	SDL_Event event;
	
	const unsigned int updateLength = 10, clockUpdate = 50, goalUpdate = 3000;
	unsigned int lastClockUpdate = 0, lastUpdate = 0, goalEvent = 0;
	
	// The main game loop
	while (!gameClock.isEnd())
	{

		// Check if we are to exit the game
		SDL_PollEvent(&event);

		if (event.type == SDL_KEYUP)
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return period;

		if (gameTime() - lastUpdate > updateLength)
		{
			if (state == FACEOFF)
			{
				dropPuck();
				state = RUNNING;
			}

			// Make AI moves
			awayTeam.makeMove();
			homeTeam.makeMove();
	
			// Check collisions
			checkPuckCollision();
			checkPlayerCollisions();

			// Check goals
			int team = goal();
			if (team != -1)
			{
				if (team == HOME_TEAM)
					homeTeam.addGoal();
				else if (team == AWAY_TEAM)
					awayTeam.addGoal();

				RoboHockey::instance()->updateWindow();
			
				// Wait a while and continue to move the puck
				goalEvent = gameTime();
				while ((gameTime() - goalEvent) <= goalUpdate)
				{
					checkPuckCollision();
					RoboHockey::instance()->updateWindow();
				}

				// Set up for a new faceoff
				faceOff();
				state = FACEOFF;
			}
			else
			{
				if (gameTime() - lastClockUpdate > clockUpdate)
				{
					gameClock.tick();
					lastClockUpdate = gameTime();
				}
			}

			// Set the new time for update
			lastUpdate = gameTime();
		}

		// Update the screen
		RoboHockey::instance()->updateWindow();
	}
	
	// Return control to the main loop and increase period
	// Also prepare for the next faceoff
	state = FACEOFF;
	faceOff();
	RoboHockey::instance()->updateWindow();
	return period++;
}

/** Reset the game to play a new game.
 */
void Game::reset()
{
	period = 1;
	state = FACEOFF;
	faceOff();

	homeTeam.resetGoals();
	awayTeam.resetGoals();
	gameClock.reset();
}

Player *Game::getNearestOpponent(Team *t, Player *p)
{
	if (t == &homeTeam)
		return getAwayTeamPlayers();
	else
		return getHomeTeamPlayers();
}

/**
 * Set the players up for a faceoff
 */
void Game::faceOff()
{
	// Make sure noone is puck holder
	puckHolder = NULL;
	
	// Put the puck in the center
	puck.setPosition(rink.CENTERX, rink.CENTERY);

	// Set up the players
	Player *h = getHomeTeamPlayers();
	h->setPosition(rink.CENTERX, rink.CENTERY - 30);

	Player *a = getAwayTeamPlayers();
	a->setPosition(rink.CENTERX, rink.CENTERY + 30);
}

/**
 * Method for dropping the puck.
 * It creates a random number to represent the result of
 * the faceoff.
 */
void Game::dropPuck()
{
	// Generate a random number
	double result = rand()/double(RAND_MAX);

	Player *a = getAwayTeamPlayers(), *h = getHomeTeamPlayers();

	double af = a->getSkills()->getFaceOff(), hf = h->getSkills()->getFaceOff();
	double skillDiff = (af - hf)/100;

	result += skillDiff/2;

	if (result > 0.5)
	{
		puckHolder = a;
		h->setLock(20);
	}
	else
	{
		puckHolder = h;
		a->setLock(20);
	}
}

int Game::goal()
{
	// Call the goal method in rink class
	// to determine if there is a goal.
	int goal = rink.goal(puck.getPosition());

	return goal;
}

void Game::checkPuckCollision()
{
	// If a player has the puck
	if (puckHolder)
	{
		puck.setPosition(puckHolder->getPosition());
		puck.setVelocity(puckHolder->getVelocity());
	}
	else
		puck.setVelocity(rink.handleCollisions(puck.getPosition(), 
	                                           puck.getVelocity(),
	                                           false));

	// Move the puck to its' new position	
	puck.move();

}

void Game::checkPlayerCollisions()
{
	// Check all the players for rink collisions
	Player *h = getHomeTeamPlayers();
	h->setVelocity(
	rink.handleCollisions(h->getPosition(), h->getVelocity()));

	Player *a = getAwayTeamPlayers();
	a->setVelocity(
	rink.handleCollisions(a->getPosition(), a->getVelocity()));

	// Move the players to their new positions
	h->move();
	a->move();
	
}

unsigned int Game::gameTime()
{
	return SDL_GetTicks();
}
