/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_TOKENS_H_INCLUDED
# define YY_YY_TOKENS_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 30 "parser.y" /* yacc.c:1909  */

#include <vector>
#include "../recmanage/TableCols.h"
#include "../recmanage/MyCol.h"
#include "../recmanage/MyData.h"
#include "../query/MyCommands.h"

#line 52 "tokens.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_VALUE_INT = 258,
    T_ID = 259,
    T_CREATE = 260,
    T_DATABASE = 261,
    T_DATABASES = 262,
    T_DROP = 263,
    T_USE = 264,
    T_SHOW = 265,
    T_TABLE = 266,
    T_TABLES = 267,
    T_NOT_NULL = 268,
    T_PRIMARY_KEY = 269,
    T_DESC = 270,
    T_IS = 271,
    T_AND = 272,
    T_INT = 273,
    T_VARCHAR = 274,
    T_INDEX = 275,
    T_INSERT = 276,
    T_INTO = 277,
    T_VALUES = 278,
    T_DELETE = 279,
    T_FROM = 280,
    T_WHERE = 281,
    T_UPDATE = 282,
    T_SET = 283,
    T_SELECT = 284,
    T_NULL = 285,
    T_EQUAL = 286,
    T_NOT_EQUAL = 287,
    T_NO_MORE_THAN = 288,
    T_NO_LESS_THAN = 289,
    T_MORE_THAN = 290,
    T_LESS_THAN = 291,
    T_COLON = 292,
    T_COMMA = 293,
    T_LEFT_BRACKET = 294,
    T_RIGHT_BRACKET = 295,
    T_QUOTATION = 296,
    T_DOT = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 37 "parser.y" /* yacc.c:1909  */

    char *id_t;
    TableCols *fieldList_t;
    MyCol *field_t;
    MyType *type_t;
    vector<MyData*> *valueLists_t;
    MyData *valueList_t;
    AllValue *value_t;
    vector<string> *tableList_t;
    char *string_t;
    int  num_t;
    char char_t;

#line 121 "tokens.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKENS_H_INCLUDED  */
