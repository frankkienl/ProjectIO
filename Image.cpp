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
#include "Image.hpp"
#include <cstring>

namespace io {
  Colour Image::getPixel(const uint32_t x, const uint32_t y) {
    if (x < getWidth() && y < getHeight()) {
      uint32_t index = (y * getWidth() * 4) + (x * 4);
      return Colour(data[index], data[index + 1], data[index + 2], data[index + 3]);
    }
    
    return Colour(0, 0, 0, 0);
  }

  /**
   *  @brief  Obtains the colour of the specified pixel.
   *  Obtains the colour of the specified pixel, and stores the values in r, g,
   *  b and a.  If the specified pixel is outside the bounds, the outputs will
   *  be assigned the value 0.
   */
  void Image::getPixel(const uint32_t x, const uint32_t y, uint8_t& r,
                        uint8_t& g, uint8_t& b, uint8_t& a) {
    if (x < getWidth() && y < getHeight()) {
      uint32_t index = (y * getWidth() * 4) + (x * 4);
      r = data[index];
      g = data[index + 1];
      b = data[index + 2];
      a = data[index + 3];
    }
    else {
      r = 0;
      g = 0;
      b = 0;
      a = 0;
    }
  }
  
  void Image::setPixel(const uint32_t x, const uint32_t y, const Colour& pixel) {
    if (x < getWidth() && y < getHeight()) {
      uint32_t index = (y * getWidth() * 4) + (x * 4);
      data[index] = pixel.getR();
      data[index + 1] = pixel.getG();
      data[index + 2] = pixel.getB();
      data[index + 3] = pixel.getA();
    }
  }
  
  /**
   *  @brief  Sets the pixel at the specified coordinate to the specified
   *          colour.
   */
  void Image::setPixel(const uint32_t x, const uint32_t y, const uint8_t r,
                       const uint8_t g, const uint8_t b, const uint8_t a) {
    if (x < getWidth() && y < getHeight()) {
      uint32_t index = (y * getWidth() * 4) + (x * 4);
      data[index] = r;
      data[index + 1] = g;
      data[index + 2] = b;
      data[index + 3] = a;
    }
  }
  
  /**
   *  @brief  Sets the image to the specified dimensions.
   *  @return true on success, false otherwise.  If false, the previous image
   *          is undamaged.
   */
  bool Image::setSize(const uint32_t width, const uint32_t height) {
    try {
      if (width == 0 || height == 0 || width > Image::MAX_DIM ||
          height > Image::MAX_DIM) {
        throw std::invalid_argument("Image::setSize");
      }
      
      uint8_t* tmp = new uint8_t[width * height * 4];
      ::memset(tmp, 0, width * height * 4);
      
      if (data) {
        delete [] data;
        data = nullptr;
      }
      
      data = tmp;
      this->width = width;
      this->height = height;
    }
    catch (std::exception&) {
      return false;
    }
    
    return true;
  }
}
