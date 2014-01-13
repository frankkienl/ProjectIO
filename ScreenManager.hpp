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
#ifndef ScreenManagerHPP
#define ScreenManagerHPP

#include <stack>
#include "Screen.hpp"
#include "InputEvent.hpp"
#include "Graphics.hpp"

namespace io {
  class ScreenManager {
  public:
    ScreenManager() {

    }

    ~ScreenManager() {

    }

    void clear() {
      while (screens.size() > 0) {
        screens.top()->deactivated();
        screens.pop();
      }
    }

    void draw(Graphics* g) {
      if (screens.size() > 0) {
        screens.top()->draw(g);
      }
    }

    bool isScreenVisible(Screen* screen) {
      if (screens.size() > 0) {
        return (screens.top() == screen);
      }

      return false;
    }

    bool handleInputEvent(const InputEvent& event) {
      if (screens.size() > 0) {
        return screens.top()->handleInputEvent(event);
      }

      return false;
    }

    void popScreen() {
      if (screens.size() > 0) {
        screens.top()->deactivated();
        screens.pop();
        if (screens.size() > 0) {
          screens.top()->activated();
        }
      }
    }

    void pushScreen(Screen* screen) {
      if (screen) {
        if (screens.size() > 0) {
          screens.top()->deactivated();
        }
        screens.push(screen);
        screens.top()->activated();
      }
    }
  private:
    std::stack<Screen*> screens;

    ScreenManager(const ScreenManager&);
    ScreenManager& operator=(const ScreenManager&);
  };
}

#endif
