#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <array>

namespace Resource
{
	namespace Texture
	{
		enum Type
		{
			Begin = 0,
			Skyblue,
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
			"",
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