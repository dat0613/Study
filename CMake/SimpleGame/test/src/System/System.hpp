#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <entt/entt.hpp>

class System
{
public:
	virtual void Execute(entt::registry& registry, float deltaTime) = 0;
};

#endif