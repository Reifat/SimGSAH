#ifndef MAIN_CORE_HPP
#define MAIN_CORE_HPP

#define WIN32_LEAN_AND_MEAN
#define TEST_CORE

#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <string>
#include <functional>

#include "tools/auxiliary_tools.hpp"
#include "dataloading/dataloading.hpp"


#ifndef ERROR_TYPE
#define ERROR_TYPE
typedef unsigned char error_t;
#endif

void Initialization(std::uint64_t sampl, std::uint64_t infs);
void Get(double* arr, std::uint16_t type, std::uint64_t f, error_t* error);
void Nose(double* arr, std::uint16_t num, double par_0, double par_1, error_t* error);
void SwapArr(double* _array);

#endif