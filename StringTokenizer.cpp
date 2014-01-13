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
#include "StringTokenizer.hpp"
#include <stdexcept>

namespace io {
  std::string StringTokenizer::getToken(const uint32_t index) const {
    if (index >= tokens.size()) {
      throw std::out_of_range("StringTokenizer::getToken");
    }

    std::list<std::string>::const_iterator iter = tokens.cbegin();
    for (uint32_t i = 0; i < index; i++) {
      iter++;
    }

    return *iter;
  }

  void StringTokenizer::tokenize(const std::string& input, char delimiter) {
    tokens.clear();

    bool in = false;
    std::string token = "";
    for (char c : input) {
      if (c == delimiter && in) {
        tokens.push_back(token);
        token.clear();
        in = false;
      }

      if (c != delimiter) {
        token.push_back(c);
        in = true;
      }
    }

    if (token.size() > 0) {
      tokens.push_back(token);
    }

    this->delimiter = delimiter;
  }
}
