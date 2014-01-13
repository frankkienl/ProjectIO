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
#include "Menu.hpp"
#include "ResourceManager.hpp"
#include <climits>

namespace io {
  Menu::Menu() {
    ResourceManager* rm = ResourceManager::getInstance();
    font = rm->getResource("data/DejaVuSansMono.ttf")->toFont();
    maxVisibleItems = UINT32_MAX;
    menuSelection = 0;
    windowEnd = maxVisibleItems;
    windowStart = 0;
  }

  void Menu::moveSelectionDown() {
    uint32_t newSelection = (menuSelection + 1);
    if (newSelection >= menuItems.size()) {
      //  We exceeded the end of the menu.
      newSelection = 0;
    }

    /*
    while (newSelection != menuSelection) {
      if (menuItems.at(newSelection)->isEnabled()) {
        break;
      }

      newSelection += 1;
      if (newSelection >= menuItems.size()) {
        newSelection = 0;
      }
    }
    */

    menuSelection = newSelection;
    validateWindow();
  }

  void Menu::moveSelectionUp() {
    uint32_t newSelection = (menuSelection - 1);
    if (newSelection > menuItems.size()) {
      //  We exceeded the top of the menu.
      newSelection = menuItems.size() - 1;
    }

    /*
    while (newSelection != menuSelection) {
      if (menuItems.at(newSelection)->isEnabled()) {
        break;
      }

      newSelection -= 1;
      if (newSelection > menuItems.size()) {
        newSelection = menuItems.size() - 1;
      }
    }
    */

    menuSelection = newSelection;
    validateWindow();
  }

  void Menu::render(Graphics* g) {
    Font* f = getFont();
    if (f) {
      for (uint32_t i = windowStart; i < menuItems.size() && i < windowEnd; i++) {
        MenuItem* item = menuItems.at(i);

        BoundingBox textBox = f->getTextBoundingBox(item->getText());
        Colour c;
        if (item->isEnabled()) {
          if (i == menuSelection) {
            c = Colour(255, 204, 0, 255);
          }
          else {
            c = Colour(255, 255, 255, 255);
          }
        }
        else {
          if (i == menuSelection) {
            c = Colour(64, 51, 0, 255);
          }
          else {
            c = Colour(64, 64, 64, 255);
          }
        }

        f->drawText(item->getText(), c);
        g->translate(0, textBox.h, 0);
      }
    }
  }
}
