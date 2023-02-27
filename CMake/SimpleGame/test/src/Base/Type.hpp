#ifndef TYPE_HPP
#define TYPE_HPP
#include <SDL.h>
#include <entt/entt.hpp>
#include "EventBroadcaster.hpp"

using SDLEventBroadcaster = EventBroadcaster<SDL_EventType, SDL_Event, entt::registry>;

#endif