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
#ifndef ImageHPP
#define ImageHPP

#include <stdexcept>
#include "Colour.hpp"
#include "Resource.hpp"

namespace io {
/**
 *  @brief  Represents an image buffer that can be modified.
 */
  class Image : public Resource {
  public:
    /**
     *  @brief  Creates a 1x1 sized image.
     */
    Image() : data(nullptr), height(0), width(0) {
      setSize(1, 1);
    }
    
    /**
     *  @brief  Creates an image of the specified dimensions.
     *  @throws std::invalid_argument width == 0 || height == 0 ||
     *          width > MAX_DIM || height > MAX_DIM
     *  @throws std::runtime_error if setSize() returns false.
     */
    Image(const uint32_t width, const uint32_t height) : data(nullptr), height(0), width(0) {
      if (width == 0 || height == 0 || width > Image::MAX_DIM ||
          height > Image::MAX_DIM) {
        throw std::invalid_argument("Image::Image");
      }
      
      if (!setSize(width, height)) {
        throw std::runtime_error("Image::Image");
      }
    }
    
    virtual ~Image() {
      if (data) {
        delete [] data;
        data = nullptr;
      }
    }
    
    uint32_t getHeight() const {
      return height;
    }
    
    Colour getPixel(const uint32_t x, const uint32_t y);
    void getPixel(const uint32_t x, const uint32_t y, uint8_t& r, uint8_t& g,
                  uint8_t& b, uint8_t& a);
  
    uint32_t getWidth() const {
      return width;
    }
    
    bool setSize(const uint32_t width, const uint32_t height);
    void setPixel(const uint32_t x, const uint32_t y, const Colour& pixel);
    void setPixel(const uint32_t x, const uint32_t y, const uint8_t r,
                  const uint8_t g, const uint8_t b, const uint8_t a);

    virtual Image* toImage() {
      return this;
    }
  private:
    const static uint32_t MAX_DIM = 8192;
    
    uint8_t* data;
    uint32_t height;
    uint32_t width;
  };
}

#endif // ImageHPP
