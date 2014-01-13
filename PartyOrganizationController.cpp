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
#include "PartyOrganizationController.hpp"
#include <exception>
#include <climits>
#include <iostream>

namespace io {
  PartyOrganizationController::PartyOrganizationController(ScreenManager* screenManager,
                                                           Guild* guild,
                                                           Party* party) {
    if (!screenManager) {
      throw std::exception();
    }

    if (!guild) {
      throw std::exception();
    }

    if (!party) {
      throw std::exception();
    }

    this->guild = guild;
    this->party = party;
    partyOrganizationScreen = new PartyOrganizationScreen();
    this->screenManager = screenManager;

    partyOrganizationScreen->addInputEventListener(this);
    partyOrganizationScreen->addScreenEventListener(this);

    partyOrganizationScreen->getGuildMenu()->addMenuActionListener(this);
    partyOrganizationScreen->getPartyMenu()->addMenuActionListener(this);

    addingCharID = 0;
    addingToParty = false;
    menuLocked = false;
  }

  PartyOrganizationController::~PartyOrganizationController() {
    if (partyOrganizationScreen) {
      delete partyOrganizationScreen;
    }
  }

  void PartyOrganizationController::doPartyOrganization() {
    screenManager->pushScreen(partyOrganizationScreen);
  }

  void PartyOrganizationController::onScreenActivated(Screen* which) {
    refreshScreen();
  }

  void PartyOrganizationController::onMenuItemSelected(Menu* notifier,
                                                       MenuItem* which) {
    if (notifier == partyOrganizationScreen->getGuildMenu()) {
      if (guild->getCharacter(which->getID())) {
        //  We're adding a character to the party.
        //  We disable the menu item to indicate that it's the selected item.
        which->setEnabled(false);
        partyOrganizationScreen->activatePartyMenu();
        menuLocked = true;
        addingToParty = true;
        addingCharID = which->getID();

        //  TODO:  Implement this.
        //  See if we can find an open slot in the party, then automatically
        //  select it.  If we can't, default to the first slot.
      }
    }
    else {
      if (addingToParty) {
        party->addCharacter(which->getID(), guild->getCharacter(addingCharID));
        menuLocked = false;
        addingToParty = false;
        addingCharID = 0;

        //  Switch back to guild menu.
        partyOrganizationScreen->activateGuildMenu();

        //  Also move the menu down one item.
        partyOrganizationScreen->getGuildMenu()->moveSelectionDown();
      }
      else {
        //  We're removing a character from the party.
        party->removeCharacter(which->getID());
      }

      refreshScreen();
    }
  }

  bool PartyOrganizationController::handleInputEvent(const InputEvent& event) {
    if (event.getState() == InputEventState::DOWN) {
      if (event.getType() == InputEventType::CANCEL) {
        //  What we do depends on what is currently going on.
        if (addingToParty) {
          addingToParty = false;
          addingCharID = 0;
          menuLocked = false;
          partyOrganizationScreen->activateGuildMenu();
          refreshScreen();
        }
        else {
          screenManager->popScreen();
        }

        return true;
      }

      if (event.getType() == InputEventType::LEFT && !menuLocked) {
        partyOrganizationScreen->activateGuildMenu();
        return true;
      }

      if (event.getType() == InputEventType::RIGHT && !menuLocked) {
        partyOrganizationScreen->activatePartyMenu();
        return true;
      }
    }

    return false;
  }

  void PartyOrganizationController::refreshScreen() {
    // On screen activation, we have to populate the menus.
    Menu* guildMenu = partyOrganizationScreen->getGuildMenu();
    guildMenu->clear();
    for (uint32_t i = 0; i < Guild::MAX_CHARACTERS; i++) {
      Character* c = guild->getCharacter(i);
      if (c) {
        guildMenu->addMenuItem(i, c->getName(), !party->hasCharacter(c));
      }
      else {
        guildMenu->addMenuItem(i, "---", true);
      }
    }

    Menu* partyMenu = partyOrganizationScreen->getPartyMenu();
    partyMenu->clear();
    for (uint32_t i = 0; i < Party::PARTY_MAX; i++) {
      Character* c = party->getCharacter(i);
      if (c) {
        partyMenu->addMenuItem(i, c->getName(), true);
      }
      else {
        partyMenu->addMenuItem(i, "---", true);
      }
    }
  }
}
