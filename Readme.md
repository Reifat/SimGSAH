﻿ ### SimGSAH - Simulator signal generator and analysis of their main characteristics
 
#### Содержание:
1. [Общие сведения](#gen_inform)
2. [Исходные файлы .dll]
3. [LabVIEW build и исходник GUI]
4. [QT example]
5. [LabView demo](#LV_demo)
6. [QT demo](#QT_demo)
 
#### <a name = "gen_inform"></a>    Общие сведения (Rus)
Программа создана в образовательных целях.\
Предназначена для лабораторных работ студентов младших и средних курсов по специальности радиотехника, а также для специальностей связанных с электрорадиоаппаратурой.\
Программа имеет генератор типовых сигналов, и случайных процессов(шумов) с задаваемыми параметрами. Количество генерируемых сигналов генератором задается и может быть изменено при работе. Все сгенерированные сигналы суммируются и поступают на выход генератора.\
Для анализа характеристик полученного сигнала, в программе имеется гистограмма, осциллограф, а также анализатор спектра.\
###### Примечания
Разработанная программа была выполнена на двух языках программирования C++ и G(LabVIEW).\
С++ использован для снижения нагрузки на ПК, которая возникает при большом количесве генерируемых сигналов. Все устройство генератора сигналов/шумов вынесено в dll библиотеку.\
G(labview) был применен для пользовательского интерфейса. На нем реализованы приборы анализа основных характеристик сигналов, а также оболочка для генератора с которой взаимодействует пользователь.\
Для более существенной разгрузки ПК, все сигналы в высоком разрешении зарание были записаны в бинарные файлы. При запросе пользователем необходимого сигнала, он считывается из файла и масштабируется под необходимые параметры.\
Исходные коды dll библиотеки могут быть использованы для расшинения имеющегося или построения более сложного генератора сигналов. Простой пример показан в разделе "qt_example".

#### General information (Eng)
The program was created for educational purposes.\
It is intended for laboratory work of students of Junior and secondary courses in the specialty of radio engineering, as well as for specialties related to electrical and radio equipment.\
The program has a generator of typical signals and random processes (noise) with set parameters. The number of signals generated by the generator is set and can be changed during operation. All generated signals are summed up and fed to the generator output.\
To analyze the characteristics of the received signal, the program has a histogram, an oscilloscope, and a spectrum analyzer.
###### Notes
The developed program was implemented in two programming languages C++ and g (LabVIEW).\
C++ is used to reduce the load on the PC, which occurs when a large number of generated signals.The entire signal/noise generator device is stored in the dll library.\
G (labview) was used to implement the user interface.It implements devices for analyzing the main characteristics of signals, as well as a shell for the generator that the user interacts with.\
For more significant PC offloading, all signals in high resolution in advance were recorded in binary files. When a user requests the required signal, it is read from the file and scaled to the required parameters.\
The source code of the dll library can be used to expand an existing one or build a more complex signal generator.A simple example is shown in the "qt_example" section.


#### <a name = "LV_demo"></a>    LabView demo
![LabView_demo]
 
#### <a name = "QT_demo"></a>    C++ QT demo
![QT_demo]

[Исходные файлы .dll]:https://github.com/Reifat/SimGSAH/tree/master/src_dll
[LabVIEW build и исходник GUI]:https://github.com/Reifat/SimGSAH/tree/master/src_labview
[QT example]:https://github.com/Reifat/SimGSAH/tree/master/qt_example
[LabView_demo]:https://raw.githubusercontent.com/Reifat/SimGSAH/master/pictures/Meander%20plus%20noise.PNG
[QT_demo]:https://raw.githubusercontent.com/Reifat/SimGSAH/master/pictures/Qt_example.PNG
