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
#ifndef MeshHPP
#define MeshHPP

#include <vector>
#include "Common.hpp"
#include "Vertex.hpp"

namespace io {
  class Mesh {
  public:
    Mesh()
      : bufferID(0), meshType(GL_INVALID_ENUM), open(false), valid(false) {
    }

    ~Mesh() {
      if (bufferID != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &bufferID);
      }
    }

    void addVertex(const Vector3& vertex, const Vector2& texCoord, const Colour& colour) {
      if (isOpen()) {
        Vertex v;
        v.position = vertex;
        v.texCoord = texCoord;
        v.colour = colour;
        vertices.push_back(v);
      }
    }

    void addVertex(const Vertex& vertex) {
      if (isOpen()) {
        vertices.push_back(vertex);
      }
    }

    void begin(GLenum meshType);

    void draw() const {
      if (!isOpen() && bufferID != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector3));
        glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector3) + sizeof(Vector2)));
        glDrawArrays(meshType, 0, vertices.size());
      }
    }

    void end();

    GLenum getMeshType() const {
      return meshType;
    }

    const std::vector<Vertex>& getVertices() const {
      return vertices;
    }

    bool isOpen() const {
      return open;
    }

    bool isValid() const {
      return valid;
    }
  private:
    GLuint bufferID;
    GLenum meshType;
    bool open;
    bool valid;
    std::vector<Vertex> vertices;

    Mesh(const Mesh&);
    Mesh& operator=(const Mesh&);
  };
}

#endif
