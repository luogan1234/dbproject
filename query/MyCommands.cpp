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

bool MyCommands::createTable(string tableName, TableCols *tableCols)
{
    if(tableCols != 0) {
        tableCols->setOrder();
        tc = tableCols;
    }
	bool ret = myFileIO->createTable(tableName, tableCols->toString());
	if(!ret) cout << "Fail to create table " << tableName << endl;
	return ret;
}

bool MyCommands::dropTable(string tableName)
{
	bool ret = myFileIO->dropTable(tableName);
    return ret;
}

bool MyCommands::insertData(string tableName, vector<MyData*> &data)
{
    MyTable *myTable = myFileIO->getTable(tableName);
    bool ret = myTable->insertData(data);
    return ret;
}

void MyCommands::setMyData(int valNum, AllValue *val, MyData *data)
{
    MyCol* myCol;
    MyValue value;
    int num,offset;
    myCol=tc->getByCol(valNum,num,offset);
    switch (val->kind){
        case 1:
            MyData::format(val->intVal, myCol, value);
            break;
        case 2:
            MyData::format(val->strVal, myCol, value);
            break;
        case 3:
            MyData::format("", myCol, value, true);
            break;
    }
    data->setValue(num, offset, myCol, value);
    value.print();
}

void MyCommands::select(std::vector<std::string> *tableList)
{
    MyTable *myTable;
    Constraints con;
    vector<MyData*> res, allRes;
    allRes.clear();
    int len = tableList->size();
    for (int i = 0; i < len; ++i)
    {
        myTable = myFileIO->getTable((*tableList)[i]);
        res.clear();
        myTable->searchData(&con, res);
        allRes.insert(allRes.end(), res.begin(), res.end());
        delete myTable;
    }

    cout << "Search results " << allRes.size() << endl;
    std::vector<MyCol> &col = myTable->cols.cols;
    int len2 = col.size();
    //表的各col的字段
    for (int i = 0; i < len2; ++i)
    {
        cout << col[i].name << " ";
    }
    cout << endl;

    len = allRes.size();
    MyCol* myCol;
    MyValue value;
    int num,offset;
    for (int i = 0; i < len; ++i)
    {
        (*allRes[i]).print();
        for (int j = 0; j < len2; ++j)
        {
            myCol=tc->getByCol(j,num,offset);
            (*allRes[i]).getValue(num,offset,myCol,value);
            value.print();
            /* code */
        }
    }
}
