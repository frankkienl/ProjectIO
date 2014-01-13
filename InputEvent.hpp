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
#ifndef InputEventHPP
#define InputEventHPP

#include <cstdint>

/**
 * This file contains an enumeration of all possible input events.  Currently
 * this includes just up, down, left, right button presses, accept and back.
 */
namespace io {
  enum class InputEventType : uint32_t {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ACCEPT,
    CANCEL,
    NOT_BOUND,
  };

  enum class InputEventState : bool {
    UP,
    DOWN,
  };

  class InputEvent {
  public:
    InputEvent(const InputEventType type, const InputEventState state,
               const char charCode) {
      this->type = type;
      this->state = state;
      this->charCode = charCode;
    }

    char16_t getCharCode() const {
      return charCode;
    }

    InputEventType getType() const {
      return type;
    }

    InputEventState getState() const {
      return state;
    }
  private:
    InputEventType type;
    InputEventState state;
    char charCode;
  };

  class InputEventListener {
  public:
    virtual ~InputEventListener() { }
    virtual bool handleInputEvent(const InputEvent& event) = 0;
  private:
  };
}

#endif
