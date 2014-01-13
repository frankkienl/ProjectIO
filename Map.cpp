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
#include "Map.hpp"
#include "Utility.hpp"
#include <exception>
#include <stdexcept>
#include "ResourceManager.hpp"

namespace io {
  const int32_t MAX_DISTANCE = 64;

  Map* Map::mapFromImage(const std::string& filename) {
    Colour unfilled(200, 200, 250, 255);
    
    Map* newMap = nullptr;
    
    /**
     *  Here's how it works.  RGB(200, 200, 250) is treated as empty.
     *  Anything else, for the time being, is treated as filled.
     *  I recommend using RGB(150, 150, 200) as the filled colour.
     */
    Image* m = ResourceManager::getInstance()->getResource(filename)->toImage();
    if (m) {
      if (m->getWidth() == Map::MAP_WIDTH && m->getHeight() == Map::MAP_HEIGHT) {
        newMap = new Map();
        for (uint32_t y = 0; y < m->getHeight(); y++) {
          for (uint32_t x = 0; x < m->getWidth(); x++) {
            if (m->getPixel(x, y) == unfilled) {
              newMap->setTile(x, y, TILE::OPEN);
            }
            else {
              newMap->setTile(x, y, TILE::SOLID);
            }
          }
        }
      }
      delete m;
    }
    
    return newMap;
  }
  
  void Map::draw(Graphics* g, const uint32_t cx, const uint32_t cy) {
    for (int32_t y = -MAX_DISTANCE; y < MAX_DISTANCE; y++) {
      for (int32_t x = -MAX_DISTANCE; x < MAX_DISTANCE; x++) {
        TILE c = getTile(cx + x, cy + y);
        TILE n = getTile(cx + x, cy + y - 1);
        TILE e = getTile(cx + x + 1, cy + y);
        TILE s = getTile(cx + x, cy + y + 1);
        TILE w = getTile(cx + x - 1, cy + y);
        
        if (c != TILE::SOLID) {
          g->drawFloorTile(x, y, 0);
          g->drawCeilingTile(x, y, 0);

          if (n == TILE::SOLID) {
            g->drawWallTile(x, y, Facing::NORTH, 0);
          }

          if (e == TILE::SOLID) {
            g->drawWallTile(x, y, Facing::EAST, 0);
          }

          if (s == TILE::SOLID) {
            g->drawWallTile(x, y, Facing::SOUTH, 0);
          }

          if (w == TILE::SOLID) {
            g->drawWallTile(x, y, Facing::WEST, 0);
          }
        }
      }
    }
  }
}
