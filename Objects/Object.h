#pragma once
#include "Objectoid.h"
#include "..\Components\Renderer.h"

#include "..\Data\Holder.h"
class Holder;
struct MeshRenderListElement;
struct Identifier;

class Object : public Objectoid
{
public:
	Object(std::shared_ptr<Holder> holder),
		Object(Object&& other) noexcept,
	~Object();

	void AddMesh(Identifier meshIdentifier, Identifier materialIdentifier);
	void RemoveMesh(int index);
	std::vector<Mesh*> meshes;

private:
	std::shared_ptr<Holder> holder;
};

