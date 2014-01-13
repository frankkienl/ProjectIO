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
#ifndef GuildHPP
#define GuildHPP

#include "Character.hpp"
#include <string>

namespace io {
  class Guild {
  public:
    const static uint32_t MAX_CHARACTERS = 30;

    Guild() {
      characterCount = 0;
      for (uint32_t i = 0; i < Guild::MAX_CHARACTERS; i++) {
        characters[i] = nullptr;
      }
    }

    void addCharacter(Character* which) {
      if (characterCount < Guild::MAX_CHARACTERS) {
        for (uint32_t i = 0; i < Guild::MAX_CHARACTERS; i++) {
          if (characters[i] == nullptr) {
            characters[i] = which;
            characterCount++;
            break;
          }
        }
      }
    }

    bool canCreateNewCharacter() const {
      return (getCharacterCount() < MAX_CHARACTERS);
    }

    Character* getCharacter(const uint32_t which) {
      if (which < Guild::MAX_CHARACTERS) {
        return characters[which];
      }

      return nullptr;
    }

    uint32_t getCharacterCount() const {
      return characterCount;
    }

    std::string getName() const {
      return name;
    }

    void removeCharacter(Character* which) {
      for (uint32_t i = 0; i < Guild::MAX_CHARACTERS; i++) {
        if (characters[i] == which) {
          characters[i] = nullptr;
          characterCount--;
        }
      }
    }

    void setName(const std::string& name) {
      this->name = name;
    }
  private:
    Character* characters[Guild::MAX_CHARACTERS];
    uint32_t characterCount;
    std::string name;
  };
}

#endif
