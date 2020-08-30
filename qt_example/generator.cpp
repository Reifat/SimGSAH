#include "generator.h"

Generator::Generator(enum_t fs, enum_t sample):_sample(sample),
    _signal(2,QVector<double>(sample)){
    _error = new error_t;
    _temp = new double[sample];
    gsn::Initialization(sample,fs);
    for(std::uint64_t n = 0; n < _sample; n++)
        _signal[0][n] = (double)n/(double)fs;
}

void Generator::DonloadSignal(std::int16_t type, double ampl, enum_t f){
    gsn::Get(_temp,type,f,_error);
    for(std::uint64_t n = 0; n < _sample; n++){
        _signal[1][n] += _temp[n] * ampl;
    }
}
void Generator::DonloadNoise(std::int16_t type, double ampl, double par_0, double par_1){
    gsn::Noise(_temp,type,par_0,par_1,_error);
    for(std::uint64_t n = 0; n < _sample; n++){
        _signal[1][n] += _temp[n] * ampl;
    }
}

QVector<QVector<double>>& Generator::GetSignal(){
    return _signal;
}

void Generator::AddHarmonic(double ampl, enum_t f){
    DonloadSignal(0, ampl, f);
}
void Generator::AddMeander(double ampl, enum_t f){
    DonloadSignal(1, ampl, f);
}
void Generator::AddSaw(double ampl, enum_t f){
    DonloadSignal(2, ampl, f);
}
void Generator::AddTriangle(double ampl, enum_t f){
    DonloadSignal(3, ampl, f);
}
void Generator::AddSinglePeriod(double ampl, enum_t f){
    DonloadSignal(4, ampl, f);
}
void Generator::AddRectified(double ampl, enum_t f){
    DonloadSignal(5, ampl, f);
}

void Generator::AddNoiseUniformDist(double ampl, double min,double max){
    DonloadNoise(0,ampl,min,max);
}
void Generator::AddNoiseNormalDist(double ampl,double mean,double sigma){
    DonloadNoise(1,ampl,mean,sigma);
}
void Generator::AddNoiseCauchyDist(double ampl,double shift,double scale){
    DonloadNoise(2,ampl,shift,scale);
}
void Generator::AddNoiseStudentDist(double ampl,double degree_freedom){
    DonloadNoise(3,ampl,degree_freedom);
}
void Generator::AddPinkNoise(double ampl){
    DonloadNoise(4,ampl);
}

double Generator::GetMinValueTime(){
    return *_signal.at(0).begin();
}
double Generator::GetMaxValueTime(){
    return *(_signal.at(0).end() - 1);
}
double Generator::GetMinValueSignal(){
    return *std::min_element(_signal.at(1).begin(),_signal.at(1).end());
}
double Generator::GetMaxValueSignal(){
    return *std::max_element(_signal.at(1).begin(),_signal.at(1).end());
}

void Generator::ResetParameters(enum_t fs, enum_t sample){
    _sample = sample;
    _signal[0].resize(sample);
    _signal[1].resize(sample);
    delete[] _temp;
    _temp = new double[sample];
    gsn::Initialization(sample,fs);
    for(std::uint64_t n = 0; n < sample; n++)
        _signal[0][n] = (double)n/(double)fs;
}

void Generator::Clear(){
    _signal[0].fill(0);
    _signal[1].fill(0);
}

Generator::~Generator(){
    delete _error;
    delete[] _temp;
}
