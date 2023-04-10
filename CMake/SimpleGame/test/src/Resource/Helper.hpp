#ifndef HELPER_HPP
#define HELPER_HPP

class GameWindow
{
public:
	constexpr GameWindow(int width, int height) : width(width), height(height) {}
	int width;
	int height;
};

namespace GameValue
{
	constexpr GameWindow Window { 500, 500 };
};

#endif