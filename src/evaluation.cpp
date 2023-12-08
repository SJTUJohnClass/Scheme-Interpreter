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

Value Let::eval(Assoc &env) {}

Value Lambda::eval(Assoc &env) {}

Value Apply::eval(Assoc &e) {}

Value Letrec::eval(Assoc &env) {}

Value Var::eval(Assoc &e) {}

Value Fixnum::eval(Assoc &e) {}

Value If::eval(Assoc &e) {}

Value True::eval(Assoc &e) {}

Value False::eval(Assoc &e) {}

Value Begin::eval(Assoc &e) {}

Value Quote::eval(Assoc &e) {}

Value MakeVoid::eval(Assoc &e) {}

Value Exit::eval(Assoc &e) {}

Value Binary::eval(Assoc &e) {}

Value Unary::eval(Assoc &e) {}

Value Mult::evalRator(const Value &rand1, const Value &rand2) {}

Value Plus::evalRator(const Value &rand1, const Value &rand2) {}

Value Minus::evalRator(const Value &rand1, const Value &rand2) {}

Value Less::evalRator(const Value &rand1, const Value &rand2) {}

Value LessEq::evalRator(const Value &rand1, const Value &rand2) {}

Value Equal::evalRator(const Value &rand1, const Value &rand2) {}

Value GreaterEq::evalRator(const Value &rand1, const Value &rand2) {}

Value Greater::evalRator(const Value &rand1, const Value &rand2) {}

Value IsEq::evalRator(const Value &rand1, const Value &rand2) {}

Value Cons::evalRator(const Value &rand1, const Value &rand2) {}

Value IsBoolean::evalRator(const Value &rand) {}

Value IsFixnum::evalRator(const Value &rand) {}

Value IsNull::evalRator(const Value &rand) {}

Value IsPair::evalRator(const Value &rand) {}

Value IsProcedure::evalRator(const Value &rand) {}

Value Not::evalRator(const Value &rand) {}

Value Car::evalRator(const Value &rand) {}

Value Cdr::evalRator(const Value &rand) {}
