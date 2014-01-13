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
#include <stdexcept>
#include <cstdio>
#include "Texture.hpp"

namespace io {
  //FIXME:  This needs serious re-working.  It works for now, though.
  Texture::Texture(Image* image) {
    if (!image) {
      throw std::invalid_argument("Texture::Texture");
    }
    
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    
    data = new uint8_t[image->getWidth() * image->getHeight() * 4];
    for (uint32_t y = 0; y < image->getHeight(); y++) {
      for (uint32_t x = 0; x < image->getWidth(); x++) {
        uint32_t index = (y * image->getWidth() * 4) + (x * 4);
        uint8_t r, g, b, a;
        image->getPixel(x, y, r, g, b, a);
        data[index] = r;
        data[index + 1] = g;
        data[index + 2] = b;
        data[index + 3] = a;
      }
    }
    
    width = image->getWidth();
    height = image->getHeight();
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  }
    

  Texture::~Texture() {
    if (data) {
      glDeleteTextures(1, &texID);
      delete [] data;
    }
  }

  void Texture::makeActive() {
    glBindTexture(GL_TEXTURE_2D, texID);
  }
  /*
      glGenTextures(1, &(newTex->texID));
      glBindTexture(GL_TEXTURE_2D, newTex->texID);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newTex->getWidth(), newTex->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  */
}
