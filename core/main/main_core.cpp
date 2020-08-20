#ifndef MAIN_CORE_CPP
#define MAIN_CORE_CPP

#include "main_core.hpp"

namespace gvar // namespace: global variables for core
{
	std::uint64_t sampl;
	std::uint64_t fs;
	std::uint64_t start;
	double period;
	std::mt19937 Mt;
	std::uniform_real_distribution<double> uniform(0.0, 1.0); 
}

// Зацикливам период сигнала пока не наберем достаточное колличество выборок
template<typename T>
void Repetition(T* signal_out, const std::vector<T>& signal_in, uint64_t sampl)
{
	for (atl::enum_t n = 0, m = gvar::start; n < sampl; n++, m++)
	{
		// n - Перебирает массив вывода
		// m - Перебирает массив с данными
		if (m < signal_in.size())
			signal_out[n] = signal_in.at(m);
		else
		{
			m = 0;
			signal_out[n] = signal_in.at(m);
		}
	}
}
void GetSignal(const char* name, double* type_signal, uint64_t f, error_t* error)
{

	uint64_t* outFs = new uint64_t;
	std::vector<double> harmonic_;
	ld::ReadSignal(name, harmonic_, f, gvar::fs, outFs, error);
	if (gvar::fs == *outFs)
	{
		Repetition(type_signal, harmonic_, gvar::sampl);
	}
	else
	{
		double original_period = 1 / (double)*outFs;
		std::vector<std::vector<double>> original_signal(2, std::vector<double>(harmonic_.size()));
		original_signal.at(1) = harmonic_;
		for (atl::enum_t n = 0; n < harmonic_.size(); n++)
			original_signal.at(0).at(n) = n * original_period;
		std::vector<std::vector<double>>&& using_signal = atl::ILagPiecewise(original_signal, gvar::fs);
		Repetition(type_signal, using_signal.at(1), gvar::sampl);
	}
	delete outFs;
}

void GenerateNose(double* arr, std::function<double(std::mt19937&)> f) {
	for (atl::enum_t n = 0; n < gvar::sampl; n++)
		arr[n] = f(gvar::Mt);
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
void Get(double* arr, std::uint16_t type, std::uint64_t f, error_t* error = 0)
{
	if ( ((double)gvar::fs / (double)f ) > (double)ld::dp::Fs)
		return;
	switch (type)
	{
	case 1: GetSignal("data/Harmonic.dat", arr, f, error);
		break;
	case 2: GetSignal("data/Meander.dat", arr, f, error);
		break;
	case 3: GetSignal("data/Saw.dat", arr, f, error); //get_signal("data/Rectified.dat", arr, F, error);
		break;
	case 4: GetSignal("data/Triangle.dat", arr, f, error); //get_signal("data/Saw.dat", arr, F, error);
		break;
	case 5: GetSignal("data/single_period.dat", arr, f, error);
		break;
	case 6: GetSignal("data/Rectified.dat", arr, f, error);
		break;
	}
	if (type < 1 || type > 6)
		*error = 3;
}

void Nose(double* arr, uint16_t num, double par_0 = 1, double par_1 = 2, error_t* error = 0) {
	if (num >= 0 && num <= 4) {

		std::function<double(std::mt19937&)> f;
		switch (num) {
		case 0:
		{
			double& min = par_0;
			double& max = par_1;
			f = std::uniform_real_distribution<double>(min, max);
			GenerateNose(arr, f);
			break;
		}
		case 1:
		{
			double& mean = par_0;
			double& sigma = par_1;
			f = std::normal_distribution<double>(mean, sigma);
			GenerateNose(arr, f);
			break;
		}
		case 2:
		{
			double& shift = par_0;
			double& scale = par_1;
			f = std::cauchy_distribution<double>(shift, scale);
			GenerateNose(arr, f);
			break;
		}
		case 3:
		{
			double& degree_freedom = par_0;
			f = std::student_t_distribution<double>(degree_freedom);
			GenerateNose(arr, f);
			break;
		}
		case 4:	
		{
			if (gvar::fs > ld::dp::Fs)
				return;
			GetSignal("data/NOSE_PINK.dat", arr, 1, error);
		}
		}
	}
	else {
		*error = 1;
		return;
	}
}

// Перемешивает элементы вектора (сделай с человеческим ГСЧ)
void SwapArr(double* array_)
{
	for (atl::enum_t n = 0; n < gvar::sampl; n++) {
		uint64_t r_n = gvar::uniform(gvar::Mt) * gvar::sampl;
		std::swap(array_[n], array_[r_n]);
	}
}


#endif