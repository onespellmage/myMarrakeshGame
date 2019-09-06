#include "stdafx.h"
#include "SDL_Setup.h"


CSDL_Setup::CSDL_Setup(bool* quit)
{
	TTF_Init();
	window = NULL;
	window = SDL_CreateWindow("Game", 50, 50, 800, 600, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << " Window is not created " << std::endl;
		*quit = true;
	}
	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, 0);
	mainEvent = new SDL_Event();
}


CSDL_Setup::~CSDL_Setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

SDL_Renderer * CSDL_Setup::GetRenderer()
{
	return renderer;
}

SDL_Event * CSDL_Setup::GetMainEvent()
{
	return mainEvent;
}

void CSDL_Setup::Begin()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);
	
}

void CSDL_Setup::End()
{
	SDL_RenderPresent(renderer);
}

