#include "Holder.h"

Object&     Holder::GetHeldObject   (Identifier objectIdentifier)
{
    return heldObjects              .at(objectIdentifier    .UUID);
}

Material&   Holder::GetHeldMaterial (Identifier materialIdentifier)
{
    return heldMaterials            .at(materialIdentifier  .UUID);
}

Mesh&       Holder::GetHeldMesh     (Identifier meshIdentifier)
{
    return heldMeshes               .at(meshIdentifier      .UUID);
}

Identifier Holder::GenerateIdentifier()
{
	Identifier newIdentifier = Identifier();
	newIdentifier.UUID = GenerateUUID();
	return newIdentifier;
}

std::string Holder::GenerateUUID()
{
    /* Copied from https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library */

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    std::uniform_int_distribution<> dis2(8, 11);

    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    };
    return ss.str();
}
