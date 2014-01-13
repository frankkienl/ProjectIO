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
#ifndef PartyOrganizationControllerHPP
#define PartyOrganizationControllerHPP

#include "PartyOrganizationScreen.hpp"
#include "InputEvent.hpp"
#include "ScreenManager.hpp"
#include "Party.hpp"
#include "Guild.hpp"

/**
 * Basic process to design this:
 * 1) Implement the screen.  The screen contains two menus.  One on each side,
 * six elements visible.
 * 2) When LEFT or RIGHT input events occur, switch focus to the specified
 * menu.
 * 3) Populate left menu with guild members.
 * 4) Populate right menu with party members.
 * 5) When an item in the left menu is selected, switch focus to the right menu
 * while also disabling the selected left menu item.
 * 6) If #5 is canceled, switch back to the left menu, re-enable item.
 * 7) If #5 is followed by ACCEPT, place the character in the party at the
 * specified location.  Keep left menu item disabled.
 * 8) If party member exists in spot chosen for #7, re-enable their left menu
 * item.
 */
namespace io {
  class PartyOrganizationController : public MenuActionListener,
                                             ScreenEventListener,
                                             InputEventListener {
  public:
    PartyOrganizationController(ScreenManager* screenManager, Guild* guild,
                                Party* party);
    virtual ~PartyOrganizationController();

    void doPartyOrganization();

    virtual void onScreenActivated(Screen* which);
    virtual void onMenuItemSelected(Menu* notifier, MenuItem* which);
    virtual bool handleInputEvent(const InputEvent& event);
  private:
    Guild* guild;
    Party* party;
    PartyOrganizationScreen* partyOrganizationScreen;
    ScreenManager* screenManager;

    uint32_t addingCharID;
    bool addingToParty;
    bool menuLocked;

    void refreshScreen();
  };
}

#endif
