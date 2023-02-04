#include "ylloc.h"
#include <climits>
#include <cstddef>

template <typename T> class allocator {
public:
  using value_type = T;
  using size_type = size_t;
  using ptr = T *;
  using const_ptr = const T *;
  using ref = T &;
  using const_ref = const T &;
  using difference_type = ptrdiff_t;

  template <typename U> struct rebind { using other = allocator<U>; };

  ptr allocate(size_type n, const void *hint = 0) {
    return ylloc::_allocate((difference_type)n, (ptr)0);
  }

  void deallocate(ptr p, size_type n) { ylloc::_deallocate(p); }

  void construct(ptr p, const T &value) { ylloc::_construct(p, value); }

  void destory(ptr p) { ylloc::_destory(p); }

  ptr address(ref x) { return ptr(x); }

  const_ptr const_address(const_ref x) { return (const_ptr)&x; }

  size_type max_size() const { return size_type(UINT_MAX / sizeof(T)); }
};