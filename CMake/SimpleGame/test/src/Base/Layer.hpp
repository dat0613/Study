#ifndef LAYER_HPP
#define LAYER_HPP

#include <entt/entt.hpp>
#include "Type.hpp"

class Layer
{
public:
	Layer(SDLEventBroadcaster& caster);

	bool Initialize();
	bool Update(float deltaTime);
	void Release();

private:
	entt::entity makePlayer();

	entt::registry registry;
	SDLEventBroadcaster& caster;
};

#endif