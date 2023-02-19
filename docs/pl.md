# Programming Language
1. 集合论
2. 符号逻辑
3. 自动数学 Post
5. Post -> 形式语言理论 -> 形式语法义
6. 信息论 + 计算复杂性理论 -> 计算密码学
7. 自动机理论
8. 递归函数论 -> lambda演算 -> 程序正确性证明 -> 指称语义学Scott -> 类型理论 (Milner) -> ML
9. 并发性(Dijkstra) -> 分布式计算 -> 协调计算

程序设计语言的设计目标
- 模型能力：语法特征能够清楚的表达计算
- 语义清晰：每个合法的表达式都定义一个清晰的、无二义的内涵
- 实用性：每个特征都应该常用
- 方便性：越频繁的特征越应该方便
- 简单性
- 可读性
- 可移植性
- 效率：编程效率、编译效率、执行效率
- 灵活性

设计准则
- 频度准则：频繁的特征应该语义清晰方便简单可读
- 结构一致准则：一个程序的静态结构，直观上应该与动态的计算机构一致，表示结构与逻辑结构一致
- 局部性准则：一个模块应该只用自己声明的局部数据，这是保持语义清晰的有效措施
公用数据极易产生副作用，而强行局部化会造成冗余和重复，所以现代语言一般会有不同层次的控制数据的措施。heap, stack, static等
- 词法内聚：逻辑相关的代码应该相邻。C++的声明就是语句，可以穿插在程序的任意地方，但是如果到处都在声明，缺乏总体概念，所以C++规定定义只能有一个。
- 语法一致性：看上去相似的特征，语法定义应该一致
- 安全性导致的强类型要求
- 正交性和正则性：每种语言特征都由独立的机制实现，与其他的特征无关，正交性可以构造更有表达力的机制，正则性是指某种规则和约束应该无一例外。正交性是基本目标，正则性可以减少程序员的记忆
- 数据隐藏
- 抽象表达
- 可移植性

# 语法Spec
Lexicon:
  字面量、标识符、关键字、操作符、特殊符号

Statement, Expression, ...

CFG
不同类型的产生式形成了不同的文法.

0型：
如果对产生式的左端和右端不加限制，得到的是 递归可枚举语言。 图灵机可以识别

1型：
  a A b -> a B b，得到是 上下文敏感语言，线性有界自动机可以识别

2型：
A -> a  上下文无关语法，非确定下推机可以识别

3型:
A -> aB | Ba 正则语言，有限自动机可以识别这种语言

简单语言设计可以用3型语言，一般采用2型。

利用BNF表示法可以表示上下文无关语言

program ::= <program_heading> ';' <program_block> '.'.
program_heading ::= 'program' <identifier>[ '('<program_parameters> ')']. program_parameters ::= <identifier_list>.
identifier_list ::= <identifier> {'，' <identifier>} .
program_block ::= <block>.
block ::= <label_declaration_part> <constant_declaration_part>
<type_declaration_part><variable_declaration_part>
<procedure_and_function_declaration_part><statement_part>. variable_declaration_part ::= ['var' <variable_declaration> ';'
{<variabe_declaration> ';' }]. variable_declaration ::= <identifier_list> ';' <type_denoter>.
statement_part ::= compound_statement.
compound_statement ::= 'begin' <statement_sequence> 'end'. statement_sequence ::= <statement> {';' <statement>}. statement::=[<label> ':'](<simple_statement>|<structured_statement>). simple_statement ::= <empty_statement> | <assignment_statement> |
<procedure_statement> | < goto_statement>. structured_statement ::= <compound_statement>|<conditional_statement>
|<repetitive_statement> | <with_statement>.


# 语义Spec:
程序的语义是在它运行的时候的行为。
操作语义学是按照计算机执行的步骤来说明语言的执行，特点是强调程序的每一步执行
另外一种观点是把程序看成数学函数的实现，函数式语言可以更明显的实现函数，我们把这个函数理解为程序的意义。这种是称为 指称语义学

公理语义学是把语言的描述看成语言的公理，该理论包含三部分
  公理表
  语法规划集
  推理规则集

主要用于程序验证、语言理解、语言规范等


# Value, Type
int, long
double, float
char
bool
tuple
array
enum
struct
table
string

计算机只能操作值，最直接的名字是字面量，表示就是他们的值。
变量是表示任何值的标识符

# 求值方式
1. 表达式求值
2. 函数引用 过程调用求值

所有的值都应该是头等程序对象
 - literal
 - object
 - pointer
 - function

程序对象的权限具体说来是:
·可作为操作数出现在表达式中求值。 · 可作为单独的存储实体。
· 可作为参数传递到过程或函数。
· 可作为函数返回值。
· 可以构成复杂的数据结构。

类型是值的集合,一种程序设计语言总是要为用户提供
- 一组直接可用的类型
- 一个用户定义类型的机制
- 一组类型规则
- 一种类型检查机制
这几个东西称为一个语言的类型系统

# 基本类型
bool = {true, false}
int = {-maxint, ..., maxint}
real = {... , 0, 1.0, 1.1, ...}
char = {'a' .. 'z' .. 'A' .. 'Z'}

op: T -> T
op: T x T -> T

# 符合类型

笛卡尔积（tuple, record)： S x T 代表所有值的对偶集合

type Person = string x string x int x int 

Unit = ()


不相交的联合 (Union): S + T

type Number = int + double

变体记录 (Variant)

type Shape = Point | Circle | Box

映射 (Mapping) (Array)

# 递归类型
表
串


# 类型系统
静态类型是在编译时刻能够确认
动态类型是在运行时刻检查
强类型是都有明确的类型，弱类型是只要兼容就可以转化

类型等价：
1. 类型T和T‘等价当且仅当T和T‘能够存储相同的值的集合
2. 结构等价容易造成语义混乱

类型完整性：涉及值的类型中不能随意限定操作

## expression
- 基本的表达式类型
- 扩展表达式 为了扩充表达式的表达能力，许多语言把表达式概念扩大，凡是求值，经比较得出真
假值都认为是表达式
- 优先级和结合性


## 存储模型
- 静态存储
- 堆存储
- 栈存储

存储对象的生命周期：
1. 和程序一样长的 全局变量
2. 和模块一样长的 局部变量
3. 大于程序执行的变量 持久变量

悬挂指针是指向一个已经死亡的、没有定义的对象 dangling reference

# Block Statement
块表达式式嵌套在程序中的局部程序，包含多个语句

# bind
把名字和存储对象联系起来叫做bind.

# 声明
声明指明了程序中用到的所有程序对象

# 作用域
在程序正文中声明有效的范围称为作用域。
可以通过嵌套块来实现

把已经绑定的作用域范围称为环境，当前环境还包括系统预定义的字面量

嵌套声明作用域称为词法作用域
语法作用域一般是通过运行时栈真实现

解释器采用动态作用域实现肥肠自然，符号表在执行的时候是存在的。

编译器则相反，符号表在编译以后要结束，所有存储对象必须在编译的时候完成bind。

# 程序控制
顺序控制 s1;s2; ...; sn
条件控制 
  if cond then s1 else s2
  switch ()
    case ...
    case ...
  
  case ()
    when xx => xx
迭代控制

# 异常
异常引发和处理以后不像子程序能够返回原处，而是从它的处理段出口


# 模块
模块定义为一组共享数据和一组子程序的程序但愿，模块名是对这个封装的抽象。