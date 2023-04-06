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

	struct DeleteTexture
	{
		void operator()(SDL_Texture* ptr) const noexcept
		{
			if (nullptr != ptr)
				SDL_DestroyTexture(ptr);
		}
	};
	using Texture = std::unique_ptr<SDL_Texture, DeleteTexture>;

	Texture LoadTexture(const char* path);

	SDL_Window* window;
	SDL_Renderer* renderer;
	std::map<int, Texture> textures;
};

#endif