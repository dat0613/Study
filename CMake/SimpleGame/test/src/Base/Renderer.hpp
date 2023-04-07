#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL.h>
#include <string>
#include <memory>
#include <map>

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize(const char* title, unsigned __int32 width, unsigned __int32 height);
	bool Render();
	void Release();

private:

	struct DeleteWindow
	{
		void operator()(SDL_Window* ptr) const noexcept
		{
			if (nullptr != ptr)
				SDL_DestroyWindow(ptr);
		}
	};

	struct DeleteRenderer
	{
		void operator()(SDL_Renderer* ptr) const noexcept
		{
			if (nullptr != ptr)
				SDL_DestroyRenderer(ptr);
		}
	};

	struct DeleteTexture
	{
		void operator()(SDL_Texture* ptr) const noexcept
		{
			if (nullptr != ptr)
				SDL_DestroyTexture(ptr);
		}
	};

	struct DeleteSurface
	{
		void operator()(SDL_Surface* ptr) const noexcept
		{
			if (nullptr != ptr)
				SDL_FreeSurface(ptr);
		}
	};

	using SDLWindow = std::unique_ptr<SDL_Window, DeleteWindow>;
	using SDLRenderer = std::unique_ptr<SDL_Renderer, DeleteRenderer>;
	using Texture = std::unique_ptr<SDL_Texture, DeleteTexture>;
	using Surface = std::unique_ptr<SDL_Surface, DeleteSurface>;

	bool LoadAllTexture();
	Texture LoadTexture(const char* path);
	Surface LoadSurface(const char* path);

	SDLWindow window;
	SDLRenderer renderer;

	std::map<int, Texture> textures;
	std::map<int, Surface> surfaces;
};

#endif