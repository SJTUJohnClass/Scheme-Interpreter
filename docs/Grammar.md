# Grammar

## 目录

- [需要实现的语法](#需要实现的语法)
- [语法介绍](#语法介绍)
    - [Before Grammar](#before-grammar)
    - [`constant`](#constant)
    - [`var`](#var)
    - [`(quote datum)`](#quote-datum)
    - [`(if expr expr expr)`](#if-expr-expr-expr)
    - [`(begin expr*)`](#begin-expr)
    - [`(lambda (var*) expr)`](#lambda-var-expr)
    - [`(let ([var expr]*) expr)`](#let-var-expr-expr)
    - [`(letrec ([var expr]*) expr)`](#letrec-var-expr-expr)
    - [`(primitive expr*)`](#primitive-expr)
        - [`+, -, *`](#----a-name--arithmetica)
        - [`<, <=, =, >=, >`](#-----a-name--comparationa)
        - [`void, exit`](#void-exit)
        - [`cons, car, cdr`](#cons-car-cdr)
        - [`not`](#not)
        - [`boolean?, fixnum?, null?, pair?, procedure?`](#boolean-fixnum-null-pair-procedure)
        - [`eq?`](#eq)
    - [`(expr expr*)`](#expr-expr)

## 需要实现的语法

你需要实现的语法为

```
expr   -->  constant
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

下面对每个语法进行介绍， 语法中的 `primitive` 为 Library 中定义的函数（你可以认为 Library 是 C++ 的 STL， 你同样需要实现这一部分函数的解释执行）。

## 语法介绍

### Before Grammar

在介绍语法之前， 我们可能需要额外花时间介绍一下 `Closure`。 `Closure` 的中文为闭包， 一种简单的理解方式是 “闭包 = 函数 + 引用环境（作用域， 包含了所有的变量和它们所绑定的值）”， 观察 `Closure` 的实现可以发现它确实是这么被定义的。 在函数被定义出来时， 它的闭包中的作用域就是定义这个函数时这个函数所处的作用域。 对函数的求值即为， 在该函数的闭包的作用域中， 加上形参的具体值得到一个新的作用域， 并在这个新的作用域上对函数的函数体求值。

### `constant`

`constant` 的值为 `Integer`， 由于我们使用 C++ 来对 Scheme 进行解释执行， `constant` 的范围应为 32 位整数（你不需要处理溢出的情况， 自动溢出即可）。

```
scm> 100
100
```

### `var`

`var` 可以被解释为任何值， 当 `var` 在当前作用域下未定义时你需要报错。

```
scm> (void)
#<void>
scm> void
RuntimeError // 此处报错
scm> (let ([x 1]) x)
1
scm> (let ([x (lambda (y) y)]) x)
#<procedure>
```

### `(quote datum)`

`(quote datum)` 的值为 `Integer, Boolean, Symbol, Pair` 中的一种， 根据 `datum` 的形式决定。 你可以理解为 `quote` 的作用是把 `datum` 原样返回。

```
scm> (quote 1)
1 // Integer
scm> (quote haha)
haha // Symbol
scm> (quote (1 2 3))
(1 2 3) // Pair
scm> (quote #t)
#t // 此处的 #t 是 Boolean 而非 Symbol
```

### `(if expr expr expr)`

我们用 `cond, conseq, alter` 分别代表第 1, 2, 3 个 `expr`。

`(if expr expr expr)` 的值可以为任意类型， 你需要执行 `cond`， 若 `cond` 为真， 则 `(if expr expr expr)` 的值为 `conseq` 的值， 否则为 `alter` 的值。

```
scm> (if (= 1 0) void (cons 1 2))
(1 . 2)
scm> (if #t void (cons 1 2))
RuntimeError // 报错, void 未定义
```
需要注意的是， Scheme 中除了 `#f`（对应的值为 `Boolean(false)`）之外的其他值都为真值。

### `(begin expr*)`

`(begin expr*)` 的值可以为任意类型， `expr*` 代表可以有 $0, 1, \cdots$ 个表达式， 你需要从左至右依次执行这些表达式， 而 `(begin expr*)` 的值为最后一个表达式的值， 若没有表达式， `(begin)` 的值应当为 `Null`。

```
scm> (begin)
()
scm> (begin 1 2 (+ 3 5))
8
```

### `(lambda (var*) expr)`

`(lambda (var*) expr)` 为定义函数的语法， 它的值应为 `Closure`， 其中 `(var*)` 代表该函数的参数表。

```
scm> (lambda (x y) (+ x y))
#<procedure>
scm> (lambda () (void))
#<procedure>
```

### `(let ([var expr]*) expr)`

我们用 `body` 指代最后一个 `expr`。
`(let ([var expr]*) expr)` 用于给局部变量赋值（赋值操作全部进行在原作用域上）并产生新的作用域， 在新的作用域下对最后的 `expr` 进行求值。 变量的赋值应当是依次进行， 即在原作用域上先给第一个 `var` 赋值， 再给第二个 `var` 赋值， 依次进行下去直到所有赋值语句完成， 创造新的作用域并对最后一个 `let` 语句的 `body` 求值。

```
scm> (let ([x 1] [y 1]) (+ x y))
2
scm> (let ([x 1] [y x]) (+ x y))
RuntimeError // 此处你应当报错
scm> (let ([x 1]) (let ([y x] [x 3]) (+ x y)))
4
```

### `(letrec ([var expr]*) expr)`

`letrec` 与 `let` 的规则相差无几， 但一些特殊的处理方式使得 `letrec` 可以实现递归调用。

具体而言， `letrec` 会先将所有的 `var` 赋值为 `Value(nullptr)` 加入原作用域中得到新的作用域 `env1`（这里赋值成 `Value(nullptr)` 意义应被理解为该变量被定义但无法被使用， 如果想要获取该变量的值则会报错， 你可以理解成 C++ 中函数的声明）， 然后再对所有的 `[var expr]` 依次求值（像 `let` 中一样）， 不同的地方是这次求值始终在作用域 `env1` 而非原作用域上， 求值的结果会得到新作用域 `env2`（如果出现求值失败则报错， 你的程序应当能够处理这种情况）。 此时， 需要注意的一点是， 假如 `[var expr]*` 中存在 `var` 被绑定到了 `Closure` 上， 则该 `Closure` 中的作用域应当被更改为 `env2` 而非原先的 `env1`（这个更改应当进行在 `env2` 中对应的 `var` 所绑定的值上， 由于我们是用指针实现作用域的， 这种对 `Closure` 的改变并不会改变 `env2` 所指向的内存空间）， 然后再返回在 `env2` 上对 `body` 求值的结果。

举一个例子

```
(letrec 
    ([fact 
        (lambda (n)
            (if (= n 0)
                1
                (* n (fact (- n 1)))))])
    (fact 5))
```

此时最开始的作用域中没有变量的绑定， 所以 `env1 -> ([fact -> Value(nullptr)])`， 在求值过程后， `env2 -> ([fact -> Closure(env1)])`， 此时我们发现 `fact` 被绑定到了一个 `Closure` 上， 我们在 `env2` 中找到了对应的变量并做出更改， 最后的 `env2` 应为 `env2 -> ([fact -> Closure(env2)])`， 然后在新的 `env2` 上对 `(fact 5)` 求值。

```
scm> (letrec ([x 1] [y x]) (+ x y))
RuntimeError // 此处会报错， 你需要思考一下为什么
scm> (letrec 
        ([fact
            (lambda (n)
                (if (= n 0)
                    1
                    (* n (fact (- n 1)))))])
        (fact 5))
120 // 为什么此处不会报错？
```

### `(primitive expr*)`

`(primitive expr*)` 根据不同的 `primitive` 有不同的值， 不同的 `primitive` 能够接受的操作数个数也不同， 当操作数个数和操作数类型不对时， 你也应当报错。

#### `+, -, *` <a name = "arithmetic"></a>

基本算数操作， 要求操作数为 $2$ 个， 且操作数的值必须为 `Integer`， 返回值为 `Integer`。

```
scm> (+ 1 2)
3
scm> (- 1 2)
-1
scm> (* (+ 1 2) (- 1 2))
-3
```

#### `<, <=, =, >=, >` <a name = "comparation"></a>

基本比较操作， 要求操作数为 $2$ 个且操作数的值必须为 `Integer`， 返回值为 `Boolean`。 需要注意的是 `=` 并非赋值操作而是判断两个操作数是否相等。

```
scm> (< 1 2)
#t
scm> (>= 1 2)
#f
scm> (= #t 1)
RuntimeError // 此处你应当报错
```

#### `void, exit`

`void` 没有操作数， 调用 `(void)` 时返回值为 `Void`。

`exit` 没有操作数， 当调用 `(exit)` 时你应当终止解释器的执行。

```
scm> (void)
#<void>
scm> (exit) // 程序终止
```

#### `cons, car, cdr`

`cons` 为构造 `Pair` 操作， 要求操作数为 $2$ 个， 对操作数的类型没有要求， 返回值为 `Pair`。 `car` 为取 `Pair` 的第一个元素， 要求操作数为 $1$ 个， 操作数的类型应当为 `Pair`， 返回值为 `Pair` 的第一个元素。 `cdr` 为取 `Pair` 的第二个元素， 操作数数量和类型与 `car` 相同， 返回值为 `Pair` 的第二个元素。

```
scm> (cons 1 2)
(1 . 2)
scm> (car (cons 1 2))
1
scm> (cdr (cons (lambda (x) x) (void)))
#<void>
```

#### `not`

`not` 为取反操作， 操作数为 $1$ 个， 类型不限， 返回值为 `Boolean`。 当操作数为 `#f` 时， 返回值为 `#t`， 否则都为 `#f`。

```
scm> (not #f)
#t
scm> (not (lambda (x) x))
#f
```

#### `boolean?, fixnum?, null?, pair?, procedure?`

类型检测操作， 操作数为 $1$ 个， 类型不限， 返回值为 `Boolean`， 若操作数为对应类型的值则返回 `#t`， 否则返回 `#f`。
- `boolean?`： 检测操作数是否为 `Boolean`
- `fixnum?`： 检测操作数是否为 `Integer`
- `null?`： 检测操作数是否为 `Null`
- `pair?`： 检测操作数是否为 `Pair`
- `procedure?`： 检测操作数是否为 `Closure`

```
scm> (procedure? (lambda (x) x))
#t
scm> (pair? (car (cons 1 2)))
#f
scm> (let ([x 1]) (fixnum? x))
#t
```

#### `eq?`

接受两个操作数， 类型不限， 判断两个操作数是否相同， 返回值为 `Boolean`， 若相同则返回 `Boolean(true)`， 否则返回 `Boolean(false)`。
具体的机制比较复杂， 我们是这样处理的
- 若两个操作数都是 `Integer`， 则判断两个 `Integer` 的值是否相同
- 若两个操作数都是 `Boolean`， 判断两个 `Boolean` 的值是否相同
- 若两个操作数都是 `Symbol`， 判断两个 `Symbol` 的值是否相同
- 若上述两种情况都不是， 则看两个操作数指向的内存位置是否相同

我们提供的接口中存的是指向值的指针而非值本身， 你可以通过定义 `Value v` 并使用 `v.get()` 来查看 `v` 指向的内存位置。

```
scm> (eq? 3 (+ 1 2))
#t
scm> (eq? #t (= 0 0))
#t
scm> (let ([x (lambda (x) x)]) (eq? x (lambda (x) x)))
#f
```
### `(expr expr*)`

处理自定义的函数调用， 称前一个 `expr` 为 `func`， 后面的 `expr*` 为 `arg*`。

`func` 的类型必须为 `Closure`， 而后面的 `arg*` 类型可以不限， 但要求能够执行 `func`， 否则报错， 同时， 若 `arg*` 中实际参数数量与 `func` 中形参数量不同也需要报错。

`func` 会读取所有的 `arg*`， 并对应地把所有的形参赋值， 创造一个新的作用域并在这个作用域上执行函数的求值。

```
scm> ((lambda (x y) (* x y)) 10 11)
110
scm> (let 
        ([x 1]
        [y 2])
        (let
            ([f (lambda (x y) (+ x y))])
            (f 5 6))) // 结合 let 使用的情况
11
```
