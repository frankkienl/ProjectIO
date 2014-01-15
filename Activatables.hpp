#ifndef ActivatablesHPP
#define ActivatablesHPP

#include "Graphics.hpp"
#include "Common.hpp"
#include "Entity.hpp"

namespace io {
  class Activatable {
  public:
    Activatable() {
      x = 0;
      y = 0;
    }

    virtual ~Activatable() { }

    virtual void activate(Entity* activator) = 0;

    virtual void draw(Graphics* g) { }

    int32_t getX() const {
      return x;
    }

    int32_t getY() const {
      return y;
    }

    virtual bool isSolid() const {
      return false;
    }

    void setX(const int32_t x) {
      this->x = x;
    }

    void setY(const int32_t y) {
      this->y = y;
    }
  private:
    int32_t x;
    int32_t y;
  };

  enum class Orientation : int8_t {
    HORIZONTAL,
    VERTICAL
  };

  class Door : public Activatable {
  public:
    Door() {
      orientation = Orientation::HORIZONTAL;
    }

    virtual ~Door() {

    }

    virtual void activate(Entity* activator) {
      if (getOrientation() == Orientation::VERTICAL) {
        switch(activator->getFacing()) {
        case Facing::NORTH:
          activator->setY(activator->getY() - 2);
          break;
        case Facing::SOUTH:
          activator->setY(activator->getY() + 2);
          break;
        default:
          break;
        }
      }
      else {
        switch(activator->getFacing()) {
        case Facing::EAST:
          activator->setX(activator->getX() + 2);
          break;
        case Facing::WEST:
          activator->setX(activator->getX() - 2);
          break;
        default:
          break;
        }
      }
    }

    Orientation getOrientation() const {
      return orientation;
    }

    virtual bool isSolid() const {
      return true;
    }

    void setOrientation(const Orientation orientation) {
      this->orientation = orientation;
    }
  private:
    Orientation orientation;
  };
}

#endif
