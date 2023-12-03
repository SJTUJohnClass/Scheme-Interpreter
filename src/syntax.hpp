#ifndef SYNTAX 
#define SYNTAX

#include <cstring>
#include <memory>
#include <vector>
#include "Def.hpp"
#include "shared.hpp"

struct SyntaxBase {
  virtual Expr parse() = 0;
  virtual void show(std::ostream &) = 0;
  virtual ~SyntaxBase() = default;
};

struct Syntax {
    SharedPtr<SyntaxBase> ptr;
    Syntax(SyntaxBase *);
    SyntaxBase* operator -> () const; 
    SyntaxBase& operator * ();
    SyntaxBase* get() const;
    Expr parse();
};

struct Number : SyntaxBase {
    int n;
    Number(int);
    virtual Expr parse() override;
    virtual void show(std::ostream &) override;
};

struct TrueSyntax : SyntaxBase {
    // TrueSyntax();
    virtual Expr parse() override;
    virtual void show(std :: ostream &) override;
};

struct FalseSyntax : SyntaxBase {
    // FalseSyntax();
    virtual Expr parse() override;
    virtual void show(std :: ostream &) override;
};

struct Identifier : SyntaxBase {
    std::string s;
    Identifier(const std::string &);
    virtual Expr parse() override;
    virtual void show(std::ostream &) override;
};

struct List : SyntaxBase {
    std :: vector<Syntax> stxs;
    List();
    virtual Expr parse() override;
    virtual void show(std::ostream &) override;
};

Syntax readSyntax(std::istream &);

std::istream &operator>>(std::istream &, Syntax);
#endif