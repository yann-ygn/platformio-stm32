#include "string.hpp"

using namespace util;

size_t String::length(const char* t_string) {
  size_t count = 0;

  while(t_string[count]) {
    ++count;
  }

  return count;
}

char* concatenate(char* t_string1, char* t_string2) {
  
}