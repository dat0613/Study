#ifndef LAYER_HPP
#define LAYER_HPP

#include <entt/entt.hpp>

class Layer
{
public:
	bool Update(float deltaTime);
	void PushEvent();

private:
	entt::registry registry;
};

#endif