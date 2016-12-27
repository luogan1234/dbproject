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
#include "../query/MyStruct.h"

using namespace std;
extern int line;

MyCommands commands;
int setPrimaryKey = 0;
int valueNum = 0;
int comNum = 0;
int yylex();

void yyerror(const char *str)
{
    printf("%s, Line:%d\n", str,line);
}

#define YYERROR_VERBOSE 1
%}
%code requires {
#include <vector>
#include "../recmanage/TableCols.h"
#include "../recmanage/MyCol.h"
#include "../recmanage/MyData.h"
#include "../query/MyCommands.h"
#include "../query/MyStruct.h"
}
%union {
    char *id_t;
    TableCols *fieldList_t;
    MyCol *field_t;
    MyType *type_t;
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
    char *string_t;
    int  num_t;
    char char_t;
}

%token<num_t> T_VALUE_INT
%token<id_t> T_ID T_STRING
%token T_CREATE T_DATABASE T_DATABASES T_DROP T_USE T_SHOW T_TABLE T_TABLES T_NOT_NULL T_PRIMARY_KEY T_FOREIGN_KEY T_DESC T_IS T_AND
%token T_INT T_CHAR T_VARCHAR T_INDEX T_INSERT T_INTO T_VALUES T_DELETE T_FROM T_WHERE T_UPDATE T_SET T_SELECT T_NULL T_CHECK
%token T_EQUAL T_NOT_EQUAL T_NO_MORE_THAN T_NO_LESS_THAN T_MORE_THAN T_LESS_THAN
%token T_COLON T_COMMA T_LEFT_BRACKET T_RIGHT_BRACKET T_DOT
%type<id_t> program stmt sysStmt dbStmt tbStmt idxStmt dbName tbName colName T_VALUE_STRING
%type<fieldList_t> fieldList
%type<field_t> field
%type<type_t> type
%type<valueLists_t> valueLists
%type<valueList_t> valueList check
%type<value_t> value
%type<tableList_t> tableList
%type<selector_t> selector
%type<col_t> col
%type<whereClause_t> whereClause
%type<setClause_t> setClause
%type<where_t> where
%type<expr_t> expr
%type<num_t> op

%%
program: 
	{
		// cout << "(((((" << comNum << endl;
	}
	|program stmt 
	{
		comNum++;
		// cout << ")))))" << comNum << endl;
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
		commands.createTable($3, $5);
		if(setPrimaryKey) commands.createPrimaryKeyIndex($3);
		cout << "--------------create table end--------------" << endl;
	}
	|T_DROP T_TABLE tbName
	{
		cout << "--------------drop table--------------" << $3 << endl;
		commands.dropTable($3);
		cout << "--------------drop table end--------------" << endl;
	}
	|T_DESC tbName	
	//意思是获取表结构
	{
		cout << "--------------DESC table--------------" << $2 << endl;
		commands.desc(string($2));
		cout << "--------------DESC table end--------------" << endl;
	}
	|T_INSERT T_INTO tbName T_VALUES valueLists
	{
    	cout << "--------------INSERT--------------" << endl;
		commands.insertData($3, *$5);
		cout << "--------------INSERT end--------------" << endl;
	}
    |T_DELETE T_FROM tbName T_WHERE whereClause
    {
    	cout << "--------------DELETE--------------" << endl;
    	commands.deleteWhere($3, $5);
		cout << "--------------DELETE end--------------" << endl;
    }
    |T_UPDATE tbName T_SET setClause T_WHERE whereClause
    {
    	commands.update(string($2), $4, $6);
    }
    |T_SELECT selector T_FROM tableList T_WHERE whereClause
    {
		cout << "--------------SELECT--------------" << endl;
		commands.selectSelectorWhere($2, $4, $6);
		cout << "--------------SELECT end--------------" << endl;
    }
    |T_SELECT T_FROM tableList
    {
    	commands.select($3);
    }
    |T_SELECT T_FROM tableList T_WHERE whereClause
    {
    	commands.selectWhere($3, $5);
    }
    |T_SELECT selector T_FROM tableList
    {
    	commands.selectSelector($2, $4);
    }
    
;
idxStmt  : T_CREATE T_INDEX tbName T_LEFT_BRACKET colName T_RIGHT_BRACKET
	{
		cout << "--------------create index--------------" << endl;
		commands.createIndex($3, $5);
		cout << "--------------create index end--------------" << endl;
	}
    |T_DROP T_INDEX tbName T_LEFT_BRACKET colName T_RIGHT_BRACKET
    {
    	cout << "--------------drop index--------------" << endl;
		commands.dropIndex($3, $5);
		cout << "--------------drop index end--------------" << endl;
    }
;
fieldList:field
	{
		$$ = new TableCols();
		setPrimaryKey = 0;
		if($1->setPrimary == false)
			$$->addCol(*$1);
		else{
			cout << "Set PrimaryKey Error: No such col" << endl;
			delete $1;
			exit(0);
		}
	}

	|fieldList T_COMMA field
	{
		$$ = $1;
		if($3->setPrimary == false)
			$$->addCol(*$3);
		else{
			setPrimaryKey++;
			if(setPrimaryKey > 1){
				cout << "Set PrimaryKey Error: One table only has one PrimaryKey" << endl;
				exit(0);
			}else if($$->setPrimary($3->name) == false){
				cout << "Set PrimaryKey Error: No such col" << endl;
				delete $3;
				exit(0);
			}
			delete $3;
		}
	}
;
field   : colName type
	{
		$$ = new MyCol($2->dataType, $2->dataWide, false, true, $1);
	}
	|colName type check
	{
		//type len is_primary can_be_null name
		$$ = new MyCol($2->dataType, $2->dataWide, false, true, $1);
		if(commands.addCheck($$, $3, $2->dataType, $2->dataWide) == false)
			exit(0);
	}
	|colName type T_NOT_NULL
	{
		$$ = new MyCol($2->dataType, $2->dataWide, false, false, $1);
	}
	|colName type check T_NOT_NULL
	{
		$$ = new MyCol($2->dataType, $2->dataWide, false, false, $1);
		if(commands.addCheck($$, $3, $2->dataType, $2->dataWide) == false){
			cout << "DASD" << endl;
			exit(0);
		}
	}
	|T_PRIMARY_KEY T_LEFT_BRACKET colName T_RIGHT_BRACKET
	{
		$$ = new MyCol(0, 4, true, true, $3, "", true);
	}
	|T_FOREIGN_KEY T_LEFT_BRACKET tbName T_DOT colName T_RIGHT_BRACKET
	{
		$$ = commands.createForeignKey(string($3), string($5));
	}
;
type 	: T_INT T_LEFT_BRACKET T_VALUE_INT T_RIGHT_BRACKET
	{
		$$ = new MyType(0, $3);
	}
	|T_CHAR T_LEFT_BRACKET T_VALUE_INT T_RIGHT_BRACKET
	{
		$$ = new MyType(1, $3);
	}
	|T_VARCHAR T_LEFT_BRACKET T_VALUE_INT T_RIGHT_BRACKET
	{
		$$ = new MyType(2, $3);
	}
;
check  	 : T_CHECK T_LEFT_BRACKET valueList T_RIGHT_BRACKET
	{
		$$ = $3;
	}
valueLists  : T_LEFT_BRACKET valueList T_RIGHT_BRACKET
	{
		$$ = new vector<vector<AllValue*>*>;
		$$->clear();
		$$->push_back($2);
	}

	|valueLists T_COMMA T_LEFT_BRACKET valueList T_RIGHT_BRACKET
	{
		$$ = $1;
		$$->push_back($4);
	}
;
valueList   : value
	{
		valueNum = 0;
		$$ = new vector<AllValue*>;
		$$->clear();
		$$->push_back($1);
		// $$ = new MyData(*(commands.tc));
		// commands.setMyData(valueNum, $1, $$);
		// cout << "SSSSSS" << valueNum << endl;
	}

	|valueList T_COMMA value
	{
		valueNum++;
		$$ = $1;
		$$->push_back($3);
		// commands.setMyData(valueNum, $3, $$);
		// cout << "SSSSSS" << valueNum << endl;
	}
;
whereClause : where
	{
		$$ = new vector<WhereClause*>;
		$$->clear();
		$$->push_back($1);
	}
    |whereClause T_AND where
    {
    	$$ = $1;
    	$$->push_back($3);
    }
;
where 	    :col op expr { $$ = new WhereClause($1, $2, $3); }
    |col T_IS T_NULL { $$ = new WhereClause($1, 0); }
    |col T_IS T_NOT_NULL { $$ = new WhereClause($1, 1); }
;
expr  : T_VALUE_INT { $$ = new Expr($1); }
	|T_VALUE_STRING { $$ = new Expr(string($1)); }
    |col { $$ = new Expr($1); }
;
op  : T_EQUAL { $$ = 2; } 
	| T_NOT_EQUAL { $$ = 3; } 
	| T_NO_MORE_THAN { $$ = 4; } 
	| T_NO_LESS_THAN { $$ = 5; } 
	| T_LESS_THAN { $$ = 6; } 
	| T_MORE_THAN { $$ = 7; }
;
setClause  : colName T_EQUAL value
	{
		$$ = new vector<SetClause*>;
		$$->clear();
		SetClause *s = new SetClause(string($1), $3);
		$$->push_back(s);		
	}
	|setClause T_COMMA colName T_EQUAL value
	{
		$$ = $1;
		SetClause *s = new SetClause(string($3), $5);
		$$->push_back(s);
	}
;
selector  :  col
	{
		$$ = new std::vector<Selector*>;
		$$->clear();
		$$->push_back($1);
	}

	|selector T_COMMA col
	{
		$$ = $1;
		$$->push_back($3);
	}
;
col  : tbName T_DOT colName { $$ = new Selector($1, $3); }
	|colName { $$ = new Selector($1); }
;
tableList  : tbName
	{
		$$ = new std::vector<string>;
		$$->clear();
		$$->push_back(string($1));
	}

    |tableList T_COMMA tbName
    {
    	$$ = $1;
    	$$->push_back(string($3));
    }
;
value       : T_VALUE_INT { $$ = new AllValue($1, false); }
    |T_VALUE_STRING { $$ = new AllValue($1, false); }
    |T_NULL { $$ = new AllValue(1, true); }
;
dbName	: T_ID{ $$=$1; }
;
tbName	: T_ID{ $$=$1; }
;
colName	: T_ID{ $$=$1; }
;
T_VALUE_STRING : T_STRING
	{ 
		int l = strlen($1);
		$$ = new char[l];  
		strncpy($$, $1+1, l-2);
		$$[l-2] = '\0';
	}
;
%%
