#pragma once

/* Parts of the engine | Comment out to disable */
//#define ENABLE_APPLICATION
//#define ENABLE_MATERIAL_BUILDER
#define ENABLE_FILE_HANDLER

#ifdef ENABLE_FILE_HANDLER
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

#include "..\Data\Holder\Loader\Loader.h"
#endif // ENABLE_FILE_HANDLER


#ifdef ENABLE_MATERIAL_BUILDER
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..\Data\Material\Material.h"
#endif // ENABLE_MATERIAL_BUILDER

#ifdef ENABLE_APPLICATION
#include "Application.h"
Application* application;
#endif // ENABLE_APPLICATION