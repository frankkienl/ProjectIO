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
#include "Log.hpp"
#include <stdexcept>
#include <cstdarg>
namespace io {
  FILE* log = nullptr;
  
  void initLog() {
    log = fopen("log.txt", "w");
    if (!log) {
      throw std::runtime_error("initLog");
    }
  }
  
  void writeToLog(const MessageLevel level, const std::string& fmtStr, ...) {
    switch(level) {
    case MessageLevel::INFO:
      fprintf(log, "INFO:  ");
      break;
    case MessageLevel::WARNING:
      fprintf(log, "WARNING:  ");
      break;
    case MessageLevel::ERROR:
      fprintf(log, "ERROR:  ");
      break;
    }
    
    va_list args;
    va_start(args, fmtStr);
    vfprintf(log, fmtStr.c_str(), args);
    va_end(args);
  }
}
