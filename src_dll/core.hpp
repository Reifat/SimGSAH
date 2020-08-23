/*
 * Copyright 2020, Reifat.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MAIN_CORE_HPP
#define MAIN_CORE_HPP

#define WIN32_LEAN_AND_MEAN

#include <functional>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include "tools/auxiliary_tools.hpp"
#include "dataloading/dataloading.hpp"

#define FILE_PATH "C:/Users/Rayfat/Desktop/C++/qt_example/untitled/data/"

#ifndef ERROR_TYPE
#define ERROR_TYPE
typedef unsigned char error_t;
#endif

#ifdef TEST_CORE
#include <windows.h>

#ifdef CORE_MATHLIBRARY_EXPORTS
#define CORE_MATHLIBRARY_API __declspec(dllexport)
#else
#define CORE_MATHLIBRARY_API __declspec(dllimport)
#endif

namespace gsn {
    extern "C" CORE_MATHLIBRARY_API {
        void Initialization(std::uint64_t sampl, std::uint64_t infs);
        void Get(double* arr, std::uint16_t type, std::uint64_t f, error_t * error);
        void Nose(double* arr, std::uint16_t num, double par_0, double par_1, error_t * error);
        void SwapArr(double* _array);
    }
}
#else 
namespace gsn {
    extern void Initialization(std::uint64_t sampl, std::uint64_t infs);
    extern void Get(double* arr, std::uint16_t type, std::uint64_t f, error_t* error);
    extern void Nose(double* arr, std::uint16_t num, double par_0, double par_1, error_t* error);
    extern void SwapArr(double* _array);
}

#endif

#endif
