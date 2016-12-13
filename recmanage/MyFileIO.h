//
// Created by luogan on 16-10-16.
//

#ifndef DBPROJECT_MYFILEIO_H
#define DBPROJECT_MYFILEIO_H

#include <string>
#include <vector>
#include <stdlib.h>
#include "../bufmanager/BufPageManager.h"
#include "MyTable.h"
#include "MyIndex.h"

class MyFileIO {
private:
    BufPageManager *bm;
    FileManager *fm;
    std::vector<std::string> dbNames;
    std::vector<std::string> tableNames,tableFormats;
    std::string nowDBPath,nowDBName;
    int fileID;
    void loadDBInfo();
    void saveDBInfo();
    void loadTableInfo();
    void saveTableInfo();
public:
    MyFileIO()
    {
        fm=new FileManager();
        bm=new BufPageManager(fm);
        if (opendir("./data")==NULL)
            system("mkdir ./data");
        loadDBInfo();
        fileID=-2147483647;
    }

    ~MyFileIO()
    {
        saveDBInfo();
        delete bm;
    }
    //创建数据库
    bool createDB(std::string dbName);
    //丢弃数据库
    bool dropDB(std::string dbName);
    //使用数据库
    bool useDB(std::string dbName);
    //显示数据库信息
    bool showDB(std::vector<std::string> &databases);
    //创建数据表
    bool createTable(std::string tableName,std::string tableFormat);
    //丢弃数据表
    bool dropTable(std::string tableName);
    //获取数据表信息
    bool getTables(std::vector<std::string> &tables);
    //根据表名获取表
    MyTable* getTable(std::string tableName);
    //关闭文件和缓存页写回，必须在最后调用
    void closeAll();
    //创建要求的索引
    bool createIndex(std::string name,short colID,char type,bool canNull,bool canDel,int valueType,int valueLen);
    //丢弃索引
    bool dropIndex(std::string name,short colID);
    //根据表名和索引列获取索引
    MyIndex* getIndex(std::string name,short colID,MyTable* myTable);
};


#endif //DBPROJECT_MYFILEIO_H
