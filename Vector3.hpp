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
#ifndef Vector3HPP
#define Vector3HPP

#include <cmath>
#include "Vector2.hpp"

namespace io {
  class Vector3 {
  public:
    //  Some convenience stuff for 2D->3D vectors.
    Vector3(const Vector2& vec2, const float z)
      : x(vec2.getX()), y(vec2.getY()), z(z) {
    }

    Vector3(const float x, const Vector2& vec2)
      : x(x), y(vec2.getX()), z(vec2.getY()) {
    }

    Vector3(const float x, const float y, const float z)
      : x(x), y(y), z(z) {
    }

    Vector3(const Vector3& rhs)
      : x(rhs.getX()), y(rhs.getY()), z(rhs.getZ()) {
    }

    Vector3& operator=(const Vector3& rhs) {
      if (this != &rhs) {
        x = rhs.getX();
        y = rhs.getY();
        z = rhs.getZ();
      }

      return *this;
    }

    Vector3 operator+(const Vector3& rhs) const {
      return Vector3(getX() + rhs.getX(), getY() + rhs.getY(), getZ() + rhs.getZ());
    }

    Vector3 operator-(const Vector3& rhs) const {
      return Vector3(getX() - rhs.getX(), getY() - rhs.getY(), getZ() - rhs.getZ());
    }

    Vector3 operator*(const float scaler) const {
      return Vector3(getX() * scaler, getY() * scaler, getZ() * scaler);
    }

    Vector3 operator/(const float scaler) const {
      return Vector3(getX() / scaler, getY() / scaler, getZ() / scaler);
    }

    Vector3 operator*(const Matrix& mat) const;;

    Vector3 cross(const Vector3& rhs) const {
      float i = (getY() * rhs.getZ()) - (rhs.getY() * getZ());
      float j = (getX() * rhs.getZ()) - (rhs.getX() * getZ());
      float k = (getX() * rhs.getY()) - (rhs.getX() * getY());

      return Vector3(i, j, k);
    }

    float dot(const Vector3& rhs) const {
      return ((getX() * rhs.getX()) + (getY() * rhs.getY()) + (getZ() * rhs.getZ()));
    }

    float getX() const {
      return x;
    }

    float getY() const {
      return y;
    }

    float getZ() const {
      return z;
    }

    float magnitude() const {
      return ::sqrt((getX() * getX()) + (getY() * getY()) + (getZ() * getZ()));
    }

    Vector3 negated() const {
      return Vector3(-getX(), -getY(), -getZ());
    }

    Vector3 normalized() const {
      float m = magnitude();
      return Vector3(getX() / m, getY() / m, getZ() / m);
    }
  private:
    float x;
    float y;
    float z;
  };
}

#endif
