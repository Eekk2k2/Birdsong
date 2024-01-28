/*
	
    Arrays/Lists/Vector: For linear access patterns and iteration over a contiguous block of memory, arrays, lists, or vectors can be suitable. They provide fast iteration and cache-friendly access.

    Maps/Dictionaries: When you need to associate objects with unique keys (e.g., entity IDs), maps or dictionaries can be useful. std::unordered_map in C++ or similar structures in other languages can provide constant-time access on average.

    Sparse Data Structures: For scenarios where only a subset of objects has significant data, sparse data structures like sparse arrays or hash maps might be useful to save memory.

    Spatial Partitioning Structures: For spatial queries and collision detection, spatial partitioning structures like quad-trees, octrees, or spatial hash maps can be effective. They help organize objects based on their positions in space, making certain queries more efficient.

    Entity-Component System (ECS): In many game engines, an ECS architecture is used. This involves storing entities as unique IDs and components as separate arrays or structures. This allows for efficient iteration over specific types of components and supports a data-oriented design.

    Object Pooling: To manage a large number of short-lived objects, object pooling can be employed. Instead of allocating and deallocating objects frequently, you reuse objects from a pool, which can improve memory locality and reduce allocation overhead.

    Custom Data Structures: Depending on the specific needs of the game, custom data structures may be designed to optimize for particular access patterns and operations.

*/

#pragma once

#include <unordered_map>
#include <typeindex>
#include <any>
#include <string>
#include <random>
#include <sstream>

#include "..\Objects\Object.h"
class Object;

#include "..\Components\Transform.h"

typedef struct Identifier {
    std::string UUID = "";
} Identifier;

typedef struct MeshRenderListElement {
public:
    Mesh* mesh;
    std::vector<Transform*> transforms;
} MeshRenderListElement;

// For better clarity
typedef std::string MaterialUUID, ObjectUUID, MeshUUID;

class Holder
{
public:
    // TODO : Make implementing frustum and lod easier
    std::unordered_map<std::string, Object>     heldObjects;
    std::unordered_map<std::string, Material>   heldMaterials;
    std::unordered_map<std::string, Mesh>       heldMeshes;

    std::unordered_map<MaterialUUID, std::unordered_map<MeshUUID, MeshRenderListElement>> renderList;

    template <typename... Args> Identifier AddNewObject(Args&&... args) {
        Identifier newIdentifier = GenerateIdentifier();
        heldObjects.emplace(newIdentifier.UUID, Object(std::forward<Args>(args)...));
        return newIdentifier;
    }

    template <typename... Args> Identifier AddNewMaterial(Args&&... args) {
        Identifier newIdentifier = GenerateIdentifier();
        heldMaterials.emplace(newIdentifier.UUID, Material(std::forward<Args>(args)...));
        
        // Create new list for meshes associated with this material
        renderList[newIdentifier.UUID] = std::unordered_map<MeshUUID, MeshRenderListElement>();

        return newIdentifier;
    }

    template <typename... Args> Identifier AddNewMesh(Args&&... args) 
    {
        Identifier newIdentifier = GenerateIdentifier();
        heldMeshes.emplace(newIdentifier.UUID, Mesh(std::forward<Args>(args)...));
        return newIdentifier;
    }

    Object&     GetHeldObject   (Identifier objectIdentifier    );
    Material&   GetHeldMaterial (Identifier materialIdentifier  );
    Mesh&       GetHeldMesh     (Identifier meshIdentifier      );

    Identifier  GenerateIdentifier();
    std::string GenerateUUID();
};
