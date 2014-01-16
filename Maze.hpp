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
#ifndef MazeHPP
#define MazeHPP

#include <list>
#include <string>
#include "Map.hpp"

namespace io {
  /**
   * Represents a multi-floor maze.  Not much to say about it.
   */
  class Maze {
  public:
    Maze() {

    }

    static Maze* mazeFromXML(const std::string& filename);

    ~Maze() {
      for (Map* m : floors) {
        delete m;
      }
      floors.clear();
    }

    //  Floors are 1-indexed.  Floor 0 indicates the town.
    Map* getFloor(const uint32_t which) {
      if (which == 0 || which > floors.size()) {
        return nullptr;
      }

      return floors.at(which - 1);
    }

    uint32_t getFloorCount() const {
      return floors.size();
    }
  private:
    std::vector<Map*> floors;
  };
}

#endif
