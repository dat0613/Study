#include "GameBase.hpp"

GameBase::GameBase() : shutDown(false)
{

}

GameBase::~GameBase()
{
	SDL_Quit();
}

bool GameBase::Initialize(const char* title, unsigned __int32 width, unsigned __int32 height)
{
	if (0 != SDL_Init(SDL_INIT_EVERYTHING))
		return false;

	if (false == renderer.Initialize(title, width, height))
		return false;

	AttachEventHandler(SDL_EventType::SDL_QUIT, EventHandler::from_method<GameBase, &GameBase::OnQuitEvent>(this));

	return true;
}

bool GameBase::Update(float deltaTime)
{
	if (shutDown)
		return false;

	return layer.Update(deltaTime);
}

void GameBase::EventHandling()
{
	SDL_Event event;

	while (SDL_PollEvent(NULL))
	{
		SDL_PollEvent(&event);

		auto pair = handlerMap.find(static_cast<SDL_EventType>(event.type));
		if (handlerMap.end() != pair)
		{
			for (auto del : pair->second)
			{
				del(event, *this);
			}
		}
	}
}

bool GameBase::Render()
{
	return renderer.Render();
}

void GameBase::AttachEventHandler(SDL_EventType eventType, EventHandler&& handler)
{
	auto pair = handlerMap.find(eventType);
	if (handlerMap.end() != pair)
	{
		pair->second.push_back(handler);
	}
	else
	{
		std::vector<EventHandler> handlerVector;// ...?
		handlerVector.reserve(10);
		handlerVector.push_back(handler);
		handlerMap.emplace(eventType, handlerVector);
	}
}

void GameBase::ShutDown()
{
	shutDown = true;
}

void GameBase::OnQuitEvent(const SDL_Event& event, GameBase& gameBase)
{
	gameBase.ShutDown();
}