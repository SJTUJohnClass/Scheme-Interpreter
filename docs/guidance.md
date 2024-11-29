## Project 4: Scheme Interpreter

> SJTU CS1958-01 2024Fall 第四次大作业
>
> 本次大作业基于 SJTU CS1958-01 2023 Fall 第四次大作业改造而来，感谢陆潇扬学长与赵天朗学长！

作业提交截止时间：2024.12.24 18:00（暂定）

### 内容简介

在本次大作业中，你需要使用 C++ 实现一个简易的 Scheme 解释器。

#### Scheme

Scheme 是一种函数式语言，它主要有两种特性：

- 采用 S-表达式，除了 `int` 类型与变量 `var`，其余语法形如 `(expr exprs ...)`，例如 `(+ 1 3)`
- 函数也被视作一个变量

如果你对 Scheme 感兴趣，可以在网上自行查阅相关信息。本次大作业并不需要你实现 Scheme 所有的功能，因此阅读文档即可完成所有的需求。

#### 解释器

在 REPL（Read-Evaluate-Print Loop）交互模式下， 用户输入的程序在输入时会被认为是一个完整的字符串， 这个字符串经过 Lexer 处理后分解成一个个的 tokens。 之后， 这些 tokens 会在 Parser 的作用下生成 AST（Abstract Syntax Tree， 抽象语法树）， 最终 AST 被交给求值部分进行求值并输出。

在我们提供的接口中， 已经为你实现了 Lexer 的部分， 由于 Scheme 的特性， 这些拆分出来的 tokens 已经组成了一个类似于 AST 的结构， 这就是 `Syntax`。

```mermaid
graph LR
    User-Input -- Read --> Input-String
    Input-String -- Lexer --> Syntax
    Syntax -- Parser --> Expr
    Expr -- Evaluate --> Value
    Value -- Print --> Output
    Output --> User-Input
```

### 项目框架

#### 编译

我们已经为你提供了 `CMakeLists.txt`， 要编译整个项目， 在根目录下输入

```
cmake -B build
cmake --build build --target myscheme
```

之后， `myscheme` 程序会生成在子目录 `bin` 下， 在根目录下执行

```
./bin/myscheme
```

来运行你的解释器。

#### 代码实现

`src` 下文件为：

```
├── src
│   ├── shared.hpp
│   ├── parser.cpp
│   ├── evaluation.cpp
│   ├── main.cpp
│   ├── Def.hpp
│   ├── Def.cpp
│   ├── syntax.hpp
│   ├── syntax.cpp
│   ├── expr.hpp
│   ├── expr.cpp
│   ├── value.hpp
│   ├── value.cpp
│   ├── RE.hpp
│   ├── RE.cpp
│   ├── expr.hpp
│   └── expr.cpp
```

其中

```
├── src
│   ├── shared.hpp
│   ├── parser.cpp
│   └── evaluation.cpp
```

为你需要修改的文件
- `shared.hpp` 为 SmartPointer 作业中你实现的 `SharedPtr` 
> 对， 我们希望你能够使用自己的 `SharedPtr` 而不是 STL 的 `shared_ptr`， 至于为什么要用 `shared_ptr` 你可以思考一下）
- `parser.cpp` 是你需要实现的 Parser 部分， 你需要填写所有的 `parse()` 函数
- `evaluation.cpp` 是你需要实现的 Evaluation 部分， 你需要填写所有的 `eval()` 函数

对于其他的文件， 它们的用处分别为
- `Def.hpp`： 声明需要用到的类型、枚举类型和辅助函数
- `Def.cpp`： 定义了辅助函数和两个 `map`， 其中 `primitive` 用来存 `library` 函数的关键字， `reserved_words` 存其他语法的关键字（希望这两个函数和枚举类型能对你有所帮助， 当然你也可以不用我们提供的工具自己实现所有的功能， it's up to you）
- `RE.hpp` 与 `RE.cpp`： 定义了需要报错时需要使用的异常类型， 你需要学习异常类型的使用， 具体可以看[这里](https://www.runoob.com/cplusplus/cpp-exceptions-handling.html)
- `syntax.hpp` 与 `syntax.cpp`： 定义了所有的 `Syntax` 和[子类](https://www.runoob.com/cplusplus/cpp-inheritance.html)， 具体实现在 `syntax.cpp` 中
- `expr.hpp` 与 `expr.cpp`： 定义了所有的 `Expr` 和子类， 子类的构造函数在 `expr.cpp` 中
- `value.hpp` 与 `value.cpp`： 定义了所有的 `Value` 和子类， 子类的构造函数和输出方式在 `value.cpp` 中； 此外， 我们提到的作用域， 被实现在 `Assoc` 和 `AssocList` 中， 具体可以参考这两个文件
- `main.cpp`： REPL 的执行部分

#### 评测

在 OJ 上进行提交测评， 我们也会下发部分数据来帮助你在本地进行调试。

具体而言， 有两种提交到 OJ 的测评方式

- 将整个文件夹压缩成压缩包在题面处上传， OJ 会根据根目录下的 CMakeLists 来构建你的程序。
- 在代码提交页面输入 `git` 仓库的地址。

#### 调试

在完成编译后，你可以运行你的解释器，并自行输入 Scheme 语言，检查你的解释器行为是否符合预期。

同时，我们在 repo 中提供了评测程序来对你的解释器进行本地测评， 评测程序在子目录 `score` 下， 评测数据在子目录 `score/data` 下。

具体而言， 评测程序会执行你的解释器并将结果与标准程序的输出进行比对， 要使用评测程序， 在子目录 `score` 下执行以下命令即可

```
./score.sh
```

若权限不够， 你可以输入下列命令后再执行

```
chmod +x score.sh
./score.sh
```

脚本中有两行

```
L = 1
R = 119
```

你可以将这两个变量改为任意数字来对给定范围内的测试点进行测评。

请合理利用本地的评测程序进行调试。

### 任务

总得来说，你的解释器应当可以接受以下语法：

```
expr   -->  Integer
		| 	Boolean
        |   (quote datum)
        |   var
        |   (if expr expr expr)
        |   (begin expr*)
        |   (lambda (var*) expr)
        |   (let ([var expr]*) expr)
        |   (letrec ([var expr]*) expr)
        |   (primitive expr*)
        |   (expr expr*)
```

对每一个输入的表达式， 你需要求出表达式的值， 值的类型有以下几种（可见于 `src/value.hpp`）

- `Integer`： 整数
- `Void`： `(void)` 时输出的值
- `Boolean`： 布尔值
- `Symbol`： 符号
- `Null`： 空 `Pair`（你可以认为是 C++ 中的 NULL）
- `Pair`： 值对， 由两个值构成
- `Terminate`： `(exit)` 函数的值， 负责退出整个程序
- `Closure`： 用户定义的函数

语法中的 `primitive` 为 Library 中定义的函数（你可以认为 Library 是 C++ 的 STL， 你同样需要实现这一部分函数的解释执行）。

#### 子任务 1（10pts）：计算器

我们从实现一个简易的计算器开始，在该子任务中，你的解释器应当可以接受以下语法：

```
expr   -->  Integer
        |   (primitive expr*)
```

##### 语法：`Integer`

在该子任务中，`constant` 表示整数，对应类型为 `Integer` 的值。在本次大作业中，你可以认为 `Integer` 就是 C++ 中的 `int`，你不需要考虑溢出等情况。

样例：

```
scm> 100
100
scm> -1
-1
```

##### 语法：`(primitive expr*)`

该子任务中，`primitive` 语法包含以下几种情况：

```
-->	(+ expr1 expr2)
 |	(- expr1 expr2)
 |	(* expr1 expr2)
 |	(exit)
```

`(+ expr1 expr2)`、`(- expr1 expr2)`、`(* expr1 expr2)` 表示对应的整数运算，它们接收两个类型为 `Integer` 的参数，值为对应的运算结果，类型为 `Integer`。

`(exit)` 没有参数，它的值类型为 `Terminate`，当 `main.cpp` 读入当前 `syntax` 并经过 `parse` 与 `evaluate` 后得到的 `value` 类型为 `Terminate` 时，解释器会停止运行。

具体实现中，我们首先求出 `expr*` 的值，然后计算 `(primitive exor*)` 的值。

特别地，当 `primitive` 接收的参数个数或参数类型不符合要求时，你应当及时抛出异常（详见 `RE.hpp` 与 `main.cpp`）。**本次大作业不要求你抛出的异常指明具体的问题，你只需要抛出 `RuntimeError("Error.")` 即可。**

样例：

```
scm> (+ 1 2)
3
scm> (- 1 2)
-1
scm> (* (+ 1 2) (- 1 2))
-3
scm> (+ 1 2 3)
Error.
scm> (exit) // 程序终止
```

#### 子任务 2（10pts）：更多的数据类型

在该子任务中，我们将在上一子任务的基础上引入更多的数据类型以及对应的构造方式，你的解释器现在应当可以接受以下语法：

```
expr   -->  Integer
		| 	Boolean
		|	(quote datum)
		|   (primitive expr*)
```

`primitive` 在原来的基础上增加了 `void, cons, car, cdr`。

我们首先来介绍该子任务中涉及到的数据类型。

##### 数据类型：`Integer`

`Integer` 属于基础类型，在本次大作业中，其行为与 C++ 中的 `int` 类型表现一致。

##### 数据类型：`Boolean`

`Boolean` 即布尔值，在 Scheme 中，我们使用 `#t` 表示 True，使用 `#f` 表示 False。

##### 数据类型：`Pair`

`Pair` 即二元有序对，它有两个值组成。在 Scheme 中，我们使用 `(A . B)` 表示一个左值为 `A`，右值为 `B` 的 `Pair`。

组成 `Pair` 的两个值的类型可以是任意类型，甚至也可以是 `Pair`，例如 `((1 . 2) . (3 . 4))`，它表示一个左值为 `(1 . 2)`，右值为 `(3 . 4)` 的 `Pair`。通过这种嵌套，我们可以用 `Pair` 表示一棵二叉树，进而表示更多、更复杂的结构。例如，我们可以使用 `Pair` 表示这么一个结构 `[1, 2, 3, 4, 5]`：`(1 . (2 . (3 . (4 . 5))))`，Scheme 会将其简写为 `(1 2 3 4 . 5)`。

##### 数据类型：`Null`

`Null` 可以被理解为空 `Pair`。在 Scheme 中，我们使用 `()` 表示 `Null`。

结合 `Null` 与 `Pair`，我们可以在 Scheme 中表示 `List`。例如上面的例子，我们实际上会用 `(1 . (2 . (3 . (4 . (5 . ())))))` 来表示一个列表 `[1, 2, 3, 4, 5]`，Scheme 会将其简写为 `(1 2 3 4 5)`，这样我们就规避了 `.` 的出现。

##### 数据类型：`Symbol`

`Symbol` 可以被视为不可变的字符串。在 Scheme 中，我们使用 `quote` 来生成 `Symbol`，具体内容请见下方语法部分的解释。

我们可以使用 `Symbol`  起到类似 C++ 中 `enum` 类型的作用。例如，我们可以创建一个列表 `(left right up down)` 来表示四个方向，其中 `left`、`right`、`up`、`down` 都是类型为 `Symbol` 的值，它们的值即为自身。

`Symbol` 类型甚至使得我们可以用 Scheme 编写一个 Scheme 解释器，因为我们可以用 `Symbol` 类型表示一个个 token，且 Scheme 本身采用 S-表达式，这使得 Scheme 的表达式本身也是一个列表。

##### 数据类型：`Void`

`Void` 是一个很特殊的数据类型，当一个函数仅包含副作用时，它的值即为 `Void`。由于本次大作业中几乎表达式都没有副作用，因此 `Void` 只能由 `(void)` 这一表达式生成。Scheme 中用 `#<void>` 表示 `Void` 类型。

##### 数据类型：`Closure`

`Closure` 用来表示用户自定义的函数。本次大作业中 `Closure` 表示函数本身以及对应的作用域。该子任务中不涉及 `Closure` 的相关操作。

现在我们逐个介绍该子任务中新增的语法。

##### 语法：`Boolean`

当表达式为 `#t` 或 `#f` 时，它的值即为 `#t` 与 `#f`（`Boolean` 类型）。

样例：

```
scm> #t
#t
scm> #f
#f
```

##### 语法：`(quote datum)`

注意，此处 `datum` 是一个 `syntax` 而非 `expr`。

`(quote datum)` 的作用是将 `datum` 原样返回。

`Integer` 与 `Boolean` 的情况很好理解。

对于 `Pair` 的情况，由于 Scheme 对一个列表求值时会将其视为调用函数（例如 `(+ 1 2)` 的值是 `3` 而非列表 `(+ 1 2)` 自身），所以我们可以通过 `(quote datum)` 直接构造一个 `Pair`（包括列表）。

对于 `Symbol` 的情况，由于 Scheme 对一个 `Identifier` 求值时会被认为取变量名为该 `Identifier` 对应的值（例如 `var` 的值是 `var` 变量对应的值而非 `var` 自身），所以我们可以通过 `(quote datum)` 直接构造一个 `Symbol`。

`(quote datum)` 的值是 `Integer`、`Boolean`、`Symbol`、`Pair` 中的一种，取决于 `datum` 的形式。

样例：

```
scm> (quote 1)
1 //注意这里是 Integer 类型
scm> (quote #t)
#t // 注意这里是 Boolean 类型
scm> (quote (+ 1 2 3))
(+ 1 2 3) // 注意这里是 Pair 类型，其中 + 为 Symbol 类型，其它为 Integer 类型
scm> (quote (4 . 5))
(4 . 5) // 注意这里是 Pair 类型，左值为 4，右值为 5，都为 Integer 类型
scm> (quote scheme)
scheme // 注意这里是 Symbol 类型
```

##### 语法：`(primitive expr*)`

该子任务中，`primitive` 语法包含以下几种情况：

```
-->	(+ expr1 expr2)
 |	(- expr1 expr2)
 |	(* expr1 expr2)
 |	(exit)
 |	(void)
 |	(cons expr1 expr2)
 | 	(car expr)
 |	(cdr expr)
```

`(void)` 不接受任何参数，值为 `Void`。

`(cons expr1 expr2)` 表示构造一个 `Pair`，其左值为 `expr1` 的值，右值 `expr2` 的值。它接受两个任意类型的参数，返回对应的 `Pair`。

`(car expr)` 与 `(cdr expr)` 分别表示取一个 `Pair` 的左值和右值。它接受一个类型为 `Pair` 的参数，返回对应的结果。

样例：

```
scm> (void)
#<void>
scm> (cons 1 2)
(1 . 2)
scm> (car (cons 5 #f))
5
scm> (cdr (cons #t (void)))
#<void>
scm> (cdr (quote ((ll . lr) . (rl . rr))))
(rl . rr)
scm> (car (quote (+ - *)))
+
```

#### 子任务 3（15pts）：顺序结构、选择结构

在该子任务中，我们在前两个子任务的基础上引入了顺序结构与条件结构，为了更好地使用条件结构，我们还引入了一些 `primitive` 来对数据类型做比较或检查。该子任务中，你的解释器应当接受以下语法：

```
expr   -->  Integer
		|	Boolean
		|	(begin expr expr*)
		|	(if expr1 expr2 expr3)
		|	(quote datum)
		|   (primitive expr*)
```

##### 语法：`(begin expr expr*)`

顺序结构。

`expr*` 表示可能 $0, 1, 2, \cdots$ 个 `expr`。

你需要从左至右依次执行 `expr`，而 `(begin expr expr*)` 的值为最右侧的 `expr` 的值。

由于本次大作业并不涉及含副作用的表达式，所以无法体现这一语法的作用。但是你仍然需要执行每个 `expr`，因为这些 `expr` 内可能包含非法情况。

样例：

```
scm> (begin 1)
1
scm> (begin (void) (cons 1 2) #t)
#t
```

#### 语法：`(if expr1 expr2 expr3)`

选择结构。

我们首先执行并求出 `expr1` 的值，若 `expr1` 的值为 `#f`，则执行 `expr3` ，该表达式的值为 `expr3` 的值；否则执行 `expr2`，该表达式的值为 `expr2` 的值。

**注意：与 C++ 不同的是，`0` 会被视为 `#t` 而非 `#f`。**

样例：

```
scm> (if 0 1 2)
1
scm> (if (< 2 1) #f #t) // (< 1 2) 的值见下一部分的内容
#t
scm> (if (void) undefined 1)
Error. // 报错，undefined 变量未定义
scm> (if #f undefined 1)
1
```

#### 语法：`(primitive expr*)`

该子任务中，`primitive` 语法包含以下几种情况：

```
-->	(+ expr1 expr2)
 |	(- expr1 expr2)
 |	(* expr1 expr2)
 |	(exit)
 |	(void)
 |	(cons expr1 expr2)
 | 	(car expr)
 |	(cdr expr)
 |	(< expr1 expr2)
 |	(<= expr1 expr2)
 |	(= expr1 expr2)
 |	(>= expr1 expr2)
 |	(> expr1 expr2)
 |	(not expr)
 |	(fixnum? expr)
 |	(boolean? expr)
 |	(null? expr)
 |	(pair? expr)
 |	(symbol? expr)
 |	(eq? expr1 expr2)
```

`(< expr1 expr2)`、`(<= expr1 expr2)`、`(= expr1 expr2)`、`(>= expr1 expr2)`、`(> expr1 expr2)` 表示对应的整数比较。它们接受两个类型为 `Integer` 的参数，值为对应的比较结果，类型为 `Boolean`。

`(not expr)` 表示取反操作。它接受一个任意类型的参数，值为对应的取反结果，类型为 `Boolean`。当 `expr` 的值为 `#f` 时，该表达式的值为 `#t`，否则为 `#f`。请注意，它与 `(if expr1 expr2 expr3)` 一样，将 `0` 视为 `#t`。

`(fixnum? expr)`、`(boolean? expr)`、`(null? expr)`、`(pair? expr)`、`(symbol? expr)` 分别表示 `expr` 的值的类型是否为 `Integer`、`Boolean`、`Null`、`Pair`、`Symbol`。它们接受一个任意类型的参数，值为对应的结果，类型为 `Boolean`。

`(eq? expr1 expr2)` 表示检查 `expr1` 与 `expr2` 的值是否相等。该表达式接受两个任意类型的参数，值为对应的结果，类型为 `Boolean`。具体的比较规则：

- 若两个参数的类型都为 `Integer`，则比较对应的整数是否相同
- 若两个参数的类型都为 `Boolean`，则比较对应的布尔值是否相同
- 若两个参数的类型都为 `Symbol`，则比较对应的字符串是否相同
- 若两个参数的类型都为 `Null` 或都为 `Void`，则值为 `#t`
- 否则，比较两个值指向的内存位置是否相同（例如两个 `Pair`，即使它们左右值都相等，但如果内存位置不同，我们也认为两者不同）

我们提供的接口中存的是指向值的指针而非值本身， 你可以通过定义 `Value v` 并使用 `v.get()` 来查看 `v` 指向的内存位置。

样例：

```
scm> (< 1 2)
#t
scm> (>= 1 2)
#f
scm> (= #t 1)
Error. // expr1 的类型不匹配
scm> (not #f)
#t
scm> (not (void))
#f
scm> (pair? (car (cons 1 2)))
#f
scm> (symbol? (quote var))
#t
scm> (fixnum? (+ 5 1))
#t
scm> (null? (quote ()))
#t
scm> (eq? 3 (+ 1 2))
#t
scm> (eq? #t (= 0 0))
#t
scm> (eq? (quote ()) (quote ()))
#t
scm> (eq? (quote (1 2 3)) (quote 1 2 3))
#f
```

