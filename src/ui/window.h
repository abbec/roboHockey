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

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "game/game.h"

class Window
{
	public:

		~Window();

		void update();

		static Window* instance();

	private:

		Window();
		
		SDL_Surface* mainSurface;

		SDL_Surface* rinkSurface;
			SDL_Rect puckRect;
			SDL_Surface* puck;

			SDL_Rect greenRect;
			SDL_Rect greenNameRect;
			SDL_Surface* greenPlayer;

			SDL_Rect blueRect;
			SDL_Rect blueNameRect;
			SDL_Surface* bluePlayer;

			SDL_Rect withPuck;
			SDL_Rect withoutPuck;

		
		SDL_Surface* statSurface;
		SDL_Rect statRect;

		SDL_Rect clockRect, homeScore, awayScore, period;
		SDL_Rect homeShots, awayShots;
		

		TTF_Font *arcade, *arcadeSmall, *nameFont;

		int drawText(SDL_Rect*, TTF_Font*, const char*);
		
		// Update methods to update the visual parts
		void updateRink();
		void updateStats();
		void updatePuck();
		void updatePlayers();

		static Window* inst;

};

#endif // _WINDOW_H_
