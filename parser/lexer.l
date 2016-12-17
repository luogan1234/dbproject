%option noyywrap

%{
#include <cstdlib>
#include <cstring>
#include "tokens.h"
#include <string>

int line=1;
%}

ID                  [A-Za-z][A-Za-z0-9]*
NUMBER              [0-9][0-9]*

%%

"CREATE" 				{ return T_CREATE; }
"DATABASE" 				{ return T_DATABASE; }
"DATABASES" 			{ return T_DATABASES; }
"DROP" 					{ return T_DROP; }
"USE" 					{ return T_USE; }
"SHOW" 					{ return T_SHOW; }
"TABLES" 				{ return T_TABLES; }
"TABLE" 				{ return T_TABLE; }
"NOT NULL" 				{ return T_NOT_NULL; }
"NULL"					{ return T_NULL; }
"PRIMARY KEY" 			{ return T_PRIMARY_KEY; }
"DESC" 					{ return T_DESC; }
"INDEX" 				{ return T_INDEX; }
"INSERT"				{ return T_INSERT; }
"INTO"					{ return T_INTO; }
"VALUES"				{ return T_VALUES; }
"DELETE"				{ return T_DELETE; }
"FROM"					{ return T_FROM; }
"WHERE"   				{ return T_WHERE; }
"UPDATE"				{ return T_UPDATE; }
"SET"					{ return T_SET; }
"SELECT"				{ return T_SELECT; }
"IS"					{ return T_IS; }
"AND"					{ return T_AND; }
"int"					{ return T_INT; }
"char"					{ return T_VARCHAR; }
"="						{ return T_EQUAL; }
"<>"					{ return T_NOT_EQUAL; }
"<="					{ return T_NO_MORE_THAN; }
">="					{ return T_NO_LESS_THAN; }
"<"						{ return T_LESS_THAN; }
">"						{ return T_MORE_THAN; }
";"						{ return T_COLON; }
"'"						{ return T_QUOTATION; }
"."						{ return T_DOT; }
","						{ return T_COMMA; }
"("						{ return T_LEFT_BRACKET; }
")"						{ return T_RIGHT_BRACKET; }

{NUMBER}			{ yylval.num_t = atoi(yytext); return T_VALUE_INT; }
{ID} 				{ yylval.id_t = strdup(yytext); return T_ID; }
['\n']+				{ }

%%
