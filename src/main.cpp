#include "Def.hpp"
#include "syntax.hpp"
#include "expr.hpp"
#include "value.hpp"
#include "RE.hpp"
#include <sstream>
#include <iostream>
#include <map>


extern std :: map<std :: string, ExprType> primitives;
extern std :: map<std :: string, ExprType> reserved_words;

void REPL()
{
    // read - evaluation - print loop
    Assoc global_env = empty();
    while (1)
    {
        printf("scm> ");
        Syntax stx = readSyntax(std :: cin); // read
        try
        {
            // stx -> show(std :: cout); // syntax print
            Expr expr = stx -> parse(); // parse
            Value val = expr -> eval(global_env);
            if (val -> v_type == V_TERMINATE)
                break;
            val -> show(std :: cout); // print
        }
        catch (const RuntimeError &RE)
        {
            std :: cout << RE.message();
        }
        puts("");
    }
}


int main(int argc, char *argv[]) {
    initPrimitives();
    initReservedWords();
    REPL();
    return 0;
}
