# Implement

帮助你实现该项目的一些 tips

## Tips 0

如同我们已经在[Intro](Intro.md)中介绍的那样， 你应当已经了解了所有文件和接口的用法。

如果还不知道如何使用这些接口和语法可以去看对应的项目文件和其他的 docs 来了解。

在本次作业的实现中， 你并不需要担心内存泄漏。

此外， 由于我们用到了一小部分关于 C++ 中继承的内容， 你需要了解如何使用 [`dynamic_cast` 函数](https://www.runoob.com/cplusplus/cpp-casting-operators.html)来实现基类指针与派生类指针的转换。

还有一个小提示， 变量的名字是可以与非 `primitive` 外的其他关键字相同的， 比如一个变量的名字可以为 `lambda, letrec` 等。

## Tips 1

你需要实现的第一个部分是 Parser， 这一部分在 `parser.cpp` 中。

一种好的实现方式是先实现对于简单 syntax 的 parse， 如 `Number, Identifier, TrueSyntax, FalseSyntax` 等， 再实现对 `List` 的 parse， 而在 parse 过程中你可以使用我们提供的 `primitives, reserved_words` 以及枚举类型 `E_TYPE` 来简化你的程序。

## Tips 2

你需要实现的第二个部分是 Evaluation， 这一部分在 `evaluation.cpp` 中。

这一部分也需要你由简单到难地实现各个 `Expr` 的求值， 具体顺序可以由你自己定， 我们推荐的方式是先实现 `Var, Fixnum` 等最简单的， 然后实现 `Mult, Plus` 等算数运算符和比较运算符。 在这之后， 实现其他的 primitives， 将 `Let, Apply` 等放到最后实现（这里的 `Apply` 是函数调用的意思， 具体可以查看 `expr.hpp` 和 [Grammar](Grammar.md)）。

## Tips 3

对于异常处理部分， 你需要使用 `RE.hpp` 中提供的异常类 `RuntimeError`， 在适当的时候抛出异常并用 `try-catch` 语法来实现异常的接收。

关于异常你可以在[这里](https://www.runoob.com/cplusplus/cpp-exceptions-handling.html)找到信息， 而什么时候会出现异常你可以参考[Grammar](Grammar.md)。
