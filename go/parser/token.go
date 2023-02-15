package parser

type TokenType string

const (
	ILLEGAL   TokenType = "ILLGEAL"
	ID        TokenType = "ID"
	NUMBER    TokenType = "NUMBER"
	LBRACE    TokenType = "{"
	RBRACE    TokenType = "}"
	LBRAKET   TokenType = "["
	RBRAKET   TokenType = "]"
	COMMA     TokenType = ","
	COLON     TokenType = ":"
	QUOTE     TokenType = "\""
	EOF       TokenType = "EOF"
	ASSIGN    TokenType = "="
	PLUS      TokenType = "+"
	MINUS     TokenType = "-"
	BANG      TokenType = "!"
	ASTERISK  TokenType = "*"
	SLASH     TokenType = "/"
	FUNCTION  TokenType = "FUNCTION"
	LET       TokenType = "LET"
	TRUE      TokenType = "TRUE"
	FALSE     TokenType = "FALSE"
	IF        TokenType = "IF"
	ELSE      TokenType = "ELSE"
	RETURN    TokenType = "RETURN"
	EQ        TokenType = "=="
	NEQ       TokenType = "!="
	SEMICOLON TokenType = ";"
	LT        TokenType = "<"
	GT        TokenType = ">"
)

type Token struct {
	Type    TokenType
	Literal string
}

var keyworkds = map[string]TokenType{
	"fn":     FUNCTION,
	"let":    LET,
	"true":   TRUE,
	"false":  FALSE,
	"if":     IF,
	"else":   ELSE,
	"return": RETURN,
}

func lookupIdent(literal string) TokenType {
	if tt, ok := keyworkds[literal]; ok {
		return tt
	}
	return ID
}
