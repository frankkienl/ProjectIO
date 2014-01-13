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
#ifndef InputTranslatorHPP
#define InputTranslatorHPP

#include "SDL.h"
#include "InputEvent.hpp"
#include <map>

/**
 *  A class that translates SDL key events into input events.
 */
namespace io {
  class InputTranslator {
  public:
    static InputTranslator* getInstance() {
      if (!InputTranslator::instance) {
        InputTranslator::instance = new InputTranslator();
      }

      return InputTranslator::instance;
    }

    void bindKeyToInputEvent(const SDL_Keycode key, const InputEventType event);
    InputEvent keyToEvent(const SDL_Event& event);
    InputEvent keyToEvent(const SDL_TextInputEvent& event);
  private:
    static InputTranslator* instance;

    std::map<SDL_Keycode, InputEventType> SDLtoIE;
    std::map<InputEventType, SDL_Keycode> IEtoSDL;

    InputTranslator();
    ~InputTranslator();
    InputTranslator(const InputTranslator&);
    InputTranslator& operator=(const InputTranslator&);
  };
}

#endif
