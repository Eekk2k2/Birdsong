#include "MainObject.h"

MainObject::MainObject(std::shared_ptr<Camera> camera)
{
	this->renderer = std::make_unique<Renderer>
		(
			camera,
			this->transform,
			std::make_shared<Mesh>(),
			std::make_shared<Shader>(),
			std::vector<std::shared_ptr<Texture>> { }
		);
}

MainObject::~MainObject()
{

}
