# Project 4: Scheme Interpreter
> 项目文档编写参考自 ACM Class
> DDL 12.30 23:59

## 目录

- [简介](#简介)
- [作业说明](#作业说明)
    - [实现](#实现)
    - [项目编译](#项目编译)
    - [评测方式](#评测方式)
        - [提交](#提交)
        - [本地评测](#本地评测)
    - [分数组成](#分数组成)
- [帮助](#帮助)
- [更新记录](#更新记录)

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
│   └── evaluation.cpp
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

> 想要输入 `myscheme` 直接运行你的程序？ 你可以参考[这个问题](https://stackoverflow.com/questions/56981754/how-to-make-a-programme-executable-anywhere-in-the-shell)

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
R = 112
```

你可以将这两个变量改为任意数字来对给定范围内的测试点进行测评。

### 分数组成

- Basic Task: 75
- Extension: 5
- Q & A: 10
- Coding Conventions: 10

Basic Task 最后我们会统一评测你交上来的文件。

## 帮助

具体要实现的语法可在[Grammar](docs/Grammar.md)查看。

对于 解释器的介绍和对 `src` 中文件的说明可在[Intro](docs/Intro.md)查看。

如果你想获取一些实现上的帮助， 可以参考[Implement](docs/Implement.md)。

## 更新记录

### Update in 2023.12.9

大家好， 我们对大作业的内容进行了一些更新， 具体包括
- 增加了 primitive 中 `symbol?` 语法的处理（要求见 `docs/Grammar.md`， 具体修改见 `src/Def.cpp, src/Def.hpp, src/expr.hpp, src/expr.cpp, src/evaluation.cpp`）
- 更新了 `eq?` 操作对 `Symbol` 的比较规则（见 `docs/Grammar.md`）
- 增加了新的测试点并对测试脚本进行了修改（见 `score/more-tests, score/score.sh`）
- 增加了对 extension 的说明（见 `docs/extension.md`）
