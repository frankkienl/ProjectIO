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
#ifndef MenuItemHPP
#define MenuItemHPP

#include <cstdint>
#include <string>

namespace io {
  class MenuItem {
  public:
    MenuItem(const uint32_t id, const std::string text, bool enabled) {
      this->id = id;
      this->text = text;
      this->enabled = enabled;
    }

    bool isEnabled() {
      return enabled;
    }

    /**
     * Returns the ID of the menu item.  The ID cannot be changed after the
     * menu item is instantiated.
     */
    uint32_t getID() const {
      return id;
    }

    std::string getText() const {
      return text;
    }

    void setEnabled(const bool enabled) {
      this->enabled = enabled;
    }

    void setText(const uint32_t text) {
      this->text = text;
    }
  private:
    bool enabled;
    uint32_t id;
    std::string text;
  };
}

#endif
