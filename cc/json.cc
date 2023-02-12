// {}
// []
// int64,
// float64,
// string

#include <string>

enum TokenType {
  COMMA,   // ,
  COLON,   // :
  LBRACE,  // {
  RBRACE,  // }
  LBRAKET, // [
  RBRAKET, // ]
  INT,     // 123
  DOUBLE,  // 123.123
  LQUOTE,  // "
  RQUOTE,  // "
  ID,      // abc
};

class Parser {
public:
  Parser() {}
  ~Parser() {}
};

int main(int argc, char *argv[]) {
  // JSON Parser

  return 0;
}