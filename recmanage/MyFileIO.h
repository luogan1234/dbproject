//
// Created by luogan on 16-10-16.
//

#ifndef DBPROJECT_MYFILEIO_H
#define DBPROJECT_MYFILEIO_H

#include <string>
#include <vector>
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

    bool createDB(std::string dbName);

    bool dropDB(std::string dbName);

    bool useDB(std::string dbName);

    bool showDB(std::vector<std::string> &databases);

    bool createTable(std::string tableName,std::string tableFormat);

    bool dropTable(std::string tableName);

    bool getTables(std::vector<std::string> &tables);

    MyTable* getTable(std::string tableName);

    void closeAll();

    bool createIndex(std::string name,short colID,char type,int valueType,int valueLen);

    bool dropIndex(std::string name,short colID);

    MyIndex* getIndex(std::string name,short colID);
};


#endif //DBPROJECT_MYFILEIO_H
