#include <iostream>
#include "static.hpp"
#include <signal.h>
#include <thread>

volatile bool stop = false;

void CallbackSIGTERM(int signal)
{
	stop = true;
}

int main()
{
	signal(SIGTERM, &CallbackSIGTERM);

	std::cout << "Hello exe!" << std::endl;

	StaticLibrary lib;

	while (false == stop)
	{
		lib.DoSomeThing();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	if (stop)
	{
		std::cout << "Signal SIGTERM was received." << std::endl;
		std::cout << "This container will stop in 5 seconds." << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));
}