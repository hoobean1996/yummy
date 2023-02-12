#include <bits/stdint-intn.h>
#include <cstddef>
#include <iostream>

template <int64_t N, int64_t D = 1> class Number {
public:
  static const int64_t number = N;
  static const int64_t denom = D;
};

template <bool flag> class Boolean {
public:
  static const bool value = flag;
};

template <char... C> class Symbol {
  static constexpr char const value[sizeof...(C) + 1] = {C..., '\0'};
};

template <typename T, typename U> class Pair {
  using car_ = T;
  using cdr_ = U;
};

template <typename X> class Car { using type = typename X::car_; };

template <typename X> class Cdr { using type = typename X::cdr_; };

template <typename T, typename U> struct Cons : public Pair<T, U> {};

class Null {};

template <typename... T> class List;

template <typename T> class List<T> : public Pair<T, Null> {};

template <typename T, typename... X>
class List<T, X...> : public Pair<T, List<X...>> {};

class BooleanTag {
  static constexpr bool is_pair = false;
  static constexpr bool is_null = false;
  static constexpr bool is_number = false;
  static constexpr bool is_boolean = true;
  static constexpr bool is_symbol = false;
};

class SymbolTag {
  static constexpr bool is_pair = false;
  static constexpr bool is_null = false;
  static constexpr bool is_number = false;
  static constexpr bool is_boolean = false;
  static constexpr bool is_symbol = true;
};

template <bool cond, typename Then, typename Else> class If {};

template <typename Then, typename Else> class If<true, Then, Else> {
public:
  using result = Then;
};

template <typename Then, typename Else> class If<false, Then, Else> {
public:
  using result = Else;
};

int main(int argc, char *argv[]) {
  constexpr int value = Number<5, 1>::number;
  constexpr int denom = Number<5, 1>::denom;

  constexpr int t = Boolean<true>::value;
  constexpr int f = Boolean<false>::value;
  constexpr int ifvalue = If<true, Number<5, 1>, Number<5, 1>>::result::number;
  std::cout << "value=" << value << ",denom" << denom << std::endl;
  std::cout << "t" << t << std::endl;
  std::cout << "f" << f << std::endl;
  std::cout << "ifvalue=" << ifvalue << std::endl;
  return 0;
}