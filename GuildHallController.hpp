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
#ifndef GuildHallControllerHPP
#define GuildHallControllerHPP

#include <exception>
#include "NamingScreen.hpp"
#include "ClassSelectionScreen.hpp"
#include "GuildHallMainScreen.hpp"
#include "ScreenManager.hpp"
#include "InputEvent.hpp"
#include "NewCharacterController.hpp"
#include "PartyOrganizationController.hpp"

namespace io {
  class GuildHallController : public InputEventListener, MenuActionListener,
                                     ScreenEventListener {
  public:
    GuildHallController(ScreenManager* screenManager, Guild* guild,
                        Party* party) {
      if (!screenManager) {
        //FIXME:  Change this to something more useful.
        throw std::exception();
      }

      if (!guild) {
        throw std::exception();
      }

      if (!party) {
        throw std::exception();
      }

      this->screenManager = screenManager;
      this->guild = guild;

      newCharacterController = new NewCharacterController(screenManager, guild);
      partyOrganizationController = new PartyOrganizationController(screenManager,
                                                                    guild,
                                                                    party);
      guildHallMainScreen = new GuildHallMainScreen();

      newCharacterMenuItem = guildHallMainScreen->getNewCharacterMenuItem();
      organizePartyMenuItem = guildHallMainScreen->getOrganizeMenuItem();

      guildHallMainScreen->addInputEventListener(this);
      guildHallMainScreen->getMainMenu()->addMenuActionListener(this);
      guildHallMainScreen->addScreenEventListener(this);
    }

    virtual ~GuildHallController() {
      delete guildHallMainScreen;
      delete newCharacterController;
      delete partyOrganizationController;
    }

    virtual bool handleInputEvent(const InputEvent& event) {
      if (event.getState() == InputEventState::DOWN) {
        if (event.getType() == InputEventType::CANCEL) {
          screenManager->popScreen();
        }
      }

      return false;
    }

    virtual void onMenuItemSelected(Menu* notifier, MenuItem* which) {
      if (which == guildHallMainScreen->getNewCharacterMenuItem()) {
        newCharacterController->startNewCharacter();
      }
      else {
        if (which == guildHallMainScreen->getOrganizeMenuItem()) {
          partyOrganizationController->doPartyOrganization();
        }
      }
    }

    virtual void onScreenActivated(Screen* which) {
      if (guild->canCreateNewCharacter()) {
        newCharacterMenuItem->setEnabled(true);
      }
      else {
        newCharacterMenuItem->setEnabled(false);
      }

      if (guild->getCharacterCount() > 0) {
        organizePartyMenuItem->setEnabled(true);
      }
      else {
        organizePartyMenuItem->setEnabled(false);
      }
    }

    void switchTo() {
      screenManager->pushScreen(guildHallMainScreen);
    }
  private:
    Guild* guild;
    NewCharacterController* newCharacterController;
    MenuItem* newCharacterMenuItem;
    GuildHallMainScreen* guildHallMainScreen;
    MenuItem* organizePartyMenuItem;
    PartyOrganizationController* partyOrganizationController;
    ScreenManager* screenManager;
  };
}

#endif
