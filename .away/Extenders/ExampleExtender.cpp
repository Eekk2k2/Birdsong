#include "ExampleExtender.h"

void ExampleExtender::PreStart()
{
	std::cout << "Helo World" << std::endl;
}

void ExampleExtender::Start()
{
	std::cout << "Helo World" << std::endl;
}

void ExampleExtender::PostStart()
{
	std::cout << "Helo World" << std::endl;
}



void ExampleExtender::PreUpdate()
{
	std::cout << "Helo Update" << std::endl;
}

void ExampleExtender::Update()
{
	std::cout << "Helo Update" << std::endl;
}

void ExampleExtender::PostUpdate()
{
	std::cout << "Helo Update" << std::endl;
}
