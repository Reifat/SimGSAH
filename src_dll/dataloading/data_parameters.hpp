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

#ifndef DATA_PARAMETERS_HPP
#define DATA_PARAMETERS_HPP

#include <cstdint>
#include <vector>

/* Parameters for recorded data files
 * Параметры для записанных файлов с данными
 */
namespace ld { // namespace loading data
	namespace dp { // namespace data parameters
               extern const std::uint32_t f;
               extern const std::uint32_t fs;
               extern const std::uint32_t ratio_f;
               extern const std::uint32_t sample;
               extern const std::uint32_t sample_period;
               extern std::vector<std::uint32_t> dividers;
	} // end namespace data parameters
} // end namespace loading data

#endif
