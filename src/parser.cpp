#ifndef PARSER 
#define PARSER

// parser of myscheme 

#include "RE.hpp"
#include "Def.hpp"
#include "syntax.hpp"
#include "expr.hpp"
#include <map>
#include <cstring>
#include <iostream>
#define mp make_pair
using std :: string;
using std :: vector;
using std :: pair;

extern std :: map<std :: string, ExprType> primitives;
extern std :: map<std :: string, ExprType> reserved_words;

Expr Syntax :: parse(Assoc &env) {}

Expr Number :: parse(Assoc &env) {}

Expr Identifier :: parse(Assoc &env) {}

Expr TrueSyntax :: parse(Assoc &env) {}

Expr FalseSyntax :: parse(Assoc &env) {}

Expr List :: parse(Assoc &env) {}

#endif