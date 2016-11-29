%{
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include "../recmanage/MyTable.h"
#include "../StaticMethod.h"
#include "../recmanage/MyFileIO.h"
#include "../recmanage/MyValue.h"
#include "../fileio/FileManager.h"
//#include "tree.h"
using namespace std;
extern int line;
const int MAX_DBNUM = 1000;

bool hasGetBuffer = false;
char buffer[100];	//create database here, decided by where program is 
struct myDB
{
	string name;
	string path;
};
myDB myDBs[MAX_DBNUM];
int dbNum = 0;
int useDB = -1; //use which database

int findDB(string name){
	for(int i = 0; i < dbNum; ++i){
		if(myDBs[i].name == name){
			return i;
		}
	}
	return -1;
}

int yylex();

void yyerror(const char *str)
{
    printf("%s, Line:%d\n", str,line);
}

#define YYERROR_VERBOSE 1
%}

%union {
    char *id_t;
    char *string_t;
    int  num_t;
    char char_t;
}

%token<num_t> T_VALUE_INT 
%token<id_t> T_ID 
%token T_CREATE T_DATABASE T_DATABASES T_DROP T_USE T_SHOW T_TABLE T_TABLES T_NOT_NULL T_PRIMARY_KEY T_DESC 
%token T_INT T_VARCHAR
%token T_COLON T_COMMA T_LEFT_BRACKET T_RIGHT_BRACKET
%type<id_t> program stmt sysStmt dbStmt tbStmt fieldList field type dbName tbName colName

%%
program: 
	| program stmt
						 
;
stmt	: sysStmt T_COLON
	|dbStmt T_COLON
	|tbStmt T_COLON
				
;
sysStmt	: T_SHOW T_DATABASES
	{
		cout << "--------------show databases--------------" << endl;
		cout << "database number: " << dbNum << endl;
		for(int i = 0; i < dbNum; ++i){
			cout << myDBs[i].name << " ";
		}
		cout << endl;
		cout << "--------------show databases end--------------" << endl;
	}			
;
dbStmt	: T_CREATE T_DATABASE dbName
	{
		cout << "--------------create database--------------" << $3 << endl;
		if(!hasGetBuffer){
			getcwd(buffer, 100);
			cout << "get buffer" << endl;
			hasGetBuffer = true;
		}
		if( (access( $3, 0 )) != -1 ){
			cout << "database " << $3 << " was created before" << endl;
			if(findDB(string($3)) == -1){
				myDBs[dbNum].name = $3;
   				myDBs[dbNum].path = buffer;
   				myDBs[dbNum].path += '/'+ myDBs[dbNum].name;
   				dbNum ++;
			}
		} else {
			int isCreate = mkdir($3, S_IRWXU);
   			if( !isCreate ){
   				cout << "database " << $3 << " has been created" << endl;
   				myDBs[dbNum].name = $3;
   				myDBs[dbNum].path = buffer;
   				myDBs[dbNum].path += '/'+ myDBs[dbNum].name;
   				dbNum ++;
   			}
   			else
   				cout << "create path failed!" << endl;
			
		}
		cout << "buffer: " << buffer << endl;
		cout << "--------------create database end--------------" << endl;
	}
	|T_DROP T_DATABASE dbName
	{
		cout << "--------------drop database--------------" << $3 << endl;
		int fdDB = findDB(string($3));
		if(fdDB == -1){
			cout << "fail to find database: " << $3 << endl;
		} else{
			if(useDB == fdDB)
				useDB = -1;
			int isCreate = mkdir(myDBs[fdDB].path.c_str(), S_IRWXU);
   			if( !isCreate ){
   				cout << "error " << myDBs[fdDB].path << endl;
   			} else{
   				remove(myDBs[fdDB].path.c_str());
   				myDBs[fdDB] = myDBs[dbNum-1];
				dbNum--;
				cout << "has dropped database: " << $3 << endl;   				
   			}
		}
		cout << "--------------drop database end--------------" << endl;
	}
	|T_USE dbName
	{
		cout << "--------------use database--------------" << $2 << endl;
		int fdDB = findDB(string($2));
		if(fdDB == -1){
			cout << "fail to find database: " << $2 << endl;
		} else{
			useDB = fdDB;
			cout << "change to use database: " << myDBs[useDB].name << endl;
		}
		cout << "--------------use database end--------------" << endl;
	}
	|T_SHOW T_TABLES
	{
		cout << "--------------show tables--------------" << endl;
		if(useDB == -1){
			cout << "Please choose(use) a database" << endl;
		} else{
			if( (access(myDBs[useDB].path.c_str() , 0 )) != -1 ){
				string command = "ls ";
				command += myDBs[useDB].path;
				system(command.c_str());
    			cout << endl;
			} else {
   				cout << "database error" << endl;
			}
		}
		cout << "--------------show tables end--------------" << endl;
	}
				
;
tbStmt 	: T_CREATE T_TABLE tbName T_LEFT_BRACKET fieldList T_RIGHT_BRACKET
	{
		cout << "--------------create table--------------" << $3 << endl;
		if(useDB == -1){
			cout << "Please choose(use) a database" << endl;
		} else{
			string tableName = string($3);
			string tablePath = myDBs[useDB].path + '/' + tableName;
			if( (access(tablePath.c_str() , 0 )) != -1 ){
				cout << "table " << tableName << " was created before" << endl;
			} else {
				ofstream fout(tablePath);
   				if(!fout)
   					cout << "create path failed!" << endl;
   				else
   					cout << "table " << $3 << " has been created" << endl;
				fout.close();
			}
		}
		cout << "--------------create table end--------------" << endl;
	}
	|T_DROP T_TABLE tbName
	{
		cout << "--------------drop table--------------" << $3 << endl;
		if(useDB == -1){
			cout << "Please choose(use) a database" << endl;
		} else{
			string tableName = string($3);
			string tablePath = myDBs[useDB].path + '/' + tableName;
			if( (access(tablePath.c_str() , 0 )) != -1 ){
				remove(tablePath.c_str());
				cout << "table " << tableName << " at " << tablePath << " has been dropped" << endl;
			} else {	
 				cout << "table " << $3 << " doesn't exist" << endl;
			}
		}
		cout << "--------------drop table end--------------" << endl;
	}
	|T_DESC tbName	
	{
		cout << "desc table " << $2 << endl;
		cout << "--------------DESC table--------------" << $2 << endl;
		cout << "--------------DESC table end--------------" << endl;
	}	

;
fieldList:field
	|fieldList T_COMMA field
;
field   : colName type
	|colName type T_NOT_NULL
	|T_PRIMARY_KEY T_LEFT_BRACKET colName T_RIGHT_BRACKET
;
type 	: T_INT T_LEFT_BRACKET T_VALUE_INT T_RIGHT_BRACKET
	|T_VARCHAR T_LEFT_BRACKET T_VALUE_INT T_RIGHT_BRACKET
;
dbName	: T_ID{$$=$1;cout << "dbName " << $1 << endl;}
;
tbName	: T_ID{$$=$1;cout << "tbName " << $1 << endl;}
;
colName	: T_ID{$$=$1;cout << "colName " << $1 << endl;}
;
%%
