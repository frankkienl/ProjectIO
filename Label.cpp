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
#include "Label.hpp"
#include "Common.hpp"
#include "BoundingBox.hpp"
#include "ResourceManager.hpp"

namespace io {
  Label::Label() {
    ResourceManager* rm = ResourceManager::getInstance();
    font = rm->getResource("data/DejaVuSansMono.ttf")->toFont();
    horizontalAlignment = HAlign::LEFT;
    verticalAlignment = VAlign::TOP;
  }

  void Label::render(Graphics* g) {
    Font *f = getFont();
    if (f) {
      BoundingBox box = f->getTextBoundingBox(getText());

      float xOffset = 0.0f;
      float yOffset = 0.0f;

      switch(getHorizontalAlignment()) {
        case HAlign::LEFT:
          xOffset = 0.0f;
          break;
        case HAlign::MIDDLE:
          xOffset = (getWidth() / 2.0f) - (box.w / 2.0f);
          break;
        case HAlign::RIGHT:
          xOffset = getWidth() - box.w;
          break;
      }

      switch(getVerticalAlignment()) {
        case VAlign::TOP:
          yOffset = 0.0f;
          break;
        case VAlign::MIDDLE:
          yOffset = (getHeight() / 2.0f) - (box.h / 2.0f);
          break;
        case VAlign::BOTTOM:
          yOffset = getHeight() - box.h;
          break;
      }

      g->translate(xOffset, yOffset, 0.0f);
      f->drawText(getText(), Colour(127, 0, 255, 255));
    }
  }
}
