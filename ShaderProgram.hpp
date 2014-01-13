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
#ifndef ShaderProgramHPP
#define ShaderProgramHPP

#include <climits>
#include <map>
#include <string>
#include "Common.hpp"
#include "FragmentShader.hpp"
#include "VertexShader.hpp"

namespace io {
  class ShaderProgram {
  public:
    ShaderProgram() : fragShader(nullptr), programID(0), programValid(false), vertShader(nullptr) {

    }

    ~ShaderProgram() {
      if (programID > 0) {
        unlink();
        glDeleteProgram(programID);
      }
    }

    void addBinding(unsigned int which, const std::string& varName) {
      if (!isProgramValid()) {
        unsigned int index = getBindingIndex(varName);
        if (bindings.count(which) == 0 && index == UINT_MAX) {
          bindings[which] = varName;
        }
      }
    }

    void clearBindings() {
      if (!isProgramValid()) {
        bindings.clear();
      }
    }

    unsigned int getBindingIndex(const std::string& varName);

    std::string getBindingVariable(unsigned int index) {
      std::string ret;

      if (bindings.count(index) > 0) {
        ret = bindings[index];
      }

      return ret;
    }

    FragmentShader* getFragmentShader() {
      return fragShader;
    }

    GLuint getProgramID() const {
      return programID;
    }

    GLint getUniformLocation(const std::string& uniformName) {
      return glGetUniformLocation(getProgramID(), uniformName.c_str());
    }

    VertexShader* getVertexShader() {
      return vertShader;
    }

    bool isProgramActive() {
      GLuint state = 0;
      glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&state);
      return (state == getProgramID());
    }

    bool isProgramValid() {
      return programValid;
    }

    void link();

    void makeActive() {
      if (isProgramValid()) {
        glUseProgram(programID);
      }
    }

    void makeInactive() {
      if (isProgramValid() && isProgramActive()) {
        glUseProgram(0);
      }
    }

    void removeBinding(unsigned int which) {
      if (!isProgramValid()) {
        if (bindings.count(which) > 0) {
          bindings.erase(which);
        }
      }
    }

    void removeBinding(const std::string& varName) {
      if (!isProgramValid()) {
        unsigned int index = getBindingIndex(varName);
        if (index != UINT_MAX) {
          bindings.erase(index);
        }
      }
    }

    void setFragmentShader(FragmentShader* shader) {
      if (!isProgramValid()) {
        fragShader = shader;
      }
    }

    void setVertexShader(VertexShader* shader) {
      if (!isProgramValid()) {
        vertShader = shader;
      }
    }

    void unlink();
  private:
    std::map<unsigned int, std::string> bindings;
    FragmentShader* fragShader;
    GLuint programID;
    bool programValid;
    VertexShader* vertShader;

    ShaderProgram(const ShaderProgram&);
    ShaderProgram& operator=(const ShaderProgram&);
  };
}

#endif
