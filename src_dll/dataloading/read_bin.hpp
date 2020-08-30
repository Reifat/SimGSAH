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

#ifndef READ_BIN_HPP
#define READ_BIN_HPP

#include <fstream>
#include <vector>
#include <string>
#include "src_dll\tools\auxiliary_tools.hpp"

#ifndef NULL
#define NULL 0
#endif

#ifndef ERROR_TYPE
#define ERROR_TYPE
typedef unsigned char* error_ptr_t;
typedef unsigned char error_t;
#endif

namespace ld { // namespace data loading

#ifndef LD_DATA_TYPE
#define LD_DATA_TYPE
    using char_c = const char;
	using uint_64c = const std::uint64_t;
	template<typename T>
	using vec_1d = std::vector<T>;
#endif

	/*  The function of loading data from binary files.
	 *  The type of data structure written to the binary file is specified in the function template parameter.
	 *  The data structure must have std-style iterators and a begin () method.
	 *  Функция загрузки данных из бинарных фалов.
	 *	Тип структуры данных записанной в бинарный файл указывается в параметре шаблона функции.
	 *  Структура данных должна иметь итераторы в стиле библиотеки "std", а также иметь метод "begin()".
	 *	Parametrs  : 1. namefile - filename with binary data to load (Имя двоичного файла с данными для загрузки)
	 *  (Параметры)  2. step_in  - data read step(шаг чтения данных)
	 *               3. data     - Link to the data structure "data_ty<T...>" into which the read data will be loaded
	 *							   (Ссылка на структуру данных "data_ty<T...>" в которую будут записанны прочитанные данные)
	 *				 4. error    - function execution code(Код выполнения процедуры)
	 */
	template<template<class ...> class data_ty, typename... T>
	void LoadData(std::string namefile, uint_64c& step_in, data_ty<T...>& data, error_ptr_t error) {

		if (error != 0) {
			if ((*error != 0xFF) & (*error != 0x00))
				return;
		}
		std::ifstream finput(namefile, std::ios_base::in | std::ios_base::binary);
		if (finput.is_open()) {
			std::uint64_t size_ty = sizeof(*data.begin()); // size data type in data struct;
			std::uint64_t step = 1;						   // step data read
			if (step_in > 1)							   // in case more
				step = size_ty * step_in - size_ty;
			auto data_it = data.begin();	// iterator on data;
			auto temp = *data_it;			
			while (finput.read((char*)&temp, size_ty)) {
				*data_it = temp;
				finput.seekg(step, std::ios_base::cur);
				data_it++;
			}
			finput.close();
		}
		else {
			if (error != 0) { // If addres pointer !=0 (Если адрес указателя != 0)
				*error = 0x77; // Set error code: file not found;
				return;
			}
		}
		if (error != 0) {
			if (*error == 0xFF) // Предполагаем если 0x00 был ранее записан, то перезапись не требуется
				*error = 0x00;
		}
	}
	
} // end namespace dl

#endif
