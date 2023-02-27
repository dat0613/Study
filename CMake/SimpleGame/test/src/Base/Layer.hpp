#ifndef LAYER_HPP
#define LAYER_HPP

#include <entt/entt.hpp>
#include "../System/System.hpp"
#include "Type.hpp"

class Layer
{
public:
	Layer(SDLEventBroadcaster& caster);

	bool Initialize();
	bool Update(float deltaTime);
	void Release();
	entt::registry& GetRegistry();

private:
	entt::entity makePlayer();

	std::vector<System*> systems;
	entt::registry registry;
	SDLEventBroadcaster& caster;
};

#endif