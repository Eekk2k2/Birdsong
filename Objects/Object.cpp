#include "Object.h"

Object::Object() { this->transform = std::make_shared<Transform>(); }

Object::~Object() { }