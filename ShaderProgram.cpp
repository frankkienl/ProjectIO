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
#include <exception>
#include <stdexcept>
#include "ShaderProgram.hpp"

namespace io {
  void ShaderProgram::unlink() {
    //  Don't try to unlink a non-existing program, or one that is currently in use.
    if (isProgramValid() && !isProgramActive()) {
      programValid = false;
      while (glGetError() != GL_NO_ERROR);

      if (getFragmentShader()) {
        glDetachShader(getProgramID(), getFragmentShader()->getShaderID());
      }

      if (getVertexShader()) {
        glDetachShader(getProgramID(), getVertexShader()->getShaderID());
      }
    }
  }

  void ShaderProgram::link() {
    GLuint programID = 0;
    try {
      programValid = true;
      while (glGetError() != GL_NO_ERROR);

      if (getProgramID() == 0) {
        programID = glCreateProgram();
        if (glGetError() != GL_NO_ERROR) {
          throw std::runtime_error("ERROR:  Could not create shader program.");
        }
      }

      if (getFragmentShader()) {
        glAttachShader(programID, getFragmentShader()->getShaderID());
        if (glGetError() != GL_NO_ERROR) {
          throw std::runtime_error("ERROR:  Could not attach fragment shader to program.");
        }
      }

      if (getVertexShader()) {
        glAttachShader(programID, getVertexShader()->getShaderID());
        if (glGetError() != GL_NO_ERROR) {
          throw std::runtime_error("ERROR:  Could not attach vertex shader to program.");
        }
      }

      //  Only try to link if there's anything attached.
      if (getFragmentShader() || getVertexShader()) {
        //  But first, bindings.
        std::map<unsigned int, std::string>::iterator iter = bindings.begin();
        while (iter != bindings.end()) {
          glBindAttribLocation(programID, iter->first, iter->second.c_str());
          iter++;
        }

        glLinkProgram(programID);
        GLint status = GL_TRUE;
        glGetProgramiv(programID, GL_LINK_STATUS, (GLint*)&status);

        if (!(glGetError() == GL_NO_ERROR && status == GL_TRUE)) {
          char infoLog[1024];
          glGetProgramInfoLog(programID, 1024, NULL, infoLog);
          throw std::runtime_error(std::string(infoLog));
        }
      }

      this->programID = programID;
    } catch(std::exception& e) {
      programValid = false;
      throw e;
    }
  }

  unsigned int ShaderProgram::getBindingIndex(const std::string& varName) {
    unsigned int ret = UINT_MAX;

    std::map<unsigned int, std::string>::iterator iter = bindings.begin();
    while (iter != bindings.end()) {
      if (iter->second.compare(varName) == 0) {
        ret = iter->first;
        iter = bindings.end();
      } else {
        iter++;
      }
    }

    return ret;
  }
}
