#include "MyCommands.h"

using namespace std;

void MyCommands::showDBs()
{
	vector<string> dbname;
    myFileIO->showDB(dbname);
    int len = dbname.size();
    if(len == 0) 
    	cout << "No database" << endl;
    else{
    	for(int i = 0; i < len; ++i)
    		cout << dbname[i] << " ";
    	cout << endl;
    }
}

bool MyCommands::createDB(string dbname)
{
    bool ret = myFileIO->createDB(dbname);
    if(!ret) cout << "Fail to create database " << dbname << endl;
    return ret;
}

bool MyCommands::dropDB(string dbname)
{
    bool ret = myFileIO->dropDB(dbname);
    return ret;
}

bool MyCommands::useDB(string dbname)
{
    bool ret = myFileIO->useDB(dbname);
    if(!ret) cout << "Fail to use database " << dbname << " No such database" << endl;
    return ret;
}

void MyCommands::showTables()
{
	vector<string> tableName;
    myFileIO->getTables(tableName);
    int len = tableName.size();
    if(len == 0) 
    	cout << "No table" << endl;
    else{
    	for(int i = 0; i < len; ++i)
    		cout << tableName[i] << " ";
    	cout << endl;
    }
}

bool MyCommands::createTable(string tableName, string tableFormat)
{
	bool ret = myFileIO->createTable(tableName, tableFormat);
	if(!ret) cout << "Fail to create table " << tableName << endl;
	return ret;
}

bool MyCommands::dropTable(string tableName)
{
	bool ret = myFileIO->dropTable(tableName);
    return ret;
}