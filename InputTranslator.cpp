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
#include "InputTranslator.hpp"

namespace io {
  InputTranslator* InputTranslator::instance = nullptr;

  InputTranslator::InputTranslator() {
  }

  void InputTranslator::bindKeyToInputEvent(const SDL_Keycode key, const InputEventType event) {
    if (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_LEFT || SDLK_RIGHT ||
        key == SDLK_ESCAPE || key == SDLK_RETURN) {
      return;
    }

    if (IEtoSDL.count(event) > 0) {
      // We're gonna need to unbind the old.
      IEtoSDL.erase(event);
      SDLtoIE.erase(key);
    }

    SDLtoIE[key] = event;
    IEtoSDL[event] = key;
  }

  InputEvent InputTranslator::keyToEvent(const SDL_Event& event) {
    /**
     * A set of constant bound keys.  These are always bound, no
     * matter what.  And cannot be unbound.  These keys also
     * cannot be used for anything else.  This is to ensure that
     * the player always has some way to exit menus and move about
     * even if they mess up their bindings so spectacularly they
     * can't do anything.
     */

    InputEventState state = InputEventState::DOWN;
    if (event.type == SDL_KEYUP) {
      state = InputEventState::UP;
    }

    switch(event.key.keysym.sym) {
      case SDLK_ESCAPE:
        return InputEvent(InputEventType::CANCEL, state, '\x1B');
      case SDLK_RETURN:
        return InputEvent(InputEventType::ACCEPT, state, '\x13');
      case SDLK_UP:
        return InputEvent(InputEventType::UP, state, '\x00');
      case SDLK_DOWN:
        return InputEvent(InputEventType::DOWN, state, '\x00');
      case SDLK_LEFT:
        return InputEvent(InputEventType::LEFT, state, '\x00');
      case SDLK_RIGHT:
        return InputEvent(InputEventType::RIGHT, state, '\x00');
      default:
        break;
    }

    return InputEvent(InputEventType::NOT_BOUND, state, 0);
  }
}
