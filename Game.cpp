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
#include "Game.hpp"
#include "Utility.hpp"

namespace io {
  Game::Game() {
    screenManager = new ScreenManager();
    guild = new Guild();
    party = new Party();
    currentState = nullptr;
    curGameState = GameState::MAZE;
    mazeState = new MazeState(this);
    townState = new TownState(this, screenManager, guild, party);

    currentState = townState;
    townState->onActivate();
  }
  
  Game::~Game() {
    if (mazeState) {
      delete mazeState;
    }
  }
  
  void Game::draw(Graphics* g) {
    currentState->draw(g);
    screenManager->draw(g);
  }

  void Game::tick() {
    currentState->tick();
  }
}
