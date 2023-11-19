#pragma once
#include <vector>
#include <memory>

#include "Components/Extender.h"

class Holder
{
public:
	Holder();
	~Holder();

	void CallPreStart(), CallStart(), CallPostStart();

	void CallPreUpdate(), CallUpdate(), CallPostUpdate();

	void AddExtender(std::shared_ptr<Extender> extender, std::string extenderName);
	
private:
	// Extenders
	std::vector<std::string> extenderNames;
	std::vector<std::shared_ptr<Extender>> extenders;
};

