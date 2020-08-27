/*
 * Copyright 2020, Reifat ©.
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
 
#ifndef CLASS_VECTOR_OPERATION_HPP
#define CLASS_VECTOR_OPERATION_HPP

#include <vector>
#include <functional>

namespace atl { // namespace auxiliary tool library

	template<typename T>
	class VecOperat2d {
		using vec1d = std::vector<T>;
		using vec2d = std::vector<std::vector<T>>;
		using func_vec_arg = std::function<T(vec1d&)>;
		using func_2arg = std::function<T(T, T)>;
		using enum_t = std::uint64_t;

		// Функция для работы с 1мерным вектором
		inline static T Operations(vec1d& vec, func_2arg f) {
			T result = vec.at(0);
			for (enum_t n = 1; n < vec.size(); n++) {
				result = f(result, vec.at(n));
			}
			return result;
		}
		// Функция для работы с 2х мерным вектором
		inline static void Operations(vec2d& in_vec, vec1d& out_vec, T(*f)(vec1d&) ) {
			if (out_vec.size() != in_vec.size())
				out_vec.resize(in_vec.size());

			for (enum_t n = 0; n < in_vec.size(); n++)
				out_vec.at(n) = f(in_vec.at(n));
		}
	public:

		// Быстрое удаление элемента вектора по идексу
		inline static void QuickRemove(vec1d& in_vec, std::size_t inx) {
			if (inx < in_vec.size()) {
				in_vec.at(inx) = std::move(in_vec.back()); // Перетаскиваем последний элемент на место удаляемого элемента
				in_vec.pop_back();      // Удаляем последний элемент
				in_vec.shrink_to_fit(); // освобождаем память
			}
		}

		// Транспонирование 2D вектора
		inline static void Transposition(vec2d& in_vec) {
			// Determining the dimension of the input vector
			std::size_t size_vec_n = in_vec[0].size(); // dimension vectors:
			std::size_t size_vec_m = in_vec.size();    // dim_vec = n x m;

			vec2d transpos_vec(size_vec_n, vec1d(size_vec_m));
			for (enum_t n = 0; n < in_vec.size(); n++) {
				for (enum_t m = 0; m < in_vec[0].size(); m++) {
					transpos_vec[m][n] = in_vec[n][m]; // Транспонирование
				}
			}
			in_vec.clear();
			in_vec = transpos_vec;
		}

		/***** Методы операций над элементами вектора *****/

		inline static T Sum(vec1d& vec) {
			func_2arg f = [](T cur_val, T next_val)->T {
				return cur_val + next_val;
			};
			return Operations(vec, f);
		}
		static void Sum(vec2d& in_vec, vec1d& out_vec) {
			T(*f)(vec1d&) = Sum;
			Operations(in_vec, out_vec, f);
		}

		template<unsigned int n = 0>
		inline static T Difference(vec1d& vec) {
			func_2arg f = [](T cur_val, T next_val)->T {
				return cur_val - next_val;
			};
			return Operations(vec, f);
		}
		inline static void Difference(vec2d& in_vec, vec1d& out_vec) {
			T(*f)(vec1d&) = Difference;
			Operations(in_vec, out_vec, f);
		}

		template<unsigned int n = 0>
		inline static T Multiplication(vec1d& vec) {
			func_2arg f = [](T cur_val, T next_val)->T {
				return cur_val * next_val;
			};
			return Operations(vec, f);
		}
		inline static void Multiplication(vec2d& in_vec, vec1d& out_vec) {
			T(*f)(vec1d&) = Multiplication;
			Operations(in_vec, out_vec, f);
		}

		template<unsigned int n = 0>
		inline static T Division(vec1d& vec) {
			func_2arg f = [](T cur_val, T next_val)->T {
				return cur_val / next_val;
			};
			return Operations(vec, f);
		}
		inline static void Division(vec2d& in_vec, vec1d& out_vec) {
			T(*f)(vec1d&) = Division;
			Operations(in_vec, out_vec, f);
		}
	};

} // end namespace auxiliary tool library
#endif