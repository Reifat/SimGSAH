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
 
#ifndef MAIN_CORE_CPP
#define MAIN_CORE_CPP

#include "src_dll\core.hpp"

#pragma warning(push)
#pragma warning(disable:4244)
namespace gsn{ // namespace generate signals and noise

template<typename T>
using vec1d = std::vector<T>;
template<typename T>
using vec2d = std::vector<vec1d<T>>;

	namespace gvar { // namespace: global variables for core

		std::uint64_t sampl;
		std::uint64_t fs;
		std::uint64_t start;
		double period;
		std::mt19937 Mt;
        std::uniform_real_distribution<double> uniform(0.0, 1.0);
        std::array<std::string,7> file_name = {
            "harmonic.dat",
            "meander.dat",
            "saw.dat",
            "triangle.dat",
            "single_period.dat",
            "rectified.dat",
            "pink_noise.dat"
        };
        std::string file_path = FILE_PATH;
	}

	// Зацикливам период сигнала пока не наберем достаточное колличество выборок
	template<typename T>
    void Repetition(T* signal_out, const vec1d<T>& signal_in, uint64_t sampl) {
		for (atl::enum_t n = 0, m = gvar::start; n < sampl; n++, m++) {
			// n - Перебирает массив вывода
			// m - Перебирает массив с данными
			if (m < signal_in.size())
				signal_out[n] = signal_in.at(m);
			else {
				m = 0;
				signal_out[n] = signal_in.at(m);
			}
		}
	}

    void GetSignal(const std::string name, double* signal, uint64_t f, error_ptr_t error = 0) {

		if (f < 1) {
			if(error != 0)
				*error = 0x33;
			return;
		}
        uint64_t&& out_fs = 0;
        vec1d<double> harmonic_;
        ld::ReadSignal(name, harmonic_, f, gvar::fs, out_fs, error);
		if (error != 0) {
			if ((*error != 0xFF) & (*error != 0x00))
				return;
		}
        if (gvar::fs == out_fs)	{
            Repetition(signal, harmonic_, gvar::sampl);
		}
		else {
            double original_period = 1 / (double)out_fs;
            vec2d<double> original_signal(2, vec1d<double>(harmonic_.size()));
			original_signal.at(1) = harmonic_;
			for (atl::enum_t n = 0; n < harmonic_.size(); n++)
				original_signal.at(0).at(n) = n * original_period;

            vec2d<double> using_signal(2,vec1d<double>());
            atl::ILagPiecewise(original_signal,using_signal, gvar::fs);
            Repetition(signal, using_signal.at(1), gvar::sampl);
		}
		if (error != 0) {
			if (*error == 0xFF) // Предполагаем если 0x00 был ранее записан, то перезапись не требуется
				*error = 0x00;
		}
	}

	
	void GenerateNoise(double* arr, std::function<double(std::mt19937&)> func_noise) {
		for (atl::enum_t n = 0; n < gvar::sampl; n++)
			arr[n] = func_noise(gvar::Mt);
	}

	/// ********************* CORE API *********************

	// Инициализация глобальных переменных core
	void Initialization(uint64_t sampl, uint64_t infs) {
		gvar::sampl = sampl;
		gvar::fs=infs;
		gvar::period = 1 / (double)infs;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count(); // Получаем текущее время
		gvar::Mt.seed(seed); // Инициализация генератора случайных чисел текущем временем
		gvar::start = (uint64_t)round(gvar::uniform(gvar::Mt) * gvar::sampl);
	}

// 
	void Get(double* arr, std::uint16_t type, std::uint64_t f, error_ptr_t error) {
		double ratio_f = (double)gvar::fs / (double)f; // The ratio of the sample rate to the signal frequency
		if ( ratio_f >= (double)ld::dp::ratio_f) {
			if(error != 0)
				*error = 0x99;
			return;
		}
        std::string full_path = gvar::file_path + gvar::file_name.at(type);
		switch (type) {
			case 0: GetSignal(full_path, arr, f, error);
				break;
			case 1: GetSignal(full_path, arr, f, error);
				break;
			case 2: GetSignal(full_path, arr, f, error);
				break;
			case 3: GetSignal(full_path, arr, f, error);
				break;
			case 4: GetSignal(full_path, arr, f, error);
				break;
			case 5: GetSignal(full_path, arr, f, error);
				break;
			default: {
				if ( error != 0 )
					*error = 0x11;
				return;
			}
		}
		if (error != 0) { // Обработка кода ошибок при выходе из структуры case
			if ((*error != 0xFF) & (*error != 0x00))
				return;
		}
		if (error != 0) {
			if (*error == 0xFF) // Предполагаем если 0x00 был ранее записан, то перезапись не требуется
				*error = 0x00;
		}
	}

	void Noise(double* arr, uint16_t type, double par_0, double par_1, error_ptr_t error) {
		std::function<double(std::mt19937&)> func_noise;
		switch (type) {
			case 0: {
				double& min = par_0;
				double& max = par_1;
				func_noise = std::uniform_real_distribution<double>(min, max);
				GenerateNoise(arr, func_noise);
				break;
			}
			case 1: {
				double& mean = par_0;
				double& sigma = par_1;
				func_noise = std::normal_distribution<double>(mean, sigma);
				GenerateNoise(arr, func_noise);
				break;
			}
			case 2: {
				double& shift = par_0;
				double& scale = par_1;
				func_noise = std::cauchy_distribution<double>(shift, scale);
				GenerateNoise(arr, func_noise);
				break;
			}
			case 3: {
				double& degree_freedom = par_0;
				func_noise = std::student_t_distribution<double>(degree_freedom);
				GenerateNoise(arr, func_noise);
				break;
			}
			case 4: {
				if (gvar::fs > ld::dp::fs)
					return;
				std::string full_path = gvar::file_path + 
										gvar::file_name.at(6);
				GetSignal(full_path, arr, 1, error);
				if (error != 0) { // Обработка кода ошибок при выходе из структуры case
					if ((*error != 0xFF) & (*error != 0x00))
						return;
				}
			}
			default: {
				if (error != 0)
					*error = 0x11;
				return;
			}
		}
		if (error != 0) {
			if (*error == 0xFF) // Предполагаем если 0x00 был ранее записан, то перезапись не требуется
				*error = 0x00;
		}
	}

	// Перемешивает элементы вектора (сделай с человеческим ГСЧ)
	void SwapArr(double* array_) {
		for (atl::enum_t n = 0; n < gvar::sampl; n++) {
			uint64_t r_n = gvar::uniform(gvar::Mt) * gvar::sampl;
			std::swap(array_[n], array_[r_n]);
		}
	}
} // end namespace gsn

#pragma warning(pop)
#endif
