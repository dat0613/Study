#include "Base/GameBase.hpp"
#include "Resource/Helper.hpp"
#include <chrono>

int main(int argv, char** args)
{
	bool running = false;
	GameBase base;
	if (!base.Initialize("test", GameValue::Window.width, GameValue::Window.height))
		return -1;

	std::chrono::high_resolution_clock timer;

	float deltaTime = 0.0f;

	while (true)
	{
		auto start = timer.now();

		base.EventHandling();

		if (!base.Update(deltaTime))
			break;

		if (!base.Render())
			break;

		auto stop = timer.now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() * 0.001f;
	}

	base.Release();

	return 0;
}