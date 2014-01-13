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
#ifndef TownMainScreenHPP
#define TownMainScreenHPP

#include <cstdint>
#include "Screen.hpp"
#include "Menu.hpp"
#include "MenuItem.hpp"

namespace io {
  class TownMainScreen : public Screen {
  public:
    const static uint32_t GUILDHALL_ID = 0;
    const static uint32_t LABYRINTH_ID = 1;

    TownMainScreen() {
      mainMenu = new Menu();

      guildHallMenuItem = mainMenu->addMenuItem(TownMainScreen::GUILDHALL_ID,
                                                "Guild Hall",
                                                true);

      labyrinthMenuItem = mainMenu->addMenuItem(TownMainScreen::LABYRINTH_ID,
                                                "Enter Labyrinth",
                                                true);

      addComponent(mainMenu);
      setFocusedComponent(mainMenu);
    };

    virtual ~TownMainScreen() {
      labyrinthMenuItem = nullptr;
      guildHallMenuItem = nullptr;
      delete mainMenu;
    }

    Menu* getMainMenu() const {
      return mainMenu;
    }

    MenuItem* getGuildHallMenuItem() const {
      return guildHallMenuItem;
    }

    MenuItem* getLabyrinthMenuItem() const {
      return labyrinthMenuItem;
    }
  private:
    Menu* mainMenu;
    MenuItem* guildHallMenuItem;
    MenuItem* labyrinthMenuItem;
  };
}

#endif
