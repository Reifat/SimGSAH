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
 
#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include <vector>
#include "src_dll\tools\vector_operation.hpp"
namespace atl {  // namespace auxiliary tool library

#ifndef ATL_DATA_TYPE
#define ATL_DATA_TYPE
	template<typename T>
	using vec1d_tmp = std::vector<T>;
	template<typename T>
	using vec2d_tmp = std::vector<vec1d_tmp<T>>;
	template<typename T>
	using vec3d_tmp = std::vector<vec2d_tmp<T>>;
	template<typename T>
	using it_vec = typename std::vector<T>::iterator;
	using vec1d_dty = std::vector<double>;
	using vec2d_dty = std::vector<vec1d_dty>;
	using enum_t = std::uint64_t;
#endif

	// Интерполяция функции полиномом Лагранжа
    extern void L_I(const vec2d_dty& f_in,const vec1d_dty& x, vec2d_dty& f_out);

} // end namespace etl

#endif
