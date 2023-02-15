package parser_test

import (
	"testing"

	"github.com/yummy/go/parser"
)

func TestString(t *testing.T) {
	program := &parser.Program{
		Statements: []parser.Statement{
			&parser.LetStatement{
				Token: parser.Token{Type: parser.LET, Literal: "let"},
				Name: &parser.Identifier{
					Token: parser.Token{parser.ID, "myvar"},
					Value: "myvar",
				},
				Value: &parser.Identifier{
					Token: parser.Token{parser.ID, "another"},
					Value: "another",
				},
			},
		},
	}

	if program.String() != "let myvar = another;" {
		t.Errorf("program.String() wrong. got=%q", program.String())
	}
}
