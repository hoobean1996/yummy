#pragma once

#include <climits>
#include <cstddef> // ptrdiff_t, size_t
#include <cstddef>
#include <glog/logging.h>
#include <new> // placement new

namespace ylloc {
template <typename T> inline T *_allocate(ptrdiff_t size, T *) {
  std::set_new_handler(nullptr);
  T *tmp = (T *)(::operator new((size_t)(size * sizeof(T))));
  if (tmp == nullptr) {
    LOG(ERROR) << "out of memory";
    return;
  }
  return tmp;
}

template <typename T> inline void _deallocate(T *buffer) {
  ::operator delete(buffer);
}

template <typename T1, typename T2>
inline void _construct(T1 *p, const T2 &value) {
  new (p) T1(value);
}

template <typename T> inline void _destory(T *ptr) { ptr->~T(); }
} // namespace ylloc