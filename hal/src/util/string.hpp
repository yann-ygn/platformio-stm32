#pragma once

#include <cstdint>
#include <cstddef>

namespace util {
  struct String {
    static size_t length(const char* t_string);
    static char* concatenate(char* t_string1, char* t_string2);
  };
}