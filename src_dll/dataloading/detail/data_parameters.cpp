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

#ifndef DATA_PARAMETERS_CPP
#define DATA_PARAMETERS_CPP

#include "src_dll\dataloading\data_parameters.hpp"

namespace ld { // namespace data loading
	namespace dp { // namespace data parameters
               const std::uint32_t f = 1;
               const std::uint32_t fs = 720720;
			   const std::uint32_t ratio_f = 720720;	// The ratio of the sample rate to the signal frequency
               const std::uint32_t sample = 720720;
               const std::uint32_t sample_period = 720720;
               std::vector<std::uint32_t> dividers = {
		  	   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, 21, 22, 24, 26, 28, 30, 33, 35,
		  	   36, 39, 40, 42, 44, 45, 48, 52, 55, 56, 60, 63, 65, 66, 70, 72, 77, 78, 80, 84, 88, 90, 91, 99,
		  	   104, 105, 110, 112, 117, 120, 126, 130, 132, 140, 143, 144, 154, 156, 165, 168, 176, 180, 182, 195,
		       198, 208, 210, 220, 231, 234, 240, 252, 260, 264, 273, 280, 286, 308, 312, 315, 330, 336, 360, 364,
		       385, 390, 396, 420, 429, 440, 455, 462, 468, 495, 504, 520, 528, 546, 560, 572, 585, 616, 624, 630,
		       660, 693, 715, 720, 728, 770, 780, 792, 819, 840, 858, 880, 910, 924, 936, 990, 1001, 1008, 1040, 1092,
		       1144, 1155, 1170, 1232, 1260, 1287, 1320, 1365, 1386, 1430, 1456, 1540, 1560, 1584, 1638, 1680, 1716,
		       1820, 1848, 1872, 1980, 2002, 2145, 2184, 2288, 2310, 2340, 2520, 2574, 2640, 2730, 2772, 2860, 3003,
		       3080, 3120, 3276, 3432, 3465, 3640, 3696, 3960, 4004, 4095, 4290, 4368, 4620, 4680, 5005, 5040, 5148,
		       5460, 5544, 5720, 6006, 6160, 6435, 6552, 6864, 6930, 7280, 7920, 8008, 8190, 8580, 9009, 9240, 9360,
		       10010, 10296, 10920, 11088, 11440, 12012, 12870, 13104, 13860, 15015, 16016, 16380, 17160, 18018, 18480,
		       20020, 20592, 21840, 24024, 25740, 27720, 30030, 32760, 34320, 36036, 40040, 45045, 48048, 51480, 55440,
		       60060, 65520, 72072, 80080, 90090, 102960, 120120, 144144, 180180, 240240, 360360, 720720
		};
	} // end namespace data parameters
} // end namespace dl

#endif
