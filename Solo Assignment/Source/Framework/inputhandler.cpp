// COMP710 GP 2D Framework 2020

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "logmanager.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
	: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_JoystickOpen(0);

	if (!m_pGameController)
	{
		LogManager::GetInstance().Log("No controller detected!");
	}

	return (true);
}

void
InputHandler::ProcessInput(Game& game)
{
	// SS04.3: Receive Input Events below...


	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		 // have issues with this event triggering calls of a key event twice, when only pressed once.
		if (event.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
		
		}
		else if (event.jbutton.button == 10)
		{
			//game.GemShot();
		}
		if (event.key.keysym.sym == SDLK_a)
		{
			game.Aim(1);
		}
		if (event.key.keysym.sym == SDLK_d)
		{
			game.Aim(2);
		}
		if (event.key.keysym.sym == SDLK_SPACE) // fire
		{
			game.GemShot();
		}
		if (event.key.keysym.sym == SDLK_e) //  select for menus
		{
			game.MenuInput(3);
		}
		if (event.key.keysym.sym == SDLK_q) // switch gems
		{
			game.SwitchGems();
		}
		if (event.key.keysym.sym == SDLK_w) // menu navigation
		{
			game.MenuInput(1);
		}
		if (event.key.keysym.sym == SDLK_s) // menu navigation
		{
			game.MenuInput(2);
		}
		if (event.key.keysym.sym == SDLK_ESCAPE) // pause menu during game
		{
			game.MenuInput(4);
		}
	}
}
