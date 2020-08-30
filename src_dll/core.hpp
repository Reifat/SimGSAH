/*
 * Copyright 2019 - 2020, Reifat ©.
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

#include <functional>
#include <algorithm>
#include <vector>
#include <array>
#include <random>
#include <chrono>
#include <string>
#include "tools/auxiliary_tools.hpp"
#include "dataloading/dataloading.hpp"



/* Remove comments on "DLL_MODE_CORE" or declare before including file
 *   |        |       |
 *  \|/      \|/     \|/  */
//#define DLL_MODE_CORE

// Define the path to the data file "file.dat", otherwise the default path will be used
#ifndef FILE_PATH
#define FILE_PATH "data/" /*Default path */
#endif
#ifndef ERROR_TYPE
#define ERROR_TYPE
typedef unsigned char* error_ptr_t;
typedef unsigned char error_t;
#endif

/* * * * Status  code list (Required when using the dll) * * * *
 * * * * 1. - 0xFF: Status undefined(!!!this value must be passed in function!!!) (Состояние не определено);
 * * * * 2. - 0x00: Successful completion (Успешное завершение);
 * * * * 3. - 0x11: No object with the requested number (Нет объекта с запрашиваемым номером);
 * * * * 4. - 0x33: Invalid frequency (Неверно введенная частота);
 * * * * 5. - 0x55: Invalid ratio of the sample rate to the signal frequency (Недопустимое отношение Fs/F);
 * * * * 6. - 0x77: Data file not found .dat (Файл с данными не найден .dat);
 * * * * 7. - 0x99: Very high sampling rate relative to the signal frequency. 
 * * * *            (Очень большая частота дискретизации по отношению к частоте сигнала);
 */

/* * * * CORE FUNCTION * * * *
 *  - Initialization : Initializes the internal state of the dll library.
 *                     (Инициализация внутреннего состояния DLL библиотеки)
 *      Parameters: 1 - Number of samples (Количество выборок);
 *      (Параметры) 2 - Sampling frequence (Частота дискретизации); 
 *  
 *   - Get : Signal request function of type "type" (Функция запроса сигнала типа "type").
 *      Parameters: 1 - Pointer to an array(with a size equal to the of samples), into which the signal will be loaded,
 *      (Параметры)     in case of a successful function execution.
 *                      (Указатель на массив(с размером равным количеству выборок) в который будет загружен сигнал,
 *                       в случаи успешного выполнения функции)
 *                  2 - Number of the signal(range from 0 to 5). (Номер запрашиваемого сигнала)
 *                      Signal types in the library: 0 - harmonic;
 *                      (Типы сигналов в библиотеки) 1 - meander;
 *                                                   2 - saw;
 *                                                   3 - triangle;
 *                                                   4 - single_period;
 *                                                   5 - rectified.dat.
 *                  3 - Signal frequency.
 *                  4 - If the function fails, it returns an error code.
 *                      (See error codes above.)
 * 
 * 
 *   - Noise : The function requests the generation of a random process.(Функция запроса генерации случайного процесса)
 *      Parameters:  1 - Pointer to an array (with a size equal to the number of samples) into which the random process
 *      (Параметры)      will be loaded, in cases of successful execution of functions. 
 *                   2 - Distribution type or noise (range from 0 to 4). (Тип распределения или шума)
 *                       Distribution and noise types: 0 - Uniform distrybution;
 *                       (Типы распределения и шумов)  1 - Normal(Gaussian) distrybution;
 *                                                     2 - Cauchy distribution;
 *                                                     3 - Student_t distribution;
 *                                                     4 - pink_noise.
 *                  3 - first distribution parameter;
 *                  4 - second distribution parameter;
 *                  5 - If the function fails, it returns an error code.
 *                      (See error codes above.)
 * 
 * 
 *   - SwapArr : The function shuffles the elements of the array. (Функция перемешивает элементы массива)
 *          Parameters:  1 - Pointer to an array with data.
 *          (Параметры)      (Указатель на массив с данными)
 */

#ifdef DLL_MODE_CORE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef CORE_MATHLIBRARY_EXPORTS
#define CORE_MATHLIBRARY_API __declspec(dllexport)
#else
#define CORE_MATHLIBRARY_API __declspec(dllimport)
#endif
namespace gsn {
    extern "C" {
        CORE_MATHLIBRARY_API void Initialization(uint64_t sampl, uint64_t infs);
        CORE_MATHLIBRARY_API void Get(double* arr, std::uint16_t type, std::uint64_t f, error_ptr_t error = 0);
        CORE_MATHLIBRARY_API void Noise(double* arr, uint16_t type, double par_0 = 1, double par_1 = 2, error_ptr_t error = 0);
        CORE_MATHLIBRARY_API void SwapArr(double* _array);
    }
}
#else 
namespace gsn {
    extern void Initialization(std::uint64_t sampl, std::uint64_t infs);
    extern void Get(double* arr, std::uint16_t type, std::uint64_t f, error_ptr_t error = 0);
    extern void Noise(double* arr, uint16_t type, double par_0 = 1, double par_1 = 2, error_ptr_t error = 0);
    extern void SwapArr(double* _array);
}
#endif
#endif
