#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <random>
#include <sstream>

class Transform {
public:
	Transform(),
		Transform(Transform&& other) noexcept;

	void SetParent(Transform* newParent);
	Transform* GetParent();

	void AddChild(std::string UUID, Transform* child), RemoveChild(std::string UUID);

	void SetPosition(glm::vec3 position), SetLocalPosition(glm::vec3 localPosition);
	glm::vec3 GetPosition(), GetLocalPosition();

	void SetScale(glm::vec3 scale), SetLocalScale(glm::vec3 localScale);
	glm::vec3 GetScale(), GetLocalScale();

	glm::mat4 GetModel();
	glm::mat3 GetNormalMatrix();

	// Flags
	void FlagRecalculate();
private:
	std::string UUID;
	std::string GenerateUUID(); // Merge with holder

	Transform* parent;
	std::unordered_map<std::string, Transform*> children;

	// This is the  relative to the parents global
	glm::vec3 localPosition, localScale;

	// If no value is updated dont recalculate the model
	bool recalculate = true;
	glm::mat4 model;
	glm::mat3 normalMatrix;
};

//#pragma once
//#include <glm/glm.hpp>
//#include <glm/gtx/matrix_decompose.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <iostream>
//#include <vector>
//
//struct Position {
//public:
//	void RecalculatePosition(), RecalculateLocalPosition();
//	void SetPosition(glm::vec3 position), SetLocalPosition(glm::vec3 localPosition);
//	glm::vec3 GetPosition(), GetLocalPosition();
//
//	glm::vec3 position;
//
//	glm::vec3 localPosition;
//};
//
//struct Rotation {
//public:
//	glm::vec3 rotation;
//
//	glm::vec3 localRotation;
//};
//
//struct Scale {
//public:
//	Scale();
//
//	glm::vec3 scale;
//
//	glm::vec3 localScale;
//};
//
//class Transform {
//public:
//	/*						   Transform						*/
//	Transform(), Transform(std::shared_ptr<Transform> parentTransform), ~Transform();
//
//	void SetParent(std::shared_ptr<Transform> parentTransform);
//
//	std::shared_ptr<Transform>	GetParentShared();
//
//	Transform*					GetParentRaw();
//
//	void AddChild(Transform* childTransform);
//
//	glm::mat4 GetModel();
//
//	/*							Position						*/
//
//	/// <summary>
//	/// Recalcuate so it matches with the local/global counterpart.
//	/// If its local it will also recalculate the global for every 
//	/// child.
//	/// </summary>
//	void RecalculatePosition(), RecalculateLocalPosition(), RecalculateChildrensPosition(), RecalculateChildrensLocalPosition();
//
//	/// <summary>
//	/// Set the either local or global position and recalcualte 
//	/// the other. If its local it will also recalculate the global 
//	/// for every child.
//	/// </summary>
//	void SetPosition(glm::vec3 newPosition), SetLocalPosition(glm::vec3 newLocalPosition);
//
//	/// <summary>
//	/// Retrieve either the local or global position.
//	/// </summary>
//	glm::vec3 GetPosition(), GetLocalPosition();
//
//	/*							Scale						*/
//
//	void RecalculateScale(), RecalculateLocalScale(), RecalculateChildrensScale(), RecalculateChildrensLocalScale();
//
//	void SetScale(glm::vec3 newScale), SetLocalScale(glm::vec3 newLocalScale);
//
//	glm::mat3 GetNormalMatrix();
//
//private:
//	/*						   Transform						*/
//
//	/// <summary>
//	/// The transform this transform is attached to/the child of.
//	/// </summary>
//	std::shared_ptr<Transform> parentTransform;
//
//	/// <summary>
//	/// The transforms of who this transform is parent to.
//	/// </summary>
//	std::vector<Transform*> childTransforms;						// TODO : Find a better solution on storing the children
//
//	/*							Position						*/
//	
//	/// <summary>
//	/// The global position. 
//	/// </summary>	
//	glm::vec3 position; 
//
//	/// <summary>
//	/// The position relative to the parent's global position.
//	/// </summary>
//	glm::vec3 localPosition;
//
//	// State change check
//	glm::vec3 lastPosition, lastLocalPosition;
//
//	/*							Scale						*/
//
//	/// <summary>
//	/// The global scale. 
//	/// </summary>
//	glm::vec3 scale;
//
//	/// <summary>
//	/// The scale relative to the parent's global scale.
//	/// </summary>
//	glm::vec3 localScale;
//
//	// State change check
//	glm::vec3 lastScale, lastLocalScale;
//
//	/*						Mr anderson						*/
//
//	bool updatedSinceLastFrame;
//	glm::mat4 model;
//	glm::mat3 normalMatrix;
//};