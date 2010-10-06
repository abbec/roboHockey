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

#include "ui/window.h"
#include <iostream>
#include <sstream>

Window* Window::inst = NULL;

Window::Window()
{
	// Set window title
	SDL_WM_SetCaption("RoboHockey",NULL);
	
	// Create surfaces
	mainSurface = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_SRCALPHA);
	
	rinkSurface = IMG_Load("data/surfaces/rink.png");
	SDL_SetColorKey(rinkSurface, SDL_RLEACCEL, rinkSurface->format->colorkey);
	
	statSurface = IMG_Load("data/surfaces/stat.png");

	puck = IMG_Load("data/objects/puck.png");
	SDL_SetColorKey(puck, SDL_RLEACCEL, puck->format->colorkey);

	greenPlayer = IMG_Load("data/objects/green_player.png");
	SDL_SetColorKey(greenPlayer, SDL_RLEACCEL, greenPlayer->format->colorkey);

	bluePlayer = IMG_Load("data/objects/blue_player.png");
	SDL_SetColorKey(bluePlayer, SDL_RLEACCEL, bluePlayer->format->colorkey);

	// Blit the surfaces
	SDL_BlitSurface(rinkSurface, NULL, mainSurface, NULL);

	// Statistics surface
	statRect.x = rinkSurface->w; statRect.w = mainSurface->w - rinkSurface->w;
	statRect.y = 0; statRect.h = mainSurface->h;
	
	SDL_BlitSurface(statSurface, NULL, mainSurface, &statRect);

	// Puck
	updatePuck();

	// Create Font(s)
	arcade = TTF_OpenFont("data/fonts/arcade.ttf", 72);
	arcadeSmall = TTF_OpenFont("data/fonts/arcade.ttf", 48);
	nameFont = TTF_OpenFont("data/fonts/sb.ttf", 12);

	// Players
	withPuck.x = 44; withPuck.y = 0;
	withPuck.w = 44; withPuck.h = 44;
	withoutPuck.x = 0; withoutPuck.y = 0;
	withoutPuck.w = 44; withoutPuck.h = 44;
	updatePlayers();

	// Set up text rectangles
	clockRect.x = 695; clockRect.y = 65;
	clockRect.w = 154; clockRect.h = 34;

	homeScore.x = 605; homeScore.y = 175;
	homeScore.w = 33; homeScore.h = 34;

	period.x = 753; period.y = 195;
	period.w = 33; period.h = 34;

	awayScore.x = 902; awayScore.y = 175;
	awayScore.w = 33; awayScore.h = 34;

	homeShots.x = 660; homeShots.y = 340;
	homeShots.w = 22; homeShots.h = 23;

	awayShots.x = 852; awayShots.y = 340;
	awayShots.w = 22; awayShots.h = 23;
	 
	// Default texts
	drawText(&clockRect, arcade, (Game::instance()->getClock()).c_str());
	drawText(&homeScore, arcade, "0");
	drawText(&period, arcade, "1");
	drawText(&awayScore, arcade, "0");
	
	drawText(&homeShots, arcadeSmall, "0");
	drawText(&awayShots, arcadeSmall, "0");

	// Swap buffers to show the whole thing
	SDL_Flip(mainSurface);
	
}

Window::~Window()
{
	// Free the inner surfaces
	SDL_FreeSurface(greenPlayer);
	SDL_FreeSurface(bluePlayer);
	SDL_FreeSurface(puck);
	SDL_FreeSurface(rinkSurface);
	SDL_FreeSurface(statSurface);
}

Window* Window::instance()
{
	if (inst == NULL)
		inst = new Window();

	return inst;
}

/** Public driver routine to call
  * other private update methods */
void Window::update()
{
	updateRink();
	updatePlayers();
	updatePuck();
	updateStats();

	// Swap buffers to show the whole thing
	SDL_Flip(mainSurface);
}

// -- PRIVATE METHODS -- //

void Window::updateRink()
{
	// Refresh the pucks old position
	SDL_BlitSurface(rinkSurface, &puckRect, mainSurface, &puckRect);
	
	// Update players' previous positions
	SDL_BlitSurface(rinkSurface, &blueRect, mainSurface, &blueRect);
	SDL_BlitSurface(rinkSurface, &greenRect, mainSurface, &greenRect);

	SDL_BlitSurface(rinkSurface, &greenNameRect, mainSurface, &greenNameRect);
	SDL_BlitSurface(rinkSurface, &blueNameRect, mainSurface, &blueNameRect);
	
}

void Window::updateStats()
{
	// Redraw the stats surface
	SDL_BlitSurface(statSurface, NULL, mainSurface, &statRect);

	// Aquire a pointer to the running game instance
	Game* game = Game::instance();
	
	// Get the clock
	std::string clock = game->getClock();
	
	// Get scoresSDL_BlitSurface(bluePlayer, &withoutPuck, mainSurface, &blueRect);
	unsigned int homeGoals = game->getHomeScore();
	unsigned int awayGoals = game->getAwayScore();
	
	/*// Get shots on goal
	unsigned int hShots = game->getHomeShots();
	unsigned int aShots = game->getAwayShots();*/

	// Get the period
	unsigned short int _period = game->getPeriod();

	// -- CLOCK --
	drawText(&clockRect, arcade, clock.c_str());

	// -- HOME SCORE --
	std::stringstream sstr;
	sstr << homeGoals;
	std::string str1 = sstr.str();
	
	drawText(&homeScore, arcade, str1.c_str());

	// -- PERIOD --
	
	// Empty the buffer
	sstr.str("");
	sstr << _period;
	str1 = sstr.str();

	drawText(&period, arcade, str1.c_str());

	// -- AWAY SCORE --
	
	// Empty the buffer
	sstr.str("");
	sstr << awayGoals;
	str1 = sstr.str();

	drawText(&awayScore, arcade, str1.c_str());

	// -- AWAY SHOTS --
	
	/*// Empty the buffer
	sstr.str("");
	sstr << aShots;
	str1 = sstr.str();

	drawText(&awayShots, arcadeSmall, str1.c_str());

	// -- HOME SHOTS --
	
	// Empty the buffer
	sstr.str("");
	sstr << hShots;
	str1 = sstr.str();

	drawText(&homeShots, arcadeSmall, str1.c_str());*/
}

void Window::updatePuck()
{
	// Get the puck position
	Math::Vector2D<double> pos = Game::instance()->getPuckPosition();
	
	// Set up the new position for the puck
	puckRect.x = floor(pos.x) - puck->w/2; puckRect.y = floor(pos.y) - puck->h/2;
	
	// Blit the puck
	SDL_BlitSurface(puck, NULL, mainSurface, &puckRect);

}

void Window::updatePlayers()
{
	Game* g = Game::instance();
	Player *p = Game::getPuckHolder();
	Player *h = g->getHomeTeamPlayers(), *a = g->getAwayTeamPlayers();

	// Get positions of the green players
	Math::Vector2D<double> greenPos = h->getPosition();

	// Get positions of the blue players
	Math::Vector2D<double> bluePos = a->getPosition();
	
	// Set up new positions
	blueRect.x = floor(bluePos.x) - withPuck.w/2; blueRect.y = floor(bluePos.y) - withPuck.h/2;
	blueNameRect.x = blueRect.x; blueNameRect.y = withPuck.h + blueRect.y;
	greenRect.x = floor(greenPos.x) - withPuck.w/2; greenRect.y = floor(greenPos.y) - withPuck.h/2;
	greenNameRect.x = greenRect.x; greenNameRect.y = withPuck.h + greenRect.y;

	// Blit surfaces
	if (p == h)
	{
		SDL_BlitSurface(greenPlayer, &withPuck, mainSurface, &greenRect);
		SDL_BlitSurface(bluePlayer, &withoutPuck, mainSurface, &blueRect);
	}
	else if (p == a)
	{
		SDL_BlitSurface(greenPlayer, &withoutPuck, mainSurface, &greenRect);
		SDL_BlitSurface(bluePlayer, &withPuck, mainSurface, &blueRect);
	}
	else
	{
		SDL_BlitSurface(greenPlayer, &withoutPuck, mainSurface, &greenRect);
		SDL_BlitSurface(bluePlayer, &withoutPuck, mainSurface, &blueRect);
	}

	// Render the player names
	drawText(&blueNameRect, nameFont, a->getName().c_str());
	drawText(&greenNameRect, nameFont, h->getName().c_str());
}


int Window::drawText(SDL_Rect* dest, TTF_Font* font, const char* text)
{
	// Text color
    SDL_Color color = {0, 0, 0};
    SDL_Surface *text_surface;

    text_surface = TTF_RenderUTF8_Blended(font, text, color);

	if (text_surface != NULL)
    {
        SDL_BlitSurface(text_surface, NULL, mainSurface, dest);
        SDL_FreeSurface(text_surface);
        return 1;
    }
    else /* Report error */
        return 0;
}