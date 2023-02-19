# Regular Expression

- a, b, c, ...
- * + ? () | 
- if e1 matches s and e2 matches t, e1 | e2 => s | t, e1e2 => st
- e1* : matches zero or more 
- e1+ : matches one or more
- e1?: matches zero or one

## Backreference
one common regular expression extension that does provide additional power is called `backreferences`. a backreference like \1 or \2 match the string matched by a previous parenthesized expression, and only that string.

(cat | dog)\1 matches `catcat` and `dogdog`, but not `catdog` nor `dogcat`

the power that backerefernece add comes at great cost, the worst case ,the best known implementations reqire exponential search with regex. 

## FA
Another way to describe sets of character strings is with finite automata.

DFA: in any state, each possible input lettter leads to at most one new state.


## Convert RE to NFAs

1. compiling to NFA
we need to compile the regular expression into an equivalent NFA.
```c++
struct State {
  int c;
  State* out;
  State *out1;
  int lastlist;
};
```

Following Thompson's paper, the compiler builds an NFA from a regular expression into postfix notation with dot (.) added as an explicit concatenation operation.

`re2post` rewrites infix regular expressions to NFA.

`a(bb)+a` => (abb.+.a.)

As the compiler scans the postfix expression, it maintains a stack of computed NFA fragments.
Literals push new NFA fragments onto the stack, while operators pop fragments off the stack and then push a new fragment

```c++
struct Fragment {
  State *start;
  Ptrlist *out;
}

// Some helper functions manipulate pointer lists:

// create a new pointer list contains the single pointer
Ptrlist *list1(State **outp);
Ptrlist *append(Ptrlist *l1, Ptrlist *l2);

void patch(Ptrlist *l, State *s);
```

Given these primitives and a fragment stack, the compiler is a simple loop over the postfix expression.

```c++
State *
post2nfa(char *postfix) {
  char *p;
  Fragment stack[1000], *stackp, e1, e2, e;
  State *s;
  #define push(s) *stackp++ = s
  #define pop *--stackp

  stackp = stack;
  for(p = postfix; *p; p++) {
    switch(*p) {
      case '.':
        e2 = pop();
        e1 = pop();
        patch(e1.out, e2.start);
        push(frag(e1.start, e2.out));
        break;
      case '|':
        e2 = pop();
        e1 = pop();
        s = state(Split, e1.start, e2.start);
        push(frag(s, append(e1.out, e2.out)));
        break;
      case '?':
        e = pop();
        s = state(Split, e.start, NULL);
        push(frag(s, append(e.out, list1(&s->out1))));
        break;
      case '+':
        e = pop();
        s = state(Split, e.start, NULL);
        patch(e.out, s);
        push(frag(e.start, list1(&s->out1)));
        break;
      case '*':
        e = pop();
        s = state(Split, e.start, NULL);
        patch(e.out, s);
        push(frag(s, list1(&s->out1)));
        break;
      default:
        // Literal
        s = state(*p, NULL, NULL);
	      push(frag(s, list1(&s->out));
	      break;
    }

    e = pop();
    patch(e.out, matchstate);
    return e.start;
  }
}

```


## Implement: simulating the NFA
```c++
struct List
{
	State **s;
	int n;
};


int
match(State *start, char *s)
{
	List *clist, *nlist, *t;

	/* l1 and l2 are preallocated globals */
	clist = startlist(start, &l1);
	nlist = &l2;
	for(; *s; s++){
		step(clist, *s, nlist);
		t = clist; clist = nlist; nlist = t;	/* swap clist, nlist */
	}
	return ismatch(clist);
}


int
ismatch(List *l)
{
	int i;

	for(i=0; i<l->n; i++)
		if(l->s[i] == matchstate)
			return 1;
	return 0;
}


```