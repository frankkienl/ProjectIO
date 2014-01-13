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
#ifndef ResourceHPP
#define ResourceHPP

namespace io {
  /**
   *  To add a new resource type, forward declare it's class here, then add
   *  a method to the following interface that returns a pointer to the
   *  resource type, returning nullptr.  In the implementing class, override
   *  the method, and return "this".
   */

  class Class;
  class Font;
  class Image;
  class OBJModel;
  
  class Resource {
  public:
    Resource() {}
    virtual ~Resource() {}
    
    virtual Class* toClass() {
      return nullptr;
    }

    virtual Font* toFont() {
      return nullptr;
    }

    virtual Image* toImage() {
      return nullptr;
    }

    virtual OBJModel* toOBJModel() {
      return nullptr;
    }
  private:
  };
}

#endif // ResourceHPP
