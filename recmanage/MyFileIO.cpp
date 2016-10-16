//
// Created by luogan on 16-10-16.
//

#include "MyFileIO.h"

void loadDBInfo()
{

}
void saveDBInfo()
{

}
void loadTableInfo()
{

}
void saveTableInfo()
{

}

bool MyFileIO::createDB(std::string dbname)
{
    int i,n=dbNames.size();
    for (i=0;i<n;++i)
        if (dbname==dbNames[i])
            return false;
    dbNames.push_back(dbname);
    saveDBInfo();
    return true;
}