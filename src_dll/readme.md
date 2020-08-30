 ## ������������ � �������� ����� dll ����������.
 ## Documentation for the source code of the dll library.

Source codes can be used to build dlls or to build exe applications.
�������� ���� ����� ���� ������������ ��� ������ dll ��� ��� ������ exe ����������.


 ### ���������� .hpp ������ �������
1. ��������� dll/interface dll
 + [core.hpp](#interface);
2. �������� ������/dataloading
 + [dataloading.hpp](#load);
 + [read_bin.hpp](#read);
 + [data_parameters.hpp](#parameters);
3. ��������������� ����������� / Auxiliary tools
 + [auxiliary_tools.hpp](#tools);
 + [interpolation.hpp](#interp);
 + [vector_operation.hpp](#vec_operat);

 ##### <a name="interface"></a>	   core.hpp - ��������� dll
=========================
eng
The header file of the entire library that provides an interface for building a signal/noise generator.
To build the dll in the "core.hpp" file, you must remove the comments before "#define DLL_MODE_CORE", or declare it before including this file.
You also need to specify the path through "#define FILE_PATH" data/" if the path is not specified, the default is "data/"
Called procedures return status codes of their work.
Status code list
1. - 0xFF: Status undefined(this value must be passed in procedure);
2. - 0x00: Successful completion;
3. - 0x11: No object with the requested number;
4. - 0x33: Invalid frequency;
5. - 0x55: Invalid ratio of the sample rate to the signal frequency;
6. - 0x77: Data file not found .dat;
7. - 0x99: Very high sampling rate relative to the signal frequency. 

procedures:
Initialization : Initializes the internal state of the dll library.
 #### Syntax:
    void Initialization(uint64_t sampl, uint64_t infs);
      Parameters:
sampl - Number of samples
infs - Sampling frequence
  
Signal request function of type "type"
 #### Syntax:
    void Get(double* arr, std::uint16_t type, std::uint64_t f, error_ptr_t error = 0);
Parameters: 
arr  - Pointer to an array(with a size equal to the of samples), into which the signal will be loaded, in case of a successful function execution.
type - Number of the signal(range from 0 to 5).
	Signal types in the library:
		0 - harmonic;
		1 - meander;
		2 - saw;
		3 - triangle;
		4 - single_period;
		5 - rectified.dat.
f     - Signal frequency.
error - If the function fails, it returns an error code.
                      (See error codes above.)
 
 
The function requests the generation of a random process.
 #### Syntax:
    void Noise(double* arr, uint16_t type, double par_0 = 1, double par_1 = 2, error_ptr_t error = 0);
Parameters:
arr - Pointer to an array (with a size equal to the number of samples) into which the random process will be loaded, in cases of successful execution of functions. 
type - Distribution type or noise (range from 0 to 4).
	Distribution and noise types: 
		0 - Uniform distrybution;
		1 - Normal(Gaussian) distrybution;
		2 - Cauchy distribution;
		3 - Student_t distribution;
		4 - pink_noise.
par_0 - first distribution parameter;
par_1 - second distribution parameter;
error - If the function fails, it returns an error code.
                     (See error codes above.)


SwapArr : The function shuffles the elements of the array.
 #### Syntax:
    void SwapArr(double* _array);
Parameters:
_array - Pointer to an array with data.

rus
������������ ���� ���� ����������, ������� ������������� ��������� ��� ���������� ���������� ��������/�����.
��� ������ dll � ����� "core.hpp" ���������� ������ ���������� ����� "#define DLL_MODE_CORE", ���� �������� ��� ����� ���������� ����� �����.
����� ���������� ������� ���� � ������ � ������� ����� "#define FILE_PATH "data/" ���� ���� �� ������ ������������ �� ��������� "data/"
��������� ��������� ���������� ������ ���� �� ������.
Status code list (Required when using the dll) * * * *
1. - 0xFF: ��������� �� ���������� (��� �������� ������ ���� �������� � ���������);
2. - 0x00: �������� ����������;
3. - 0x11: ��� ������� � ������������� �������;
4. - 0x33: ������� ��������� �������;
5. - 0x55: ������������ ��������� Fs/F;
6. - 0x77: ���� � ������� �� ������ .dat;
7. - 0x99: ����� ������� ������� ������������� �� ��������� � ������� �������;
���������:
������������� ����������� ��������� DLL ����������
 #### ���������:
    void Initialization(uint64_t sampl, uint64_t infs);
���������:
sampl - ���������� �������;
infs  - ������� �������������; 
  
������� ������� ������� ���� "type"
 #### ���������:
void Get(double* arr, std::uint16_t type, std::uint64_t f, error_ptr_t error = 0);
���������:
arr  - ��������� �� ������(� �������� ������ ���������� �������) � ������� ����� �������� ������,� ������ ��������� ���������� ���������;
type - ����� �������������� �������(�������� �� 0 �� 5)
���� �������� � ����������:
	0 - harmonic;
	1 - meander;
	2 - saw;
	3 - triangle;
	4 - single_period;
	5 - rectified.dat.
f - ������� �������
error - ������ ���������� ��������� (���� �������� ����)

������� ������� ��������� ���������� ��������
 #### ���������:
    void Noise(double* arr, uint16_t type, double par_0 = 1, double par_1 = 2, error_ptr_t error = 0);
���������
arr - ��������� �� ������(� �������� ������ ���������� �������) � ������� ����� �������� ������,� ������ ��������� ���������� ���������;
type - ��� ������������� ��� ����(�������� �� 0 �� 4)
���� ������������� � �����:
	0 - Uniform distrybution;
	1 - Normal(Gaussian) distrybution;
	2 - Cauchy distribution;
	3 - Student_t distribution;
	4 - pink_noise.
par_0 - ������ �������� �������������;
par_1 - ������ �������� �������������;
error - ������ ���������� ��������� (���� �������� ����)


������� ������������ �������� �������
 #### ���������:
    void SwapArr(double* _array);
���������:  
1 - ��������� �� ������ � �������.


 ##### <a name="load"></a>	   dataloading.hpp - �������� ������
=========================
eng
Reading the data of the requested signal from the file and selecting the one closest to the entered sampling rate "in_fs" from the available set for interpolation(if required)
 #### Syntax:
template<typename T>
    void ReadSignal(std::string name, vec_1d<T>& signal,std::uint64_t  f,std::uint64_t  in_fs,std::uint64_t& out_fs,error_ptr_t error = 0);
Parameters:
name   - file name
signal - reference to the vector in which the signal will be written
f      - signal frequence
in_fs  - original sampling rate
out_fs - Sample rate of the signal that was read
error  - function execution code

Procedure execution codes:
0xFF - status undefined(!!!this value must be passed in function!!!);
0x00 - Successful completion;
0x77 - Data file not found.
0x55 - Invalid ratio of the sample rate to the signal frequency

rus
������ ������ ������������ ������� �� ����� � ����� ��������� �������� ������� ������� ������������� � ��������� "in_fs" �� ���������� ������ ��� ����������� ������������(���� �����������)
 #### ���������:
    void ReadSignal(std::string name, vec_1d<T>& signal,std::uint64_t  f,std::uint64_t  in_fs,std::uint64_t& out_fs,error_ptr_t error = 0);
���������:
name   - ��� �����
signal - ������ �� ������, � ������� ����� ������� ������
f      - ������� �������
in_fs  - �������� ������� �������������
out_fs - ������� ������������� ������������ ������� �� �����
error  - ��� ���������� ���������.

��� ���������� ���������:
0xFF - ������ �� ���������(��� �������� ������ ���� �������� � �������);
0x00 - �������� ����������;
0x77 - ���� ������ �� ������.
0x55 - ������������ ��������� ������� ������������� � ������� �������


 ##### <a name="read"></a>	   read_bin.hpp - ������ �������� ������
=========================
eng
The function of loading data from binary files.
The type of data structure written to the binary file is specified in the function template parameter.
The data structure must have std-style iterators and a begin () method.
 #### Syntax:
    template<template<class ...> class data_ty, typename... T>
    void LoadData(std::string namefile, uint_64c& step_in, data_ty<T...>& data, error_ptr_t error);
Parametrs:
namefile - filename with binary data to load
step_in  - data read step
data     - Link to the data structure "data_ty<T...>" into which the read data will be loaded
error    - function execution code

Procedure execution codes:
0xFF - status undefined(!!!this value must be passed in function!!!);
0x00 - Successful completion;
0x77 - Data file not found.


rus
������� �������� ������ �� �������� �����.
��� ��������� ������ ���������� � �������� ���� ����������� � ��������� ������� �������.
��������� ������ ������ ����� ��������� � ����� ���������� "std", � ����� ����� ����� "begin()".
 #### ���������:
    template<template<class ...> class data_ty, typename... T>
    void LoadData(std::string namefile, uint_64c& step_in, data_ty<T...>& data, error_ptr_t error);
���������:
namefile - ��� ��������� ����� � ������� ��� ��������;
step_in  - ��� ������ ������;
data     - ������ �� ��������� ������ "data_ty<T...>" � ������� ����� ��������� ����������� ������;
error    - ��� ���������� ���������.

��� ���������� ���������:
0xFF-������ �� ���������(!!!��� �������� ������ ���� �������� � �������!!!);
0x00-�������� ����������;
0x77-���� ������ �� ������.

 ##### <a name="parameters"></a>   data_parameters - ��������� ���������� ������ � ����
=========================
eng\
Parameters of recorded signals in binary files.
All data parameter declarations are located in the "ld::dp" namespace\
ld - loading data, dp - data parameters.
Parameters of recorded signals:
f  - frequency of the recorded signal;
fs - sample rate;
ratio_f - the ratio of the signal frequency to the sample rate;
sample  - total signal counts recorded in the file;
sample_period - counts the signal for a single period.


rus\
��������� ���������� �������� � �������� �����.
��� ���������� ���������� ������ ��������� � ������������ ���� "ld::dp"\
����������� ����������� ���� ld - loading data, dp - data parameters.
��������� ���������� ��������:
f - ������� ����������� �������;
fs - ������� �������������;
ratio_f - ��������� ������� ������� � ������� �������������;
sample  - ����� �������� ������� ���������� � ����;
sample_period - �������� ������� �� ���� ������.

 ### <a name="tools"></a>	   auxiliary_tools.hpp - ����� ��������������� ������������
=========================
[eng]
All auxiliary tools are located in the "atl" namespace (namespace auxiliary tool library)\
 #### Functions and procedures:
Round a number to the nearest from an vector/���������� ����� � ���������� �� �������\
 #### Syntax:
    template<typename T0, typename T1>
    it_vec<T0> RoundingDivider( it_vec<T0> it_first, it_vec<T0> it_last,T1 number, enum_t size = 0);
When calling the function, you must explicitly specify template parameters!
example call:
    rounding_divider<T0,T1>(...);
Parametrs:
it_first,it_last - first and last iterator on vector;
number           - The number to be rounded;
size             - Vector size.

=========================
Extracts an interval of type (a: b] or [a: b) from a vector and searches for a number in this interval closest to "a" or closest to "b", returns an iterator to an array element that is close ( or which is) to the desired number.
 #### Syntax:
    	template<typename T0, typename T1>
	it_vec<T0> Nearest(vec1d_tmp<T0>& arr,T1 num_0,T1 num_1,bool on_of = true,bool direction = true);
Parametrs:
arr         - Reference to the vector from which the interval is selected
num_0,num_1 - Interval start/end
on_of       - Turn on-off (start-end) interval
direction   - Aim towards "false" - minus infinity, "true" - plus infinity.

=========================
Dividing a signal into segments and interpolating it for a new sample rate
 #### Syntax:
    template<typename T>
    void ILagPiecewise(vec2d_tmp<T>& f,vec2d_tmp<T>& f_out,uint64_t fs,uint64_t window = 4 );
Parametrs:
f      - reference to the vector of the original signal
f_out  - A reference to the vector to which the interpolation result will be written
fs     - New sampling rate
window - Size of the window for splitting
 [rus]
=========================
 ��� ��������������� ����������� ��������� � ������������ ���� "atl" (������������ ���� auxiliary tool library)\
 #### ������� � ���������:\
���������� ����� � ���������� �� �������\
 #### ���������
    template<typename T0, typename T1>
    it_vec<T0> RoundingDivider( it_vec<T0> it_first, it_vec<T0> it_last,T1 number, enum_t size = 0);
��� ������ ������� ���������� ���� ������� ��������� ��������!
������ ������:
    rounding_divider<T0,T1>(...);
���������:
it_first,it_last - ������ � ��������� �������� �� ������ � ����������
number           - ����������� �����
size             - Vector size.

=========================
�������� �������� ���� (a:b] ��� [a:b) �� ������� � ���� ����� � ���� ��������� ��������� � "a" ���� ��������� � "b", ���������� �������� �� ������� ������� ������� ������(��� ������� ��������) � �������� �����
 #### ���������:
    	template<typename T0, typename T1>
	it_vec<T0> Nearest(vec1d_tmp<T0>& arr,T1 num_0,T1 num_1,bool on_of = true,bool direction = true);
���������:
arr 	    - ������ �� ������ �� �������� ���������� �������� ����� ����� num_0, num_1
num_0,num_1 - ������/����� ���������
on_of 	    - ��������-��������� (������-�����) ���������
direction   - ��������� � ������� false-����� �������������, true-���� �������������

=========================
��������� �� �������� ������� � ���������������� ��� ��� ����� ������� �������������
 #### ���������:
    template<typename T>
    void ILagPiecewise(vec2d_tmp<T>& f,vec2d_tmp<T>& f_out,uint64_t fs,uint64_t window = 4 );
���������:
f      - ������ �� ������ ��������� �������
f_out  - ������ �� ������, � ������� ����� ������� ��������� ������������
fs     - ����� ������� �������������
window - ������ ���� ���������


 ##### <a name="interp"></a>	   interpolation.hpp - ��������� ��� ������������ �������
=========================

 #### ���������/Syntax:
    void L_I(const vec2d_dty& f_in,const vec1d_dty& x, vec2d_dty& f_out);\

Function interpolation by Lagrange polynomial. \
Parameters: 1. f_in  - Reference to the vector of the original function. \
	    2. x     - A reference to a vector with points where you want to define the function. \
	    3. f_out - A reference to the vector to which the interpolation result will be written. \

������������ ������� ��������� �������� \
���������: 1. f_in  - ������ �� ������ �������� �������; \
	   2. x     - ������ �� ������ � �������, � ������� ���������� ���������� �������; \
	   3. f_out - ������ �� ������, ��� ������ ���������� ������������. \



 ##### <a name="vec_operat"></a>   vector_operation.hpp - ����������� ����� ��� �������� ��� ���������
=========================
[eng]
Static class of operations on 1D/2D vectors
metodth: 
+ Quick removal of an item by its index
Syntax:	  
    void QuickRemove(vec1d& in_vec, std::size_t inx);
Parametrs: 
in_vec - Reference to the vector where you want to remove the element
inx    - The index of the item in the vector
+ Transpose 2D vector elements
    void Transposition(vec2d& in_vec);
Parametrs:
in_vec - Reference to the 2D vector to be transposed
=====================
##### The following functions have the same internal structure and differ only in the operation performed.
 + Sum/Difference/Multiplication/Division all elements of the input "vec" 1D vector, and returns the result. 
Syntax:	 
    T Sum(vec1d& vec)
    T Difference(vec1d& vec)
    T Multiplication(vec1d& vec)
    T Division(vec1d& vec)
Parametrs: vec - Reference to the vector whose elements you want to perform the operation on.

* * * Overloads, for 2D vectors * * * 
+ Sum/Difference/Multiplication/Division all row elements of the input" in_vec "2D vector and returns the result in the" out_vec " 1D vector.
Syntax:	
    void Sum(vec2d& in_vec, vec1d& out_vec);
    void Difference(vec2d& in_vec, vec1d& out_vec);
    void Multiplication(vec2d& in_vec, vec1d& out_vec);
    void Division(vec2d& in_vec, vec1d& out_vec);
Parametrs:
in_vec  - Reference to the vector whose elements you want to perform the operation on.
out_vec - A reference to the 1D vector in which the result of the operation will be written.
	  The size of the 1D vector must be equal to the number of rows of the 2D vector!

[rus]
����������� ����� �������� ��� 1D/2D ���������
������:
 + ������� �������� �������� ������� �� �������
���������:
    void QuickRemove(vec1d& in_vec, std::size_t inx);
���������:
in_vec - ������ �� ������, � ������� ��������� ������� �������
inx    - ������ �������� � �������
================
 + ���������������� ��������� 2D �������
���������:
    void Transposition(vec2d& in_vec);
���������:
in_vec - ������ �� 2D ������ ������� ����� ���������������
===============
##### ������������� ������� �������� �� ���������� ��������, � ���������� ������ ����������� ���������
+ �����/��������/������������/��������� ���� ��������� �������� "vec" 1D �������, � ����������� ����������.
���������:
    T Sum(vec1d& vec);
    T Difference(vec1d& vec);
    T Multiplication(vec1d& vec);
    T Division(vec1d& vec);
���������:
vec - ������ �� ������, � ���������� �������� �� ������ ��������� ��������.

* * * ����������� ��� 2D �������� * * * 
+ �����/��������/������������/��������� ���� ��������� ����� �������� "in_vec" 2D ������� � ���������� ��������� � "out_vec" 1D ������.
���������:
    void Sum(vec2d& in_vec, vec1d& out_vec);
    void Difference(vec2d& in_vec, vec1d& out_vec);
    void Multiplication(vec2d& in_vec, vec1d& out_vec);
    void Division(vec2d& in_vec, vec1d& out_vec);
���������:
in_vec  - ������ �� ������, � ���������� �������� �� ������ ��������� ��������
out_vec - ������ �� 1D ������, � ������� ����� ������� ��������� ��������.
	  ������ 1D ������� ������ ���� ����� ���������� ����� 2D �������!