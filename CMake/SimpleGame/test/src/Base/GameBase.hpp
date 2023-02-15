#ifndef GAMEBASE_HPP
#define GAMEBASE_HPP

#include "Layer.hpp"
#include "Renderer.hpp"

class GameBase
{
public:
	~GameBase();
	bool Initialize(const char* title, unsigned __int32 width, unsigned __int32 height);
	bool Update(float deltaTime);
	bool Render();

private:
	Layer layer;
	Renderer renderer;
};

#endif 