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
 
#include "game/player.h"
#include "game/game.h"
#include <cstdlib>
#include <ctime>
 
// Constructor
Player::Player(std::string n, bool g, Skills s) : 
	gender(g), 
	name(n),
	skills(s),
	lock(0)
{}
 
// Move the player
void Player::move()
{	
	position += velocity;
}

void Player::makeMove()
{

	if (lock > 0)
		--lock;
	else
	{
		// Make sure players do not get stuck
		if (velocity == Math::Vector2D<double>(0,0))
		{
			srand(time(NULL));
				
			setVelocity(
						Math::Vector2D<double>(
											   (rand()/double(RAND_MAX))*2-1, 
											   (rand()/double(RAND_MAX))*2-1 )*(0.05*skills.getSkating()));
		}
		else
		{
			if (Game::instance()->getPuckHolder() == this)
				makeOffensiveMove();
			else
				makeDefensiveMove();
		}
	}
}

// Tackle the puck holder
void Player::tackle()
{
	Game::setPuckHolder(this);
}

void Player::shoot()
{
	Game *g = Game::instance();
	
	Math::Vector2D<double> goalVector = 
		Math::Vector2D<double>(g->getRinkCenterX(), team->getGoal()->getFrontY()) -
		position;

	srand(time(NULL));
	double randX = (((rand()/double(RAND_MAX))*2)-1)/(0.05*skills.getShooting());
	double randY = (((rand()/double(RAND_MAX))*2)-1)/(0.05*skills.getShooting());
	
	Math::Vector2D<double> newVelocity = 
		Math::Vector2D<double>(randX, randY) 
		+ (goalVector/goalVector.norm());
	newVelocity = (newVelocity/newVelocity.norm())*(0.15*skills.getShooting());



	g->setPuckVelocity(newVelocity);
	g->setPuckHolder(NULL);
}

void Player::makeOffensiveMove()
{
	// Distance and angle to goal
	Game *g = Game::instance();
	Math::Vector2D<double> centerVector
		(g->getRinkCenterX(), team->getGoal()->getFrontY());

	Math::Vector2D<double> rinkCenter(g->getRinkCenterX(), g->getRinkCenterY());
	
	Math::Vector2D<double> goalVector = centerVector - position;

	double goalDistance = goalVector.squareNorm();

	double goalAngle = 
		goalVector*(centerVector-rinkCenter);

	// Get the distance to the nearest opponent
	Player *otherPlayer = Game::instance()->getNearestOpponent(team, this);

	Math::Vector2D<double> playerDistanceVector = (position - otherPlayer->getPosition());
	double playerDistance = playerDistanceVector.squareNorm();
	
	// Check distance and angle
	if ((goalDistance <= 157*157 
	     || goalDistance <= 180*180 && playerDistance <= 20*20 ) 
	    && goalAngle > 0)
	{
		shoot();
	}
	else
	{

		if (playerDistance <= 40*40)
		{
			srand(time(NULL));

			
			setVelocity((playerDistanceVector/playerDistanceVector.norm())*(0.025*skills.getSkating()) +
						Math::Vector2D<double>( ((rand()/double(RAND_MAX))*2)-1, ((rand()/double(RAND_MAX))*2)-1 ));			            
			
		}
		else
		{		
			if (goalAngle < 0)
				goalVector = Math::Vector2D<double>(position.x,g->getRinkCenterY()) - position;
			
			setVelocity((goalVector/goalVector.norm())*(0.025*skills.getSkating()));
		}
		
	}

}

void Player::makeDefensiveMove()
{
	Player *p = Game::getPuckHolder();

	Math::Vector2D<double> puckVector = 
		(Game::instance()->getPuckPosition() - position);

	double puckDistance = puckVector.squareNorm();
	
	Math::Vector2D<double> newVelocity = 
		(puckVector/puckVector.norm())*(0.05*skills.getSkating());

	if (p)
	{
		double puckHolderDistance =
			(p->getPosition() - position).squareNorm();
		

		if (puckHolderDistance <= 2)
		{
			tackle();
			Math::Vector2D<double> otherVelocity = p->getVelocity();
			p->setLock(40);
		}
		else
			setVelocity(newVelocity);
	}
	else
	{
		if (puckDistance <= 10 && Game::instance()->getRink()->goal(position) == -1)
		{
			Game::instance()->setPuckHolder(this);
			makeOffensiveMove();
		}
		else
		{
			setVelocity(newVelocity);
		}
	}
}
