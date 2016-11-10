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

    static bool cmp3(const pair<int,int> &x,const pair<int,int> &y);

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
    std::vector<bool> indexCanNull,indexCanDel;
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
    //插入一条数据
    bool insertData(MyData *data);
    //插入一批数据，仅当有簇集索引时一条条插入，否则不管索引重复
    bool insertData(std::vector<MyData*> &data);
    //查找符合要求的数据
    bool searchData(Constraints* con,std::vector<MyData*> &res);
    //直接删除符合要求的数据
    bool deleteData(Constraints* con);
    //直接更新符合要求的数据
    bool updateData(Constraints* con,Updates* upd);
    //保证唯一索引值唯一，先把符合要求的数据拿出来更新好，放回去时重复的被丢弃
    bool updateDataSafe(Constraints* con,Updates* upd);
    //创建指定列的指定类型的索引
    bool createIndex(short colID,char type,bool canNull,bool canDel);
    //删除指定列的索引
    bool dropIndex(short colID);
    //更新索引信息
    bool indexInfoUpdate();
    //是否有唯一索引
    bool hasUniqueIndex();

    MyIndex* getClusteredIndex();

    MyIndex* getIndex(int colID);

    int getClusteredID();
    //唯一索引有重复则返回false
    bool isUnique(MyData*);
    //唯一索引有重复就去掉重复的，并返回false
    bool isUnique(std::vector<MyData*> &datas);
    //通过页号和槽号获得数据
    bool getData(std::vector<std::pair<int,int>> &datas,std::vector<MyData*> &res);
    //删除指定页号和槽号的符合要求的数据，如果槽号是-1则是页中全部
    bool deleteData(std::vector<std::pair<int,int>> &datas,Constraints* con);
    //更新指定页号和槽号的数据，不管唯一索引的重复问题
    bool updateData(std::vector<std::pair<int,int>> &datas,Constraints* con,Updates* upd);
    //保证唯一索引值唯一，先把符合要求的数据拿出来更新好，放回去时重复的被丢弃
    bool updateDataSafe(std::vector<std::pair<int,int>> &datas,Constraints* con,Updates* upd);
};

#endif //DBPROJECT_MYTABLE_H