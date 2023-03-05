给出该语法的CC0 


0. S′	→	S
1. S	→	C C
2. C	→	c C
3. C	→	d


State	c	d	$	S	C
0	s3	s4		1	2
1			acc		
2	s3	s4			5
3	s3	s4			6
4	r3	r3	r3		
5			r1		
6			r2		


L型和S型都是指在使用语法制导翻译技术（Syntax-Directed Translation Technique）时，可能的翻译方案类型。

L型 SDT (L-Attributed Definition) 意味着翻译方案仅依赖于所翻译的符号的属性和它的祖先结点的属性，它可以在语法分析期间或者语法分析和代码生成之间执行。
S型 SDT (S-Attributed Definition) 意味着翻译方案依赖于翻译方案的整个上下文，这意味着需要等待所有翻译方案计算完成之后才能进行。
在L型SDT中，语法制导翻译规则在语法分析期间被执行，而在S型SDT中，规则在语法分析之后执行。