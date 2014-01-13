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
#ifndef StringTokenizerHPP
#define StringTokenizerHPP

#include <string>
#include <list>

namespace io {
  /*
   * String tokenizer.  Defaults to tokenizing strings with spaces.
   */
  class StringTokenizer {
  public:
    StringTokenizer() : StringTokenizer("") {
    }

    StringTokenizer(const std::string& input, const char delimiter = ' ') {
      tokenize(input, delimiter);
    }

    ~StringTokenizer() {

    }

    std::list<std::string>::iterator begin() noexcept {
      return tokens.begin();
    }

    std::list<std::string>::iterator end() noexcept {
      return tokens.end();
    }

    void tokenize(const std::string& input, const char delimiter = ' ');

    const char getDelimiter() const {
      return delimiter;
    }

    std::string getToken(const uint32_t index) const;

    const uint32_t getTokenCount() const {
      return tokens.size();
    }
  private:
    char delimiter;
    std::list<std::string> tokens;
  };
}

#endif
