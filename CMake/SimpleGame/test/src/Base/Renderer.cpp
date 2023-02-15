#include "Renderer.hpp"

Renderer::Renderer() : window(nullptr), renderer(nullptr)
{

}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

bool Renderer::Initialize(const char* title, unsigned __int32 width, unsigned __int32 height)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (nullptr == window)
		return false;

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (nullptr == renderer)
		return false;

	return true;
}

bool Renderer::Render()
{
	return true;
}