package parser

import "strconv"

type Lexer struct {
	input string

	position     int  // current position in input (current char)
	readPosition int  // current reading position in input (after current char)
	ch           byte // current char
}

func NewLexer(input string) *Lexer {
	l := &Lexer{input: input}
	l.readChar()
	return l
}

func (l *Lexer) readChar() {
	if l.readPosition >= len(l.input) {
		l.ch = 0
	} else {
		l.ch = l.input[l.readPosition]
	}
	l.position = l.readPosition
	l.readPosition += 1
}

func (l *Lexer) NextToken() Token {
	var tok Token

	l.skipWhitespace()

	switch l.ch {
	case '<':
		tok = Token{LT, "<"}
	case '>':
		tok = Token{GT, ">"}
	case '[':
		tok = Token{LBRAKET, "["}
	case ']':
		tok = Token{RBRAKET, "]"}
	case '{':
		tok = Token{LBRACE, "{"}
	case '}':
		tok = Token{RBRACE, "}"}
	case ',':
		tok = Token{COMMA, ","}
	case ':':
		tok = Token{COLON, ":"}
	case '"':
		tok = Token{QUOTE, "\""}
	case '=':
		if l.peerChar() == '=' {
			l.readChar()
			tok = Token{EQ, "=="}
		} else {
			tok = Token{ASSIGN, "="}
		}
	case '+':
		tok = Token{PLUS, "+"}
	case '-':
		tok = Token{MINUS, "-"}
	case '!':
		if l.peerChar() == '=' {
			l.readChar()
			tok = Token{NEQ, "!="}
		} else {
			tok = Token{BANG, "!"}
		}
	case '*':
		tok = Token{ASTERISK, "*"}
	case '/':
		tok = Token{SLASH, "/"}
	case ';':
		tok = Token{SEMICOLON, ";"}
	case 0:
		tok.Literal = ""
		tok.Type = EOF
	default:
		if isLetter(l.ch) {
			tok = Token{ID, l.readIdentifier()}
			tok.Type = lookupIdent(tok.Literal)
			return tok
		} else if isDigit(l.ch) {
			val, ok := l.readNumber()
			if ok {
				tok = Token{NUMBER, strconv.Itoa(val)}
				return tok
			}
			tok = Token{ILLEGAL, strconv.Itoa(val)}
			return tok
		} else {
			tok = Token{ILLEGAL, string(l.ch)}
		}
	}
	l.readChar()
	return tok
}

func (l *Lexer) readIdentifier() string {
	position := l.position
	for isLetter(l.ch) {
		l.readChar()
	}

	return l.input[position:l.position]
}

func isLetter(ch byte) bool {
	return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z'
}

func (l *Lexer) readNumber() (int, bool) {
	position := l.position
	for isDigit(l.ch) {
		l.readChar()
	}
	digits := l.input[position:l.position]

	v, err := strconv.Atoi(digits)
	if err != nil {
		return 0, false
	}
	return v, true
}

func isDigit(ch byte) bool {
	return ch >= '0' && ch <= '9'
}
func (l *Lexer) skipWhitespace() {
	for l.ch == ' ' || l.ch == '\t' || l.ch == '\n' || l.ch == '\r' {
		l.readChar()
	}
}

func (l *Lexer) peerChar() byte {
	if l.readPosition >= len(l.input) {
		return 0
	} else {
		return l.input[l.readPosition]
	}
}
