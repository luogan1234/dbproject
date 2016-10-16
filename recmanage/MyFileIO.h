//
// Created by luogan on 16-10-16.
//

#ifndef DBPROJECT_MYFILEIO_H
#define DBPROJECT_MYFILEIO_H

#include <string>
#include <vector>
#include "../bufmanager/BufPageManager.h"

class MyFileIO {
private:
    std::string nowPath;
    BufPageManager *bm;
    FileManager *fm;
    std::vector<std::string> dbNames;
    std::vector<std::string> tableNames;
    void loadDBInfo();
    void saveDBInfo();
    void loadTableInfo();
    void saveTableInfo();
public:
    MyFileIO()
    {
        fm=new FileManager();
        bm=new BufPageManager(fm);
        loadDBInfo();
    }

    ~MyFileIO()
    {
        saveDBInfo();
        delete bm;
    }

    bool createDB(std::string dbname);

    bool dropDB(std::string dbname);

    bool useDB(std::string dbname);

    bool show
};


#endif //DBPROJECT_MYFILEIO_H
