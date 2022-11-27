#pragma once

#include <LibOpenGL/Utils.h>

#define ASSERT(x) \
	if (!(x))     \
		__debugbreak();

#define GlCall(_fct)                \
	libgl::utils::glClearError(); \
	_fct;                           \
	ASSERT(libgl::utils::glCheckError(__LINE__, __FILE__));

#define LOG(x) std::cout << x << std::endl;
