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

#include "game/rink.h"
#include <iostream>
#include <fstream>

const double Rink::DAMPING = 0.8;


Rink::Rink() : 
awayGoal(236, 697, 719, 287),
homeGoal(236, 70, 48, 287),
CENTERX(261), CENTERY(384),
vertUp(95), vertDown(672),
vertLeft(61), vertRight(462),
horizLeft(128),	horizRight(395),
horizDown(739), horizUp(28)	
{
	// Corners
	upperLeft[0] = Point(62, 94);
	upperLeft[1] = Point(62, 93);
	upperLeft[2] = Point(62, 92);
	upperLeft[3] = Point(62, 91);
	upperLeft[4] = Point(62, 90);
	upperLeft[5] = Point(62, 89);
	upperLeft[6] = Point(62, 88);
	upperLeft[7] = Point(62, 87);
	upperLeft[8] = Point(63, 86);
	upperLeft[9] = Point(63, 85);
	upperLeft[10] = Point(63, 84);
	upperLeft[11] = Point(63, 83);
	upperLeft[12] = Point(63, 82);
	upperLeft[13] = Point(64, 81);
	upperLeft[14] = Point(64, 80);
	upperLeft[15] = Point(64, 79);
	upperLeft[16] = Point(64, 78);
	upperLeft[17] = Point(65, 77);
	upperLeft[18] = Point(65, 76);
	upperLeft[19] = Point(66, 75);
	upperLeft[20] = Point(66, 74);
	upperLeft[21] = Point(67, 73);
	upperLeft[22] = Point(67, 72);
	upperLeft[23] = Point(68, 71);
	upperLeft[24] = Point(69, 70);
	upperLeft[25] = Point(69, 69);
	upperLeft[26] = Point(70, 68);
	upperLeft[27] = Point(71, 67);
	upperLeft[28] = Point(71, 66);
	upperLeft[29] = Point(72, 65);
	upperLeft[30] = Point(73, 64);
	upperLeft[31] = Point(73, 63);
	upperLeft[32] = Point(74, 62);
	upperLeft[33] = Point(75, 61);
	upperLeft[34] = Point(76, 60);
	upperLeft[35] = Point(76, 59);
	upperLeft[36] = Point(77, 58);
	upperLeft[37] = Point(78, 57);
	upperLeft[38] = Point(79, 56);
	upperLeft[39] = Point(80, 55);
	upperLeft[40] = Point(81, 54);
	upperLeft[41] = Point(81, 53);
	upperLeft[42] = Point(82, 52);
	upperLeft[43] = Point(83, 51);
	upperLeft[44] = Point(84, 50);
	upperLeft[45] = Point(85, 49);
	upperLeft[46] = Point(86, 48);
	upperLeft[47] = Point(87, 48);
	upperLeft[48] = Point(88, 47);
	upperLeft[49] = Point(89, 46);
	upperLeft[50] = Point(90, 45);
	upperLeft[51] = Point(91, 44);
	upperLeft[52] = Point(92, 43);
	upperLeft[53] = Point(93, 43);
	upperLeft[54] = Point(94, 42);
	upperLeft[55] = Point(95, 41);
	upperLeft[56] = Point(96, 40);
	upperLeft[57] = Point(97, 40);
	upperLeft[58] = Point(98, 39);
	upperLeft[59] = Point(99, 38);
	upperLeft[60] = Point(100, 38);
	upperLeft[61] = Point(101, 37);
	upperLeft[62] = Point(102, 36);
	upperLeft[63] = Point(103, 36);
	upperLeft[64] = Point(104, 35);
	upperLeft[65] = Point(105, 34);
	upperLeft[66] = Point(106, 34);
	upperLeft[67] = Point(107, 33);
	upperLeft[68] = Point(108, 33);
	upperLeft[69] = Point(109, 32);
	upperLeft[70] = Point(110, 32);
	upperLeft[71] = Point(111, 31);
	upperLeft[72] = Point(112, 31);
	upperLeft[73] = Point(113, 31);
	upperLeft[74] = Point(114, 31);
	upperLeft[75] = Point(115, 30);
	upperLeft[76] = Point(116, 30);
	upperLeft[77] = Point(117, 30);
	upperLeft[78] = Point(118, 30);
	upperLeft[79] = Point(119, 30);
	upperLeft[80] = Point(120, 29);
	upperLeft[81] = Point(121, 29);
	upperLeft[82] = Point(122, 29);
	upperLeft[83] = Point(123, 29);
	upperLeft[84] = Point(124, 29);
	upperLeft[85] = Point(125, 29);
	upperLeft[86] = Point(126, 29);
	upperLeft[87] = Point(127, 29);

	cornerSize = 88;

	// Set up the other corners
	for (unsigned int i = 0; i < cornerSize; i++)
	{
		// Move x values and invert y
		upperRight[i] = 
			Point((CENTERX-upperLeft[i].x)+CENTERX+1, upperLeft[i].y);

		lowerLeft[i] =
			Point(upperLeft[i].x, (CENTERY-upperLeft[i].y)+CENTERY+1);

		lowerRight[i] =
			Point((CENTERX-upperLeft[i].x)+CENTERX+1, (CENTERY-upperLeft[i].y)+CENTERY+1);
	}
 
}

/** 
 * Public interface for handling collisions.
 */
Math::Vector2D<double> Rink::handleCollisions(Math::Vector2D<double>& position, 
                                              Math::Vector2D<double>& velocity,
                                              bool player)
{

	Math::Vector2D<double> returnVelocity;
	
	// Get the position and call the right sub-function
	unsigned int x = floor(position.x); unsigned int y = floor(position.y);
	if (x < CENTERX && y >= vertUp && y <= vertDown) /* LEFT BOARD */
		returnVelocity = verticalBoardsCollision(position, velocity, LEFT, player);
	else if (x >= CENTERX && y >= vertUp && y <= vertDown) /* RIGHT BOARD */
		returnVelocity = verticalBoardsCollision(position, velocity, RIGHT, player);
	else if (y < vertUp && x >= horizLeft && x<= horizRight) /* UPPER BOARD */
		returnVelocity = horizontalBoardsCollision(position, velocity, UP, player);
	else if (y > vertDown && x >= horizLeft && x<= horizRight) /* LOWER BOARD */
		returnVelocity = horizontalBoardsCollision(position, velocity, DOWN, player);
	else /* CORNERS */
	{
		if (x < CENTERX && y < CENTERY)
			returnVelocity = cornerCollision(position, velocity, UP_LEFT, player);
		else if (x < CENTERX && y > CENTERY)
			returnVelocity = cornerCollision(position, velocity, DOWN_LEFT, player);
		else if (x > CENTERX && y > CENTERX)
			returnVelocity = cornerCollision(position, velocity, DOWN_RIGHT, player);
		else
			returnVelocity = cornerCollision(position, velocity, UP_RIGHT, player);
	}
	
	// Check also for collision with the goal
	return goalCollision(position, returnVelocity, player);
}

/** 
 * Check collision with the goal posts
 */
Math::Vector2D<double> Rink::goalCollision(Math::Vector2D<double>& position, 
                                           Math::Vector2D<double>& velocity,
                                           bool player)
{
	Math::Vector2D<double> newPos = position + velocity;
	const double damping = 0.1;

	unsigned int frontY = awayGoal.getFrontY(), backY = awayGoal.getBackY();
	unsigned int leftX = awayGoal.getLeftX(), rightX = awayGoal.getRightX();
	unsigned int homeBackY = homeGoal.getBackY(), homeFrontY = homeGoal.getFrontY();

	Math::Vector2D<double> goalPoint, normal, othergoal;
	Point intersect;


	// Check collision with left post
	if (lineIntersection(position.x, position.y, 
	                     newPos.x, newPos.y, 
	                     leftX, backY, 
	                     leftX, frontY,
	                     intersect) ||
	    lineIntersection(position.x, position.y, 
	                     newPos.x, newPos.y, 
	                     leftX, homeBackY, 
	                     leftX, homeFrontY,
	                     intersect))
	{
		
		if (position.x <= leftX)
		{
			normal.x = -1; normal.y = 0; 
			return calculateRefraction(velocity, normal, damping, player);
		}
		else
		{
			normal.x = 1; normal.y = 0; 
			return calculateRefraction(velocity, normal, damping, player);
		}
	}
	else if (lineIntersection(position.x, position.y, 
	                          newPos.x, newPos.y, 
	                          rightX, backY, 
	                          rightX, frontY,
	                          intersect) ||
	         lineIntersection(position.x, position.y, 
	                          newPos.x, newPos.y, 
	                          rightX, homeBackY, 
	                          rightX, homeFrontY,
	                          intersect))
	{
		
		if (position.x >= rightX)
		{
			normal.x = 1; normal.y = 0; 
			return calculateRefraction(velocity, normal, damping, player);
		}
		else
		{
			normal.x = -1; normal.y = 0; 
			return calculateRefraction(velocity, normal, damping, player);
		}
	}
	else if (lineIntersection(position.x, position.y, 
	                          newPos.x, newPos.y, 
	                          rightX, backY, 
	                          leftX, backY,
	                          intersect)) 
	{
		
		if (position.y >= backY)
		{
			normal.y = 1; normal.x = 0; 
			return calculateRefraction(velocity, normal, damping, player);
		}
		else
		{
			normal.y = -1; normal.x = 0; 
			return calculateRefraction(velocity, normal, damping, player);
		}
	}
	else if (lineIntersection(position.x, position.y, 
	                          newPos.x, newPos.y, 
	                          rightX, homeBackY, 
	                          leftX, homeBackY,
	                          intersect)) 
	{
		
		if (position.y >= homeBackY)
		{
			normal.y = 1; normal.x = 0; 
			return calculateRefraction(velocity, normal, damping, player);
		}
		else
		{
			normal.y = -1; normal.x = 0; 
			return calculateRefraction(velocity, normal, damping, player);
		}
	}
	


	if (player)
	{

		if (lineIntersection(position.x, position.y, 
	                          newPos.x, newPos.y, 
	                          rightX, frontY, 
	                          leftX, frontY,
	                          intersect)) 
		{
		
			if (position.y >= backY)
			{
				normal.y = 1; normal.x = 0; 
				return calculateRefraction(velocity, normal, damping, player);
			}
			else
			{
				normal.y = -1; normal.x = 0; 
				return calculateRefraction(velocity, normal, damping, player);
			}
		}
		else if (lineIntersection(position.x, position.y, 
			                      newPos.x, newPos.y, 
			                      rightX, homeFrontY, 
			                      leftX, homeFrontY,
			                      intersect)) 
		{
		
			if (position.y >= homeBackY)
			{
				normal.y = 1; normal.x = 0; 
				return calculateRefraction(velocity, normal, damping, player);
			}
			else
			{
				normal.y = -1; normal.x = 0; 
				return calculateRefraction(velocity, normal, damping, player);
			}
		}

	}

	return velocity;

}

int Rink::goal(Math::Vector2D<double> &puck)
{
	if (awayGoal.isGoal(puck))
		return 1;
	else if (homeGoal.isGoal(puck))
		return 0;
	else
		return -1;
}


Math::Vector2D<double> Rink::verticalBoardsCollision(Math::Vector2D<double>& position,
		                                             Math::Vector2D<double>& velocity,
													 unsigned int side,
		                                             bool player)
{
	Math::Vector2D<double> boardPoint, normal;
	const double radius = (player ? 12 : 9);
	
	// Check which side we should work on
	unsigned int pointX, normalX;

	if (side == LEFT)
	{
		pointX = vertLeft;
		normalX = vertLeft+1;
	}
	else
	{
		pointX = vertRight;
		normalX = vertRight-1;
	}
	
	for (unsigned int i=vertUp; i <= vertDown; i++)
	{
		boardPoint.x = pointX; boardPoint.y = i;
		if (inCircle(position, radius, boardPoint))
		{
			normal = Math::Vector2D<double>(normalX, i) - boardPoint;
			return calculateRefraction(velocity, normal, DAMPING, player);
		}
	}

	return velocity;
}

Math::Vector2D<double> Rink::horizontalBoardsCollision(Math::Vector2D<double>& position,
		                                             Math::Vector2D<double>& velocity,
													 unsigned int side,
		                                             bool player)
{
	Math::Vector2D<double> boardPoint, normal;
	const double radius = (player ? 12 : 9);
	
	// Check which side we should work on
	unsigned int pointY, normalY;

	if (side == UP)
	{
		pointY = horizUp;
		normalY = horizUp+1;
	}
	else
	{
		pointY = horizDown;
		normalY = horizDown-1;
	}
	
	for (unsigned int i=horizLeft; i <= horizRight; i++)
	{
		boardPoint.x = i; boardPoint.y = pointY;
		if (inCircle(position, radius, boardPoint))
		{
			normal = Math::Vector2D<double>(i, normalY) - boardPoint;
			return calculateRefraction(velocity, normal, DAMPING, player);
		}
	}

	return velocity;
}

Math::Vector2D<double> Rink::cornerCollision(Math::Vector2D<double>& position,
		                                       Math::Vector2D<double>& velocity,
											   unsigned int side,
		                                       bool player)
{
	Point *corner;
	Math::Vector2D<double> boardPoint, normal;
	unsigned int centroidX, centroidY;
	const double radius = (player ? 12 : 9);

	// Check which corner we are dealing with
	switch (side)
	{
		case UP_LEFT:
		{
			corner = upperLeft;
			centroidX = horizLeft-1;
			centroidY = vertUp-1;
			break;
		}
		case UP_RIGHT:
		{
			corner = upperRight;
			centroidX = horizRight+1;
			centroidY = vertUp-1;
			break;
		}
		case DOWN_LEFT:
		{
			corner = lowerLeft;
			centroidX = horizLeft-1;
			centroidY = vertDown+1;
			break;
		}
		case DOWN_RIGHT:
		{
			corner = lowerRight;
			centroidX = horizRight+1;
			centroidY = vertDown+1;
			break;
		}
		default:
			break;
	}

	for (unsigned int i = 0; i < cornerSize; i++)
	{
		boardPoint.x = (*(corner+i)).x; boardPoint.y = (*(corner+i)).y;
		if (inCircle(position, radius, boardPoint))
		{
			normal = Math::Vector2D<double>(centroidX, centroidY) - boardPoint;
			// Norm the vector
			normal = normal / (normal.norm());
			return calculateRefraction(velocity, normal , DAMPING, player);
		}
	}

	return velocity;
}

bool Rink::inCircle(Math::Vector2D<double>& position, double radius,
                    Math::Vector2D<double>& boardPoint)
{
	Math::Vector2D<double> distance = position - boardPoint;
	
	return distance.squareNorm() <= radius*radius; 
}

bool Rink::lineIntersection(
double a1x, double a1y,
double a2x, double a2y,
double b1x, double b1y,
double b2x, double b2y, Point& result)
{
	double  distAB, theCos, theSin, newX, ABpos ;

	//  Fail if either line is undefined.
	if (a1x == a2x && a1y == a2y || b1x == b2x && b1y == b2y) 
		return false;

	//  Fail if the segments share an end-point.
  	if (a1x==b1x && a1y==b1y || a2x==b1x && a2y==b1y
  	||  a1x==b2x && a1y==b2y || a2x==b2x && a2y==b2y)
    	return false;

	//  (1) Translate the system so that point A is on the origin.
	a2x -=a1x; a2y -= a1y;
	b1x -=a1x; b1y -= a1y;
	b2x -=a1x; b2y -= a1y;

	//  Discover the length of segment A-B.
	distAB = sqrt(a2x*a2x + a2y*a2y);

	//  (2) Rotate the system so that point B is on the positive X axis.
	theCos = a2x / distAB;
	theSin = a2y / distAB;
	newX = b1x * theCos + b1y * theSin;
	b1y = b1y * theCos - b1x * theSin; b1x = newX;
	newX = b2x * theCos+ b2y * theSin;
	b2y = b2y * theCos - b2x * theSin; b2x = newX;

	//  Fail if the lines are parallel.
	if (b1y == b2y) 
		return false;

	//  Fail if segment C-D doesn't cross line A-B.
	if (b1y<0. && b2y<0. || b1y>=0. && b2y>=0.) 
		return false;

	//  (3) Discover the position of the intersection point along line A-B.
	ABpos = b2x + (b1x-b2x) * b2y / (b2y-b1y);

	if (ABpos < 0.0 || ABpos > distAB) 
		return false;

	//  (4) Apply the discovered position to line A-B in the original coordinate system.
	result.x = floor(a1x+ABpos*theCos);
	result.y = floor(a1y+ABpos*theSin);

	//  Success.
	return true; 
}

Math::Vector2D<double> Rink::calculateRefraction(Math::Vector2D<double>& velocity, Math::Vector2D<double>& normal, double damping, bool player)
{
	if (velocity*normal < 0)
	{
		if (!player)
			return (velocity + (2*(-velocity*normal))*normal)*damping;
		else
			return Math::Vector2D<double>(0, 0);
	}
	else
		return velocity;
}