#include "Layer.hpp"
#include "../Component/Transform.hpp"
#include "../Component/Animation.hpp"
#include "../Component/PlayerInput.hpp"

Layer::Layer(SDLEventBroadcaster& caster) : caster(caster) {}

bool Layer::Initialize()
{
	makePlayer();

	return true;
}

bool Layer::Update(float deltaTime)
{
	return true;
}

void Layer::Release()
{
	registry.clear();
}

entt::entity Layer::makePlayer()
{
	const entt::entity entity = registry.create();

	registry.emplace<Transform>(entity);
	registry.emplace<Animation>(entity);
	registry.emplace<PlayerInput>(entity, caster);

	return entity;
}