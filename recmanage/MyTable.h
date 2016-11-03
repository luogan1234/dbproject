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
#include "MyFileIO.h"
#include "ModifyInfo.h"
#include "ModifyInfoForCluster.h"

class MyTable
{
private:
    static bool cmp(const pair<MyData*,MyValue*> &x,const pair<MyData*,MyValue*> &y);

    bool _insertData(MyData *data);

    bool _insertData(std::vector<MyData*> &data);
public:
    std::string name;
    TableCols cols;
    BufPageManager* bm;
    MyFileIO* myFileIO;
    int fileID,index,totalUsed,_totalUsed,indexingTot;
    std::vector<short> indexingCol;
    std::vector<char> indexingType;
    std::vector<ModifyInfo*> infos;
    std::vector<ModifyInfoForCluster*> infoClusters;

    MyIndex* myIndex;

    MyTable(BufPageManager* bm,MyFileIO* m,int f,std::string n,std::string c)
    {
        this->bm=bm;
        myFileIO=m;
        fileID=f;
        name=n;cols=TableCols(c);
        deal();
    }

    MyTable(BufPageManager* bm,MyFileIO* m,int f,std::string n,TableCols c)
    {
        this->bm=bm;
        myFileIO=m;
        fileID=f;
        name=n;cols=c;
        deal();
    }

    void deal();

    void init();

    void pageUsedUpdate();

    bool insertData(MyData *data);

    bool insertData(std::vector<MyData*> &data);

    bool searchData(Constraints* con,std::vector<MyData*> &res);

    bool deleteData(Constraints* con);

    bool updateData(Constraints* con,Updates* upd);

    bool createIndex(short colID,char type);

    bool dropIndex(short colID);

    bool getAllIndex(std::vector<std::pair<short,char>> indexs);

    bool indexInfoUpdate();

};

#endif //DBPROJECT_MYTABLE_H