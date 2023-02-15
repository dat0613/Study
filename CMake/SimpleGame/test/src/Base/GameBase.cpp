#include "GameBase.hpp"

GameBase::~GameBase()
{
	SDL_Quit();
}

bool GameBase::Initialize(const char* title, unsigned __int32 width, unsigned __int32 height)
{
	if (0 != SDL_Init(SDL_INIT_EVERYTHING))
		return false;

	return renderer.Initialize(title, width, height);
}

bool GameBase::Update(float deltaTime)
{
	SDL_Event event;
	while (SDL_PollEvent(NULL))
	{
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			return false;
			break;
		}
	}

	return layer.Update(deltaTime);
}

bool GameBase::Render()
{
	return renderer.Render();
}
