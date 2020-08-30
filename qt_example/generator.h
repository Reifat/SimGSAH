#ifndef GENERATORSIGNALNOSE_H
#define GENERATORSIGNALNOSE_H
#include <qvector.h>
#include <algorithm>
#include "src_dll/core.hpp"

class Generator
{
    using enum_t = std::uint64_t;
    enum_t _sample;
    QVector<QVector<double>> _signal;
    double *_temp;
    error_t *_error;
    void DonloadSignal(std::int16_t type, double ampl, enum_t f);
    void DonloadNoise(std::int16_t type, double ampl, double par_0 = 0, double par_1 = 0);

public:
    Generator(enum_t fs, enum_t sample);

    void AddHarmonic(double ampl, enum_t f);
    void AddMeander(double ampl, enum_t f);
    void AddSaw(double ampl, enum_t f);
    void AddTriangle(double ampl, enum_t f);
    void AddSinglePeriod(double ampl, enum_t f);
    void AddRectified(double ampl, enum_t f);

    void AddNoiseUniformDist(double ampl, double min = 0,double max = 1);
    void AddNoiseNormalDist(double ampl,double mean,double sigma);
    void AddNoiseCauchyDist(double ampl,double shift,double scale);
    void AddNoiseStudentDist(double ampl,double degree_freedom);
    void AddPinkNoise(double ampl);

    double GetMinValueTime();
    double GetMaxValueTime();
    double GetMinValueSignal();
    double GetMaxValueSignal();

    void ResetParameters(enum_t fs, enum_t sample);
    void Clear();

    QVector<QVector<double>>& GetSignal();
    ~Generator();
};

#endif // GENERATORSIGNALNOSE_H
