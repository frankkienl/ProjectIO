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
#ifndef GameHPP
#define GameHPP

#include "Guild.hpp"
#include "Party.hpp"
#include "Graphics.hpp"
#include "Screen.hpp"
#include "StateMachine.hpp"
#include "MazeState.hpp"
#include "TownState.hpp"
#include "InputEvent.hpp"
#include "ScreenManager.hpp"
#include <cstdint>
#include <stack>

namespace io {
  class Game : public StateMachine {
  public:
    Game();
    virtual ~Game();
    
    void draw(Graphics* g);
    
    void handleInputEvent(const InputEvent& event) {
      if (!screenManager->handleInputEvent(event)) {
        currentState->handleInputEvent(event);
      }
    }
    
    void tick();

    virtual void setState(const GameState state) {
      switch(state) {
        case GameState::TOWN:
          currentState = townState;
          break;
        case GameState::MAZE:
          currentState = mazeState;
          break;
        case GameState::BATTLE:
          return;
      }
      screenManager->clear();

      curGameState = state;
      currentState->onActivate();
    }
  private:
    ScreenManager* screenManager;
    State* currentState;
    Guild* guild;
    MazeState* mazeState;
    Party* party;
    TownState* townState;
    GameState curGameState;
  };
}

#endif // GameHPP
