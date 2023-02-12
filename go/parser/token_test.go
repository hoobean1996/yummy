package parser_test

import (
	"testing"

	"github.com/yummy/go/parser"
)

func TestNextToken(t *testing.T) {
	input := `[]12,{}abc""`

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
