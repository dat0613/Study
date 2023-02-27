#ifndef PLAYERINPUTSYSTEM_HPP
#define PLAYERINPUTSYSTEM_HPP

#include "../Base/Type.hpp"
#include <vector>
#include "System.hpp"
#include "../Component/Transform.hpp"
#include "../Component/Player.hpp"

class PlayerInputSystem final : public System
{
public:
	PlayerInputSystem(SDLEventBroadcaster& caster) : caster(caster)
	{
		SDLEventBroadcaster::Identity identity = SDLEventBroadcaster::Identity_null;
		handlerIdentityVector.reserve(2);

		identity = caster.Attach(SDLEventBroadcaster::EventType::SDL_KEYDOWN, SDLEventBroadcaster::EventHandler::from_method<PlayerInputSystem, &PlayerInputSystem::KeyDownHandler>(this));
		handlerIdentityVector.push_back(identity);

		identity = caster.Attach(SDLEventBroadcaster::EventType::SDL_KEYUP, SDLEventBroadcaster::EventHandler::from_method<PlayerInputSystem, &PlayerInputSystem::KeyUpHandler>(this));
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
	void KeyDownHandler(const SDLEventBroadcaster::EventObject& eventObject, entt::registry& registry)
	{
		auto view = registry.view<Player, Transform>();

		for (auto entity : view)
		{
			auto& transform = view.get<Transform>(entity);
		}
	}

	void KeyUpHandler(const SDLEventBroadcaster::EventObject& eventObject, entt::registry& registry)
	{
	}

	SDLEventBroadcaster& caster;
	std::vector<SDLEventBroadcaster::Identity> handlerIdentityVector;// 소멸자에서 EventHandler를 회수하기 위함
};

#endif