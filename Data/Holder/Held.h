#pragma once

#ifndef HELDTYPE_S
#define HELDTYPE_S

#include <unordered_map>
#include <string>
#include <any>
#include <iostream>

#include "..\Core\Result.h"
#include "..\Core\Identifier.h"

using HeldT = std::any;

template <typename T>
struct HeldType {
	Result<bool> isKeyHeld(const Identifier& identifier) {
		if (identifier.typeID != typeid(T))
			return Result<bool>(false, "typeID of identifier in HeldType<T>::isKeyHeld(identifier) needs to be the same as typeid(T)");

		if (this->held.find(identifier.UUID) != this->held.end()) { return Result<bool>(true); }
		else { return Result<bool>(false); }
	}

	BS_VOID EnrollItem(const Identifier& identifier, T item) {
		if (identifier.typeID != typeid(T))
			return BS_VOID(false, "typeID of identifier in HeldType<T>::EnrollItem(identifier) needs to be the same as typeid(T)");

		Result<bool> keyHeld = this->isKeyHeld(identifier);
		if (!keyHeld.success) { return BS_VOID(false, keyHeld.info); }
		if (keyHeld.item) { return BS_VOID(false, "Cannot enroll item in EnrollItem(identifier, item) as identifier is already enrolled"); }

		this->held.emplace(identifier.UUID, item);
		return BS_VOID(nullptr);
	}

	template <typename ...Args>
	Result<Identifier> EnrollNewItem(Args&&... args) {
		Identifier identifier = Identifier(GenerateUUID(), typeid(T));
		this->held.emplace(identifier.UUID, T(std::forward<Args>(args)...));
		return Result<Identifier>(identifier);
	}

	Result_Ptr<T> RetrieveItemPointer(const Identifier& identifier) {
		if (identifier.typeID != typeid(T))
			return Result_Ptr<T>(false, "typeID of identifier in HeldType<T>::RetrieveItemPointer(identifier) needs to be the same as typeid(T)");

		Result<bool> keyHeld = this->isKeyHeld(identifier);
		if (!keyHeld.success) { return Result_Ptr<T>(false, keyHeld.info); }
		if (!keyHeld.item) { return Result_Ptr<T>(false, "Cannot retrieve item in RetrieveItemPointer(identifier) as identifier cannot be found"); }

		return Result_Ptr<T>(&this->held.at(identifier.UUID));
	}

private:
	std::unordered_map<std::string, T> held;
};

template <typename T>
struct HeldType_Ptr {
	Result<bool> isKeyHeld(const Identifier& identifier) {
		if (identifier.typeID != typeid(T))
			return Result<bool>(false, "typeID of identifier in HeldType<T>::isKeyHeld(identifier) needs to be the same as typeid(T)");

		if (this->held.find(identifier.UUID) != this->held.end()) { return Result<bool>(true); }
		else { return Result<bool>(false); }
	}

	BS_VOID EnrollItem(const Identifier& identifier, T* item) {
		if (identifier.typeID != typeid(T))
			return BS_VOID(false, "typeID of identifier in HeldType<T>::EnrollItem(identifier) needs to be the same as typeid(T)");

		Result<bool> keyHeld = this->isKeyHeld(identifier);
		if (!keyHeld.success) { return BS_VOID(false, keyHeld.info); }
		if (keyHeld.item) { return BS_VOID(false, "Cannot enroll item in EnrollItem(identifier, item) as identifier is already enrolled"); }

		this->held.emplace(identifier.UUID, item);
		return BS_VOID(nullptr);
	}

	BS_VOID DisenrollItem(const Identifier& identifier) {
		if (identifier.typeID != typeid(T))
			return BS_VOID(false, "typeID of identifier in HeldType<T>::DisenrollItem(identifier) needs to be the same as typeid(T)");

		Result<bool> keyHeld = this->isKeyHeld(identifier);
		if (!keyHeld.success) { return BS_VOID(false, keyHeld.info); }
		if (!keyHeld.item) { return BS_VOID(false, "Cannot disenroll item in DisenrollItem(identifier) as identifier isnt enrolled"); }

		this->held.erase(identifier.UUID);
		return BS_VOID(nullptr);
	}

	// TODO : new T would create memory leaks as this HeldType_Ptr doesnt delete objects
	//template <typename ...Args>
	//Result<Identifier> EnrollNewItem(Args&&... args) {
	//	Identifier identifier = Identifier(GenerateUUID(), typeid(T));
	//	this->held.emplace(identifier.UUID, new T(std::forward<Args>(args)));
	//	return Result<Identifier>(identifier);
	//}

	Result_Ptr<T> RetrieveItemPointer(const Identifier& identifier) {
		if (identifier.typeID != typeid(T))
			return Result_Ptr<T>(false, "typeID of identifier in HeldType<T>::RetrieveItemPointer(identifier) needs to be the same as typeid(T)");

		Result<bool> keyHeld = this->isKeyHeld(identifier);
		if (!keyHeld.success) { return Result_Ptr<T>(false, keyHeld.info); }
		if (!keyHeld.item) { return Result_Ptr<T>(false, "Cannot retrieve item in RetrieveItemPointer(identifier) as identifier cannot be found"); }

		return Result_Ptr<T>(this->held.at(identifier.UUID));
	}

private:
	std::unordered_map<std::string, T*> held;
};

#endif // !HELDTYPE_S