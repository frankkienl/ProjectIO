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
#ifndef MazeStateHPP
#define MazeStateHPP

#include <cstdint>
#include "State.hpp"
#include "Map.hpp"
#include "StateMachine.hpp"

namespace io {
  enum class MazeAnimationState {
    TURNING_LEFT,
    TURNING_RIGHT,
    MOVING_FORWARD,
    MOVING_BACKWARD,
  };

  class MazeState : public State {
  public:
    MazeState(StateMachine* stateMachine);
    virtual ~MazeState();

    virtual void tick();
    virtual void draw(Graphics* g);
    virtual void handleInputEvent(const InputEvent& event);
    virtual void onActivate();

    void movePlayerForward();
    void movePlayerBackward();
    void turnPlayerLeft();
    void turnPlayerRight();
  private:
    uint32_t currentFloor;
    Map* currentMap;
    Facing playerFacing;
    int32_t playerX;
    int32_t playerY;
    StateMachine* stateMachine;

    bool inputDisabled;
    uint32_t inputDisabledTicks;
    MazeAnimationState animationState;
    float cameraX;
    float cameraY;
    float cameraAngle;
  };
}

#endif
