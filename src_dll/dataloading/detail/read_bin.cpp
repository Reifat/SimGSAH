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

#ifndef READ_BIN_CPP
#define READ_BIN_CPP

#include "src_dll\dataloading\read_bin.hpp"


namespace ld { // namespace data loading
    void LoadData(std::string namefile, uint_64c& step_in, data_t& data, error_ptr_t error) {
		
		if (error != 0) {
			if ((*error != 0xFF) & (*error != 0x00))
				return;
		}
	
		std::ifstream finput(namefile, std::ios_base::in | std::ios_base::binary);
		if (finput.is_open()) {
			std::uint64_t size_ty = sizeof(double); // size data type in vector(vector - data)
			std::uint64_t step = 1;				    // step data read
			if (step_in > 1)					    // in case more
				step = size_ty * step_in - 8;

			std::uint64_t n = 0;
			double temp = 0;
			while (finput.read((char*)&temp, size_ty) && n < data.size()) {
				data.at(n) = temp;
				finput.seekg(step, std::ios_base::cur);
				n++;
			}
			finput.close();
		}
		else {
			if (error != 0) { // If addres pointer !=0 (Если адрес указателя != 0)
				*error = 0x77; // Set error code: file not found;
				return;
			}
		}
		if (error != 0) {
			if (*error == 0xFF) // Предполагаем если 0x00 был ранее записан, то перезапись не требуется
				*error = 0x00;
		} 
	}
} // end namespace ld

#endif
