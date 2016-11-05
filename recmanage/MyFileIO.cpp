//
// Created by luogan on 16-10-16.
//

#include <fstream>
#include "MyFileIO.h"

using namespace std;

void MyFileIO::loadDBInfo()
{
    ifstream fin("./data/dbnames");
    string name;
    dbNames.clear();
    while (fin>>name)
    {
        dbNames.push_back(name);
    }
    fin.close();
}

void MyFileIO::saveDBInfo()
{
    ofstream fout("./data/dbnames");
    for (size_t i=0;i<dbNames.size();++i)
        fout<<dbNames[i]<<endl;
    fout.close();
}

void MyFileIO::loadTableInfo()
{
    if (opendir(nowDBPath.c_str())==NULL)
        return;
    ifstream fin(nowDBPath+"/tables");
    string name,format;
    tableNames.clear();
    tableFormats.clear();
    while (fin>>name>>format)
    {
        tableNames.push_back(name);
        tableFormats.push_back(format);
    }
    fin.close();
}

void MyFileIO::saveTableInfo()
{
    if (opendir(nowDBPath.c_str())==NULL)
        return;
    ofstream fout(nowDBPath+"/tables");
    for (size_t i=0;i<tableNames.size();++i)
        fout<<tableNames[i]<<' '<<tableFormats[i]<<endl;
    fout.close();
}

bool MyFileIO::createDB(string dbname)
{
    for (size_t i=0;i<dbNames.size();++i)
        if (dbname==dbNames[i])
            return false;
    string ins="mkdir ./data/"+dbname;
    system(ins.c_str());
    dbNames.push_back(dbname);
    saveDBInfo();
    return true;
}

bool MyFileIO::dropDB(string dbName)
{
    if (dbName==nowDBName)
    {
        nowDBName="";
        nowDBPath="./data/";
    }
    for (size_t i=0;i<dbNames.size();++i)
        if (dbName==dbNames[i])
        {
            dbNames.erase(dbNames.begin()+i);
            saveDBInfo();
            string p="./data/"+dbName;
            if (opendir(p.c_str())==NULL)
                return false;
            string ins="rm -rf "+p;
            system(ins.c_str());
            return true;
        }
    return false;
}

bool MyFileIO::useDB(string dbName)
{
    for (size_t i=0;i<dbNames.size();++i)
        if (dbName==dbNames[i])
        {
            nowDBName=dbName;
            nowDBPath="./data/"+dbName;
            loadTableInfo();
            return true;
        }
    return false;
}

bool MyFileIO::showDB(vector<string> &databases)
{
    databases.clear();
    for (size_t i=0;i<dbNames.size();++i)
        databases.push_back(dbNames[i]);
    return true;
}

bool MyFileIO::createTable(string tableName,string tableFormat)
{
    for (size_t i=0;i<tableNames.size();++i)
        if (tableNames[i]==tableName)
            return false;
    tableNames.push_back(tableName);
    tableFormats.push_back(tableFormat);
    string tar=nowDBPath+"/"+tableName+".data";
    fm->createFile(tar.c_str());
    int fileIDInit;
    fm->openFile(tar,fileIDInit);
    MyTable mt=MyTable(bm,this,fileIDInit,tableName,tableFormat);
    mt.init();
    saveTableInfo();
    return true;
}

bool MyFileIO::dropTable(string tableName)
{
    if (nowDBName=="")
        return false;
    for (size_t i=0;i<tableNames.size();++i)
        if (tableNames[i]==tableName)
        {
            tableNames.erase(tableNames.begin()+i);
            tableFormats.erase(tableFormats.begin()+i);
            saveTableInfo();
            string tar=nowDBPath+"/"+tableName+".data";
            string ins="rm "+tar;
            system(ins.c_str());
            fm->closeFile(tar);
            return true;
        }
    return false;
}

bool MyFileIO::getTables(vector<string> &tables)
{
    tables.clear();
    for (size_t i=0;i<tableNames.size();++i)
        tables.push_back(tableNames[i]);
    return true;
}

MyTable* MyFileIO::getTable(string tableName)
{
    if (nowDBName=="")
        return 0;
    for (size_t i=0;i<tableNames.size();++i)
        if (tableNames[i]==tableName)
        {
            string tar=nowDBPath+"/"+tableName+".data";
            fm->openFile(tar,fileID);
            return new MyTable(bm,this,fileID,tableName,tableFormats[i]);
        }
    return 0;
}

void MyFileIO::closeAll()
{
    bm->close();
    fm->closeAll();
}

bool MyFileIO::createIndex(string name,short colID,char type,int valueType,int valueLen)
{
    if (nowDBPath=="")
        return false;
    char id[4];
    sprintf(id,"%d",int(colID));
    string ID=id;
    string tar=nowDBPath+"/"+name+"_"+ID+".index";
    fm->createFile(tar.c_str());
    int fileIDInit;
    fm->openFile(tar,fileIDInit);
    MyIndex mi=MyIndex(bm,name,colID,type,valueType,valueLen,fileIDInit);
    return true;
}

bool MyFileIO::dropIndex(string name,short colID)
{
    if (nowDBPath=="")
        return false;
    char id[4];
    sprintf(id,"%d",int(colID));
    string ID=id;
    string tar=nowDBPath+"/"+name+"_"+ID+".index";
    fm->closeFile(tar);
    string ins="rm -rf "+tar;
    system(ins.c_str());
    return true;
}

MyIndex* MyFileIO::getIndex(string name,short colID,MyTable* myTable)
{
    if (nowDBPath=="")
        return 0;
    char id[4];
    sprintf(id,"%d",int(colID));
    string ID=id;
    string tar=nowDBPath+"/"+name+"_"+ID+".index";
    fm->openFile(tar,fileID);
    MyIndex *mi=new MyIndex(bm,name,colID,fileID,myTable);
    return mi;
}