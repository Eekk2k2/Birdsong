#pragma once

//class Objectoid;
//#include "..\Data\Core\Identifier.h"
//struct Identifier;
//#include "..\Data\Core\Result.h"
//template <typename T> struct Result;
//template <typename T> struct Result_Ptr;
//#include "..\Data\Mesh\Mesh.h"
//class Mesh;
//#include "..\Data\Holder\Holder.h"
//class Holder;

#include <unordered_map>

#include "..\Data\Holder\Holder.h"
#include "..\Objects\Objectoid.h"
#include "..\Data\Core\Result.h"
#include "..\Data\Core\Identifier.h"

#include "..\Data\Mesh\Mesh.h"

class Object : public Objectoid
{
public:
	Object();
	~Object();

	Result<bool> isMeshEnrolled(const Identifier& identifier);
	BS_VOID EnrollMesh(const Identifier& identifier, const Holder& holder);
	BS_VOID DisenrollMesh(const Identifier& identifier);
	Result<int> MeshesEnrolled();

	BS_VOID SetMaterial(const Identifier& identifier);
	BS_VOID SetMaterial(const Identifier& materialIdentifier, const Identifier& meshIdentifier);
private:
	std::unordered_map<std::string, Mesh*> meshes;
};

