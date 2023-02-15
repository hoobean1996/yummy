package parser_test

import (
	"testing"

	"github.com/yummy/go/parser"
)

func TestNextToken(t *testing.T) {
	input := `[]12,{}abc""=+-!*/ fn let true false if else return == !=`

	tests := []struct {
		expectedType    parser.TokenType
		expectedLiteral string
	}{
		{parser.LBRAKET, "["},
		{parser.RBRAKET, "]"},
		{parser.NUMBER, "12"},
		{parser.COMMA, ","},
		{parser.LBRACE, "{"},
		{parser.RBRACE, "}"},
		{parser.ID, "abc"},
		{parser.QUOTE, "\""},
		{parser.QUOTE, "\""},
		{parser.ASSIGN, "="},
		{parser.PLUS, "+"},
		{parser.MINUS, "-"},
		{parser.BANG, "!"},
		{parser.ASTERISK, "*"},
		{parser.SLASH, "/"},
		{parser.FUNCTION, "fn"},
		{parser.LET, "let"},
		{parser.TRUE, "true"},
		{parser.FALSE, "false"},
		{parser.IF, "if"},
		{parser.ELSE, "else"},
		{parser.RETURN, "return"},
		{parser.EQ, "=="},
		{parser.NEQ, "!="},
	}

	l := parser.NewLexer(input)

	for i, tt := range tests {
		tok := l.NextToken()

		if tok.Type != tt.expectedType {
			t.Fatalf("tests[%d] - tokentype wrong. expected=%q, got=%q",
				i, tt.expectedType, tok.Type)
		}
		if tok.Literal != tt.expectedLiteral {
			t.Fatalf("tests[%d] - literal wrong. expected=%q, got=%q", i, tt.expectedLiteral, tok.Literal)
		}
	}
}

func TestNextTokenComplex(t *testing.T) {
	input := `{"name": "hebin"}`

	tests := []struct {
		expectedType    parser.TokenType
		expectedLiteral string
	}{
		{parser.LBRACE, "{"},
		{parser.QUOTE, "\""},
		{parser.ID, "name"},
		{parser.QUOTE, "\""},
		{parser.COLON, ":"},
		{parser.QUOTE, "\""},
		{parser.ID, "hebin"},
		{parser.QUOTE, "\""},
		{parser.RBRACE, "}"},
	}

	l := parser.NewLexer(input)
	for i, tt := range tests {
		tok := l.NextToken()

		if tok.Type != tt.expectedType {
			t.Fatalf("tests[%d] - tokentype wrong. expected=%q, got=%q",
				i, tt.expectedType, tok.Type)
		}
		if tok.Literal != tt.expectedLiteral {
			t.Fatalf("tests[%d] - literal wrong. expected=%q, got=%q", i, tt.expectedLiteral, tok.Literal)
		}
	}
}
