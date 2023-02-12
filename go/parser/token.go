package parser

type TokenType string

const (
	ILLEGAL TokenType = "ILLGEAL"
	ID      TokenType = "ID"
	NUMBER  TokenType = "NUMBER"
	LBRACE  TokenType = "{"
	RBRACE  TokenType = "}"
	LBRAKET TokenType = "["
	RBRAKET TokenType = "]"
	COMMA   TokenType = ","
	COLON   TokenType = ":"
	QUOTE   TokenType = "\""
	EOF     TokenType = "EOF"
)

type Token struct {
	Type    TokenType
	Literal string
}
