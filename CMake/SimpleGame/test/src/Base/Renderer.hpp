#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL.h>
#include <string>

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize(const char* title, unsigned __int32 width, unsigned __int32 height);
	bool Render();
	void Release();

private:

	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif