#pragma once

#include <unordered_map>
#include <iostream>
#include <typeindex>
#include <any>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "..\Data\Holder\Holder.h"
#include "..\Data\Core\Result.h"
#include "..\Data\Core\Identifier.h"
#include "..\Data\RenderPipeline\PipelineElement.h"
#include "..\Objects\Lights\Light.h"
#include "..\Data\Holder\Held.h"
using HeldT = std::any;

#define STATIC_ASSERT_IS_DERIVED_LIGHT(T) \
	static_assert(std::is_base_of<Light, T>::value, "T has to be derived from class Light");

class RenderPipeline {
public:
	RenderPipeline();
	~RenderPipeline();

	virtual BIRD_VOID Render();

	virtual BIRD_VOID Setup();

	template <typename T> 
	bool isLightTypeHeld() const;

	template <typename T>
	BIRD_VOID AddLightType();

	template <typename T>
	BIRD_VOID RemoveLightType();

	template <typename T>
	BIRD_VOID EnrollLight(const Identifier& identifier, Holder& holder);

	template <typename T>
	BIRD_VOID DisenrollLight(const Identifier& identfier);

	Result<bool> isMaterialEnrolled(const Identifier& identifier);

	BIRD_VOID EnrollMaterial(const Identifier& identifier, Holder& holder);

	BIRD_VOID DisenrollMaterial(const Identifier& identifier);

	Result<bool> isMeshEnrolled(const Identifier& material, const Identifier& mesh);

	BIRD_VOID EnrollMesh(const Identifier& material, const Identifier& mesh, Transform* transform, Holder& holder);

	BIRD_VOID DisenrollMesh(const Identifier& material, const Identifier& mesh, Transform* transform);

protected:
	std::unordered_map<std::string, PipelineElement> heldElements;
	std::unordered_map<std::type_index, HeldT> heldLights;
	
};

template<typename T>
inline bool RenderPipeline::isLightTypeHeld() const
{
	STATIC_ASSERT_IS_DERIVED_LIGHT(T);
	return this->heldLights.find(typeid(T)) != this->heldLights.end();
}

template<typename T>
inline BIRD_VOID RenderPipeline::AddLightType()
{
	STATIC_ASSERT_IS_DERIVED_LIGHT(T);
	if (this->isLightTypeHeld<T>())
		return BIRD_VOID(false, "Cannot add new light type T in AddLightType<T>() due it already existing");

	//this->heldLights.emplace(typeid(T), HeldType_Ptr<T>());
	return BIRD_VOID(nullptr);
}

template<typename T>
inline BIRD_VOID RenderPipeline::RemoveLightType()
{
	STATIC_ASSERT_IS_DERIVED_LIGHT(T);
	if (!this->isLightTypeHeld<T>())
		return BIRD_VOID(false, "Cannot remove light type T in RemoveLightType<T>() due it not existing");

	this->heldLights.erase(typeid(T));
	return BIRD_VOID(false, "RemoveLightType() not implemented yet");
}

template<typename T>
inline BIRD_VOID RenderPipeline::EnrollLight(const Identifier& identifier, Holder& holder)
{
	STATIC_ASSERT_IS_DERIVED_LIGHT(T);
	if (identifier.typeID != typeid(T))
		return BIRD_VOID(false, "T and identifier.typeID in EnrollLight<T>(identifier, holder) has to match");
	if (!this->isLightTypeHeld<T>())
		return BIRD_VOID(false, "Cannot add light of type T due to T not being held");

	HeldType_Ptr<T>& heldLightType = std::any_cast<HeldType_Ptr<T>&>(this->heldLights.at(typeid(T)));
	Result_Ptr<T> heldLight = holder.GetHeldItem(identifier);
	if (!heldLight.success) { return BIRD_VOID(false, heldLight.info); }

	heldLightType.EnrollItem(identifier, heldLight.item);
	return BIRD_VOID(nullptr);
}

template<typename T>
inline BIRD_VOID RenderPipeline::DisenrollLight(const Identifier& identifier)
{
	STATIC_ASSERT_IS_DERIVED_LIGHT(T);
	if (identifier.typeID != typeid(T))
		return BIRD_VOID(false, "T and identifier.typeID in DisenrollLight<T>(identifier) has to match");
	if (!this->isLightTypeHeld<T>())
		return BIRD_VOID(false, "Cannot remove light of type T due to T not being held");

	HeldType_Ptr<T>& heldLightType = std::any_cast<HeldType_Ptr<T>&>(this->heldLights.at(typeid(T)));

	BIRD_VOID result = heldLightType.DisenrollItem(identifier);
	if (result.success) { return BIRD_VOID(nullptr); }
	else { return BIRD_VOID(false, result.info); }
}


/*

struct Foo {

	Foo(const Foo& other) : fooData(other.fooData) {}

	// Commenting this out removes the error
	Foo(Foo&& other) noexcept {
		this->fooData = std::move(other.fooData);
	}

	Foo& operator=(const Foo& other) {
		if (this != &other) {
			this->fooData = other.fooData;
		}
		return *this;
	}

	int fooData;
};


class Bar {
public:
	// OR commenting this out
	~Bar() { Any code inside here also produces the error };

	Bar& operator=(const Bar& other) {
		if (this != &other) {
			// Copy the heldElements map (or implement your own logic)
			this->heldElements = other.heldElements;
		}
		return *this;
	}

protected:
	std::unordered_map<int, Foo> heldElements;
};

class BarHandler {
public:
	BarHandler() {
		this->bar = Bar();
	}

	Bar bar;
};

*/