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
#ifndef MapHPP
#define MapHPP

#include "Graphics.hpp"
#include <string>
#include <cstdint>

namespace io {
  enum class TILE : uint8_t {
    SOLID = 0,
    OPEN = 1,
    TILE_MAX = 2
  };

  /**
   * Represents a map.  Currently hard-coded to 35 * 30 units in size.
   */
  class Map {
  public:
    const static uint32_t MAP_WIDTH = 35;
    const static uint32_t MAP_HEIGHT = 30;

    Map() {
      for (uint32_t y = 0; y < Map::MAP_HEIGHT; y++) {
        for (uint32_t x = 0; x < Map::MAP_WIDTH; x++) {
          setTile(x, y, TILE::SOLID);
        }
      }
    }

    static Map* mapFromImage(const std::string& filename);
    
    void draw(Graphics* g, const uint32_t x, const uint32_t y);

    TILE getTile(const uint32_t x, const uint32_t y) {
      if (x < Map::MAP_WIDTH && y < Map::MAP_HEIGHT) {
        return tiles[y][x];
      }

      return TILE::SOLID;
    }

    void setTile(const uint32_t x, const uint32_t y, const TILE tile) {
      if (x < Map::MAP_WIDTH && y < Map::MAP_HEIGHT) {
        tiles[y][x] = tile;
      }
    }
  private:
    TILE tiles[MAP_HEIGHT][MAP_WIDTH];
  };
}
#endif // mapHPP
