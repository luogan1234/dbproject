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
#include "ModifyInfo.h"
#include "ModifyInfoForCluster.h"

class MyFileIO;
class MyIndex;

class MyTable
{
private:
    static bool cmp(const pair<MyData*,MyValue*> &x,const pair<MyData*,MyValue*> &y);

    static bool cmp2(const pair<MyValue*,int> &x,const pair<MyValue*,int> &y);

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
    MyIndex* indexes[MAX_COL_NUM];
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

    MyIndex* getClusteredIndex();

    MyIndex* getIndex(int colID);

    int getClusteredID();

    bool isUnique(MyData*); //重复则返回false

    bool isUnique(vector<MyData*> &datas);  //有重复就去掉重复的，并返回false

};

#endif //DBPROJECT_MYTABLE_H