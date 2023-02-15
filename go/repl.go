package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"os/user"

	"github.com/yummy/go/parser"
)

const PROMPT = ">>"

func Start(in io.Reader, out io.Writer) {
	scanner := bufio.NewScanner(in)

	for {
		fmt.Printf(PROMPT)
		scanned := scanner.Scan()
		if !scanned {
			return
		}

		line := scanner.Text()
		l1 := parser.NewLexer(line)
		for tok := l1.NextToken(); tok.Type != parser.EOF; tok = l1.NextToken() {
			fmt.Printf("%+v\n", tok)
		}
		l2 := parser.NewLexer(line)
		p := parser.NewParser(l2)
		program := p.Parse()
		fmt.Println("program", program.String())
	}
}

func main() {
	user, err := user.Current()
	if err != nil {
		panic(err)
	}
	fmt.Printf("Hello %s! This is the Monkey programming language!\n",
		user.Username)
	fmt.Printf("Feel free to type in commands\n")
	Start(os.Stdin, os.Stdout)
}
