# Project 4: Scheme Interpreter
> 项目文档编写参考自 ACM Class

## 目录

- [简介](#简介)
- [作业说明](#作业说明)
    - [实现](#实现)
    - [项目编译](#项目编译)
    - [评测方式](#评测方式)
        - [提交](#提交)
        - [本地评测](#本地评测)
    - [分数组成](#分数组成)
- [帮助]()

## 简介

本次大作业需要你实现一个简单的 Scheme 解释器, 接受 Scheme 语言的子集并按照控制流执行代码。

你需要实现的功能有：
- 实现 parser。
- 利用 REPL 交互模式对给定的语句进行解释执行。
- 实现部分 Library 中的函数。
- 对输入的语句进行语法检查。

## 作业说明

### 实现

你需要补充代码的部分为
```
├── src
│   ├── shared.hpp
│   ├── parser.cpp
│   └── evaluation.hpp
```
下面是可能对程序编写有帮助的一些文件
```
├── src
│   ├── Def.hpp
│   ├── Def.cpp
│   ├── syntax.hpp
│   ├── expr.hpp
│   ├── value.hpp
│   ├── syntax.hpp
│   └── expr.hpp
```
其中 `shared.hpp` 应为 SmartPointer 中你编写的 `SharedPtr` 对应的 `.hpp`。

### 项目编译

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

### 评测方式

#### 提交

在 OJ 上进行提交测评， 我们也会下发所有数据来实现本地的调试。

具体而言， 有两种提交到 OJ 的测评方式
- 将整个文件夹压缩成压缩包在题面处上传， OJ 会根据根目录下的 CMakeLists 来构建你的程序。
- 在代码提交页面输入 `git` 仓库的地址。

#### 本地评测

我们在 repo 中提供了评测程序来对你的解释器进行本地测评， 评测程序在子目录 `score` 下， 评测数据在子目录 `score/data` 下。

具体而言， 评测程序会执行你的解释器并将结果与标准程序的输出进行比对， 要使用评测程序， 在子目录 `score` 下执行以下命令即可
```
g++ -o score score.cpp
./score -f
```

### 分数组成

- Task Completion: 80
- Q & A: 10
- Coding Conventions: 10

## 帮助

对于 Scheme 语言的介绍可在[About-Scheme](docs/About-Scheme.md)查看。

具体要实现的语法可在[Grammar](docs/Grammar.md)查看。

对于 `src` 中文件的说明可在[Intro](docs/Intro.md)查看。

如果你想获取一些实现上的帮助， 可以参考[Implement](docs/Implement.md)。