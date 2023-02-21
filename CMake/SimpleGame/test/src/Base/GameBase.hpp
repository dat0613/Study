#ifndef GAMEBASE_HPP
#define GAMEBASE_HPP

#include "Type.hpp"
#include "Layer.hpp"
#include "Renderer.hpp"

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
	void Release();

	SDLEventBroadcaster& GetSDLEventcaster();

private:
	void OnQuitEvent(const SDLEventBroadcaster::EventObject& eventObject);

	Layer layer;
	Renderer renderer;
	bool shutDown;
	SDLEventBroadcaster SDLEventcaster;
};

#endif 