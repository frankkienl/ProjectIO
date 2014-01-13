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
#ifndef ScreenHPP
#define ScreenHPP

#include "Graphics.hpp"
#include "Component.hpp"
#include "InputEvent.hpp"
#include <list>
#include <iostream>

namespace io {
  class Screen;

  class ScreenEventListener {
  public:
    virtual ~ScreenEventListener() { }
    virtual void onScreenActivated(Screen* which) { }
    virtual void onScreenDeactivated(Screen* which) { }
  private:
  };

  class Screen {
  public:
    Screen() {
      focusedComponent = nullptr;
    }
    
    virtual ~Screen() {
    }
    
    void activated() {
      for (ScreenEventListener* l : screenEventListeners) {
        l->onScreenActivated(this);
      }
    }

    void addComponent(Component* component) {
      if (component && !hasComponent(component)) {
        components.push_back(component);
      }
    }
    
    void addInputEventListener(InputEventListener* listener) {
      if (listener && !hasInputEventListener(listener)) {
        inputEventListeners.push_back(listener);
      }
    }

    void addScreenEventListener(ScreenEventListener* listener) {
      if (listener && !hasScreenEventListener(listener)) {
        screenEventListeners.push_back(listener);
      }
    }

    void deactivated() {
      for (ScreenEventListener* l : screenEventListeners) {
        l->onScreenDeactivated(this);
      }
    }

    void draw(Graphics* g) {
      g->setMatrixMode(MatrixMode::VIEW);
      g->pushMatrix();
      g->loadIdentity();
      
      g->setMatrixMode(MatrixMode::PROJECTION);
      g->pushMatrix();
      g->loadIdentity();
      g->ortho(0, 640, 480, 0, 0, 1);
      
      for (Component* c : components) {
        c->draw(g);
      }
      
      g->setMatrixMode(MatrixMode::PROJECTION);
      g->popMatrix();
      
      g->setMatrixMode(MatrixMode::VIEW);
      g->popMatrix();
    }
    
    Component* getFocusedComponent() const {
      return focusedComponent;
    }

    virtual bool handleInputEvent(const InputEvent& event) {
      if (getFocusedComponent()) {
        bool result = getFocusedComponent()->handleInputEvent(event);
        if (result) {
          return result;
        }
      }

      return handleInputEventListeners(event);
    }

    void removeComponent(Component* component) {
      if (component && hasComponent(component)) {
        components.remove(component);
      }
    }

    void removeInputEventListeners(InputEventListener* listener) {
      if (listener && hasInputEventListener(listener)) {
        inputEventListeners.remove(listener);
      }
    }

    void removeScreenEventListener(ScreenEventListener* listener) {
      if (listener && hasScreenEventListener(listener)) {
        screenEventListeners.remove(listener);
      }
    }

    void setFocusedComponent(Component* component) {
      if (component) {
        if (hasComponent(component)) {
          focusedComponent = component;
        }
      }
      else {
        focusedComponent = nullptr;
      }
    }
  private:
    std::list<Component*> components;
    Component* focusedComponent;
    std::list<InputEventListener*> inputEventListeners;
    std::list<ScreenEventListener*> screenEventListeners;

    bool handleInputEventListeners(const InputEvent& event) {
      for (InputEventListener* l : inputEventListeners) {
        bool result = l->handleInputEvent(event);
        if (result) {
          return true;
        }
      }

      return false;
    }

    bool hasComponent(Component* component) {
      for (Component* c : components) {
        if (component == c) {
          return true;
        }
      }
      
      return false;
    }

    bool hasInputEventListener(InputEventListener* listener) {
      for (InputEventListener* l : inputEventListeners) {
        if (listener == l) {
          return true;
        }
      }

      return false;
    }

    bool hasScreenEventListener(ScreenEventListener* listener) {
      for (ScreenEventListener* l : screenEventListeners) {
        if (listener == l) {
          return true;
        }
      }

      return false;
    }
  };
}

#endif // ScreenHPP
