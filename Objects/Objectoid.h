#pragma once
#include "..\Components\Transform.h"

class Objectoid : public Transform
{
public:
	Objectoid();
	Objectoid(Objectoid&& other) noexcept;
	Objectoid(const Objectoid& other);
	~Objectoid();
private:
	
};

