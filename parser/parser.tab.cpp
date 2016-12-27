/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include "../fileio/FileManager.h"
#include "../recmanage/TableCols.h"
#include "../recmanage/MyCol.h"
#include "../recmanage/MyData.h"
#include "../query/MyCommands.h"
#include "../query/MyStruct.h"

using namespace std;
extern int line;

MyCommands commands;
<<<<<<< Updated upstream
=======
int setPrimaryKey = 0;
int valueNum = 0;
>>>>>>> Stashed changes
int comNum = 0;
int yylex();

void yyerror(const char *str)
{
    printf("%s, Line:%d\n", str,line);
}

#define YYERROR_VERBOSE 1

<<<<<<< Updated upstream
#line 95 "parser.tab.c" /* yacc.c:339  */
=======
#line 98 "parser.tab.c" /* yacc.c:339  */
>>>>>>> Stashed changes

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "tokens.h".  */
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
<<<<<<< Updated upstream
#line 29 "parser.y" /* yacc.c:355  */
=======
#line 32 "parser.y" /* yacc.c:355  */
>>>>>>> Stashed changes

#include "../recmanage/TableCols.h"
#include "../recmanage/MyCol.h"
#include "../recmanage/MyData.h"
#include "../query/MyCommands.h"
#include "../query/MyStruct.h"

<<<<<<< Updated upstream
#line 132 "parser.tab.c" /* yacc.c:355  */
=======
#line 137 "parser.tab.c" /* yacc.c:355  */
>>>>>>> Stashed changes

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_VALUE_INT = 258,
    T_ID = 259,
    T_STRING = 260,
    T_CREATE = 261,
    T_DATABASE = 262,
    T_DATABASES = 263,
    T_DROP = 264,
    T_USE = 265,
    T_SHOW = 266,
    T_TABLE = 267,
    T_TABLES = 268,
    T_NOT_NULL = 269,
    T_PRIMARY_KEY = 270,
    T_FOREIGN_KEY = 271,
    T_DESC = 272,
    T_IS = 273,
    T_AND = 274,
    T_INT = 275,
    T_CHAR = 276,
    T_VARCHAR = 277,
    T_INDEX = 278,
    T_INSERT = 279,
    T_INTO = 280,
    T_VALUES = 281,
    T_DELETE = 282,
    T_FROM = 283,
    T_WHERE = 284,
    T_UPDATE = 285,
    T_SET = 286,
    T_SELECT = 287,
    T_NULL = 288,
    T_CHECK = 289,
    T_EQUAL = 290,
    T_NOT_EQUAL = 291,
    T_NO_MORE_THAN = 292,
    T_NO_LESS_THAN = 293,
    T_MORE_THAN = 294,
    T_LESS_THAN = 295,
    T_COLON = 296,
    T_COMMA = 297,
    T_LEFT_BRACKET = 298,
    T_RIGHT_BRACKET = 299,
    T_DOT = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
<<<<<<< Updated upstream
#line 35 "parser.y" /* yacc.c:355  */
=======
#line 40 "parser.y" /* yacc.c:355  */
>>>>>>> Stashed changes

    char *id_t;
    TableCols *fieldList_t;
    MyCol *field_t;
    MyType *type_t;
<<<<<<< Updated upstream
=======
    vector<vector<AllValue*>*> *valueLists_t;
    vector<AllValue*> *valueList_t;
    AllValue *value_t;
    vector<string> *tableList_t;
    Selector *col_t;
    vector<Selector*> *selector_t;
    vector<WhereClause*> *whereClause_t;
    WhereClause* where_t;
    Expr *expr_t;
    vector<SetClause*> *setClause_t;
>>>>>>> Stashed changes
    char *string_t;
    int  num_t;
    char char_t;

<<<<<<< Updated upstream
#line 197 "parser.tab.c" /* yacc.c:355  */
=======
#line 215 "parser.tab.c" /* yacc.c:355  */
>>>>>>> Stashed changes
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKENS_H_INCLUDED  */

/* Copy the second part of user declarations.  */

<<<<<<< Updated upstream
#line 214 "parser.tab.c" /* yacc.c:358  */
=======
#line 232 "parser.tab.c" /* yacc.c:358  */
>>>>>>> Stashed changes

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
<<<<<<< Updated upstream
#define YYLAST   121
=======
#define YYLAST   145
>>>>>>> Stashed changes

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
<<<<<<< Updated upstream
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135
=======
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  155
>>>>>>> Stashed changes

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
<<<<<<< Updated upstream
       0,    58,    58,    61,    66,    67,    68,    69,    71,    78,
      84,    90,    96,   105,   112,   118,   123,   129,   130,   131,
     133,   134,   136,   148,   160,   166,   171,   176,   181,   186,
     187,   189,   190,   192,   193,   194,   195,   197,   198,   200,
     201,   203,   203,   203,   203,   203,   203,   205,   206,   208,
     209,   211,   212,   214,   215,   216,   218,   220,   222,   224
=======
       0,    84,    84,    87,    93,    94,    95,    96,    98,   105,
     111,   117,   123,   132,   139,   145,   152,   158,   164,   168,
     174,   178,   182,   188,   194,   201,   214,   233,   237,   244,
     248,   256,   260,   265,   269,   273,   278,   282,   289,   295,
     306,   315,   321,   327,   328,   329,   331,   332,   333,   335,
     336,   337,   338,   339,   340,   342,   349,   356,   363,   369,
     370,   372,   379,   385,   386,   387,   389,   391,   393,   395
>>>>>>> Stashed changes
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
<<<<<<< Updated upstream
  "$end", "error", "$undefined", "T_VALUE_INT", "T_ID", "T_CREATE",
  "T_DATABASE", "T_DATABASES", "T_DROP", "T_USE", "T_SHOW", "T_TABLE",
  "T_TABLES", "T_NOT_NULL", "T_PRIMARY_KEY", "T_DESC", "T_IS", "T_AND",
  "T_INT", "T_VARCHAR", "T_INDEX", "T_INSERT", "T_INTO", "T_VALUES",
  "T_DELETE", "T_FROM", "T_WHERE", "T_UPDATE", "T_SET", "T_SELECT",
  "T_NULL", "T_EQUAL", "T_NOT_EQUAL", "T_NO_MORE_THAN", "T_NO_LESS_THAN",
  "T_MORE_THAN", "T_LESS_THAN", "T_COLON", "T_COMMA", "T_LEFT_BRACKET",
  "T_RIGHT_BRACKET", "T_QUOTATION", "T_DOT", "$accept", "program", "stmt",
  "sysStmt", "dbStmt", "tbStmt", "idxStmt", "fieldList", "field", "type",
  "valueLists", "valueList", "whereClause", "expr", "col", "op",
  "setClause", "selector", "tableList", "value", "dbName", "tbName",
  "colName", "T_VALUE_STRING", YY_NULLPTR
=======
  "$end", "error", "$undefined", "T_VALUE_INT", "T_ID", "T_STRING",
  "T_CREATE", "T_DATABASE", "T_DATABASES", "T_DROP", "T_USE", "T_SHOW",
  "T_TABLE", "T_TABLES", "T_NOT_NULL", "T_PRIMARY_KEY", "T_FOREIGN_KEY",
  "T_DESC", "T_IS", "T_AND", "T_INT", "T_CHAR", "T_VARCHAR", "T_INDEX",
  "T_INSERT", "T_INTO", "T_VALUES", "T_DELETE", "T_FROM", "T_WHERE",
  "T_UPDATE", "T_SET", "T_SELECT", "T_NULL", "T_CHECK", "T_EQUAL",
  "T_NOT_EQUAL", "T_NO_MORE_THAN", "T_NO_LESS_THAN", "T_MORE_THAN",
  "T_LESS_THAN", "T_COLON", "T_COMMA", "T_LEFT_BRACKET", "T_RIGHT_BRACKET",
  "T_DOT", "$accept", "program", "stmt", "sysStmt", "dbStmt", "tbStmt",
  "idxStmt", "fieldList", "field", "type", "check", "valueLists",
  "valueList", "whereClause", "where", "expr", "op", "setClause",
  "selector", "col", "tableList", "value", "dbName", "tbName", "colName",
  "T_VALUE_STRING", YY_NULLPTR
>>>>>>> Stashed changes
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

<<<<<<< Updated upstream
#define YYPACT_NINF -75

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-75)))

#define YYTABLE_NINF -58
=======
#define YYPACT_NINF -81

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-81)))

#define YYTABLE_NINF -68
>>>>>>> Stashed changes

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
<<<<<<< Updated upstream
     -75,    47,   -75,    31,    52,    -2,    26,    35,   -13,    42,
      35,    56,   -75,    -7,     9,    33,    38,    -2,    35,    35,
      -2,    35,    35,   -75,   -75,   -75,   -75,   -75,   -75,    35,
      35,    59,    36,   -75,   -17,    51,   -75,   -75,   -75,   -75,
     -75,   -75,    55,    57,   -75,   -75,    58,    66,    65,    91,
      35,    56,    91,     6,    91,    91,    60,    56,   -75,    10,
      69,    39,   -75,   -75,   -75,    62,   -21,   -75,    67,    63,
      64,     4,    68,    81,    48,    56,    91,     4,    56,    35,
      91,     6,   -75,    70,    71,    89,   -75,   -75,   -75,   -75,
     101,    21,   -75,   -75,    72,    56,     5,   -75,   -75,   -75,
     -75,   -75,   -75,     2,    81,    76,   -75,    81,   -75,    73,
     -75,   105,   109,   -75,    74,     4,   -75,     4,    81,   -75,
     -75,   -75,   -75,   -75,     4,   -75,    77,    78,   -75,   -75,
      50,   -75,   -75,   -75,   -75
=======
     -81,    12,   -81,     3,    38,     0,    67,    15,    30,    -8,
      15,     7,   -81,    -4,    61,    62,    63,     0,    15,    15,
       0,    15,    15,   -81,   -81,   -81,   -81,   -81,   -81,    15,
      15,    27,    42,    15,    -1,   -81,    60,   -81,   -81,   -81,
     -81,   -81,   -81,    64,    65,   -81,   -81,    66,    53,    52,
     102,    34,   -81,    15,   106,   102,    70,   102,   102,    68,
     106,   -81,    35,    77,   106,    15,    36,   -81,   -81,    72,
      73,    40,   -81,    71,    69,    74,    29,    75,    95,   -81,
      31,   106,   102,    29,    95,   -81,   106,   102,    15,    70,
     -81,    76,    78,    79,    17,   -81,   -81,   -81,   -81,   -81,
      46,   -81,   -81,    80,   106,    39,   -81,   -81,   -81,   -81,
     -81,   -81,    91,    95,    85,   -81,    95,    81,    82,   -81,
     121,   123,   125,   -81,    86,   116,    29,   -81,    29,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,    29,   -81,   102,    87,
      88,    89,    29,   -81,   -81,    55,   -81,    90,   -81,   -81,
     -81,    56,   -81,   -81,   -81
>>>>>>> Stashed changes
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     0,
<<<<<<< Updated upstream
       0,     0,     0,    56,    11,     8,    12,    57,    15,     0,
       0,     0,    58,    49,     0,     0,    40,     4,     5,     6,
       7,     9,     0,     0,    10,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,     0,
       0,     0,    51,    50,    39,     0,     0,    22,     0,     0,
       0,     0,    16,    17,     0,     0,     0,     0,     0,     0,
       0,     0,    13,     0,     0,    24,    20,    21,    53,    55,
       0,     0,    31,    54,     0,     0,     0,    41,    42,    43,
      44,    46,    45,     0,    18,     0,    47,    19,    52,     0,
      23,     0,     0,    25,     0,     0,    29,     0,    36,    35,
      34,    33,    38,    37,     0,    26,     0,     0,    59,    32,
       0,    48,    27,    28,    30
=======
       0,     0,     0,    66,    11,     8,    12,    67,    15,     0,
       0,     0,    68,     0,     0,    57,     0,    60,     4,     5,
       6,     7,     9,     0,     0,    10,    14,     0,     0,     0,
       0,    20,    61,     0,     0,     0,     0,     0,     0,     0,
       0,    68,     0,     0,     0,     0,    22,    58,    59,     0,
       0,     0,    25,     0,     0,     0,     0,    16,    17,    41,
       0,     0,     0,     0,    21,    62,     0,     0,     0,     0,
      13,     0,     0,     0,    27,    23,    24,    63,    69,    65,
       0,    39,    64,     0,     0,     0,    49,    50,    51,    52,
      54,    53,     0,    18,     0,    55,    19,     0,     0,    26,
       0,     0,     0,    29,     0,    28,     0,    37,     0,    42,
      45,    44,    46,    43,    48,    47,     0,    31,     0,     0,
       0,     0,     0,    30,    40,     0,    56,     0,    33,    34,
      35,     0,    38,    32,    36
>>>>>>> Stashed changes
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
<<<<<<< Updated upstream
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,    40,   -75,
     -75,    -3,   -64,   -75,   -11,   -75,   -75,   -75,   -75,   -74,
      49,    -6,   -27,   -75
=======
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,    47,   -81,
     -81,   -81,   -69,   -34,    33,   -81,   -81,   -81,   -81,   -11,
      92,   -80,    37,    -5,   -49,    23
>>>>>>> Stashed changes
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
<<<<<<< Updated upstream
      -1,     1,    12,    13,    14,    15,    16,    66,    67,    85,
      72,    91,    73,   121,    74,   103,    59,    34,    61,    92,
      24,    35,    36,    93
=======
      -1,     1,    12,    13,    14,    15,    16,    71,    72,    94,
     125,    77,   100,    78,    79,   133,   112,    62,    34,    80,
      51,   101,    24,    36,    37,   102
>>>>>>> Stashed changes
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
<<<<<<< Updated upstream
      33,    28,    23,   106,    31,    88,    32,    88,    50,    29,
      58,   104,    42,    43,   107,    45,    46,    81,   119,    82,
      65,    51,    60,    47,    48,    64,    68,    69,    70,   123,
      37,   118,    89,    25,    89,   120,    75,    17,    26,    27,
      63,   129,    18,    90,    62,    90,    38,     2,    76,   105,
     131,    19,     3,   109,    68,     4,     5,     6,    20,   115,
      32,   116,     7,    21,    96,    78,    41,    30,     8,    44,
      39,     9,    22,   108,    10,    40,    11,    79,   -57,    97,
      98,    99,   100,   101,   102,    83,    84,    49,   115,    56,
     134,    57,   122,    52,    53,    58,    54,    55,    95,    71,
      77,    80,   113,    86,    87,   114,    94,   124,   126,   111,
     112,   117,   127,   125,   130,   128,     0,   132,   133,     0,
       0,   110
=======
      35,    63,    28,   115,    23,    31,    68,    73,    74,    75,
      17,    32,     2,    43,    44,    18,    46,    47,     3,    27,
      30,     4,     5,     6,    48,    49,    19,    53,    52,     7,
      84,   123,    97,   114,    98,    33,     8,    38,   117,     9,
      73,    54,    10,    67,    11,    20,   144,   113,    52,   105,
      21,   124,   116,   130,    42,    29,   146,    45,    50,   145,
      85,    22,    99,    64,    81,    86,   106,   107,   108,   109,
     110,   111,   131,   151,    61,    25,    65,    82,    65,    59,
      26,    60,    89,   118,    90,    69,    70,   -67,   126,   147,
     127,    91,    92,    93,   132,    32,    98,   126,   126,   152,
     154,   134,    39,    40,    41,    55,    61,    56,    57,    58,
      32,    76,    83,    95,   104,    87,    88,   103,    96,   120,
     136,   121,   122,   128,   139,   137,   140,   138,   141,   142,
     143,   148,   149,   150,   153,   135,   119,   129,     0,     0,
       0,     0,     0,     0,     0,    66
>>>>>>> Stashed changes
};

static const yytype_int16 yycheck[] =
{
<<<<<<< Updated upstream
      11,     7,     4,    77,    10,     3,     4,     3,    25,    22,
       4,    75,    18,    19,    78,    21,    22,    38,    13,    40,
      14,    38,    49,    29,    30,    52,    53,    54,    55,   103,
      37,    95,    30,     7,    30,    30,    26,     6,    12,     4,
      51,   115,    11,    41,    50,    41,    37,     0,    38,    76,
     124,    20,     5,    80,    81,     8,     9,    10,     6,    38,
       4,    40,    15,    11,    16,    26,    17,    25,    21,    20,
      37,    24,    20,    79,    27,    37,    29,    38,    42,    31,
      32,    33,    34,    35,    36,    18,    19,    28,    38,    23,
      40,    26,   103,    42,    39,     4,    39,    39,    17,    39,
      31,    39,    13,    40,    40,     4,    38,    31,     3,    39,
      39,    39,     3,    40,   117,    41,    -1,    40,    40,    -1,
      -1,    81
=======
      11,    50,     7,    83,     4,    10,    55,    56,    57,    58,
       7,     4,     0,    18,    19,    12,    21,    22,     6,     4,
      28,     9,    10,    11,    29,    30,    23,    28,    33,    17,
      64,    14,     3,    82,     5,    28,    24,    41,    87,    27,
      89,    42,    30,    54,    32,     7,   126,    81,    53,    18,
      12,    34,    86,    14,    17,    25,   136,    20,    31,   128,
      65,    23,    33,    29,    29,    29,    35,    36,    37,    38,
      39,    40,    33,   142,     4,     8,    42,    42,    42,    26,
      13,    29,    42,    88,    44,    15,    16,    45,    42,   138,
      44,    20,    21,    22,     3,     4,     5,    42,    42,    44,
      44,   112,    41,    41,    41,    45,     4,    43,    43,    43,
       4,    43,    35,    44,    19,    43,    43,    42,    44,    43,
      35,    43,    43,    43,     3,    44,     3,    45,     3,    43,
      14,    44,    44,    44,    44,   112,    89,   104,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53
>>>>>>> Stashed changes
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
<<<<<<< Updated upstream
       0,    44,     0,     5,     8,     9,    10,    15,    21,    24,
      27,    29,    45,    46,    47,    48,    49,     6,    11,    20,
       6,    11,    20,     4,    63,     7,    12,     4,    64,    22,
      25,    64,     4,    57,    60,    64,    65,    37,    37,    37,
      37,    63,    64,    64,    63,    64,    64,    64,    64,    28,
      25,    38,    42,    39,    39,    39,    23,    26,     4,    59,
      65,    61,    64,    57,    65,    14,    50,    51,    65,    65,
      65,    39,    53,    55,    57,    26,    38,    31,    26,    38,
      39,    38,    40,    18,    19,    52,    40,    40,     3,    30,
      41,    54,    62,    66,    38,    17,    16,    31,    32,    33,
      34,    35,    36,    58,    55,    65,    62,    55,    64,    65,
      51,    39,    39,    13,     4,    38,    40,    39,    55,    13,
      30,    56,    57,    62,    31,    40,     3,     3,    41,    62,
      54,    62,    40,    40,    40
=======
       0,    47,     0,     6,     9,    10,    11,    17,    24,    27,
      30,    32,    48,    49,    50,    51,    52,     7,    12,    23,
       7,    12,    23,     4,    68,     8,    13,     4,    69,    25,
      28,    69,     4,    28,    64,    65,    69,    70,    41,    41,
      41,    41,    68,    69,    69,    68,    69,    69,    69,    69,
      31,    66,    69,    28,    42,    45,    43,    43,    43,    26,
      29,     4,    63,    70,    29,    42,    66,    65,    70,    15,
      16,    53,    54,    70,    70,    70,    43,    57,    59,    60,
      65,    29,    42,    35,    59,    69,    29,    43,    43,    42,
      44,    20,    21,    22,    55,    44,    44,     3,     5,    33,
      58,    67,    71,    42,    19,    18,    35,    36,    37,    38,
      39,    40,    62,    59,    70,    67,    59,    70,    69,    54,
      43,    43,    43,    14,    34,    56,    42,    44,    43,    60,
      14,    33,     3,    61,    65,    71,    35,    44,    45,     3,
       3,     3,    43,    14,    67,    58,    67,    70,    44,    44,
      44,    58,    44,    44,    44
>>>>>>> Stashed changes
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
<<<<<<< Updated upstream
       0,    43,    44,    44,    45,    45,    45,    45,    46,    47,
      47,    47,    47,    48,    48,    48,    48,    48,    48,    48,
      49,    49,    50,    50,    51,    51,    51,    52,    52,    53,
      53,    54,    54,    55,    55,    55,    55,    56,    56,    57,
      57,    58,    58,    58,    58,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    62,    63,    64,    65,    66
=======
       0,    46,    47,    47,    48,    48,    48,    48,    49,    50,
      50,    50,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    52,    52,    53,    53,    54,    54,    54,
      54,    54,    54,    55,    55,    55,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    60,    61,    61,    61,    62,
      62,    62,    62,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    67,    68,    69,    70,    71
>>>>>>> Stashed changes
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     3,
       3,     2,     2,     6,     3,     2,     5,     5,     6,     6,
<<<<<<< Updated upstream
       6,     6,     1,     3,     2,     3,     4,     4,     4,     3,
       5,     1,     3,     3,     3,     3,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     5,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     3
=======
       3,     5,     4,     6,     6,     1,     3,     2,     3,     3,
       4,     4,     6,     4,     4,     4,     4,     3,     5,     1,
       3,     1,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     1,     3,     3,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1
>>>>>>> Stashed changes
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
<<<<<<< Updated upstream
#line 58 "parser.y" /* yacc.c:1646  */
=======
#line 84 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		cout << "(((((" << comNum << endl;
	}
<<<<<<< Updated upstream
#line 1381 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 62 "parser.y" /* yacc.c:1646  */
=======
#line 1414 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 88 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		comNum++;cout << ")))))" << comNum << endl;
	}
<<<<<<< Updated upstream
#line 1389 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 72 "parser.y" /* yacc.c:1646  */
=======
#line 1423 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 99 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		cout << "--------------show databases--------------" << endl;
		commands.showDBs();
		cout << "--------------show databases end--------------" << endl;
	}
<<<<<<< Updated upstream
#line 1399 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 79 "parser.y" /* yacc.c:1646  */
=======
#line 1433 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 106 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		cout << "--------------create database--------------" << (yyvsp[0].id_t) << endl;
		commands.createDB((yyvsp[0].id_t));
		cout << "--------------create database end--------------" << endl;
	}
<<<<<<< Updated upstream
#line 1409 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 85 "parser.y" /* yacc.c:1646  */
=======
#line 1443 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 112 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		cout << "--------------drop database--------------" << (yyvsp[0].id_t) << endl;
		commands.dropDB((yyvsp[0].id_t));
		cout << "--------------drop database end--------------" << endl;
	}
<<<<<<< Updated upstream
#line 1419 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 91 "parser.y" /* yacc.c:1646  */
=======
#line 1453 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 118 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		cout << "--------------use database--------------" << (yyvsp[0].id_t) << endl;
		commands.useDB((yyvsp[0].id_t));
		cout << "--------------use database end--------------" << endl;
	}
<<<<<<< Updated upstream
#line 1429 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 97 "parser.y" /* yacc.c:1646  */
=======
#line 1463 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 124 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		cout << "--------------show tables--------------" << endl;
		//show table names
		commands.showTables();
		cout << "--------------show tables end--------------" << endl;
	}
<<<<<<< Updated upstream
#line 1440 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 106 "parser.y" /* yacc.c:1646  */
    {
		cout << "--------------create table--------------" << (yyvsp[-3].id_t) << endl;
		// if($5 != 0) delete $5;
		commands.createTable((yyvsp[-3].id_t), (yyvsp[-1].fieldList_t)->toString());
		cout << "--------------create table end--------------" << endl;
	}
#line 1451 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 113 "parser.y" /* yacc.c:1646  */
=======
#line 1474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 133 "parser.y" /* yacc.c:1646  */
    {
		cout << "--------------create table--------------" << (yyvsp[-3].id_t) << endl;
		commands.createTable((yyvsp[-3].id_t), (yyvsp[-1].fieldList_t));
		if(setPrimaryKey) commands.createPrimaryKeyIndex((yyvsp[-3].id_t));
		cout << "--------------create table end--------------" << endl;
	}
#line 1485 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 140 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		cout << "--------------drop table--------------" << (yyvsp[0].id_t) << endl;
		commands.dropTable((yyvsp[0].id_t));
		cout << "--------------drop table end--------------" << endl;
	}
<<<<<<< Updated upstream
#line 1461 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 119 "parser.y" /* yacc.c:1646  */
=======
#line 1495 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 147 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		cout << "--------------DESC table--------------" << (yyvsp[0].id_t) << endl;
		commands.desc(string((yyvsp[0].id_t)));
		cout << "--------------DESC table end--------------" << endl;
	}
<<<<<<< Updated upstream
#line 1470 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 124 "parser.y" /* yacc.c:1646  */
    {
		cout << "--------------INSERT--------------" << (yyvsp[-2].id_t) << endl;

		cout << "--------------INSERT end--------------" << endl;
	}
#line 1480 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 137 "parser.y" /* yacc.c:1646  */
=======
#line 1505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 153 "parser.y" /* yacc.c:1646  */
    {
    	cout << "--------------INSERT--------------" << endl;
		commands.insertData((yyvsp[-2].id_t), *(yyvsp[0].valueLists_t));
		cout << "--------------INSERT end--------------" << endl;
	}
#line 1515 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 159 "parser.y" /* yacc.c:1646  */
    {
    	cout << "--------------DELETE--------------" << endl;
    	commands.deleteWhere((yyvsp[-2].id_t), (yyvsp[0].whereClause_t));
		cout << "--------------DELETE end--------------" << endl;
    }
#line 1525 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 165 "parser.y" /* yacc.c:1646  */
    {
    	commands.update(string((yyvsp[-4].id_t)), (yyvsp[-2].setClause_t), (yyvsp[0].whereClause_t));
    }
#line 1533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 169 "parser.y" /* yacc.c:1646  */
    {
		cout << "--------------SELECT--------------" << endl;
		commands.selectSelectorWhere((yyvsp[-4].selector_t), (yyvsp[-2].tableList_t), (yyvsp[0].whereClause_t));
		cout << "--------------SELECT end--------------" << endl;
    }
#line 1543 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 175 "parser.y" /* yacc.c:1646  */
    {
    	commands.select((yyvsp[0].tableList_t));
    }
#line 1551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 179 "parser.y" /* yacc.c:1646  */
    {
    	commands.selectWhere((yyvsp[-2].tableList_t), (yyvsp[0].whereClause_t));
    }
#line 1559 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 183 "parser.y" /* yacc.c:1646  */
    {
    	commands.selectSelector((yyvsp[-2].selector_t), (yyvsp[0].tableList_t));
    }
#line 1567 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 189 "parser.y" /* yacc.c:1646  */
    {
		cout << "--------------create index--------------" << endl;
		commands.createIndex((yyvsp[-3].id_t), (yyvsp[-1].id_t));
		cout << "--------------create index end--------------" << endl;
	}
#line 1577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 195 "parser.y" /* yacc.c:1646  */
    {
    	cout << "--------------drop index--------------" << endl;
		commands.dropIndex((yyvsp[-3].id_t), (yyvsp[-1].id_t));
		cout << "--------------drop index end--------------" << endl;
    }
#line 1587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 202 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		(yyval.fieldList_t) = new TableCols();
		setPrimaryKey = 0;
		if((yyvsp[0].field_t)->setPrimary == false)
			(yyval.fieldList_t)->addCol(*(yyvsp[0].field_t));
		else{
			cout << "Set PrimaryKey Error: No such col" << endl;
			delete (yyvsp[0].field_t);
			exit(0);
		}
	}
<<<<<<< Updated upstream
#line 1495 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 149 "parser.y" /* yacc.c:1646  */
=======
#line 1603 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 215 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		(yyval.fieldList_t) = (yyvsp[-2].fieldList_t);
		if((yyvsp[0].field_t)->setPrimary == false)
			(yyval.fieldList_t)->addCol(*(yyvsp[0].field_t));
		else{
			setPrimaryKey++;
			if(setPrimaryKey > 1){
				cout << "Set PrimaryKey Error: One table only has one PrimaryKey" << endl;
				exit(0);
			}else if((yyval.fieldList_t)->setPrimary((yyvsp[0].field_t)->name) == false){
				cout << "Set PrimaryKey Error: No such col" << endl;
				delete (yyvsp[0].field_t);
				exit(0);
			}
			delete (yyvsp[0].field_t);
		}
	}
<<<<<<< Updated upstream
#line 1510 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 161 "parser.y" /* yacc.c:1646  */
=======
#line 1625 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 234 "parser.y" /* yacc.c:1646  */
>>>>>>> Stashed changes
    {
		(yyval.field_t) = new MyCol((yyvsp[0].type_t)->dataType, (yyvsp[0].type_t)->dataWide, false, true, (yyvsp[-1].id_t));
	}
<<<<<<< Updated upstream
#line 1519 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 167 "parser.y" /* yacc.c:1646  */
    {
		(yyval.field_t) = new MyCol((yyvsp[-1].type_t)->dataType, (yyvsp[-1].type_t)->dataWide, false, false, (yyvsp[-2].id_t));
	}
#line 1527 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 172 "parser.y" /* yacc.c:1646  */
    {
		(yyval.field_t) = new MyCol(0, 4, true, true, (yyvsp[-1].id_t), "", true);
	}
#line 1535 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 177 "parser.y" /* yacc.c:1646  */
    {
		(yyval.type_t) = new MyType(0, (yyvsp[-1].num_t));
	}
#line 1543 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 182 "parser.y" /* yacc.c:1646  */
    {
		(yyval.type_t) = new MyType(2, (yyvsp[-1].num_t));
	}
#line 1551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 218 "parser.y" /* yacc.c:1646  */
    {(yyval.id_t)=(yyvsp[0].id_t);}
#line 1557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 220 "parser.y" /* yacc.c:1646  */
    {(yyval.id_t)=(yyvsp[0].id_t);}
#line 1563 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.id_t)=(yyvsp[0].id_t);}
#line 1569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 224 "parser.y" /* yacc.c:1646  */
    {(yyval.id_t)=(yyvsp[-1].id_t);}
#line 1575 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 1579 "parser.tab.c" /* yacc.c:1646  */
=======
#line 1633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 238 "parser.y" /* yacc.c:1646  */
    {
		//type len is_primary can_be_null name
		(yyval.field_t) = new MyCol((yyvsp[-1].type_t)->dataType, (yyvsp[-1].type_t)->dataWide, false, true, (yyvsp[-2].id_t));
		if(commands.addCheck((yyval.field_t), (yyvsp[0].valueList_t), (yyvsp[-1].type_t)->dataType, (yyvsp[-1].type_t)->dataWide) == false)
			exit(0);
	}
#line 1644 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 245 "parser.y" /* yacc.c:1646  */
    {
		(yyval.field_t) = new MyCol((yyvsp[-1].type_t)->dataType, (yyvsp[-1].type_t)->dataWide, false, false, (yyvsp[-2].id_t));
	}
#line 1652 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 249 "parser.y" /* yacc.c:1646  */
    {
		(yyval.field_t) = new MyCol((yyvsp[-2].type_t)->dataType, (yyvsp[-2].type_t)->dataWide, false, false, (yyvsp[-3].id_t));
		if(commands.addCheck((yyval.field_t), (yyvsp[-1].valueList_t), (yyvsp[-2].type_t)->dataType, (yyvsp[-2].type_t)->dataWide) == false){
			cout << "DASD" << endl;
			exit(0);
		}
	}
#line 1664 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 257 "parser.y" /* yacc.c:1646  */
    {
		(yyval.field_t) = new MyCol(0, 4, true, true, (yyvsp[-1].id_t), "", true);
	}
#line 1672 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 261 "parser.y" /* yacc.c:1646  */
    {
		(yyval.field_t) = commands.createForeignKey(string((yyvsp[-3].id_t)), string((yyvsp[-1].id_t)));
	}
#line 1680 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 266 "parser.y" /* yacc.c:1646  */
    {
		(yyval.type_t) = new MyType(0, (yyvsp[-1].num_t));
	}
#line 1688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 270 "parser.y" /* yacc.c:1646  */
    {
		(yyval.type_t) = new MyType(1, (yyvsp[-1].num_t));
	}
#line 1696 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 274 "parser.y" /* yacc.c:1646  */
    {
		(yyval.type_t) = new MyType(2, (yyvsp[-1].num_t));
	}
#line 1704 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 279 "parser.y" /* yacc.c:1646  */
    {
		(yyval.valueList_t) = (yyvsp[-1].valueList_t);
	}
#line 1712 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 283 "parser.y" /* yacc.c:1646  */
    {
		(yyval.valueLists_t) = new vector<vector<AllValue*>*>;
		(yyval.valueLists_t)->clear();
		(yyval.valueLists_t)->push_back((yyvsp[-1].valueList_t));
	}
#line 1722 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 290 "parser.y" /* yacc.c:1646  */
    {
		(yyval.valueLists_t) = (yyvsp[-4].valueLists_t);
		(yyval.valueLists_t)->push_back((yyvsp[-1].valueList_t));
	}
#line 1731 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 296 "parser.y" /* yacc.c:1646  */
    {
		valueNum = 0;
		(yyval.valueList_t) = new vector<AllValue*>;
		(yyval.valueList_t)->clear();
		(yyval.valueList_t)->push_back((yyvsp[0].value_t));
		// $$ = new MyData(*(commands.tc));
		// commands.setMyData(valueNum, $1, $$);
		// cout << "SSSSSS" << valueNum << endl;
	}
#line 1745 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 307 "parser.y" /* yacc.c:1646  */
    {
		valueNum++;
		(yyval.valueList_t) = (yyvsp[-2].valueList_t);
		(yyval.valueList_t)->push_back((yyvsp[0].value_t));
		// commands.setMyData(valueNum, $3, $$);
		// cout << "SSSSSS" << valueNum << endl;
	}
#line 1757 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 316 "parser.y" /* yacc.c:1646  */
    {
		(yyval.whereClause_t) = new vector<WhereClause*>;
		(yyval.whereClause_t)->clear();
		(yyval.whereClause_t)->push_back((yyvsp[0].where_t));
	}
#line 1767 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 322 "parser.y" /* yacc.c:1646  */
    {
    	(yyval.whereClause_t) = (yyvsp[-2].whereClause_t);
    	(yyval.whereClause_t)->push_back((yyvsp[0].where_t));
    }
#line 1776 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 327 "parser.y" /* yacc.c:1646  */
    { (yyval.where_t) = new WhereClause((yyvsp[-2].col_t), (yyvsp[-1].num_t), (yyvsp[0].expr_t)); }
#line 1782 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 328 "parser.y" /* yacc.c:1646  */
    { (yyval.where_t) = new WhereClause((yyvsp[-2].col_t), 0); }
#line 1788 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 329 "parser.y" /* yacc.c:1646  */
    { (yyval.where_t) = new WhereClause((yyvsp[-2].col_t), 1); }
#line 1794 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 331 "parser.y" /* yacc.c:1646  */
    { (yyval.expr_t) = new Expr((yyvsp[0].num_t)); }
#line 1800 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 332 "parser.y" /* yacc.c:1646  */
    { (yyval.expr_t) = new Expr(string((yyvsp[0].id_t))); }
#line 1806 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 333 "parser.y" /* yacc.c:1646  */
    { (yyval.expr_t) = new Expr((yyvsp[0].col_t)); }
#line 1812 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 335 "parser.y" /* yacc.c:1646  */
    { (yyval.num_t) = 2; }
#line 1818 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 336 "parser.y" /* yacc.c:1646  */
    { (yyval.num_t) = 3; }
#line 1824 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 337 "parser.y" /* yacc.c:1646  */
    { (yyval.num_t) = 4; }
#line 1830 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 338 "parser.y" /* yacc.c:1646  */
    { (yyval.num_t) = 5; }
#line 1836 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 339 "parser.y" /* yacc.c:1646  */
    { (yyval.num_t) = 6; }
#line 1842 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 340 "parser.y" /* yacc.c:1646  */
    { (yyval.num_t) = 7; }
#line 1848 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 343 "parser.y" /* yacc.c:1646  */
    {
		(yyval.setClause_t) = new vector<SetClause*>;
		(yyval.setClause_t)->clear();
		SetClause *s = new SetClause(string((yyvsp[-2].id_t)), (yyvsp[0].value_t));
		(yyval.setClause_t)->push_back(s);		
	}
#line 1859 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 350 "parser.y" /* yacc.c:1646  */
    {
		(yyval.setClause_t) = (yyvsp[-4].setClause_t);
		SetClause *s = new SetClause(string((yyvsp[-2].id_t)), (yyvsp[0].value_t));
		(yyval.setClause_t)->push_back(s);
	}
#line 1869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 357 "parser.y" /* yacc.c:1646  */
    {
		(yyval.selector_t) = new std::vector<Selector*>;
		(yyval.selector_t)->clear();
		(yyval.selector_t)->push_back((yyvsp[0].col_t));
	}
#line 1879 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 364 "parser.y" /* yacc.c:1646  */
    {
		(yyval.selector_t) = (yyvsp[-2].selector_t);
		(yyval.selector_t)->push_back((yyvsp[0].col_t));
	}
#line 1888 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 369 "parser.y" /* yacc.c:1646  */
    { (yyval.col_t) = new Selector((yyvsp[-2].id_t), (yyvsp[0].id_t)); }
#line 1894 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 370 "parser.y" /* yacc.c:1646  */
    { (yyval.col_t) = new Selector((yyvsp[0].id_t)); }
#line 1900 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 373 "parser.y" /* yacc.c:1646  */
    {
		(yyval.tableList_t) = new std::vector<string>;
		(yyval.tableList_t)->clear();
		(yyval.tableList_t)->push_back(string((yyvsp[0].id_t)));
	}
#line 1910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 380 "parser.y" /* yacc.c:1646  */
    {
    	(yyval.tableList_t) = (yyvsp[-2].tableList_t);
    	(yyval.tableList_t)->push_back(string((yyvsp[0].id_t)));
    }
#line 1919 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 385 "parser.y" /* yacc.c:1646  */
    { (yyval.value_t) = new AllValue((yyvsp[0].num_t), false); }
#line 1925 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 386 "parser.y" /* yacc.c:1646  */
    { (yyval.value_t) = new AllValue((yyvsp[0].id_t), false); }
#line 1931 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 387 "parser.y" /* yacc.c:1646  */
    { (yyval.value_t) = new AllValue(1, true); }
#line 1937 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 389 "parser.y" /* yacc.c:1646  */
    { (yyval.id_t)=(yyvsp[0].id_t); }
#line 1943 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 391 "parser.y" /* yacc.c:1646  */
    { (yyval.id_t)=(yyvsp[0].id_t); }
#line 1949 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 393 "parser.y" /* yacc.c:1646  */
    { (yyval.id_t)=(yyvsp[0].id_t); }
#line 1955 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 396 "parser.y" /* yacc.c:1646  */
    { 
		int l = strlen((yyvsp[0].id_t));
		(yyval.id_t) = new char[l];  
		strncpy((yyval.id_t), (yyvsp[0].id_t)+1, l-2);
		(yyval.id_t)[l-2] = '\0';
	}
#line 1966 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 1970 "parser.tab.c" /* yacc.c:1646  */
>>>>>>> Stashed changes
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
<<<<<<< Updated upstream
#line 226 "parser.y" /* yacc.c:1906  */
=======
#line 403 "parser.y" /* yacc.c:1906  */
>>>>>>> Stashed changes

