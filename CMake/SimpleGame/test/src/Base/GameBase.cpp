#include "GameBase.hpp"

GameBase::GameBase() : layer(SDLEventcaster), shutDown(false)
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

	SDLEventcaster.Attach(SDL_EventType::SDL_QUIT, SDLEventBroadcaster::EventHandler::from_method<GameBase, &GameBase::OnQuitEvent>(this));

	layer.Initialize();

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

		SDLEventcaster.Broadcast(static_cast<SDL_EventType>(event.type), event, layer.GetRegistry());
	}
}

bool GameBase::Render()
{
	return renderer.Render();
}

void GameBase::ShutDown()
{
	shutDown = true;
}

void GameBase::Release()
{
	layer.Release();
	renderer.Release();
}

SDLEventBroadcaster& GameBase::GetSDLEventcaster()
{
	return SDLEventcaster;
}

void GameBase::OnQuitEvent(const SDLEventBroadcaster::EventObject& eventObject, entt::registry& registry)
{
	ShutDown();
}