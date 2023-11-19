#pragma once
#include "..\..\Components\Extender.h"

class ExampleExtender : public Extender
{
public:
	void PreStart() override;

	void Start() override;

	void PostStart() override;


	void PreUpdate() override;

	void Update() override;
	
	void PostUpdate() override;
};

