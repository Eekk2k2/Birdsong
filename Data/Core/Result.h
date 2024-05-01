#pragma once

#ifndef RESULT_S
#define RESULT_S
#include <string>
#include <iostream>

// Shorthand 
#define BIRD_VOID Result_Ptr<void>
#define BIRD_ID Result<Identifier>

template <typename T>
struct Result {
	Result(T m_item) : success(true), info(""), item(m_item) { }
	Result(bool m_success, std::string m_info) : success(m_success), info(m_info) { }

	bool success;
	std::string info;

	T item;
	operator T() { return item; }
	operator T* () { return &item; }

	void Print() const { std::cout << this->info << std::endl; }
};

template <typename T>
struct Result_Ptr {
	Result_Ptr(T* m_item) : success(true), info(""), item(m_item) { }
	Result_Ptr(bool m_success, std::string m_info) : success(m_success), info(m_info), item(nullptr) { }

	// TODO : ENUM
	bool success;
	std::string info;

	T* item;
	operator T* () { return item; }

	void Print() const { std::cout << this->info << std::endl; }
};

#endif !RESULT_S