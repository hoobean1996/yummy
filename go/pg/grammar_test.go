package pg

import "testing"

func TestCase1(t *testing.T) {
	bnf := `E => E '+' T | E '-' T | T;
	T => T '*' F | T '/' F | F;
	@token whitespace [\t\n\n]*;
	@token number \d+;
	`
	lexer := NewBNFLexer(bnf)
	expect := []BNFToken{
		// E => E '+' T | E '-' T | T;
		{Symbol, "E"}, {ARROW, "=>"}, {Symbol, "E"}, {Literal, "+"}, {Symbol, "T"}, {OR, "|"}, {Symbol, "E"}, {Literal, "-"}, {Symbol, "T"}, {OR, "|"}, {Symbol, "T"}, {Colon, ";"},
		{Symbol, "T"}, {ARROW, "=>"}, {Symbol, "T"}, {Literal, "*"}, {Symbol, "F"}, {OR, "|"}, {Symbol, "T"}, {Literal, "/"}, {Symbol, "F"}, {OR, "|"}, {Symbol, "F"}, {Colon, ";"},
		{Macro, "@token"}, {Symbol, "whitespace"}, {Literal, `[\t\n\n]*`}, {Colon, ";"},
		{Macro, "@token"}, {Symbol, "number"}, {Literal, `\d+`}, {Colon, ";"},
	}
	for i := 0; i < len(expect); i++ {
		tok := lexer.NextToken()
		if tok.Type == EOF {
			break
		}
		if expect[i].Type != tok.Type || expect[i].Literal != tok.Literal {
			t.Error("failed on i", i, expect[i], "!=", tok)
			t.FailNow()
		}
	}
}
