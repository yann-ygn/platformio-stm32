#pragma once

#include <cstdint>
#include <cstddef>

namespace util {
  template <typename T, size_t S>
  class CircBuff {
    public:
      CircBuff() = default;

      bool isEmpty() const {
        return (!m_full && (m_head == m_tail));
      }

      bool isFull() const {
        return m_full;
      }

      size_t capacity() const {
        return m_maxSize;
      }

    private:
      T m_buffer[S];

      size_t m_maxSize = S;
      size_t m_head = 0;
      size_t m_tail = 0;
      bool m_full = false;
  };
}
