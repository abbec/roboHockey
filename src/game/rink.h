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

#ifndef _RINK_H
#define _RINK_H

#include "math/vector2D.h"
#include "game/goal.h"

class Rink
{
	public:
	
		Rink();

		// Public interface for handling collisions
		Math::Vector2D<double> handleCollisions(Math::Vector2D<double>& position,
		                                        Math::Vector2D<double>& velocity,
		                                        bool player=true);
	
		const int CENTERX, CENTERY;

		Goal* getHomeGoal() {return &homeGoal;}
		Goal* getAwayGoal() {return &awayGoal;}

		int goal(Math::Vector2D<double>&);
	
	private:
	
		// The four straight segments of the boards
		const unsigned int vertUp, vertDown, vertLeft, vertRight,
		horizUp, horizDown, horizLeft, horizRight;

		static const double DAMPING;

		enum boards {LEFT, 
					UP_LEFT, 
					UP, 
					UP_RIGHT, 
					RIGHT, 
					DOWN_LEFT, 
					DOWN, 
					DOWN_RIGHT};
		
		// The corners
		class Point
		{
			public:
				Point() : x(0), y(0) {}
				Point(unsigned int _x, unsigned int _y) : x(_x), y(_y) {}
				unsigned int x, y;
		};
		Point upperLeft[88], lowerLeft[88], upperRight[88], lowerRight[88];
		unsigned int cornerSize;

		Goal awayGoal, homeGoal;

		// PRIVATE FUNCTIONS

		bool inCircle(Math::Vector2D<double>&, double, 
		              Math::Vector2D<double>&);

		bool lineIntersection(double, double, double, double, 
		                      double, double, double, double, Point&);

		Math::Vector2D<double> calculateRefraction(Math::Vector2D<double>&,
		                                           Math::Vector2D<double>&,
												   double,
		                                           bool player);

		// Private subroutines to check for collisions
		Math::Vector2D<double> verticalBoardsCollision(Math::Vector2D<double>&,
		                                               Math::Vector2D<double>&,
													   unsigned int,
		                                               bool player);

		Math::Vector2D<double> horizontalBoardsCollision(Math::Vector2D<double>&,
		                                                 Math::Vector2D<double>&,
													     unsigned int,
		                                                 bool player);

		Math::Vector2D<double> cornerCollision(Math::Vector2D<double>&,
		                                       Math::Vector2D<double>&,
											   unsigned int,
		                                       bool player);

		
		Math::Vector2D<double> goalCollision(Math::Vector2D<double>&,
		                                     Math::Vector2D<double>&,
		                                     bool player);
		
};

#endif