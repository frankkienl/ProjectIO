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
#ifndef GraphicsHPP
#define GraphicsHPP

#include <cstdint>
#include <stack>
#include <string>
#include "Font.hpp"
#include "Mesh.hpp"
#include "Matrix.hpp"
#include "Common.hpp"
#include "FragmentShader.hpp"
#include "VertexShader.hpp"
#include "ShaderProgram.hpp"
#include "OBJModel.hpp"
#include "BoundingBox.hpp"

namespace io {
  enum class MatrixMode : uint8_t {
    MODEL,
    VIEW,
    PROJECTION
  };

  class Graphics {
  public:
    Graphics();
    ~Graphics();

    void drawCeilingTile(const int32_t x, const int32_t y, const uint32_t modelID);
    void drawFloorTile(const int32_t x, const int32_t y, const uint32_t modelID);
    void drawText(const std::string& text);
    void drawQuad(float x, float y, float w, float h);
    void drawWallTile(const int32_t x, const int32_t y, const Facing side, const uint32_t modelID);

    MatrixMode getMatrixMode() const {
      return matrixMode;
    }

    BoundingBox getTextBoundingBox(const std::string& text) {
      return font->getTextBoundingBox(text);
    }

    void setMatrixMode(const MatrixMode mode) {
      matrixMode = mode;
    }

    void pushMatrix();
    void popMatrix();
    void loadIdentity();
    void frustum(const float left, const float right, const float bottom, const float top, const float near, const float far);
    void ortho(const float left, const float right, const float bottom, const float top, const float near, const float far);
    void translate(const float x, const float y, const float z);
    void rotate(const float angle, const float x, const float y, const float z);
    void scale(const float x, const float y, const float z);
  private:
    MatrixMode matrixMode;
    std::stack<Matrix> matrixStack;
    
    GLuint vertexArray;
    GLuint texUniform;

    FragmentShader* fragShader;
    VertexShader* vertShader;
    ShaderProgram* shaderProgram;

    Mesh* floorMesh;
    Mesh* wallMesh;
    Mesh* ceilingMesh;

    Matrix modelMatrix;
    GLuint modelMatrixUniform;

    Matrix projectionMatrix;
    GLuint projectionMatrixUniform;

    Matrix viewMatrix;
    GLuint viewMatrixUniform;
    
    Font* font;
    
    const Matrix& getMatrix() const;
    void setMatrix(const Matrix& toApply);
  };
}

#endif
