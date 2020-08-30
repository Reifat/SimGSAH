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
 
#ifndef AUXILIARY_TOOLS_HPP
#define AUXILIARY_TOOLS_HPP

#include <vector>
#include <algorithm>
#include <cmath>
#include "src_dll\tools\vector_operation.hpp"
#include "src_dll\tools\interpolation.hpp"

#pragma warning(push)
#pragma warning(disable:4244)
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

	/* Round a number to the nearest from an vector
	 * (Округление числа к ближайшему из вектора)
	 * Specify the type explicitly! (Указать явно тип!)
	 * in form(В форме): rounding_divider<T0,T1>(...);
	 * Parametrs:  
	 *			 1,2 - first and last iterator on vector;
	 *			 3   - The number to be rounded;
	 *			 4   - Vector size.
	 */	
	template<typename T0, typename T1>
	it_vec<T0> RoundingDivider(
		it_vec<T0> it_first,
		it_vec<T0> it_last,
		T1 number,
        enum_t size = 0) {
		enum_t s_vec = size;
		if (s_vec == 0) { // Если размер вектора не был указан, вычислим его
			while (it_first != it_last) {
				it_first++;
				s_vec++;
			}
			it_first -= s_vec;
		}
		if (s_vec > 1) {
			enum_t half_first = round(s_vec / 2);
			enum_t half_last = s_vec - half_first;
			if (number > * (it_first + half_first - 1))
				return atl::RoundingDivider<T0, T1>(it_first + half_first, it_last, number, half_last);
			else
				return atl::RoundingDivider<T0, T1>(it_first, it_first + half_first - 1, number, half_first);
		}
		else {
			return it_first;
		}
	}


	/* Extracts an interval of type (a: b] or [a: b) from 
	 * a vector and searches for a number in this interval
	 * closest to "a" or closest to "b", returns an iterator to
	 * an array element that is close ( or which is) to the desired number.
	 * Выделяет интервал типа (a:b] или [a:b) из вектора 
	 * и ищет число в этом интервале ближайшее к "a" либо ближайшее к "b",
	 * возвращает итератор на элемент массива который близок(или который является) к искомому числу
	 *	Parametrs : 1   - Reference to the vector from which the interval is selected
	 *				2,3 - Interval start/end
	 *				4   - Turn on-off (start-end) interval
	 *				5   - Aim towards "false" - minus infinity, "true" - plus infinity.
	 */
	template<typename T0, typename T1>
	it_vec<T0> Nearest(
			   vec1d_tmp<T0>& arr,	   // Ссылка на вектор из которого выделяется интервал между чисел num_0, num_1;
			   T1 num_0,			   // Начало интервала
			   T1 num_1,			   // Конец интервала
			   bool on_of = true,	   // Включить-выключить (начало-конец) интервала
			   bool direction = true){ // Устремить в сторону false-минус бесконечности, true-плюс бесконечности
		if (*(arr.end() - 1) - *arr.begin() <= 0)
			return arr.end();
		it_vec<T0> first = atl::RoundingDivider<T0, T1>(arr.begin(), arr.end(), num_0);
		it_vec<T0> last = atl::RoundingDivider<T0, T1>(arr.begin(), arr.end(), num_1);
		size_t s_array = 0;
		while (first != last) {
			first++;
			s_array++;
		}
		first -= s_array;
		if ((on_of && direction) == true)
			return atl::RoundingDivider<T0, T1>(first, last, num_1);
		if ((on_of && !direction) == true)
			return atl::RoundingDivider<T0, T1>(first, last, num_0);
		if ((!on_of && direction) == true) {
			it_vec<T0> temp = atl::RoundingDivider<T0, T1>(first, last, num_1);
			return (*temp == num_1) ? temp-- : temp;
		}
		if ((!on_of && !direction) == true) {
			it_vec<T0> temp = atl::RoundingDivider<T0, T1>(first, last, num_0);
			return (*temp == num_1) ? temp++ : temp;
		}
	}

	/* Dividing a signal into segments and interpolating it for a new sample rate
	 * Разбиение на сегменты сигнала и интерполирование его для новой частоты дискретизации
	 * Parametrs : 1 - reference to the vector of the original signal
	 *			   2 - A reference to the vector to which the interpolation result will be written
	 *			   3 - New sampling rate
	 *			   5 - Size of the window for splitting
	 */
	template<typename T>
    void ILagPiecewise(vec2d_tmp<T>& f,     // Ссылка на вектор исходного сигнала
					   vec2d_tmp<T>& f_out, // Ссылка на вектор, в который будет записан результат интерполяции
					   uint64_t fs,			// Новая частота дискретизации
					   uint64_t window = 4 ) {	// Размер окна разбиения
        double period = 1 / (double)fs;
        enum_t s_of = round(*(f.at(0).end() - 1) / period) + 1; // плюс 1 тк также нужно учесть последнюю точку
        f_out.at(0).resize(s_of,0);
        f_out.at(1).resize(s_of,0);

        for (enum_t n = 0; n < s_of; n++)
			f_out.at(0).at(n) += n * period;

        uint64_t /*32*/ segments;
		if (f.at(0).size() < f_out.at(0).size())
			segments = floor(f.at(0).size() / window);
		else
			segments = floor(f_out.at(0).size() / window);

		vec3d_tmp<T> segment_f(segments, vec2d_tmp<T>(2));
		vec3d_tmp<T> segment_of(segments, vec2d_tmp<T>(2));
        vec1d_tmp<enum_t> numCeil_of(segments);
        vec1d_tmp<it_vec<T>> it_f(segments);

		for (enum_t n = 0; n < segments; n++) {
			for (enum_t m = 0; m < 2; m++) {
				it_vec<T> first_it = f.at(m).begin() + window * n;
				it_vec<T> last_it = (segments - 1 != n) ? (f.at(m).begin() + window * n + window + 1) : f.at(m).end();
                enum_t size_seg = last_it - first_it;
				segment_f.at(n).at(m).resize(size_seg, 0);
				std::copy(first_it, last_it, segment_f.at(n).at(m).begin());
			}

			{
				T temp_0 = *segment_f.at(n).at(0).begin();
				T temp_1 = *(segment_f.at(n).at(0).begin() + 1);
				T temp_2 = *(segment_f.at(n).at(0).end() - 2);
				T temp_3 = *(segment_f.at(n).at(0).end() - 1);
				it_vec<T> first_it = atl::Nearest(f_out.at(0), temp_0, temp_1, true, false);
				it_vec<T> last_it = (segments - 1 != n) ? atl::Nearest(f_out.at(0), temp_2, temp_3, false, true) + 1 : f_out.at(0).end();
				it_f.at(n) = f_out.at(1).begin() + (first_it - f_out.at(0).begin());
				numCeil_of.at(n) = last_it - first_it;
				segment_of.at(n).at(0).resize(numCeil_of.at(n), 0);
				segment_of.at(n).at(1).resize(numCeil_of.at(n), 0);
				std::copy(first_it, last_it, segment_of.at(n).at(0).begin());
			}
            L_I(segment_f.at(n), segment_of.at(n).at(0), segment_of.at(n));
		}
		{
			for (enum_t n = 0; n < segments; n++) {
				std::copy(segment_of.at(n).at(1).begin(),
					segment_of.at(n).at(1).end(),
					it_f.at(n));
			}
		}
	}

} // end namespace atl
#pragma warning(pop)
#endif
