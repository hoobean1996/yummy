package pg

import "log"

type BNFTokenType string

// E => E '+' T | E '-' T | T;
// T => T '*' F | T '/' F | F;
// F => number | '(' E ')';

// @token whitespace [\t\n\n]*
// @token number \d+
// @token number \

const (
	Symbol  BNFTokenType = "symbol"
	Literal BNFTokenType = "literal" // 'c' "str"
	Colon   BNFTokenType = ";"
	Comma   BNFTokenType = ","
	OR      BNFTokenType = "|"
	EOF     BNFTokenType = "eof"
	ARROW   BNFTokenType = "=>"
	Macro   BNFTokenType = "@"
)

type BNFToken struct {
	Type    BNFTokenType
	Literal string
}

type BNFLexer struct {
	input string

	position     int  // current position in input (current char)
	readPosition int  // current reading position in input (after current char)
	ch           byte // current char
}

func NewBNFLexer(input string) *BNFLexer {
	l := &BNFLexer{input: input}
	l.readChar()
	return l
}

func (l *BNFLexer) readChar() {
	if l.readPosition >= len(l.input) {
		l.ch = 0
	} else {
		l.ch = l.input[l.readPosition]
	}
	l.position = l.readPosition
	l.readPosition += 1
}

func (l *BNFLexer) skipWhitespace() {
	for l.ch == ' ' || l.ch == '\t' || l.ch == '\n' || l.ch == '\r' {
		l.readChar()
	}
}

func (l *BNFLexer) NextToken() BNFToken {
	var tok BNFToken
	defer func() {
		log.Println("tok=", tok, "position", l.position, "readPosition", l.readPosition)
	}()
	l.skipWhitespace()
	switch l.ch {
	case ';':
		tok = BNFToken{Colon, ";"}
	case '|':
		tok = BNFToken{OR, "|"}
	case '=':
		if l.peerChar() == '>' {
			l.readChar()
			tok = BNFToken{ARROW, "=>"}
		}
	case '\'':
		l.readChar()
		tok = BNFToken{Type: Literal, Literal: string(l.ch)}
		l.readChar()
	case 0:
		tok.Literal = ""
		tok.Type = EOF
	case '@':
		l.readChar()
		literal := l.readSymbol()
		tok = BNFToken{Type: Macro, Literal: "@" + literal}
	default:
		if l.ch == '"' {
			literal := l.readSymbol()
			l.readChar()
			tok = BNFToken{Type: Literal, Literal: literal}
		}
		if isLetter(l.ch) {
			tok = BNFToken{Symbol, l.readSymbol()}
			return tok
		}
		literal := l.readUntilWhitespace()
		tok = BNFToken{Literal, literal}
		return tok
	}
	l.readChar()
	return tok
}

func isLetter(ch byte) bool {
	return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z'
}

func (l *BNFLexer) peerChar() byte {
	if l.readPosition >= len(l.input) {
		return 0
	} else {
		return l.input[l.readPosition]
	}
}

func (l *BNFLexer) readSymbol() string {
	position := l.position
	for isLetter(l.ch) {
		l.readChar()
	}

	return l.input[position:l.position]
}

func (l *BNFLexer) readUntilWhitespace() string {
	position := l.position
	for l.ch != ';' {
		l.readChar()
	}
	return l.input[position:l.position]
}

type BNFSymbol struct {
	name     string
	terminal bool
}

type BNFProducation struct {
	head       *BNFSymbol
	body       []*BNFSymbol
	isEpsilon  bool
	hasEpsilon bool
}

func (pr *BNFProducation) RightMostTerminal() *BNFSymbol {
	return nil
}

func (pr *BNFProducation) LeftMostTerminal() *BNFSymbol {
	return nil
}

type BNFGrammar struct {
}

func NewBNFGrammar(tokens []BNFToken) *BNFGrammar {
	grammar := &BNFGrammar{}

	line := 0
	lineTokens := []BNFToken{}
	for _, tok := range tokens {

		if tok.Literal == ";" {
			line++

			// Handle current tokens in one row.

			continue
		} else {
			lineTokens = append(lineTokens, tok)
		}

	}

	return grammar
}

// 对于形如
// E -> E \alpha | \beta
// 转化为
// E -> \bete E'
// E' -> \alpha E' | \epsion
func (g *BNFGrammar) EliminateLeftRecursion() {}

// 利用lookahead symbol，来消除在解析右递归表达式
// 定义FIRST和FOLLOW集合
// FIRST(\alpha): 从\alpha推导出来的每个符号串的第一个单词所对应的终结符集合。
// 如果\alpha是终结符, \epsilon或者EOF，那么FIRST(\alpha) = \alpha
// 对于非终结符A, FIRST(A)包含从A推导出来的每个巨型的第一个符号中所有可能的终结符

func (g *BNFGrammar) FirstSet() {}

// FOLLOW(A)集合定义为A到处的符号串之后的可能单词
// 利用FIRST 和 FOLLOW集合，可以得到无回溯的条件
// 对于产生式A->\beta
// FIRST+(A->\beta) = if \epsilon not in FIRST(\beta) then FIRST(\beta) else FIRST(\beta) \/ FOLLOW(A)
// 对任何匹配多个产生式的非终结符A,
// A -> \beta1 | \beta2 | ... | \betan
// FIRST+(A->\betai) /\ FIRST+(A->\betaj) = \empty
func (g *BNFGrammar) FollowSet() {}

// 提取左因子
// 在一组产生式中，提取并隔离共同前缀
// A -> \alpha \beta1 | \alpha \beta2 | \alpha \beta3
// A -> \alph B
// B -> \beta1 | \beta2 | \beta3

// 为构建LL(1)语法分析器、我们需要提供右递归，无回溯的语法，和一个用于
// 构建实际语法分析器的语法分析器生成器。
// 一般基于LL(1)表驱动。
