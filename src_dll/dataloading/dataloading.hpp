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

#ifndef DATALOADING_HPP
#define DATALOADING_HPP

#include <fstream>
#include <vector>
#include <string>
#include "src_dll\dataloading\data_parameters.hpp"
#include "src_dll\dataloading\read_bin.hpp"
#include "src_dll\tools\auxiliary_tools.hpp"

#ifndef NULL
#define NULL 0
#endif

#ifndef ERROR_TYPE
#define ERROR_TYPE
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
	// Читаем данные сигнала из файла и преобразуем в массив
	template<typename T>
    void ReadSignal(std::string name, vec_d<T>& signal, std::uint64_t f, std::uint64_t in_fs, std::uint64_t* out_fs, error_t* error)
	{
		std::uint64_t a = in_fs / f;

                if (a >= 3 && a <= ld::dp::sample_period)
		{
                        std::uint64_t d = ld::dp::sample_period * f / in_fs;
            int ds = *atl::RoundingDivider<std::uint32_t, std::uint64_t>(dp::dividers.begin(), dp::dividers.end(), d);
			if (out_fs != NULL)
                                *out_fs = ld::dp::sample_period * f / ds;
                        size_t size_ = ld::dp::sample_period / ds;
			signal.resize(size_);
			ld::LoadData(name, ds, signal, error);
		}
	}

} // end namespace dl

#endif
