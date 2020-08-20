#ifndef AUXILIARY_TOOLS_HPP
#define AUXILIARY_TOOLS_HPP

#include <vector>
#include <algorithm>
#include <cmath>
#include "tools\vector_operation.hpp"

namespace atl {

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


	// Интерполяция функции
	void L_I(vec2d_dty& f_in, vec1d_dty& x, vec2d_dty& f_out) {
		// f[0] - Xi Значения узлов 
		// f[1] - Yi Значения функции в узлах
		// x[n] - значения точек интерполяции
		int  k = f_in.at(0).size() - 1;		  // Инициализация степени полинома
		f_out[0] = x;						  // Присвоение массиву значений x интерполяции
		vec2d_dty intermediate_L_I(k + 1); // Инициализация массива промежуточных вычисленний
		for (enum_t i = 0; i <= k; i++) {        // Цикл выражает базовые полимы в точках x
			vec2d_dty L_i(x.size(), vec1d_dty(k)); // Инициализируем массив для записи iго полинома
			unsigned int flag = 0;
			for (enum_t m = 0; m <= k; m++) // выразить iй базовый полином
			{							 //			|	   |	
				if (i != m) {			 //		   \'/	  \'/
					for (enum_t j = 0; j < x.size(); j++) // в точках x
						L_i[j][m - flag] = (x[j] - f_in[0][m]) / (f_in[0][i] - f_in[0][m]); // основное выражение полинома
				}
				else
					flag = 1;
			}
			VecOperat2d<double>::Multiplication(L_i, intermediate_L_I.at(i)); // Вычислим произведения основных выражений iго полинома
																			   // Результат будет выражен в iй базовый полином
			for (enum_t m = 0; m < x.size(); m++)  // Умножим базовый полином на значение функции в iм узле
				intermediate_L_I[i][m] *= f_in[1][i];
		}
		VecOperat2d<double>::Transposition(intermediate_L_I);
		VecOperat2d<double>::Sum(intermediate_L_I, f_out.at(1)); // Результат интерполяции функции на отрезке [a ... b]
	}

	// Округление числа к ближайшему из массива
	// Указать явно тип! В форме rounding_divider<T0,T1>(...);
	template<typename T0, typename T1>
	it_vec<T0> RoundingDivider(
		it_vec<T0> d_first,
		it_vec<T0> d_last,
		T1 number,
		size_t size = 0) {

		size_t s_array = size;
		if (s_array == 0) {
			while (d_first != d_last) {
				d_first++;
				s_array++;
			}
			d_first -= s_array;
		}

		if (s_array > 1) {
			size_t half_first = round(s_array / 2);
			size_t half_last = s_array - half_first;
			if (number > * (d_first + half_first - 1))
				return atl::RoundingDivider<T0, T1>(d_first + half_first, d_last, number, half_last);
			else
				return atl::RoundingDivider<T0, T1>(d_first, d_first + half_first - 1, number, half_first);
		}
		else {
			return d_first;
		}
	}



	// Выделяет интервал типа (a:b] или [a:b) из массива 
	// и ищет число в этом интервале ближайшее к "a" либо ближайшее к "b",
	// возвращает итератор на элемент массива который близок(или который является) к искомому числу
	template<typename T0, typename T1>
	it_vec<T0> Nearest(
			   vec1d_tmp<T0>& arr,	   // Массив из которого выделяется интервал между чисел num_0, num_1;
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



	// Разбиение на сегменты сигнала и интерполирование его
	template<typename T>
	vec2d_tmp<T> ILagPiecewise(vec2d_tmp<T> f, uint64_t fs, uint64_t /*32*/ window = 4) {
		double period = 1 / (double)fs;
		size_t s_of = round(*(f.at(0).end() - 1) / period) + 1; // плюс 1 тк также нужно учесть последнюю точку
		vec2d_tmp<T> f_out(2, vec1d_tmp<T>(s_of, 0));
		for (enum_t n = 0; n < s_of; n++)
			f_out.at(0).at(n) += n * period;

		uint64_t /*32*/ segments;
		if (f.at(0).size() < f_out.at(0).size())
			segments = floor(f.at(0).size() / window);
		else
			segments = floor(f_out.at(0).size() / window);

		vec3d_tmp<T> segment_f(segments, vec2d_tmp<T>(2));
		vec3d_tmp<T> segment_of(segments, vec2d_tmp<T>(2));
		std::vector<size_t> numCeil_of(segments);
		std::vector<std::vector<T>::iterator> it_f(segments);

		for (enum_t n = 0; n < segments; n++) {
			for (enum_t m = 0; m < 2; m++) {
				it_vec<T> first_it = f.at(m).begin() + window * n;
				it_vec<T> last_it = (segments - 1 != n) ? (f.at(m).begin() + window * n + window + 1) : f.at(m).end();
				size_t size_seg = last_it - first_it;
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
		return f_out;
	}

} // end namespace etl

#endif