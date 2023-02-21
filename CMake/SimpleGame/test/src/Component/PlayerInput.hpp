#ifndef PLAYERINPUT_HPP
#define PLAYERINPUT_HPP

#include "../Base/Type.hpp"
#include <vector>

class PlayerInput
{
public:
	PlayerInput(SDLEventBroadcaster& caster) : caster(caster)
	{
		SDLEventBroadcaster::Identity identity = SDLEventBroadcaster::Identity_null;
		handlerIdentityVector.reserve(2);

		identity = caster.Attach(SDLEventBroadcaster::EventType::SDL_KEYDOWN, SDLEventBroadcaster::EventHandler::from_method<PlayerInput, &PlayerInput::KeyDownHandler>(this));
		handlerIdentityVector.push_back(identity);

		identity = caster.Attach(SDLEventBroadcaster::EventType::SDL_KEYUP, SDLEventBroadcaster::EventHandler::from_method<PlayerInput, &PlayerInput::KeyUpHandler>(this));
		handlerIdentityVector.push_back(identity);
	}

	~PlayerInput()
	{
		for (const SDLEventBroadcaster::Identity& identity : handlerIdentityVector)
			caster.Detach(identity);
	}

private:
	// ECS에서 component에 method가 있는것은 적절하지 않다. 수정 필요
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