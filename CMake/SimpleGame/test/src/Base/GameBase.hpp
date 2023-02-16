#ifndef GAMEBASE_HPP
#define GAMEBASE_HPP

#include "Layer.hpp"
#include "Renderer.hpp"
#include "Delegate.hpp"

class GameBase
{
public:
	using EventHandler = delegate<void, const SDL_Event&, GameBase&>;
	using EventHandlerMap = std::map<SDL_EventType, std::vector<EventHandler>>;

	GameBase();
	~GameBase();
	bool Initialize(const char* title, unsigned __int32 width, unsigned __int32 height);
	bool Update(float deltaTime);
	void EventHandling();
	bool Render();
	void AttachEventHandler(SDL_EventType eventType, EventHandler&& handler);// 나중에 Detach도 추가해야 할듯 한데, identity 관리는 어떻게 할까...
	void ShutDown();

private:
	void OnQuitEvent(const SDL_Event& event, GameBase& gameBase);

	Layer layer;
	Renderer renderer;
	EventHandlerMap handlerMap;
	bool shutDown;
};

#endif 