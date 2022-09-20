#pragma once

#include <cstdint>
#include <cstddef>

namespace util {
  template <typename T, size_t S>
  class CircBuff {
    public:
      CircBuff() = default;

      void putItem(T t_item) {
        m_buffer[m_head] = t_item;

        if (m_full) {
          m_tail = (m_tail + 1) % m_maxSize;
        }

        m_head = (m_head + 1) % m_maxSize;
        m_full = (m_head == m_tail);
      }

      T getItem() {
        if (! isEmpty())
        {
          T data = m_buffer[m_tail];
          m_full = false;
          m_tail = (m_tail + 1) % m_maxSize;

          return data;
        }
      }

      bool isEmpty() const {
        return (m_head == m_tail);
      }

      bool isFull() const {
        return m_full;
      }

      size_t getCapacity() const {
        size_t size = m_maxSize;

        if (! m_full) {
          if (m_head >= m_tail) {
            size = m_head - m_tail;
          } else {
            size = m_maxSize + m_head - m_tail;
          }
        }

        return size;
      }

      size_t getMaxSize() const {
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
