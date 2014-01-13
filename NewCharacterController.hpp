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
#ifndef NewCharacterControllerHPP
#define NewCharacterControllerHPP

#include "NamingScreen.hpp"
#include "ClassSelectionScreen.hpp"
#include "InputEvent.hpp"
#include "ScreenManager.hpp"
#include "ResourceManager.hpp"
#include "Character.hpp"
#include "Log.hpp"
#include "Guild.hpp"

/**
 * Basically, this class handles all of character creation.  So switching
 * between the naming and character selection screens.
 */
namespace io {
  class NewCharacterController : public InputEventListener,
                                        EditBoxActionListener,
                                        MenuActionListener {
  public:
    NewCharacterController(ScreenManager* screenManager, Guild* guild) {
      if (!screenManager) {
        throw std::invalid_argument("NewCharacterController::NewCharacterController:  nullptr screen manager");
      }

      if (!guild) {
        throw std::invalid_argument("NewCharacterController::NewCharacterController:  nullptr guild");
      }

      namingScreen = new NamingScreen();
      classSelectionScreen = new ClassSelectionScreen();

      namingScreen->addInputEventListener(this);
      namingScreen->getNameEntryBox()->addEditBoxActionListener(this);

      classSelectionScreen->addInputEventListener(this);
      classSelectionScreen->getClassMenu()->addMenuActionListener(this);

      this->screenManager = screenManager;

      name = "";
      classID = 0;
      this->guild = guild;
    }

    virtual ~NewCharacterController() {
      delete classSelectionScreen;
      delete namingScreen;
    }

    virtual bool handleInputEvent(const InputEvent& event) {
      if (event.getType() == InputEventType::CANCEL) {
        screenManager->popScreen();
      }

      return false;
    }

    virtual void onEditBoxTextChanged(EditBox* which) {
    }

    virtual void onEditBoxTextEntered(EditBox* which) {
      //  Continue on to class selection.
      screenManager->pushScreen(classSelectionScreen);

      name = namingScreen->getNameEntryBox()->getText();
    }

    virtual void onMenuItemSelected(Menu* notifier, MenuItem* which) {
      classID = which->getID();

      Class* c = ResourceManager::getInstance()->getClasses().at(classID);

      Character* character = new Character();
      character->setClass(c);
      character->setName(name);

      guild->addCharacter(character);

      //  Go back to the guild hall.
      screenManager->popScreen();
      screenManager->popScreen();
    }

    /**
     * Just pushes the initial naming screen up.  Also resets everything else.
     */
    void startNewCharacter() {
      name = "";
      classID = 0;

      namingScreen->getNameEntryBox()->setText("");

      screenManager->pushScreen(namingScreen);

      Menu* menu = classSelectionScreen->getClassMenu();
      menu->clear();
      uint32_t id = 0;
      for (Class* c : ResourceManager::getInstance()->getClasses()) {
        menu->addMenuItem(id, c->getName(), true);
        id++;
      }
    }
  private:
    NamingScreen* namingScreen;
    ClassSelectionScreen* classSelectionScreen;
    ScreenManager* screenManager;

    std::string name;
    uint32_t classID;
    Guild* guild;
  };
}

#endif
