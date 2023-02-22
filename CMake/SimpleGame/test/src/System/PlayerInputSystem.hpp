#ifndef PLAYERINPUTSYSTEM_HPP
#define PLAYERINPUTSYSTEM_HPP

#include "../Base/Type.hpp"
#include <vector>
#include "System.hpp"

class PlayerInputSystem final : public System
{
public:
	PlayerInputSystem(SDLEventBroadcaster& caster) : caster(caster)
	{
		SDLEventBroadcaster::Identity identity = SDLEventBroadcaster::Identity_null;
		handlerIdentityVector.reserve(2);

		identity = caster.Attach(SDLEventBroadcaster::EventType::SDL_KEYDOWN, SDLEventBroadcaster::EventHandler::from_method<PlayerInput, &PlayerInput::KeyDownHandler>(this));
		handlerIdentityVector.push_back(identity);

		identity = caster.Attach(SDLEventBroadcaster::EventType::SDL_KEYUP, SDLEventBroadcaster::EventHandler::from_method<PlayerInput, &PlayerInput::KeyUpHandler>(this));
		handlerIdentityVector.push_back(identity);
	}

	~PlayerInputSystem()
	{
		for (const SDLEventBroadcaster::Identity& identity : handlerIdentityVector)
			caster.Detach(identity);
	}

	void Execute(entt::registry& registry, float deltaTime) override
	{

	}

private:
	void KeyDownHandler(const SDLEventBroadcaster::EventObject& eventObject)
	{
		
	}

	void KeyUpHandler(const SDLEventBroadcaster::EventObject& eventObject)
	{

	}

	SDLEventBroadcaster& caster;
	std::vector<SDLEventBroadcaster::Identity> handlerIdentityVector;// 소멸자에서 EventHandler를 회수하기 위함
};

#endif