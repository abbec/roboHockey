/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#ifndef ROBOHOCKEY_H
#define ROBOHOCKEY_H

#include "ui/window.h"

class Game;

class RoboHockey
{

	public:
		
		RoboHockey();

		~RoboHockey();

		void initSDL();

		int Main(int argc, char *argv[]);
		void updateWindow() { window->update(); };

		static RoboHockey * instance();

	private:

		bool running;
		unsigned short int period;

		Game *game;

		Window *window;

		static RoboHockey* inst;

		void handleGlobalEvents(SDL_Event*);
		void keyboardEvents(SDL_keysym&);
};
#endif