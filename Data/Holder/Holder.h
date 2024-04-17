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
#include <vector>
#include <memory>
#include <string>
#include <random>
#include <any>
#include <sstream>

#include "..\Data\Core\Result.h"
#include "..\Data\Core\Identifier.h"

#include ".\Held.h"
using HeldT = std::any;

#ifndef IsTemplateClassStruct
#define IstemplateClassStruct

template <typename T>
struct IsTemplateClass : std::false_type { };

template <template<typename...> class C, typename... Args>
struct IsTemplateClass<C<Args...>> : std::true_type { };

#define STATIC_ASSERT_IS_TEMPLATE_CLASS(T) \
    static_assert(!IsTemplateClass<T>::value, "T cannot be a template class");

#endif // !IsTemplateClass

class Holder {
public:
    Holder();
    ~Holder();

    template <typename T>
    bool isTypeHeld() const;

    template <typename T>
    BS_VOID AddHeldType();

    template <typename T, typename... Args>
    Result<Identifier> AddNewItem(Args&&... args);

    template <typename T>
    Result_Ptr<T> GetHeldItem(const Identifier& identifier) const; 

    // Render Pipelines
    // ...

private:
    std::unordered_map<std::type_index, HeldT> heldTypes;
};

template<typename T>
inline bool Holder::isTypeHeld() const
{
    STATIC_ASSERT_IS_TEMPLATE_CLASS(T);
    return heldTypes.find(typeid(T)) != heldTypes.end();
}


template<typename T>
inline BS_VOID Holder::AddHeldType()
{
    // Checks
    STATIC_ASSERT_IS_TEMPLATE_CLASS(T);
    if (this->isTypeHeld<T>())
        return BS_VOID(false, "Cannot add type T in AddHeldType<T>() because it already exists.");

    // Adds
    heldTypes.emplace(typeid(T), HeldType<T>());
    return BS_VOID(nullptr);
}

template<typename T, typename ...Args>
inline Result<Identifier> Holder::AddNewItem(Args&& ...args)
{
    // Checks
    STATIC_ASSERT_IS_TEMPLATE_CLASS(T);
    if (!this->isTypeHeld<T>())
        return Result<Identifier>(false, "Cannot AddNewItem() of instance T due to type T not being held");

    // Adds
    HeldType<T>& heldType = std::any_cast<HeldType<T>&>(this->heldTypes.at(typeid(T)));
    Result<Identifier> newItemIdentifier = heldType.EnrollNewItem(std::forward<Args>(args)...);

    return Result<Identifier>(newItemIdentifier);
}


template<typename T>
inline Result_Ptr<T> Holder::GetHeldItem(const Identifier& identifier) const
{
    // Checks
    STATIC_ASSERT_IS_TEMPLATE_CLASS(T);
    if (!this->isTypeHeld<T>())
        return Result_Ptr<T>(false, "Cannot GetHeldItem() T due to type T not being held");

    // Retrieve
    // TODO : Check if identifier acutally points to item T
    HeldType<T>* heldType = std::any_cast<HeldType<T>*>(this->heldTypes.at(typeid(T)));
    return heldType->RetrieveItemPointer(identifier);
}