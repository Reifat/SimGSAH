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

    extern void LoadData(std::string namefile, uint_64c& step_in, data_t& data, error_t* error);
	
} // end namespace dl

#endif
