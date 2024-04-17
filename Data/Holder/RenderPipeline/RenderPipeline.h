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
#include "..\Data\Holder\RenderPipeline\PipelineElement.h"
#include "..\Objects\Lights\Light.h"
#include "..\Data\Holder\Held.h"
using HeldT = std::any;

#define STATIC_ASSERT_IS_DERIVED_LIGHT(T) \
	static_assert(std::is_base_of<Light, T>::value, "T has to be derived from class Light");

class RenderPipeline {
public:
	virtual BS_VOID Render();

	virtual BS_VOID Setup();

	template <typename T> 
	bool isLightTypeHeld() const;

	template <typename T>
	BS_VOID AddLightType();

	template <typename T>
	BS_VOID RemoveLightType();

	template <typename T>
	BS_VOID EnrollLight(const Identifier& identifier, const Holder& holder);

	template <typename T>
	BS_VOID DisenrollLight(const Identifier& identfier);

	Result<bool> isMaterialEnrolled(const Identifier& identifier);

	BS_VOID EnrollMaterial(const Identifier& identifier, const Holder& holder);

	BS_VOID DisenrollMaterial(const Identifier& identifier);

	Result<bool> isMeshEnrolled(const Identifier& material, const Identifier& mesh);

	BS_VOID EnrollMesh(const Identifier& material, const Identifier& mesh, Transform* transform, const Holder& holder);

protected:
	std::unordered_map<std::type_index, HeldT> heldLights;
	std::unordered_map<std::string, PipelineElement> heldElements;
};

template<typename T>
inline bool RenderPipeline::isLightTypeHeld() const
{
	STATIC_ASSERT_IS_DERIVED_LIGHT(T);
	return this->heldLights.find(typeid(T)) != this->heldLights.end();
}

template<typename T>
inline BS_VOID RenderPipeline::AddLightType()
{
	STATIC_ASSERT_IS_DERIVED_LIGHT(T);
	if (this->isLightTypeHeld<T>())
		return BS_VOID(false, "Cannot add new light type T in AddLightType<T>() due it already existing");

	this->heldLights.emplace(typeid(T), HeldType_Ptr<T>());
	return BS_VOID(nullptr);
}

template<typename T>
inline BS_VOID RenderPipeline::RemoveLightType()
{
	STATIC_ASSERT_IS_DERIVED_LIGHT(T);
	if (!this->isLightTypeHeld<T>())
		return BS_VOID(false, "Cannot remove light type T in RemoveLightType<T>() due it not existing");

	this->heldLights.erase(typeid(T));
	return BS_VOID(false, "RemoveLightType() not implemented yet");
}

template<typename T>
inline BS_VOID RenderPipeline::EnrollLight(const Identifier& identifier, const Holder& holder)
{
	STATIC_ASSERT_IS_DERIVED_LIGHT(T);
	if (identifier.typeID != typeid(T))
		return BS_VOID(false, "T and identifier.typeID in EnrollLight<T>(identifier, holder) has to match");
	if (!this->isLightTypeHeld<T>())
		return BS_VOID(false, "Cannot add light of type T due to T not being held");

	HeldType_Ptr<T>& heldLightType = std::any_cast<HeldType_Ptr<T>&>(this->heldLights.at(typeid(T)));
	Result_Ptr<T> heldLight = holder.GetHeldItem(identifier);
	if (!heldLight.success) { return BS_VOID(false, heldLight.info); }

	heldLightType.EnrollItem(identifier, heldLight.item);
	return BS_VOID(nullptr);
}

template<typename T>
inline BS_VOID RenderPipeline::DisenrollLight(const Identifier& identifier)
{
	STATIC_ASSERT_IS_DERIVED_LIGHT(T);
	if (identifier.typeID != typeid(T))
		return BS_VOID(false, "T and identifier.typeID in DisenrollLight<T>(identifier) has to match");
	if (!this->isLightTypeHeld<T>())
		return BS_VOID(false, "Cannot remove light of type T due to T not being held");

	HeldType_Ptr<T>& heldLightType = std::any_cast<HeldType_Ptr<T>&>(this->heldLights.at(typeid(T)));

	BS_VOID result = heldLightType.DisenrollItem(identifier);
	if (result.success) { return BS_VOID(nullptr); }
	else { return BS_VOID(false, result.info); }
}