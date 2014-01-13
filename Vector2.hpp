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
#ifndef Vector2HPP
#define Vector2HPP

#include <cmath>
#include <exception>
#include <cstdint>
#include "Matrix.hpp"

namespace io {
  class Vector2 {
  public:
    Vector2(const float x, const float y)
      : x(x), y(y) {
    }

    Vector2(const Vector2& rhs)
      : x(rhs.getX()), y(rhs.getY()) {
    }

    Vector2& operator=(const Vector2& rhs) {
      if (&rhs != this) {
        x = rhs.getX();
        y = rhs.getY();
      }

      return *this;
    }

    Vector2 operator+(const Vector2& rhs) const {
      return Vector2(getX() + rhs.getX(), getY() + rhs.getY());
    }

    Vector2 operator-(const Vector2& rhs) const {
      return Vector2(getX() - rhs.getX(), getY() - rhs.getY());
    }

    Vector2 operator*(const float scaler) const {
      return Vector2(getX() * scaler, getY() * scaler);
    }

    Vector2 operator*(const Matrix& matrix) const;

    Vector2 operator/(const float scaler) const {
      return Vector2(getX() / scaler, getY() / scaler);
    }

    float angle() const {
      return ::atan2(getY(), getX());
    }

    Vector2 cross() const {
      return Vector2(-getY(), getX());
    }

    float dot(const Vector2& rhs) const {
      return (getX() * rhs.getX()) + (getY() * rhs.getY());
    }

    float getX() const {
      return x;
    }

    float getY() const {
      return y;
    }

    float magnitude() const {
      return ::sqrt((getX() * getX()) + (getY() * getY()));
    }

    Vector2 negated() const {
      return Vector2(-getX(), -getY());
    }

    Vector2 normalized() const {
      float m = this->magnitude();
      return Vector2(getX() / m, getY() / m);
    }

    static Vector2 vectorFromOrientation(const float orientation) {
      return Vector2(::cos(orientation), ::sin(orientation));
    }
  private:
    float x;
    float y;
  };
}

#endif
