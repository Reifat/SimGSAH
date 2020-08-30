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

#ifndef DATALOADING_HPP
#define DATALOADING_HPP

#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "src_dll\dataloading\data_parameters.hpp"
#include "src_dll\dataloading\read_bin.hpp"
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
	using vec_d = std::vector<T>; // vector data type template
	using data_t = vec_d<double>;
#endif
	/*  Reading the data of the requested signal from the file and selecting the one closest
	 *  to the entered sampling rate "in_fs" from the available set for interpolation(if required)
	 *  Чтение данных запрошенного сигнала из файла а также подбирает наиболее близкую частоту
	 *  дискретизации к введенной "in_fs" из имеющегося набора для последующей интерполяции(если потребуется)
	 *  Parameters: 1. name - file name(Имя файла)
	 *  (Параметры) 2. signal - reference to the vector in which the signal will be written
	 *				   (Ссылка на вектор, в который будет записан сигнал)
	 *				3. f - signal frequence
	 *              4. in_fs - original sampling rate (Исходная частота дискретизации)
	 *				5. out_fs - Sample rate of the signal that was read(частота дискретизации прочитанного сигнала из файла)
	 *				6. error - function execution code
	 */
	template<typename T>
    void ReadSignal(std::string name, vec_1d<T>& signal,
		std::uint64_t  f,
		std::uint64_t  in_fs,
		std::uint64_t& out_fs,
		error_ptr_t error = 0) {

		if (error != 0) {
			if ((*error != 0xFF) & (*error != 0x00))
				return;
		}
		std::uint64_t sempl_ratio = std::round((double)in_fs / (double)f); // sempl ratio on period
        if (sempl_ratio >= 3 && sempl_ratio <= ld::dp::sample_period){

			std::uint64_t sempl = ld::dp::sample_period * f; // sempl on periond
            std::uint64_t first_step = std::round((double)sempl / (double)in_fs);
			std::uint64_t last_step = 
						  *atl::RoundingDivider<std::uint32_t,
												std::uint64_t>(dp::dividers.begin(),
															   dp::dividers.end(),
															   first_step);
            out_fs = ld::dp::sample_period * f / last_step;
			std::uint64_t data_size = ld::dp::sample_period / last_step;
			signal.resize(data_size);
			ld::LoadData(name, last_step, signal, error);
		}
		else {
			if (error != 0) // If addres pointer !=0 (Если адрес указателя != 0)
				*error = 0x55; // Set error code
		}
		if (error != 0) {
			if (*error == 0xFF) // Предполагаем если 0x00 был ранее записан, то перезапись не требуется
				*error = 0x00;
		}
	}

} // end namespace dl

#endif
