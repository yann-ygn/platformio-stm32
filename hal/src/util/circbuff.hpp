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

        if (isFull()) {
          m_tail = (m_tail + 1) % m_maxSize;
        }

        m_head = (m_head + 1) % m_maxSize;
        m_full = (m_head == m_tail);
      }

      void putItems(const T* t_items, size_t t_len) {
        copy(t_items, &m_buffer[m_head], t_len)
      }

      T getItem() {
        if (isEmpty()) {
          return;
        }

        T item = m_buffer[m_tail];
        m_full = false;
        m_tail = (m_tail + 1) % m_maxSize;

        return item;
      }

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

      void copy(T* t_dest, const T* t_src, size_t t_len) {
        while (t_len--) {
          *t_dest++ = *t_src++;
        }
      }
  };
}
