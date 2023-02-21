#ifndef TYPE_HPP
#define TYPE_HPP
#include <SDL.h>
#include "EventBroadcaster.hpp"

using SDLEventBroadcaster = EventBroadcaster<SDL_EventType, SDL_Event>;

#endif