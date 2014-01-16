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
#include "Maze.hpp"
#include "tinyxml2.h"
#include "Log.hpp"
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace tinyxml2;

namespace io {
  Maze* Maze::mazeFromXML(const std::string& filename) {
    Maze* newMaze = nullptr;

    try {
      XMLDocument doc;
      if (doc.LoadFile(filename.c_str()) == XML_SUCCESS) {
        XMLElement* root = doc.RootElement();

        if (!root || std::string(root->Name()).compare("maze") != 0) {
          throw std::runtime_error("Maze::mazeFromXML():  Not a maze file.");
        }

        XMLElement* floorElement = root->FirstChildElement("floor");
        if (!floorElement) {
          throw std::runtime_error("Maze::mazeFromXML():  Empty maze.");
        }

        newMaze = new Maze();

        while (floorElement) {
          if (!floorElement->GetText()) {
            throw std::runtime_error("Maze::mazeFromXML():  Empty floor element.");
          }

          Map* floor = Map::mapFromXML(floorElement->GetText());
          if (!floor) {
            throw std::runtime_error("Maze::mazeFromXML():  Could not load a floor.");
          }

          newMaze->floors.push_back(floor);

          floorElement = floorElement->NextSiblingElement("floor");
        }
      }
    }
    catch (std::exception& e) {
      if (newMaze) {
        delete newMaze;
        newMaze = nullptr;
      }

      writeToLog(MessageLevel::ERROR, "%s\n", e.what());
    }

    return newMaze;
  }
}
