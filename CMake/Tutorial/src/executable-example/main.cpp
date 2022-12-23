#include <iostream>
#include "static.hpp"

int main()
{
	std::cout << "Hello exe!" << std::endl;

	StaticLibrary lib;
	lib.DoSomeThing();
}