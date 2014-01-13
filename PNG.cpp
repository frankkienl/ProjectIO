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
#include "PNG.hpp"
#include <libpng16/png.h>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

namespace io {
  Image* loadPNG(const std::string& filename) {
    Image* ret = nullptr;
    path p(filename);
    if (exists(p) && is_regular_file(p)) {
      png_image image;
      memset(&image, 0, sizeof(png_image));
      image.version = PNG_IMAGE_VERSION;
      uint8_t* data = nullptr;
      
      try {
        png_image_begin_read_from_file(&image, filename.c_str());
        
        if (image.warning_or_error != 0) {
          throw std::runtime_error("::loadPNG");
        }
        
        image.format = PNG_FORMAT_RGBA;

        data = new uint8_t[PNG_IMAGE_SIZE(image)];
        png_image_finish_read(&image, nullptr, data, 0, nullptr);
        if (image.warning_or_error != 0) {
          throw std::runtime_error("::loadPNG");
        }

        ret = new Image(image.width, image.height);
        for (uint32_t y = 0; y < image.height; y++) {
          for (uint32_t x = 0; x < image.width; x++) {
            uint32_t index = (y * image.width * 4) + (x * 4);
            uint8_t r = data[index];
            uint8_t g = data[index + 1];
            uint8_t b = data[index + 2];
            uint8_t a = data[index + 3];
            
            ret->setPixel(x, y, r, g, b, a);
          }
        }

        delete [] data;
        data = nullptr;
        png_image_free(&image);
      }
      catch (std::exception&) {
        if (data) {
          delete [] data;
          data = nullptr;
        }
        
        if (image.opaque) {
          png_image_free(&image);
        }
      }
    }
    
    return ret;
  }
}
