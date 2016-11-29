#ifndef _TREE_H_ 
#define _TREE_H_

#include <string>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <cstring>
#include <list>
#include <map>

using namespace std;


typedef list<string> IdList;

enum VarType {
    MY_INT, BOOLEAN, STRINGS, CHARACTER, FUNCTION, ARRAY
};

enum MethodType {
    M_VOID, M_INT, M_BOOLEAN
};

struct VValue {

    int IntValue() {
        
        return u.ivalue;
    }

    bool BoolValue() {
        if (type == MY_INT) {
            return true;
        }
        
        return u.bvalue;
    }

    char* StringValue() {
        return u.svalue;
    }

    char CharValue() {
        return u.cvalue;
    }

    void setIntArrayValue(int pos, int val) {
        if(pos>=ArraySize){
            printf("Out of range.\n");
            exit(0);
        }
        u.a_ivalue[pos]=val;
    }

    void setBoolArrayValue(int pos, bool val) {
        if(pos>=ArraySize){
            printf("Out of range.\n");
            exit(0);
        }
        u.a_bvalue[pos]=val;
    }
    int getIntArrayValue() {
        if(Pos>=ArraySize){
            printf("Out of range.\n");
            exit(0);
        }
        return u.a_ivalue[Pos];
    }

    bool getBoolArrayValue() {
        if(Pos>=ArraySize){
            printf("Out of range.\n");
            exit(0);
        }
        return u.a_bvalue[Pos];
    }

    VarType type;
    bool isArray;
    int ArraySize;
    int Pos;

    union {
        int ivalue;
        bool bvalue;
        char* svalue;
        char cvalue;

        int* a_ivalue;
        bool* a_bvalue;
    } u;
};
class DeclItem {
public:

    DeclItem(string id) {
        this-> id = id;
    }
    
    DeclItem(string id, int dimension) {
        this-> id = id;
        this->dimension = dimension;
    }
    string id;
    int dimension;
};
typedef list<DeclItem*> DeclItemList;

class Expr {
public:
    virtual VValue evaluate() = 0;
};

typedef list<Expr*> ExprList;

class BinaryExpr : public Expr {
public:

    BinaryExpr(Expr *expr1, Expr *expr2) {
        this->expr1 = expr1;
        this->expr2 = expr2;
    }

    Expr *expr1;
    Expr *expr2;
};

class LessThanExpr : public BinaryExpr {
public:

    LessThanExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class GreaterThanExpr : public BinaryExpr {
public:

    GreaterThanExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class LessThanEqualExpr : public BinaryExpr {
public:

    LessThanEqualExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class GreaterThanEqualExpr : public BinaryExpr {
public:

    GreaterThanEqualExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class NotEqualExpr : public BinaryExpr {
public:

    NotEqualExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class EqualExpr : public BinaryExpr {
public:

    EqualExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class AddExpr : public BinaryExpr {
public:

    AddExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class SubExpr : public BinaryExpr {
public:

    SubExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class MultExpr : public BinaryExpr {
public:

    MultExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class DivExpr : public BinaryExpr {
public:

    DivExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class NegativeExpr : public Expr {
public:

    NegativeExpr(Expr *expr) {
        this->expr = expr;
    }

    VValue evaluate();
    Expr *expr;
};

class NotExpr : public Expr {
public:

    NotExpr(Expr *expr) {
        this->expr = expr;
    }

    VValue evaluate();
    Expr *expr;
};

class OrExpr : public BinaryExpr {
public:

    OrExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class AndExpr : public BinaryExpr {
public:

    AndExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class ShiftLeftExpr : public BinaryExpr {
public:

    ShiftLeftExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class RotExpr : public BinaryExpr {
public:

    RotExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class ModExpr : public BinaryExpr {
public:

    ModExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class ShiftRightExpr : public BinaryExpr {
public:

    ShiftRightExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2) {
    }

    VValue evaluate();
};

class IntExpr : public Expr {
public:

    IntExpr(int value) {
        this->value.type = MY_INT;
        this->value.u.ivalue = value;
    }

    VValue evaluate() {
        return value;
    }

    VValue value;
};

class BoolExpr : public Expr {
public:

    BoolExpr(bool value) {
        this->value.type = BOOLEAN;
        this->value.u.bvalue = value;
    }

    VValue evaluate() {
        return value;
    }

    VValue value;
};

class IdExpr : public Expr {
public:

    IdExpr(string id) {
        this->id = id;
    }
    VValue evaluate();

    string id;
};

class ArrayExpr : public Expr {
public:

    ArrayExpr(string id, Expr* dim) {
        this->id = id;
        this->dim = dim;
    }
    VValue evaluate();

    string id;
    Expr* dim;
};

class StrExpr : public Expr {
public:

    StrExpr(string id) {
        this->val = id;
    }
    VValue evaluate();

    string val;
};

class CharExpr : public Expr {
public:

    CharExpr(char value) {
        this->value.type = CHARACTER;
        this->value.u.cvalue = value;
    }

    VValue evaluate() {
        return value;
    }

    VValue value;
};

class MethodExpr : public Expr {
public:

    MethodExpr(string id, ExprList ls) {
        this->id = id;
        this->exprs = ls;
    }
    VValue evaluate();

    string id;
    ExprList exprs;
};

enum StatementKind {
    BLOCK_STATEMENT,
    PRINT_STATEMENT,
    ASSIGN_STATEMENT,
    IF_STATEMENT,
    WHILE_STATEMENT,
    FOR_STATEMENT,
    CONTINUE_STATEMENT,
    BREAK_STATEMENT,
    READ_STATEMENT,
    RETURN_STATEMENT,
    METHOD_STATEMENT
};

class Statement {
public:
    virtual void execute() = 0;
    virtual StatementKind getKind() = 0;
};

typedef list<Statement*> StatementList;

class BlockStatement : public Statement {
public:

    BlockStatement(list<Statement *> stList) {
        this->stList = stList;
    }
    void execute();

    StatementKind getKind() {
        return BLOCK_STATEMENT;
    }

    list<Statement *> stList;
};

class ReadStatement : public Statement {
public:

    ReadStatement(DeclItemList ids) {
        this->ids = ids;
    }
    void execute();

    StatementKind getKind() {
        return READ_STATEMENT;
    }
    DeclItemList ids;
};

class ReturnStatement : public Statement {
public:

    ReturnStatement(Expr* expr) {
        this->expr = expr;
    }
    void execute();

    StatementKind getKind() {
        return RETURN_STATEMENT;
    }
    Expr* expr;
    
};

class ContinueStatement : public Statement {
public:

    ContinueStatement() {
    }
    void execute();

    StatementKind getKind() {
        return CONTINUE_STATEMENT;
    }
};

class BreakStatement : public Statement {
public:

    BreakStatement() {
    }
    void execute();

    StatementKind getKind() {
        return BREAK_STATEMENT;
    }
};

class MethodStatement : public Statement {
public:

    MethodStatement(string id, ExprList ls) {
        this->id = id;
        this->exprs = ls;
    }
    void execute();

    StatementKind getKind() {
        return METHOD_STATEMENT;
    }
    
    string id;
    ExprList exprs;
};

class PrintStatement : public Statement {
public:

    PrintStatement(ExprList expr) {
        this->expr = expr;
    }
    void execute();

    StatementKind getKind() {
        return PRINT_STATEMENT;
    }
    ExprList expr;
};

class AssignStatement : public Statement {
public:

    AssignStatement(string id, Expr* dim, Expr *expr) {
        this->id = id;
        this->dim = dim;
        this->expr = expr;
    }
    void execute();

    StatementKind getKind() {
        return ASSIGN_STATEMENT;
    }
    string id;
    Expr *expr;
    Expr *dim;
};

class IfStatement : public Statement {
public:

    IfStatement(Expr *cond, list<Statement *>trueBlock, list<Statement *>falseBlock) {
        this->cond = cond;
        this->trueBlock = trueBlock;
        this->falseBlock = falseBlock;
    }
    void execute();

    StatementKind getKind() {
        return IF_STATEMENT;
    }
    Expr *cond;
    list<Statement *>trueBlock;
    list<Statement *>falseBlock;
};

class WhileStatement : public Statement {
public:

    WhileStatement(Expr *cond, list<Statement *>statementBlock) {
        this->cond = cond;
        this->statementBlock = statementBlock;
    }
    void execute();

    StatementKind getKind() {
        return WHILE_STATEMENT;
    }
    Expr *cond;
    list<Statement *>statementBlock;
};

class ForStatement : public Statement {
public:

    ForStatement(StatementList assignStatement, Expr *cond, StatementList finalAssignStatement, list<Statement *> statementBlock) {
        this->assignStatement = assignStatement;
        this->cond = cond;
        this->finalAssignStatement = finalAssignStatement;
        this->statementBlock = statementBlock;
    }
    void execute();

    StatementKind getKind() {
        return FOR_STATEMENT;
    }
    StatementList assignStatement;
    Expr *cond;
    StatementList finalAssignStatement;
    list<Statement *> statementBlock;
};

class Declaration {
public:

    Declaration(VarType type, DeclItemList ids, Expr *value) {
        this->ids = ids;
        this->type = type;
        this->value = value;
    }
    void execute();
    DeclItemList ids;
    VarType type;
    Expr* value;
};

class Param {
public:

    Param(VarType type, string id) {
        this->id = id;
        this->type = type;
    }
    void execute();
    string id;
    VarType type;
};

typedef list<Param*> ParamList;
typedef list<Declaration*> DeclList;

class Method {
public:
    Method(){
    
    }
    Method(MethodType type, string id, ParamList params, DeclList declare, list<Statement*> statementBlock) {
        this->id = id;
        this->type = type;
        this->statementBlock = statementBlock;
        this->params = params;
        this->declare = declare;
    }
    void execute();
    string id;
    MethodType type;
    list<Statement*> statementBlock;
    ParamList params;
    DeclList declare;
    map<string, VValue> LTable;
};
typedef list<Method*> MethodList;


class Program {
public:
    Program(DeclList *variables,MethodList *methods){
        this->Variables = variables;
        this->Methods = methods;
    }
    void Initialize();
    void RunMain();
    MethodList *Methods;
    DeclList *Variables;
};

typedef list<AssignStatement*> AssignList;

extern map<string, VValue> sTable;
extern map<string, Method*> mTable;
typedef map<string, Method*> AcVariables;
extern VValue returnValue;
extern string MethodName;
#endif
