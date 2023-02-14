#ifndef GAMEBASE_HPP
#define GAMEBASE_HPP

#include "Renderer.hpp"

class GameBase
{
public:

	bool Initialize(const char* title, unsigned __int32 width, unsigned __int32 height);
private:
	Renderer renderer;
};

#endif 