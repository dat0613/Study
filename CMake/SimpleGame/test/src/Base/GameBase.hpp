#ifndef GAMEBASE_HPP
#define GAMEBASE_HPP

#include "Layer.hpp"
#include "Renderer.hpp"
#include "EventBroadcaster.hpp"

using SDLEventBroadcaster = EventBroadcaster<SDL_EventType, SDL_Event>;

class GameBase
{
public:
	GameBase();
	~GameBase();
	bool Initialize(const char* title, unsigned __int32 width, unsigned __int32 height);
	bool Update(float deltaTime);
	void EventHandling();
	bool Render();
	void ShutDown();

private:
	void OnQuitEvent(const SDL_Event& event);

	Layer layer;
	Renderer renderer;
	bool shutDown;
	SDLEventBroadcaster SDLEventcaster;
};

#endif 