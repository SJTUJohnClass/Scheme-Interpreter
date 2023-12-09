#include "Def.hpp"
#include "value.hpp"
#include "expr.hpp"
#include "RE.hpp"
#include "syntax.hpp"
#include <cstring>
#include <vector>
#include <map>

extern std :: map<std :: string, ExprType> primitives;
extern std :: map<std :: string, ExprType> reserved_words;

Value Let::eval(Assoc &env) {} // let expression

Value Lambda::eval(Assoc &env) {} // lambda expression

Value Apply::eval(Assoc &e) {} // for function calling

Value Letrec::eval(Assoc &env) {} // letrec expression

Value Var::eval(Assoc &e) {} // evaluation of variable

Value Fixnum::eval(Assoc &e) {} // evaluation of a fixnum

Value If::eval(Assoc &e) {} // if expression

Value True::eval(Assoc &e) {} // evaluation of #t

Value False::eval(Assoc &e) {} // evaluation of #f

Value Begin::eval(Assoc &e) {} // begin expression

Value Quote::eval(Assoc &e) {} // quote expression

Value MakeVoid::eval(Assoc &e) {} // (void)

Value Exit::eval(Assoc &e) {} // (exit)

Value Binary::eval(Assoc &e) {} // evaluation of two-operators primitive

Value Unary::eval(Assoc &e) {} // evaluation of single-operator primitive

Value Mult::evalRator(const Value &rand1, const Value &rand2) {} // *

Value Plus::evalRator(const Value &rand1, const Value &rand2) {} // +

Value Minus::evalRator(const Value &rand1, const Value &rand2) {} // -

Value Less::evalRator(const Value &rand1, const Value &rand2) {} // <

Value LessEq::evalRator(const Value &rand1, const Value &rand2) {} // <=

Value Equal::evalRator(const Value &rand1, const Value &rand2) {} // =

Value GreaterEq::evalRator(const Value &rand1, const Value &rand2) {} // >=

Value Greater::evalRator(const Value &rand1, const Value &rand2) {} // >

Value IsEq::evalRator(const Value &rand1, const Value &rand2) {} // eq?

Value Cons::evalRator(const Value &rand1, const Value &rand2) {} // cons

Value IsBoolean::evalRator(const Value &rand) {} // boolean?

Value IsFixnum::evalRator(const Value &rand) {} // fixnum?

Value IsSymbol::evalRator(const Value &rand) {} // symbol?

Value IsNull::evalRator(const Value &rand) {} // null?

Value IsPair::evalRator(const Value &rand) {} // pair?

Value IsProcedure::evalRator(const Value &rand) {} // procedure?

Value Not::evalRator(const Value &rand) {} // not

Value Car::evalRator(const Value &rand) {} // car

Value Cdr::evalRator(const Value &rand) {} // cdr
