#include "GameBase.hpp"

bool GameBase::Initialize(const char* title, unsigned __int32 width, unsigned __int32 height)
{
	return renderer.Initialize(title, width, height);
}
