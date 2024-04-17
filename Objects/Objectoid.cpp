#include "Objectoid.h"

Objectoid::Objectoid() { }

Objectoid::Objectoid(Objectoid&& other) noexcept : Transform(std::move(other)) { }

Objectoid::Objectoid(const Objectoid& other) : Transform(other) { }

Objectoid::~Objectoid() { }
