#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <SDL.h>

class Transform
{
public:
	Transform() : position{ 0.0f, 0.0f }, scale{ 1.0f, 1.0f }, radian(0.0f) {}

	SDL_FPoint position;
	SDL_FPoint scale;
	float radian;
};

#endif