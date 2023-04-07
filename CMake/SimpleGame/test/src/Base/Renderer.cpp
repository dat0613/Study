#include "Renderer.hpp"
#include "../Resource/Resource.hpp"

Renderer::Renderer() : window(nullptr), renderer(nullptr)
{

}

Renderer::~Renderer()
{
	Release();
}

bool Renderer::Initialize(const char* title, unsigned __int32 width, unsigned __int32 height)
{
	window = Renderer::SDLWindow(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN));
	if (nullptr == window)
		return false;

	renderer = Renderer::SDLRenderer(SDL_CreateRenderer(window.get(), -1, 0));
	if (nullptr == renderer)
		return false;

	if (false == LoadAllTexture())
		return false;

	return true;
}

bool Renderer::Render()
{
	SDL_SetRenderDrawColor(renderer.get(), 0, 255, 255, 255);
	SDL_RenderClear(renderer.get());



	SDL_RenderPresent(renderer.get());

	return true;
}

void Renderer::Release()
{
	textures.clear();
	surfaces.clear();
}

bool Renderer::LoadAllTexture()
{
	for (int i = Resource::Texture::Type::Begin; i < Resource::Texture::Type::End; i++)
	{
		Resource::Texture::Type textureToLoad = (Resource::Texture::Type)i;
		auto surface = LoadSurface(Resource::Texture::GetPath(textureToLoad));

		if (nullptr == surface)
			return false;

		auto texture = Renderer::Texture(SDL_CreateTextureFromSurface(renderer.get(), surface.get()));

		if (nullptr == texture)
			return false;

		surfaces.emplace(textureToLoad, std::move(surface));
		textures.emplace(textureToLoad, std::move(texture));
	}

	return true;
}

Renderer::Texture Renderer::LoadTexture(const char* path)
{
	auto texture = Renderer::Texture(SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, 0, 0));
	SDL_UpdateTexture(texture.get(), nullptr, texture.get(), 0);
	SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);

	return texture;
}

Renderer::Surface Renderer::LoadSurface(const char* path)
{
	return Renderer::Surface(SDL_LoadBMP(path));
}