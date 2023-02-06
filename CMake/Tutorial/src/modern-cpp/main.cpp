#include <iostream>
#include <memory>
#include <vector>

namespace _Allocator
{
	class Object
	{
	public:
		Object(int num) : num(num)
		{
			std::cout << "생성자 호출" << std::endl;
		}

		~Object()
		{
			std::cout << "소멸자 호출" << std::endl;
		}

		int num;
	};

	void Run()
	{
		std::allocator<Object> allocator;
		constexpr size_t size = 10;

		{
			auto ret = std::allocator_traits<std::allocator<Object>>::allocate(allocator, size);
			for (int i = 0; i < size; i++)
			{// allocate는 단순히 메모리를 할당하기만 해서 생성자가 호출되지 않음. num에는 쓰레기 값이 들어감
				std::cout << i << " : " << ret[i].num << std::endl;
			}
			std::allocator_traits<std::allocator<Object>>::deallocate(allocator, ret, size);
		}

		{
			auto ret = std::allocator_traits<std::allocator<Object>>::allocate(allocator, size);
			for (int i = 0; i < size; i++)
			{// construct, deallocate 함수로 이미 할당된 메모리에서 생성자와 소멸자를 호출할 수 있음
				std::allocator_traits<std::allocator<Object>>::construct(allocator, std::addressof(ret[i]), i);
				std::cout << i << " : " << ret[i].num << std::endl;
				std::allocator_traits<std::allocator<Object>>::destroy(allocator, std::addressof(ret[i]));
			}
			std::allocator_traits<std::allocator<Object>>::deallocate(allocator, ret, size);
		}
	}
}

void main()
{
	_Allocator::Run();

	return;
}