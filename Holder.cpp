#include "Holder.h"

Holder::Holder()
{

}

Holder::~Holder()
{
}



void Holder::CallPreStart()
{
	for (size_t i = 0; i < this->extenders.size(); i++)
	{
		this->extenders[i]->PreStart();
	}
}

void Holder::CallStart()
{
	for (size_t i = 0; i < this->extenders.size(); i++)
	{
		this->extenders[i]->Start();
	}
}

void Holder::CallPostStart()
{
	for (size_t i = 0; i < this->extenders.size(); i++)
	{
		this->extenders[i]->PostStart();
	}
}



void Holder::CallPreUpdate()
{
	for (size_t i = 0; i < this->extenders.size(); i++)
	{
		this->extenders[i]->PreUpdate();
	}
}

void Holder::CallUpdate()
{
	for (size_t i = 0; i < this->extenders.size(); i++)
	{
		this->extenders[i]->Update();
	}
}

void Holder::CallPostUpdate()
{
	for (size_t i = 0; i < this->extenders.size(); i++)
	{
		this->extenders[i]->PostUpdate();
	}
}



void Holder::AddExtender(std::shared_ptr<Extender> extender, std::string extenderName)
{
	std::string foundExtender = "";
	
	for (size_t i = 0; i < this->extenderNames.size(); i++)
		if (this->extenderNames[i] == extenderName) { std::cout << "Extender " << extenderName << " already exists." << std::endl;  return; }

	this->extenders.push_back(extender);
	this->extenderNames.push_back(extenderName);
}
