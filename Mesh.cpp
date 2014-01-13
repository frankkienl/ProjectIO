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
#include "Mesh.hpp"
#include <iostream>

namespace io {
  void Mesh::begin(GLenum meshType) {
    if (!isOpen()) {
      vertices.clear();
      open = true;
      this->meshType = meshType;
    }
  }

  void Mesh::end() {
    if (isOpen()) {
      valid = true;
      std::size_t minVertices = 0;
      switch(meshType) {
      case GL_POINTS:
        minVertices = 1;
        break;
      case GL_LINES:
      case GL_LINE_STRIP:
        minVertices = 2;
        break;
      case GL_LINE_LOOP:
      case GL_TRIANGLES:
      case GL_TRIANGLE_STRIP:
      case GL_TRIANGLE_FAN:
        minVertices = 3;
        break;
      default:
        valid = false;
        break;
      }

      if (vertices.size() >= minVertices && isValid()) {
        if (bufferID == 0) {
          glGenBuffers(1, &bufferID);
        }

        if (bufferID != 0) {
          GLuint oldVBuffer = 0;
          glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (GLint*)&oldVBuffer);

          glBindBuffer(GL_ARRAY_BUFFER, bufferID);

          if (glGetError() != GL_NO_ERROR) {
          }

          Vertex* tmpBuffer = new (std::nothrow) Vertex[vertices.size()];
          for (std::size_t i = 0; i < vertices.size(); i++) {
            tmpBuffer[i] = vertices[i];
          }

          glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), tmpBuffer, GL_STATIC_DRAW);

          delete [] tmpBuffer;

          open = false;
          valid = true;

          glBindBuffer(GL_ARRAY_BUFFER, oldVBuffer);
        }
      } else {
        valid = false;
      }
    }
  }
}
