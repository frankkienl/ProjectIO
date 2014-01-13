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
#include "Graphics.hpp"
#include <iostream>
#include <cmath>
#include "Common.hpp"
#include "Utility.hpp"
#include "ResourceManager.hpp"

namespace io {
  Graphics::Graphics() {
	glewExperimental = GL_TRUE;
    glewInit();

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    fragShader = new FragmentShader("data/fragment.glsl");
    vertShader = new VertexShader("data/vertex.glsl");
    shaderProgram = new ShaderProgram();

    shaderProgram->setFragmentShader(fragShader);
    shaderProgram->setVertexShader(vertShader);

    shaderProgram->addBinding(0, "inVertex");
    shaderProgram->addBinding(1, "inTexCoord");
    shaderProgram->addBinding(2, "inColour");

    shaderProgram->link();
    shaderProgram->makeActive();

    modelMatrixUniform = shaderProgram->getUniformLocation("inModelMatrix");
    projectionMatrixUniform = shaderProgram->getUniformLocation("inProjectionMatrix");
    viewMatrixUniform = shaderProgram->getUniformLocation("inViewMatrix");
    texUniform = shaderProgram->getUniformLocation("inTexture");

    setMatrixMode(MatrixMode::MODEL);
    loadIdentity();

    setMatrixMode(MatrixMode::VIEW);
    loadIdentity();

    setMatrixMode(MatrixMode::PROJECTION);
    loadIdentity();
    //ortho(-8, 8, -8, 8, 0, 0);
    frustum(-(1 + ((3.0 / 4.0) / 2.0)), 1 + ((3.0 / 4.0) / 2.0), -1, 1, 1, 512);

    setMatrixMode(MatrixMode::MODEL);

    ResourceManager* rm = ResourceManager::getInstance();
    
    floorMesh = rm->getResource("data/model.obj")->toOBJModel()->compose();
    wallMesh = rm->getResource("data/wall.obj")->toOBJModel()->compose();
    ceilingMesh = rm->getResource("data/ceiling.obj")->toOBJModel()->compose();
    
    font = rm->getResource("data/DejaVuSansMono.ttf")->toFont();
    if (!font) {
      //  Throw an error;
      throw std::runtime_error("Graphics::Graphics():  Could not load font.");
    }
  }

  Graphics::~Graphics() {
    shaderProgram->makeInactive();
    shaderProgram->unlink();
    shaderProgram->setFragmentShader(nullptr);
    shaderProgram->setVertexShader(nullptr);

    delete shaderProgram;
    delete vertShader;
    delete fragShader;

    glDisableVertexAttribArray(vertexArray);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vertexArray);
    
    delete ceilingMesh;
    delete floorMesh;
    delete wallMesh;
  }

  void Graphics::drawCeilingTile(const int32_t x, const int32_t y, const uint32_t modelID) {
    glUniform1i(texUniform, 0);

    pushMatrix();
    loadIdentity();
    translate(x * 16.0f, 0.0f, y * 16.0f);

    if (ceilingMesh) {
      ceilingMesh->draw();
    }

    popMatrix();
  }

  void Graphics::drawFloorTile(const int32_t x, const int32_t y, const uint32_t modelID) {
    glUniform1i(texUniform, 0);

    pushMatrix();
    loadIdentity();
    translate(x * 16.0f, 0.0f, y * 16.0f);

    if (floorMesh) {
      floorMesh->draw();
    }

    popMatrix();
  }
  
  void Graphics::drawText(const std::string& text) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_CONSTANT_COLOR, GL_ONE_MINUS_SRC_COLOR);
    font->drawText(text);
    glDisable(GL_BLEND);
  }

  void Graphics::drawQuad(float x, float y, float w, float h) {
    glUniform1i(texUniform, 0);
    
    pushMatrix();
    loadIdentity();
    translate(x, y, 0);
    
    popMatrix();
  }

  void Graphics::drawWallTile(const int32_t x, const int32_t y, const Facing side, const uint32_t modelID) {
    glUniform1i(texUniform, 0);

    pushMatrix();
    loadIdentity();
    translate(x * 16.0f, 0.0f, y * 16.0f);

    switch(side) {
    case Facing::SOUTH:
      rotate(toRadians(270), 0.0f, 1.0f, 0.0f);
      break;
    case Facing::WEST:
      rotate(toRadians(180), 0.0f, 1.0f, 0.0f);
      break;
    case Facing::NORTH:
      rotate(toRadians(90), 0.0f, 1.0f, 0.0f);
      break;
    case Facing::EAST:
      rotate(toRadians(0), 0.0f, 1.0f, 0.0f);
      break;
    default:
      break;
    }
    
    if (wallMesh) {
      wallMesh->draw();
    }
    
    popMatrix();
  }

  void Graphics::pushMatrix() {
    matrixStack.push(getMatrix());
  }

  void Graphics::popMatrix() {
    if (matrixStack.size() > 0) {
      setMatrix(matrixStack.top());
      matrixStack.pop();
    }
  }

  void Graphics::loadIdentity() {
    setMatrix(Matrix::identity());
  }

  void Graphics::frustum(const float left, const float right, const float bottom, const float top, const float near, const float far) {
    setMatrix(getMatrix() * Matrix::frustum(left, right, bottom, top, near, far));
  }

  void Graphics::ortho(const float left, const float right, const float bottom, const float top, const float near, const float far) {
    setMatrix(getMatrix() * Matrix::ortho2D(left, right, bottom, top));
  }

  void Graphics::translate(const float x, const float y, const float z) {
    setMatrix(getMatrix() * Matrix::translation(x, y, z));
  }

  void Graphics::rotate(const float angle, const float x, const float y, const float z) {
    setMatrix(getMatrix() * Matrix::rotation(angle, x, y, z));
  }

  void Graphics::scale(const float x, const float y, const float z) {
    setMatrix(getMatrix() * Matrix::scale(x, y, z));
  }

  const Matrix& Graphics::getMatrix() const {
    switch(getMatrixMode()) {
    case MatrixMode::MODEL:
      return modelMatrix;
    case MatrixMode::VIEW:
      return viewMatrix;
    default:
      break;
    }

    return projectionMatrix;
  }

  void Graphics::setMatrix(const Matrix& matrix) {
    switch(getMatrixMode()) {
    case MatrixMode::MODEL:
      modelMatrix = matrix;
      glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix.getData());
      break;
    case MatrixMode::VIEW:
      viewMatrix = matrix;
      glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix.getData());
      break;
    case MatrixMode::PROJECTION:
      projectionMatrix = matrix;
      glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix.getData());
      break;
    }
  }
}
