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
#ifndef TilesetHPP
#define TilesetHPP

#include <map>
#include "Mesh.hpp"

namespace io {
  class Tileset {
  public:
    void addMesh(const uint32_t id, Mesh* mesh) {
      meshes[id] = mesh;
    }

    Mesh* getMesh(const uint32_t id) const {
      if (meshes.count(id) > 0) {
        return meshes.at(id);
      }

      return nullptr;
    }
  private:
    std::map<uint32_t, Mesh*> meshes;
  };
}

#endif // TilesetHPP
