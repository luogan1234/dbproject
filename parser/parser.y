%{
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

using namespace std;
extern int line;

MyCommands commands;
int comNum = 0;
int yylex();

void yyerror(const char *str)
{
    printf("%s, Line:%d\n", str,line);
}

#define YYERROR_VERBOSE 1
%}
%code requires {
#include "../recmanage/TableCols.h"
#include "../recmanage/MyCol.h"
#include "../recmanage/MyData.h"
#include "../query/MyCommands.h"
}
%union {
    char *id_t;
    TableCols *fieldList_t;
    MyCol *field_t;
    MyType *type_t;
    char *string_t;
    int  num_t;
    char char_t;
}

%token<num_t> T_VALUE_INT 
%token<id_t> T_ID 
%token T_CREATE T_DATABASE T_DATABASES T_DROP T_USE T_SHOW T_TABLE T_TABLES T_NOT_NULL T_PRIMARY_KEY T_DESC T_IS T_AND
%token T_INT T_VARCHAR T_INDEX T_INSERT T_INTO T_VALUES T_DELETE T_FROM T_WHERE T_UPDATE T_SET T_SELECT T_NULL
%token T_EQUAL T_NOT_EQUAL T_NO_MORE_THAN T_NO_LESS_THAN T_MORE_THAN T_LESS_THAN
%token T_COLON T_COMMA T_LEFT_BRACKET T_RIGHT_BRACKET T_QUOTATION T_DOT
%type<id_t> program stmt sysStmt dbStmt tbStmt idxStmt dbName tbName colName T_VALUE_STRING
%type<fieldList_t> fieldList
%type<field_t> field
%type<type_t> type

%%
program: 
	{
		cout << "(((((" << comNum << endl;
	}
	|program stmt 
	{
		comNum++;cout << ")))))" << comNum << endl;
	}
;
stmt	: sysStmt T_COLON
	|dbStmt T_COLON
	|tbStmt T_COLON
	|idxStmt T_COLON
;
sysStmt	: T_SHOW T_DATABASES
	{
		cout << "--------------show databases--------------" << endl;
		commands.showDBs();
		cout << "--------------show databases end--------------" << endl;
	}			
;
dbStmt	: T_CREATE T_DATABASE dbName
	{
		cout << "--------------create database--------------" << $3 << endl;
		commands.createDB($3);
		cout << "--------------create database end--------------" << endl;
	}
	|T_DROP T_DATABASE dbName
	{
		cout << "--------------drop database--------------" << $3 << endl;
		commands.dropDB($3);
		cout << "--------------drop database end--------------" << endl;
	}
	|T_USE dbName
	{
		cout << "--------------use database--------------" << $2 << endl;
		commands.useDB($2);
		cout << "--------------use database end--------------" << endl;
	}
	|T_SHOW T_TABLES
	{
		cout << "--------------show tables--------------" << endl;
		//show table names
		commands.showTables();
		cout << "--------------show tables end--------------" << endl;
	}
				
;
tbStmt 	: T_CREATE T_TABLE tbName T_LEFT_BRACKET fieldList T_RIGHT_BRACKET
	{
		cout << "--------------create table--------------" << $3 << endl;
		// if($5 != 0) delete $5;
		commands.createTable($3, $5->toString());
		cout << "--------------create table end--------------" << endl;
	}
	|T_DROP T_TABLE tbName
	{
		cout << "--------------drop table--------------" << $3 << endl;
		commands.dropTable($3);
		cout << "--------------drop table end--------------" << endl;
	}
	|T_DESC tbName	
	{
		cout << "--------------DESC table--------------" << $2 << endl;
		cout << "--------------DESC table end--------------" << endl;
	}
	|T_INSERT T_INTO tbName T_VALUES valueLists
	{
		cout << "--------------INSERT--------------" << $3 << endl;

		cout << "--------------INSERT end--------------" << endl;
	}
    |T_DELETE T_FROM tbName T_WHERE whereClause
    |T_UPDATE tbName T_SET setClause T_WHERE whereClause
    |T_SELECT selector T_FROM tableList T_WHERE whereClause
;
idxStmt  : T_CREATE T_INDEX tbName T_LEFT_BRACKET colName T_RIGHT_BRACKET
    |T_DROP T_INDEX tbName T_LEFT_BRACKET colName T_RIGHT_BRACKET
;
fieldList:field
	{
		$$ = new TableCols();
		// cout << "<<<<<" << endl;
		if($1->setPrimary == false)
			$$->addCol(*$1);
		else{
			$$->setPrimary($1->name);
			delete $1;
		}
	}

	|fieldList T_COMMA field
	{
		// cout << ">>>>>" << endl;
		$$ = $1;
		if($3->setPrimary == false)
			$$->addCol(*$3);
		else{
			$$->setPrimary($3->name);
			delete $3;
		}
	}
;
field   : colName type
	{
		//type len is_primary can_be_null name
		$$ = new MyCol($2->dataType, $2->dataWide, false, true, $1);
	}

	|colName type T_NOT_NULL
	{
		$$ = new MyCol($2->dataType, $2->dataWide, false, false, $1);
	}

	|T_PRIMARY_KEY T_LEFT_BRACKET colName T_RIGHT_BRACKET
	{
		$$ = new MyCol(0, 4, true, true, $3, "", true);
	}
;
type 	: T_INT T_LEFT_BRACKET T_VALUE_INT T_RIGHT_BRACKET
	{
		$$ = new MyType(0, $3);
	}

	|T_VARCHAR T_LEFT_BRACKET T_VALUE_INT T_RIGHT_BRACKET
	{
		$$ = new MyType(2, $3);
	}
;
valueLists  : T_LEFT_BRACKET valueList T_RIGHT_BRACKET
	|valueLists T_COMMA T_LEFT_BRACKET valueList T_RIGHT_BRACKET
;
valueList   : value
	|valueList T_COMMA value
;
whereClause : col op expr
    |col T_IS T_NULL
    |col T_IS T_NOT_NULL
    |whereClause T_AND whereClause
;
expr  : value
    |col
;
col  : tbName T_DOT colName
	|colName
;
op  : T_EQUAL | T_NOT_EQUAL | T_NO_MORE_THAN | T_NO_LESS_THAN | T_LESS_THAN | T_MORE_THAN
;
setClause  : colName T_EQUAL value
	|setClause T_COMMA colName T_EQUAL value
;
selector  :  col
	|selector T_COMMA col
;
tableList  : tbName
    |tableList T_COMMA tbName
;
value       : T_VALUE_INT
    |T_VALUE_STRING
    |T_NULL
;
dbName	: T_ID{$$=$1;}
;
tbName	: T_ID{$$=$1;}
;
colName	: T_ID{$$=$1;}
;
T_VALUE_STRING : T_QUOTATION T_ID T_QUOTATION{$$=$2;}
;
%%
