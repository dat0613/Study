#include "Renderer.hpp"
#include "../Resource/Resource.hpp"

Renderer::Renderer() : window(nullptr), renderer(nullptr)
{

}

Renderer::~Renderer()
{
	if (nullptr != renderer)
		SDL_DestroyRenderer(renderer);

	if (nullptr != window)
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

	// Resource::Texture::GetPath(Resource::Texture::Type::Box);
	// 여기서 뭔가 로드

	return true;
}

bool Renderer::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderClear(renderer);



	SDL_RenderPresent(renderer);

	return true;
}

void Renderer::Release()
{
}

Renderer::Texture Renderer::LoadTexture(const char* path)
{
	auto texture = Renderer::Texture(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, 0, 0));
	SDL_UpdateTexture(texture.get(), nullptr, texture.get(), 0);
	SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);

	return texture;
}
