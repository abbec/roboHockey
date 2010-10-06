// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA

#include "SDL_ttf.h"
#include <iostream>
#include "app/roboHockey.h"
#include "game/game.h"

RoboHockey* RoboHockey::inst = NULL;

RoboHockey::RoboHockey() : running(false), period(1)
{
	// Get the game instance
	game = Game::instance();

	// Initialize SDL
	initSDL();
	
	// Create main window
	window = Window::instance();
}

RoboHockey::~RoboHockey()
{
	// Free memory associated with game
	delete game;
}

RoboHockey* RoboHockey::instance()
{
	if (inst == NULL)
		inst = new RoboHockey();

	return inst;

}

int RoboHockey::Main(int argc, char *argv[])
{
	// Parse the command line
	//parseCommandLine(argc, argv);

	// See to that the program is in running state
	running = true;

	// Create an event structure
	SDL_Event event;

	// Program loop
	while (running)
	{
		SDL_WaitEvent(&event);
		handleGlobalEvents(&event);
	}

	// Shut down SDL
	TTF_Quit();
	SDL_Quit();
	
	return 0;

}

void RoboHockey::initSDL()
{
	int result = SDL_Init(SDL_INIT_EVERYTHING);

	// Check if we did OK
	if (result == -1)
		std::cout << "ERROR: Could not initialize SDL: " << SDL_GetError() << std::endl;

	// Initialize TrueType font API
	TTF_Init();
}

/**
 * Handle global events in the main loop
 */
void RoboHockey::handleGlobalEvents(SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_QUIT:
		{	
			std::cout << "Closing RoboHockey. Thank you for watching ;)" << std::endl;
			running = false;
			break;
		}

		case SDL_KEYUP:
		{	
			keyboardEvents(event->key.keysym);
			break;
		}

		default:
			break;
	}
}

void RoboHockey::keyboardEvents(SDL_keysym &s)
{
	SDLKey key = s.sym;

	switch(key)
	{
		case SDLK_s:
		{
			if (period < 3)
				period = game->play();
			break;
		}

		case SDLK_n:
		{
			game->reset();
			period = game->play();
			break;
		}

		default:
			std::cout << "You pressed an unsupported key." << std::endl;
			break;
	}
}
