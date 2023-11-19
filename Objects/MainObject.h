#pragma once
#include "Object.h"
#include "..\Components\Renderer.h"

class MainObject : public Object
{
public:
	MainObject(std::shared_ptr<Camera> camera);
	~MainObject();

	std::unique_ptr<Renderer> renderer;
};

