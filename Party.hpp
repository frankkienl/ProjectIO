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
#ifndef PartyHPP
#define PartyHPP

#include "Character.hpp"
#include <cstdint>

namespace io {
  enum class Row {
    FRONT = 0,
    BACK = 1,
  };

  class Party {
  public:
    const static uint8_t PARTY_MAX = 6;

    void addCharacter(const uint8_t index, Character* which) {
      if (index < Party::PARTY_MAX) {
        characters[index] = which;
      }
    }

    void clear() {
      for (uint8_t i = 0; i < Party::PARTY_MAX; i++) {
        characters[i] = nullptr;
      }
    }

    Character* getCharacter(const uint8_t index) {
      if (index < Party::PARTY_MAX) {
        return characters[index];
      }

      return nullptr;
    }

    bool hasCharacter(Character* c) {
      for (uint32_t i = 0; i < Party::PARTY_MAX; i++) {
        if (characters[i] == c) {
          return true;
        }
      }

      return false;
    }

    void removeCharacter(const uint8_t which) {
      if (which < Party::PARTY_MAX) {
        characters[which] = nullptr;
      }
    }

    void swapCharacter(const uint8_t first, const uint8_t second) {
      if (first < Party::PARTY_MAX && second < Party::PARTY_MAX) {
        Character* tmp = characters[first];
        characters[first] = characters[second];
        characters[second] = tmp;
      }
    }
  private:

    Character* characters[Party::PARTY_MAX];
  };
}

#endif
