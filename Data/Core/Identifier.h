#pragma once

#ifndef IDENTIFIER_S
#define IDENTIFIER_S
#include <string>
#include <typeindex>
#include <sstream>
#include <random>

// SLOW : String comparisons yuck, use UINT32 instead 

struct Identifier {
	Identifier() : UUID(""), typeID(typeid(void)) { }
	Identifier(std::string m_UUID) : UUID(m_UUID), typeID(typeid(void)) { }
	Identifier(std::type_index m_typeID) : UUID(""), typeID(m_typeID) { }
	Identifier(std::string m_UUID, std::type_index m_typeID) : UUID(m_UUID), typeID(m_typeID) { }

	std::string UUID;
	std::type_index typeID;
};

static std::string GenerateUUID() {
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

#endif !IDENTIFIER_S
