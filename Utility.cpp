/*
 * Copyright 2013 Cepheid
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
*/
#include "Utility.hpp"
#include <cctype>
#include <stdexcept>

namespace io {

  uint8_t hexToNibble(const char hex);

  //  This is honestly the absolute, 100% safest way I could do this.
  uint8_t hexToByte(const char upper, const char lower) {
    return (hexToNibble(upper) << 4 | hexToNibble(lower));
  }

  uint8_t hexToNibble(const char hex) {
    if (isxdigit(hex)) {
      if (isdigit(hex)) {
        return hex - '0';
      } else {
        return tolower(hex) - 'a';
      }
    }

    return 0;
  }

  float toRadians(float degrees) {
    return ((degrees * M_PI) / 180.0f);
  }

  float toDegrees(float radians) {
    return ((radians * 180.0f) / M_PI);
  }
  
  /**
   * @brief Returns the minimum power of two that is greater than the input value.
   * @returns The largest power of two integer that is greater than the input.
   * @throws std::range_error if the power of two is greater than 2^32.
   */
  uint32_t minPowerOfTwo(const uint32_t in) {
    uint32_t ret = 1;
    uint32_t curPower = 0;
    
    while (ret < in && curPower < 32) {
      curPower++;
      ret *= 2;
    }
    
    if (curPower >= 32) {
      throw std::range_error("minPowerOfTwo");
    }
    
    return ret;
  }
}
