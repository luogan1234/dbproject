//
// Created by luogan on 16-10-14.
//

#ifndef DBPROJECT_MYTABLE_H
#define DBPROJECT_MYTABLE_H

#include "TableCols.h"
#include "MyData.h"
#include "../bufmanager/BufPageManager.h"
#include "../searchanalysis/Constraints.h"
#include "../searchanalysis/Updates.h"

class MyTable
{
public:
    std::string name;
    TableCols cols;
    BufPageManager* bm;
    int fileID,index;

    MyTable(BufPageManager* bm,int f,std::string n,std::string c)
    {
        this->bm=bm;
        fileID=f;
        name=n;cols=TableCols(c);
    }

    MyTable(BufPageManager* bm,int f,std::string n,TableCols c)
    {
        this->bm=bm;
        fileID=f;
        name=n;cols=c;
    }

    bool insertData(MyData *Mydata);

    bool insertData(std::vector<MyData*> &data);

    bool searchData(Constraints* con,std::vector<MyData*> &res);

    bool deleteData(Constraints* con);

    bool updateData(Constraints* con,Updates* upd);

};

#endif //DBPROJECT_MYTABLE_H