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
#include "Matrix.hpp"
#include <exception>

namespace io {
  Matrix::Matrix() {
    this->set(0, 0, 0.0f);
    this->set(0, 1, 0.0f);
    this->set(0, 2, 0.0f);
    this->set(0, 3, 0.0f);
    this->set(1, 0, 0.0f);
    this->set(1, 1, 0.0f);
    this->set(1, 2, 0.0f);
    this->set(1, 3, 0.0f);
    this->set(2, 0, 0.0f);
    this->set(2, 1, 0.0f);
    this->set(2, 2, 0.0f);
    this->set(2, 3, 0.0f);
    this->set(3, 0, 0.0f);
    this->set(3, 1, 0.0f);
    this->set(3, 2, 0.0f);
    this->set(3, 3, 0.0f);
  }

  Matrix::Matrix(const float m11, const float m12, const float m13, const float m14,
                 const float m21, const float m22, const float m23, const float m24,
                 const float m31, const float m32, const float m33, const float m34,
                 const float m41, const float m42, const float m43, const float m44) {
    this->set(0, 0, m11);
    this->set(0, 1, m12);
    this->set(0, 2, m13);
    this->set(0, 3, m14);
    this->set(1, 0, m21);
    this->set(1, 1, m22);
    this->set(1, 2, m23);
    this->set(1, 3, m24);
    this->set(2, 0, m31);
    this->set(2, 1, m32);
    this->set(2, 2, m33);
    this->set(2, 3, m34);
    this->set(3, 0, m41);
    this->set(3, 1, m42);
    this->set(3, 2, m43);
    this->set(3, 3, m44);
  }

  Matrix Matrix::operator+(const Matrix& rhs) const {
    Matrix out;

    for (uint32_t row = 0; row < 4; row++) {
      for (uint32_t column = 0; column < 4; column++) {
        out.set(row, column, this->get(row, column) + rhs.get(row, column));
      }
    }

    return out;
  }

  Matrix Matrix::operator-(const Matrix& rhs) const {
    Matrix out;

    for (uint32_t row = 0; row < 4; row++) {
      for (uint32_t column = 0; column < 4; column++) {
        out.set(row, column, this->get(row, column) - rhs.get(row, column));
      }
    }

    return out;
  }

  Matrix Matrix::operator*(const Matrix& rhs) const {
    Matrix out;

    for (uint32_t row = 0; row < 4; row++) {
      for (uint32_t column = 0; column < 4; column++) {
        float sum = 0.0;

        for (uint32_t i = 0; i < 4; i++) {
          sum += this->get(row, i) * rhs.get(i, column);
        }

        out.set(row, column, sum);
      }
    }

    return out;
  }

  Matrix Matrix::operator*(const float scaler) const {
    Matrix out;

    for (uint32_t row = 0; row < 4; row++) {
      for (uint32_t column = 0; column < 4; column++) {
        out.set(row, column, this->get(row, column) * scaler);
      }
    }

    return out;
  }

  Matrix Matrix::operator/(const float scaler) const {
    Matrix out;

    try {
      for (uint32_t row = 0; row < 4; row++) {
        for (uint32_t column = 0; column < 4; column++) {
          out.set(row, column, this->get(row, column) / scaler);
        }
      }
    } catch(std::exception&) {
      out = Matrix::zero();
    }

    return out;
  }

  float Matrix::get(const uint32_t row, const uint32_t column) const {
    if (row >= 4 || column >= 4) {
      return 0.0f;
    }

    return this->matrix[row][column];
  }

  void Matrix::set(const uint32_t row, const uint32_t column, const float in) {
    if (row >= 4 || column >= 4) {
      return;
    }

    this->matrix[row][column] = in;
  }

  Matrix Matrix::transpose() const {
    Matrix out;

    for (uint32_t y = 0; y < 4; y++) {
      for (uint32_t x = 0; x < 4; x++) {
        out.set(y, x, this->get(y, x));
      }
    }

    return out;
  }
}
