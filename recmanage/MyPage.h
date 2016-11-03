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

    int insertData(MyData *data);

    int searchData(Constraints* con,std::vector<MyData*> &res);

    int deleteData(Constraints* con);

    int updateData(Constraints* con,Updates* upd,std::vector<MyData*> &updated);

    bool findData(std::vector<int> &slots,std::vector<MyData*> &res);

    bool findAllData(std::vector<MyData*> &res,std::vector<int> &pages,std::vector<int> &slots);

    int deleteAllData();
};


#endif //DBPROJECT_MYPAGE_H