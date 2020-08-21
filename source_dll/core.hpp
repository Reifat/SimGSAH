#ifndef MAIN_CORE_HPP
#define MAIN_CORE_HPP

#define WIN32_LEAN_AND_MEAN

#include <functional>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include "tools/auxiliary_tools.hpp"
#include "dataloading/dataloading.hpp"

#ifndef ERROR_TYPE
#define ERROR_TYPE
typedef unsigned char error_t;
#endif

#ifndef TEST_CORE
#include <windows.h>

#ifdef CORE_MATHLIBRARY_EXPORTS
#define CORE_MATHLIBRARY_API __declspec(dllexport)
#else
#define CORE_MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" CORE_MATHLIBRARY_API {
	void Initialization(std::uint64_t sampl, std::uint64_t infs);
	void Get(double* arr, std::uint16_t type, std::uint64_t f, error_t * error);
	void Nose(double* arr, std::uint16_t num, double par_0, double par_1, error_t * error);
	void SwapArr(double* _array);
}
#else 
extern void Initialization(std::uint64_t sampl, std::uint64_t infs);
extern void Get(double* arr, std::uint16_t type, std::uint64_t f, error_t* error);
extern void Nose(double* arr, std::uint16_t num, double par_0, double par_1, error_t* error);
extern void SwapArr(double* _array);


#endif

#endif