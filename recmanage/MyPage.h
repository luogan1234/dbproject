//
// Created by luogan on 16-10-15.
//

#ifndef DBPROJECT_MYPAGE_H
#define DBPROJECT_MYPAGE_H


#include "MyData.h"
#include "../searchanalysis/Constraints.h"
#include "../searchanalysis/Updates.h"
#include "../bufmanager/BufPageManager.h"
#include "MyTable.h"

class MyPage {
private:
    int _deleteData();
public:
    int fileID,pageID,index,spaceLeft;
    BufPageManager* bm;
    char* page;
    std::vector<int> reserves;
    MyTable* myTable;
    MyIndex* myIndex;
    bool needChange;
    MyValue myValue;
    MyPage(int f,int p,BufPageManager *bm,MyTable* m)
    {
        fileID=f;pageID=p;
        this->bm=bm;
        spaceLeft=-1;
        page=bm->getPage(fileID,pageID,index);
        myTable=m;
    }

    int init()
    {
        memset(page,0,PAGE_SIZE);
        bm->markDirty(index);
        return spaceLeft=8184;
    }
    //插入一条数据
    int insertData(MyData *data);
    //根据簇集索引插入数据
    bool insertDataClustered(MyData *data,int num,int offset,MyValue &value,MyCol* myCol,MyIndex* myIndex,int &spaceLeft,int &page2,int &spaceLeft2);
    //查找符合要求的数据
    int searchData(Constraints* con,std::vector<MyData*> &res);
    //删除符合要求的数据
    int deleteData(Constraints* con);
    //更新符合要求的数据
    int updateData(Constraints* con,Updates* upd,std::vector<MyData*> &updated);
    //查找对应槽号的数据
    bool findData(std::vector<int> &slots,std::vector<MyData*> &res);
    //获取所有数据
    bool findAllData(std::vector<MyData*> &res,std::vector<int> &pages,std::vector<int> &slots);
    //删除所有数据
    int deleteAllData();
};


#endif //DBPROJECT_MYPAGE_H