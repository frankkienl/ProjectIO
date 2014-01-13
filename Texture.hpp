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
#ifndef TextureHPP
#define TextureHPP

#include <cstdint>
#include <string>
#include "Common.hpp"
#include "Image.hpp"

namespace io {
  class Texture {
  public:
    Texture(Image* inImage);
    ~Texture();

    uint32_t getHeight() const {
      return height;
    }

    uint32_t getWidth() const {
      return width;
    }

    void makeActive();
  private:
    uint8_t* data;
    uint32_t height;
    GLuint texID;
    uint32_t width;
  };
}

#endif
