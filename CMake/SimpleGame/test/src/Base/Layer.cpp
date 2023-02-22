#include "Layer.hpp"
#include "../Component/Transform.hpp"
#include "../Component/Animation.hpp"
#include "../System/PlayerInputSystem.hpp"

Layer::Layer(SDLEventBroadcaster& caster) : caster(caster) {}

bool Layer::Initialize()
{
	makePlayer();

	systems.reserve(10);
	systems.push_back(new PlayerInputSystem(caster));
	
	return true;
}

bool Layer::Update(float deltaTime)
{
	for (System* system : systems)
		system->Execute(registry, deltaTime);

	return true;
}

void Layer::Release()
{
	for (System* system : systems)
		delete system;

	systems.clear();
	registry.clear();
}

entt::entity Layer::makePlayer()
{
	const entt::entity entity = registry.create();

	registry.emplace<Transform>(entity);
	registry.emplace<Animation>(entity);

	return entity;
}