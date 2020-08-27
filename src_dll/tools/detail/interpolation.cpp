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
 
#ifndef INTERPOLATION_CPP
#define INTERPOLATION_CPP

#include "src_dll\tools\interpolation.hpp"

namespace atl {  // namespace auxiliary tool library

	// Function interpolation by Lagrange polynomial(Интерполяция функции полиномом Лагранжа)
    void L_I(const vec2d_dty& f_in,const vec1d_dty& x, vec2d_dty& f_out) {
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

} // end namespace etl

#endif
