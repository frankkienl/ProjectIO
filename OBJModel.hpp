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
#ifndef OBJModelHPP
#define OBJModelHPP

#include <string>
#include <vector>
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Mesh.hpp"
#include "Resource.hpp"

namespace io {
  /**
   * This holds the definition of a face.  Not much else to it.
   */
  class OBJFace {
  public:
    int32_t getV(const uint32_t index) {
      return v.at(index);
    }

    int32_t getVT(const uint32_t index) const {
      return vt.at(index);
    }

    int32_t getVN(const uint32_t index) const {
      return vn.at(index);
    }

    uint32_t getTripletCount() const {
      return v.size();
    }

    void push(const int32_t v, const int32_t vt, const int32_t vn) {
      this->v.push_back(v);
      this->vt.push_back(vt);
      this->vn.push_back(vn);
    }
  private:
    std::vector<int32_t> v;
    std::vector<int32_t> vt;
    std::vector<int32_t> vn;
  };

  class OBJModel : public Resource {
  public:
    OBJModel();
    virtual ~OBJModel();

    bool isValid() {
      return valid;
    }

    bool loadFile(const std::string& filename);
    Mesh* compose();

    virtual OBJModel* toOBJModel() {
      return this;
    }
  private:
    bool valid;
    std::vector<Vector3> vertices;
    std::vector<Vector2> textureCoords;
    std::vector<Vector3> normals;
    std::vector<OBJFace> faces;

    bool validate();
  };
}

#endif
