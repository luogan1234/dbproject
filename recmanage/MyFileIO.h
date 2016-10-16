//
// Created by luogan on 16-10-16.
//

#ifndef DBPROJECT_MYFILEIO_H
#define DBPROJECT_MYFILEIO_H

#include <string>
#include <vector>
#include "../bufmanager/BufPageManager.h"
#include "MyTable.h"

class MyFileIO {
private:
    std::string nowPath;
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

    bool getTable(std::string tableName,MyTable *table);
};


#endif //DBPROJECT_MYFILEIO_H
