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
#include "Class.hpp"
#include "tinyxml2.h"
#include <boost/filesystem.hpp>
#include <stdexcept>

using namespace boost::filesystem;
using namespace tinyxml2;

namespace io {
  Class::Class(const std::string& filename) {
    path p(filename);
    if (exists(p) && is_regular_file(p)) {
      XMLDocument doc;
      if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
        throw std::runtime_error("Class::Class:  Could not load file.");
      }

      XMLElement* root = doc.RootElement();
      if (std::string(root->Name()).compare("class") == 0) {
        XMLElement* nameNode = root->FirstChildElement("name");
        XMLElement* shortNameNode = root->FirstChildElement("shortName");
        XMLElement* levelNode = root->FirstChildElement("level");

        if (!nameNode) {
          throw std::runtime_error("Class::Class:  No name node found.");
        }

        if (!shortNameNode) {
          throw std::runtime_error("Class::Class:  No short name node found.");
        }

        if (!levelNode) {
          throw std::runtime_error("Class::Class:  No level nodes found.");
        }

        name = std::string(nameNode->GetText());
        shortName = std::string(shortNameNode->GetText());

        int16_t level = 0;
        while (levelNode) {
          if (level >= Class::MAX_LEVEL) {
            throw std::runtime_error("Class::Class:  Too many level nodes.");
          }

          XMLElement* hpNode = levelNode->FirstChildElement("hp");
          XMLElement* tpNode = levelNode->FirstChildElement("tp");
          XMLElement* strNode = levelNode->FirstChildElement("str");
          XMLElement* vitNode = levelNode->FirstChildElement("vit");
          XMLElement* tecNode = levelNode->FirstChildElement("tec");
          XMLElement* agiNode = levelNode->FirstChildElement("agi");
          XMLElement* lukNode = levelNode->FirstChildElement("luk");

          int hp = 0;
          hpNode->QueryIntText(&hp);

          int tp = 0;
          tpNode->QueryIntText(&tp);

          int str = 0;
          strNode->QueryIntText(&str);

          int vit = 0;
          vitNode->QueryIntText(&vit);

          int tec = 0;
          tecNode->QueryIntText(&tec);

          int agi = 0;
          agiNode->QueryIntText(&agi);

          int luk = 0;
          lukNode->QueryIntText(&luk);

          stats[level].hp = hp;
          stats[level].tp = tp;
          stats[level].str = str;
          stats[level].vit = vit;
          stats[level].tec = tec;
          stats[level].agi = agi;
          stats[level].luk = luk;

          levelNode = levelNode->NextSiblingElement("level");
          level++;
        }

        /**
         * For now, if less than 70 levels are specified, we fill the rest of
         * the table with the last specified level.
         */
        for (int16_t i = level; i < Class::MAX_LEVEL; i++) {
          stats[i] = stats[level - 1];
        }
      }
    }
  }
}
