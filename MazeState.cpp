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
#include "MazeState.hpp"
#include "Map.hpp"
#include "Common.hpp"
#include "Utility.hpp"

namespace io {
  MazeState::MazeState(StateMachine* stateMachine, Player* player) {
    currentFloor = 1;
    currentMap = Map::mapFromImage("data/map.png");
    this->player = player;
    inputDisabled = false;
    inputDisabledTicks = 0;
    animationState = MazeAnimationState::TURNING_LEFT;
    cameraX = 0;
    cameraY = 0;
    cameraAngle = 0;

    this->stateMachine = stateMachine;
  }

  MazeState::~MazeState() {
    delete currentMap;
  }

  void MazeState::tick() {
    if (inputDisabled) {
      inputDisabledTicks--;

      //if (inputDisabledTicks == 0) {
      inputDisabled = false;
      //}
    }
  }

  void MazeState::draw(Graphics* g) {
    g->setMatrixMode(MatrixMode::VIEW);
    g->loadIdentity();
    g->translate(cameraX, -6.0f, cameraY);
    g->rotate(cameraAngle, 0.0f, 1.0f, 0.0f);
    switch (player->getFacing()) {
    case Facing::NORTH:
      g->rotate(toRadians(0), 0.0f, 1.0f, 0.0f);
      break;
    case Facing::EAST:
      g->rotate(toRadians(90), 0.0f, 1.0f, 0.0f);
      break;
    case Facing::SOUTH:
      g->rotate(toRadians(180), 0.0f, 1.0f, 0.0f);
      break;
    case Facing::WEST:
      g->rotate(toRadians(270), 0.0f, 1.0f, 0.0f);
      break;
    default:
      break;
    }

    g->setMatrixMode(MatrixMode::MODEL);
    g->loadIdentity();

    currentMap->draw(g, player->getX(), player->getY());
  }

  void MazeState::handleInputEvent(const InputEvent& event) {
    if (event.getState() == InputEventState::DOWN) {
      switch (event.getType()) {
      case InputEventType::ACCEPT:
        activateActivatable();
        break;
      case InputEventType::UP:
        movePlayerForward();
        break;
      case InputEventType::DOWN:
        movePlayerBackward();
        break;
      case InputEventType::LEFT:
        turnPlayerLeft();
        break;
      case InputEventType::RIGHT:
        turnPlayerRight();
        break;
      default:
        break;
      }
    }
  }

  void MazeState::onActivate() {
    player->setX(7);
    player->setY(20);
    player->setFacing(Facing::NORTH);

    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraAngle = 0;
  }

  void MazeState::activateActivatable() {
    Activatable* activatable = nullptr;
    switch (player->getFacing()) {
    case Facing::NORTH:
      activatable = currentMap->getCell(player->getX(), player->getY() - 1)
          .getActivatable();
      break;
    case Facing::EAST:
      activatable = currentMap->getCell(player->getX() + 1, player->getY())
          .getActivatable();
      break;
    case Facing::SOUTH:
      activatable = currentMap->getCell(player->getX(), player->getY() + 1)
          .getActivatable();
      break;
    case Facing::WEST:
      activatable = currentMap->getCell(player->getX() - 1, player->getY())
          .getActivatable();
      break;
    }

    if (activatable) {
      activatable->activate(player);
    }
  }

  void MazeState::movePlayerForward() {
    if (inputDisabled) {
      return;
    }

    int32_t newX = player->getX();
    int32_t newY = player->getY();

    switch (player->getFacing()) {
    case Facing::NORTH:
      newY--;
      break;
    case Facing::EAST:
      newX++;
      break;
    case Facing::SOUTH:
      newY++;
      break;
    case Facing::WEST:
      newX--;
      break;
    }

    if (!currentMap->isCellSolid(newX, newY)) {
      player->setX(newX);
      player->setY(newY);
    }

    //animationState = MazeAnimationState::MOVING_FORWARD;
    //inputDisabledTicks = 30;
    //inputDisabled = true;
  }

  void MazeState::movePlayerBackward() {
    if (inputDisabled) {
      return;
    }

    int32_t newX = player->getX();
    int32_t newY = player->getY();

    switch (player->getFacing()) {
    case Facing::NORTH:
      newY++;
      break;
    case Facing::EAST:
      newX--;
      break;
    case Facing::SOUTH:
      newY--;
      break;
    case Facing::WEST:
      newX++;
      break;
    }

    if (!currentMap->isCellSolid(newX, newY)) {
      player->setX(newX);
      player->setY(newY);
    }

    //animationState = MazeAnimationState::MOVING_BACKWARD;
    //inputDisabledTicks = 30;
    //inputDisabled = true;
  }

  void MazeState::turnPlayerLeft() {
    if (inputDisabled) {
      return;
    }

    switch (player->getFacing()) {
    case Facing::NORTH:
      player->setFacing(Facing::WEST);
      break;
    case Facing::EAST:
      player->setFacing(Facing::NORTH);
      break;
    case Facing::SOUTH:
      player->setFacing(Facing::EAST);
      break;
    case Facing::WEST:
      player->setFacing(Facing::SOUTH);
      break;
    }

    //animationState = MazeAnimationState::TURNING_LEFT;
    //inputDisabledTicks = 30;
    //inputDisabled = true;
  }

  void MazeState::turnPlayerRight() {
    if (inputDisabled) {
      return;
    }

    switch (player->getFacing()) {
    case Facing::NORTH:
      player->setFacing(Facing::EAST);
      break;
    case Facing::EAST:
      player->setFacing(Facing::SOUTH);
      break;
    case Facing::SOUTH:
      player->setFacing(Facing::WEST);
      break;
    case Facing::WEST:
      player->setFacing(Facing::NORTH);
      break;
    }

    //animationState = MazeAnimationState::TURNING_RIGHT;
    //inputDisabledTicks = 30;
    //inputDisabled = true;
  }
}
