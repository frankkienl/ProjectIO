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
            //  We offset by 1 to account for the border.
            if (m->getPixel(x, y) == unfilled) {
              newMap->getCell(x + 1, y + 1).setSolid(false);
            }
            else {
              newMap->getCell(x + 1, y + 1).setSolid(true);
            }
          }
        }
      }
      delete m;
    }
    
    return newMap;
  }
  
  void Map::draw(Graphics* g, const uint32_t cx, const uint32_t cy) {
    for (int8_t y = -MAX_DISTANCE; y < MAX_DISTANCE; y++) {
      for (int8_t x = -MAX_DISTANCE; x < MAX_DISTANCE; x++) {
        if (!isCellSolid(cx + x, cy + y)) {
          g->drawFloorTile(x, y, 0);
          g->drawCeilingTile(x, y, 0);

          /*
           * Remember, the get*Wall() methods return the wall you'd see if you
           * were facing the cell from that direction.  If we're to the east
           * of the current cell, and facing it(We're facing west), we want
           * the EAST wall of the cell.
           */

          uint8_t wallID;
          if (isCellSolid(cx + x, cy + y - 1)) {
            wallID = getCell(cx + x, cy + y - 1).getSouthWall();
            g->drawWallTile(x, y, Facing::NORTH, wallID);
          }

          if (isCellSolid(cx + x + 1, cy + y)) {
            wallID = getCell(cx + x + 1, cy + y).getWestWall();
            g->drawWallTile(x, y, Facing::EAST, wallID);
          }

          if (isCellSolid(cx + x, cy + y + 1)) {
            wallID = getCell(cx + x, cy + y + 1).getNorthWall();
            g->drawWallTile(x, y, Facing::SOUTH, wallID);
          }

          if (isCellSolid(cx + x - 1, cy + y)) {
            wallID = getCell(cx + x - 1, cy + y).getEastWall();
            g->drawWallTile(x, y, Facing::WEST, wallID);
          }
        }
      }
    }
  }
}
