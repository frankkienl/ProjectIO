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
#ifndef ColourHPP
#define ColourHPP

#include <cstdint>

namespace io {
  class Colour {
  public:
    Colour() {
      setColour(0, 0, 0, 255);
    }

    Colour(const uint8_t r, const uint8_t g, const uint8_t b) {
      setColour(r, g, b, 255);
    }
    
    Colour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
      setColour(r, g, b, a);
    }
    
    Colour(const Colour& rhs) {
      setColour(rhs.getR(), rhs.getG(), rhs.getB(), rhs.getA());
    }
    
    bool operator==(const Colour& rhs) {
      return (getR() == rhs.getR() && getG() == rhs.getG() &&
              getB() == rhs.getB() && getA() == rhs.getA());
    }

    Colour& operator=(const Colour& rhs) {
      if (&rhs != this) {
        setColour(rhs.getR(), rhs.getG(), rhs.getB(), rhs.getA());
      }

      return *this;
    }
    
    uint8_t getA() const {
      return this->a;
    }

    uint8_t getB() const {
      return this->b;
    }

    uint8_t getG() const {
      return this->g;
    }

    uint8_t getR() const {
      return this->r;
    }
  private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    void setColour(const int32_t r, const int32_t g, const int32_t b, const int32_t a);
    uint8_t clamp(const int32_t value);
  };
}

#endif
