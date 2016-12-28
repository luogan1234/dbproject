#ifndef MY_STRUCT_H
#define MY_STRUCT_H

#include <iostream>
using namespace std;
struct MyType
{
    int dataType;
    int dataWide;
    MyType(int dataType, int dataWide):dataType(dataType), dataWide(dataWide)
    {}
    ~MyType(){}
};
struct AllValue
{
    int intVal;
    string strVal;
    int kind;
    AllValue(int p, bool is_null)
    {
        if(is_null) 
            kind = 3;
        else{
            intVal = p;
            kind = 1;
        }
    }
    AllValue(char *p, bool is_null)
    {
        if(is_null) 
            kind = 3;
        else{
            strVal = string(p);
            kind = 2;
        }
    }
    ~AllValue(){}
};
struct Selector
{
    string tableName, colName;
    bool  hasTableName;
    Selector(char *p)
    {
        colName = string(p);
        hasTableName = false;
    }
    Selector(char *p, char *q)
    {
        tableName = string(p);
        colName = string(q);
        hasTableName = true;
    }
    Selector(string p, string q)
    {
        tableName = (p);
        colName = (q);
        hasTableName = true;
    }
    bool tableNameIsNot(string n)
    {
        if(hasTableName && tableName != n) return true;
        return false;
    }
};
struct Expr
{
    int intVal;
    Selector *colVal;
    string strVal;
    int kind;
    Expr(int v):intVal(v), kind(1){}
    Expr(Selector *s): colVal(s), kind(2){}
    Expr(string s): strVal(s), kind(3){}
    //1 int
    //2 selector
    //3 string
};
struct WhereClause
{
    int op, rightValKind, rightCol1;
    Selector *leftCol, *rightCol2;
    string rightCol3;
    WhereClause(Selector *l, int p)
    :leftCol(l), op(p)
    {}
    WhereClause(Selector *l, int p, Expr *r)
    :leftCol(l), op(p)
    {
        rightValKind = r->kind;
        if(rightValKind == 1)
            rightCol1 = r->intVal;
        else if(rightValKind == 2)
            rightCol2 = r->colVal;
        else
            rightCol3 = r->strVal;
    }
    void test(){std::cout << "test" << std::endl;}
    ~WhereClause(){}
    /*
    0 is null
    1 is not null
    2 =
    3 <>
    4 <=
    5 >=
    6 <
    7 >
    rightValKind
    0 no
    1 int value
    2 col name
    3 string
    */
};
struct SetClause
{
    string colName;
    AllValue *val;
    SetClause(string s, AllValue *v):colName(s),val(v)
    {}
};
#endif //MY_STRUCT_H
