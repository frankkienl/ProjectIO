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
#include <fstream>
#include <exception>
#include <stdexcept>
#include "Shader.hpp"

namespace io {
  void Shader::loadShaderFromFile(const std::string& filename) {
    char* buffer = nullptr;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      file.open(filename.c_str(), std::ios::binary | std::ios::in);
      if (!file.is_open()) {
        throw std::runtime_error("Could not open shader file.");
      }

      std::size_t size = 0;
      file.seekg(0, std::ios::end);
      size = (std::size_t)file.tellg();
      file.seekg(0, std::ios::beg);

      if (size == 0) {
        throw std::length_error("Filesize of shader file is zero.");
      }

      buffer = new char[size + 1];
      file.read(buffer, size).gcount();
      buffer[size] = 0;
      file.close();

      std::string text(buffer);
      this->loadShaderFromText(text);

      delete [] buffer;
      buffer = NULL;
    } catch (const std::exception& e) {
      if (buffer) {
        delete [] buffer;
        buffer = nullptr;
      }

      if (file.is_open()) {
        file.close();
      }

      throw e;
    }
  }

  void Shader::loadShaderFromText(const std::string& text) {
    GLuint shaderID = 0;
    try {
      //  Clear GL error flag..
      while (glGetError() != GL_NO_ERROR);

      shaderID = glCreateShader(getShaderType());
      if (glGetError() != GL_NO_ERROR) {
        throw std::runtime_error("Unknown error creating a shader object.");
      }

      const GLchar* textBuffer = const_cast<const GLchar*>(text.c_str());
      const GLint size = text.length();
      glShaderSource(shaderID, 1, &textBuffer, &size);
      if (glGetError() != GL_NO_ERROR) {
        throw std::runtime_error("Unknown error reading in shader source.");
      }

      glCompileShader(shaderID);
      GLint status = GL_TRUE;
      glGetShaderiv(shaderID, GL_COMPILE_STATUS, (GLint*)&status);

      if (!(glGetError() == GL_NO_ERROR && status == GL_TRUE)) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
        throw std::runtime_error(std::string(infoLog));
      }

      this->shaderID = shaderID;
    } catch (const std::exception& e) {
      if (shaderID != 0) {
        glDeleteShader(shaderID);
      }

      throw e;
    }
  }
}
