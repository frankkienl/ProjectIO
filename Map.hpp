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
   * A MapCell represents a single cell in a map.  The resource IDs represent
   * how the cell looks from the outside, not from the inside.  Thus, when the
   * player is standing to the north, looking south, they will be seeing the
   * north facing resource of the cell.
   */
  class MapCell {
  public:
    uint8_t getCellCeiling() const {
      return cellCeiling;
    }

    uint8_t getCellFloor() const {
      return cellFloor;
    }

    uint8_t getEastWall() const {
      return eastWall;
    }

    uint8_t getNorthWall() const {
      return northWall;
    }

    uint8_t getSouthWall() const {
      return southWall;
    }

    uint8_t getWestWall() const {
      return westWall;
    }

    bool isSolid() const {
      return solid;
    }

    void setCellCeiling(const uint8_t cellCeiling) const {
      this->cellCeiling = cellCeiling;
    }

    void setCellFloor(const uint8_t cellFloor) const {
      this->cellFloor = cellFloor;
    }

    void setEastWall(const uint8_t eastWall) const {
      this->eastWall = eastWall;
    }

    void setNorthWall(const uint8_t northWall) const {
      this->northWall = northWall;
    }

    void setSouthWall(const uint8_t southWall) const {
      this->southWall = southWall;
    }

    void setWestWall(const uint8_t westWall) const {
      this->westWall = westWall;
    }

    void setSolid(bool solid) {
      this->solid = solid;
    }
  private:
    uint8_t cellCeiling;
    uint8_t cellFloor;
    uint8_t eastWall;
    uint8_t northWall;
    uint8_t southWall;
    uint8_t westWall;
    bool solid;
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
