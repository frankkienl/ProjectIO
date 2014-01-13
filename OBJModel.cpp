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
#include "OBJModel.hpp"
#include "StringTokenizer.hpp"
#include <boost/filesystem.hpp>
#include <fstream>
#include "Log.hpp"

using namespace boost::filesystem;

namespace io {
  Vector2 vector2FromTokens(const std::string& x, const std::string& y);
  Vector3 vector3FromTokens(const std::string& x, const std::string& y,
                            const std::string& z);

  OBJModel::OBJModel() {
    valid = false;
  }

  OBJModel::~OBJModel() {

  }

  /**
   * Loads the specified file, then validates.
   */
  bool OBJModel::loadFile(const std::string& filename) {
    writeToLog(MessageLevel::INFO, "Loading model from file \"%s\"\n", filename.c_str());
    valid = false;
    
    path p(filename);
    uint32_t fileLine = 0;
    if (exists(p) && is_regular_file(p)) {
      std::ifstream file(p.generic_string());

      vertices.clear();
      textureCoords.clear();
      normals.clear();
      faces.clear();

      vertices.push_back(Vector3(0.0f, 0.0f, 0.0f));
      textureCoords.push_back(Vector2(0.0f, 0.0f));
      normals.push_back(Vector3(0.0f, 0.0f, 0.0f));

      do {
        std::string line;
        std::getline(file, line);
        fileLine++;
        StringTokenizer tokens(line, ' ');

        if (tokens.getTokenCount() > 0) {
          std::string type = tokens.getToken(0);
          if (type.compare("v") == 0) {
            Vector3 vertex = vector3FromTokens(tokens.getToken(1),
                                               tokens.getToken(2),
                                               tokens.getToken(3));

            vertices.push_back(vertex);
          } else if (type.compare("vt") == 0) {
            Vector2 texCoord = vector2FromTokens(tokens.getToken(1),
                                                 tokens.getToken(2));

            textureCoords.push_back(texCoord);
          } else if (type.compare("vn") == 0) {
            Vector3 normal = vector3FromTokens(tokens.getToken(1),
                                               tokens.getToken(2),
                                               tokens.getToken(3));

            normals.push_back(normal);
          } else if (type.compare("f") == 0) {
            OBJFace face;

            for (uint32_t i = 1; i < tokens.getTokenCount(); i++) {
              StringTokenizer faceTokens(tokens.getToken(i), '/');

              int32_t v = 0;
              int32_t vt = 0;
              int32_t vn = 0;

              try {
                v = std::stoi(faceTokens.getToken(0));
                if (v < 0) {
                  v += vertices.size();
                }
              } catch (std::exception&) {
                v = 0;
              }

              try {
                vt = std::stoi(faceTokens.getToken(1));
                if (vt < 0) {
                  vt += textureCoords.size();
                }
              } catch (std::exception&) {
                vt = 0;
              }

              try {
                vn = std::stoi(faceTokens.getToken(2));
                if (vn < 0) {
                  vn += normals.size();
                }
              } catch (std::exception&) {
                vn = 0;
              }

              face.push(v, vt, vn);
            }
            
            //  We only support triangulated models.
            if (face.getTripletCount() > 3) {
              writeToLog(MessageLevel::ERROR, "Malformed face on line %d in \"%s\":  Too many points, only triangles are supported.\n", fileLine, filename.c_str());
              return false;
            }
            
            faces.push_back(face);
          } else {
            //  Currently a no-op.
          }
        }
      } while(!file.eof() && file.good());
    } else {
      writeToLog(MessageLevel::ERROR, "Could not find file \"%s\".\n", filename.c_str());
      return false;
    }

    return validate();
  }

  Mesh* OBJModel::compose() {
    if (!isValid()) {
      return nullptr;
    }

    Mesh* m = new Mesh();
    m->begin(GL_TRIANGLES);

    for (uint32_t i = 0; i < faces.size(); i++) {
      OBJFace f = faces.at(i);
      for (uint32_t j = 0; j < f.getTripletCount(); j++) {
        int32_t v = f.getV(j);
        int32_t vt = f.getVT(j);
        int32_t vn = f.getVN(j);

        m->addVertex(vertices.at(v), textureCoords.at(vt), Colour(255, 255, 255, 255));
      }
    }

    m->end();

    return m;
  }

  /**
   * Validates everything.  Returns true if no errors, false otherwise.
   */
  bool OBJModel::validate() {
    try {
      for (uint32_t i = 0; i < faces.size(); i++) {
        OBJFace f = faces.at(i);
        bool vtAvail = false;
        bool vnAvail = false;

        for (uint32_t j = 0; j < f.getTripletCount(); j++) {
          int32_t v = f.getV(j);
          int32_t vt = f.getVT(j);
          int32_t vn = f.getVN(j);

          if (v != 0) {
            if (v >= vertices.size()) {
              throw std::out_of_range("OBJModel::validate");
            }
          } else {
            throw std::runtime_error("OBJModel::validate");
          }

          if (vt != 0) {
            //  Each specifier must have the same number of arguments.
            if (j != 0 && !vtAvail) {
              throw std::runtime_error("OBJModel::validate");
            }
            
            vtAvail = true;
            if (vt >= textureCoords.size()) {
              throw std::out_of_range("OBJModel::validate");
            }
          }

          if (vn != 0) {
            //  Each specifier must have the same number of arguments.
            if (j != 0 && !vnAvail) {
              throw std::runtime_error("OBJModel::validate");
            }
              
            vnAvail = true;
            if (vn >= normals.size()) {
              throw std::out_of_range("OBJModel::validate");
            }
          }
        }
      }
    } catch (std::exception& e) {
      writeToLog(MessageLevel::ERROR, "EXCEPTION:  %s\n", e.what());
      valid = false;
      return false;
    }

    valid = true;
    return true;
  }

  Vector2 vector2FromTokens(const std::string& x, const std::string& y) {
    float outX = 0.0f;
    float outY = 0.0f;

    try {
      outX = std::stof(x);
    } catch (std::exception&) {
      outX = 0.0f;
    }

    try {
      outY = std::stof(y);
    } catch (std::exception&) {
      outY = 0.0f;
    }

    return Vector2(outX, outY);
  }

  Vector3 vector3FromTokens(const std::string& x, const std::string& y,
                            const std::string& z) {
    Vector2 outVec2 = vector2FromTokens(x, y);
    float outZ = 0.0f;

    try {
      outZ = std::stof(z);
    } catch (std::exception&) {
      outZ = 0.0f;
    }

    return Vector3(outVec2, outZ);
  }
}
