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
#ifndef MatrixHPP
#define MatrixHPP

#include <cmath>
#include <new>
#include <cstring>
#include <cstdint>

namespace io {
  /**
   * Represents a 4x4 matrix in column-major form, for OpenGL.
   */
  class Matrix {
  public:
    Matrix();

    Matrix(const Matrix& other) {
      ::memcpy(this->matrix, other.matrix, sizeof(float) * 16);
    }

    Matrix(const float m11, const float m12, const float m13, const float m14,
           const float m21, const float m22, const float m23, const float m24,
           const float m31, const float m32, const float m33, const float m34,
           const float m41, const float m42, const float m43, const float m44);

    ~Matrix() {

    }

    Matrix& operator=(const Matrix& rhs) {
      if (&rhs != this) {
        ::memcpy(this->matrix, rhs.matrix, sizeof(float) * 16);
      }

      return *this;
    }

    Matrix operator+(const Matrix& rhs) const;

    Matrix operator-(const Matrix& rhs) const;

    Matrix operator*(const Matrix& rhs) const;

    Matrix operator*(const float scaler) const;

    Matrix operator/(const float scaler) const;

    float get(const uint32_t row, const uint32_t column) const;

    //  Returns an identity matrix.
    static Matrix identity() {
      return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    float* getData() {
      return (float*)this->matrix;
    }

    //  Returns a 2D rotation matrix along the Z axis.
    static Matrix rotation(const float angle) {
      float x = ::cos(angle);
      float y = ::sin(angle);

      return Matrix(   x,   -y, 0.0f, 0.0f,
                       y,    x, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Matrix rotation(const float angle, const float x, const float y, const float z) {
      float s = ::sin(angle);
      float c = ::cos(angle);
      float c1 = 1 - c;

      return Matrix(((x * x) * c1) + c,
                    ((x * y) * c1) - (z * s),
                    ((x * z) * c1) + (y * s),
                    0,
                    ((y * x) * c1) + (z * s),
                    ((y * y) * c1) + c,
                    ((y * z) * c1) - (x * s),
                    0,
                    ((x * z) * c1) - (y * s),
                    ((y * z) * c1) + (x * s),
                    ((z * z) * c1) + c,
                    0,
                    0,
                    0,
                    0,
                    1);
    }


    //  Returns a 2D scaling matrix.
    static Matrix scale(const float x, const float y) {
      return Matrix(   x, 0.0f, 0.0f, 0.0f,
                       0.0f,    y, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Matrix scale(const float x, const float y, const float z) {
      return Matrix(   x, 0.0f, 0.0f, 0.0f,
                       0.0f,    y, 0.0f, 0.0f,
                       0.0f, 0.0f,    z, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Matrix ortho2D(const float left, const float right, const float bottom, const float top) {
      float ffar = 1.0;
      float fnear = -1.0;
      return Matrix((2.0f / (right - left)), 0.0f,  0.0f, -((right + left) / (right - left)),
                    0.0f, (2.0f / (top - bottom)),  0.0f, -((top + bottom) / (top - bottom)),
                    0.0f, 0.0f, (-2.0f / (ffar - fnear)), -((ffar + fnear) / (ffar - fnear)),
                    0.0f, 0.0f,                     0.0f,                              1.0f);
    }

    static Matrix frustum(const float left, const float right, const float bottom, const float top, const float near, const float far) {
      float A = (right + left) / (right - left);
      float B = (top + bottom) / (top - bottom);
      float C = -(far + near) / (far - near);
      float D = -(2 * far * near) / (far - near);
      return Matrix((2 * near) / (right - left),                           0,  A, 0,
                    0, (2 * near) / (top - bottom),  B, 0,
                    0,                           0,  C, D,
                    0,                           0, -1, 0);
    }

    void set(const uint32_t row, const uint32_t column, const float in);

    //  Returns a 2D translation matrix.
    static Matrix translation(const float x, const float y) {
      return Matrix(1.0, 0.0, 0.0,   x,
                    0.0, 1.0, 0.0,   y,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
    }

    static Matrix translation(const float x, const float y, const float z) {
      return Matrix(1.0f, 0.0f, 0.0f,    x,
                    0.0f, 1.0f, 0.0f,    y,
                    0.0f, 0.0f, 1.0f,    z,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix transpose() const;

    Matrix zero() const {
      return Matrix(0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f);
    }
  private:
    float matrix[4][4];
  };
}

#endif
