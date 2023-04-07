#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <array>

namespace Resource
{
	namespace Texture
	{
		enum Type : __int32
		{
			Nil = -1,
			Begin = 0,

			Skyblue = Begin,
			Orange,
			Blue,
			Yellow,
			Green,
			Purple,
			Red,

			End
		};

		constexpr std::array<const char*, static_cast<int>(Type::End)> Path 
		{
			".\\..\\..\\..\\data\\skyblue.bmp",
			".\\..\\..\\..\\data\\orange.bmp",
			".\\..\\..\\..\\data\\blue.bmp",
			".\\..\\..\\..\\data\\yellow.bmp",
			".\\..\\..\\..\\data\\green.bmp",
			".\\..\\..\\..\\data\\purple.bmp",
			".\\..\\..\\..\\data\\red.bmp"
		};

		const char* GetPath(Type type)
		{
			if (Type::Begin > type || Type::End <= type)
				return nullptr;

			return Path[type];
		}
	}
}

#endif