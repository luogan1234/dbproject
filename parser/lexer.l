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
"TABLE" 				{ return T_TABLE; }
"TABLES" 				{ return T_TABLES; }
"NOT NULL" 				{ return T_NOT_NULL; }
"PRIMARY KEY" 			{ return T_PRIMARY_KEY; }
"DESC" 					{ return T_DESC; }
"int"					{ return T_INT; }
"char"				{ return T_VARCHAR; }
";"						{ return T_COLON; }
","						{ return T_COMMA; }
"("						{ return T_LEFT_BRACKET; }
")"						{ return T_RIGHT_BRACKET; }

{NUMBER}			{ yylval.num_t = atoi(yytext); return T_VALUE_INT; }
{ID} 				{ yylval.id_t = strdup(yytext); return T_ID; }
['\n']+				{ printf("new line\n"); }

%%
