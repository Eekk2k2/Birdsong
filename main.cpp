#include "main.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb_image.h"

Application* application;
int main() {
	application = new Application();

	application->Start();

	while (!glfwWindowShouldClose(application->applicationWindow))
		application->Update();

	application->Terminate();
	return 0;
}