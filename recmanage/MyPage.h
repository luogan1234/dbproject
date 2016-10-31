//
// Created by luogan on 16-10-15.
//

#ifndef DBPROJECT_MYPAGE_H
#define DBPROJECT_MYPAGE_H


#include "MyData.h"
#include "../searchanalysis/Constraints.h"
#include "../searchanalysis/Updates.h"
#include "../bufmanager/BufPageManager.h"

class MyPage {
private:
    int _deleteData();
public:
    int fileID,pageID,index,spaceLeft;
    BufPageManager* bm;
    char* page;
    std::vector<int> reserves;
    MyPage(int f,int p,BufPageManager *bm)
    {
        fileID=f;pageID=p;
        this->bm=bm;
        spaceLeft=-1;
        page=bm->getPage(fileID,pageID,index);
    }

    int init()
    {
        int i;
        for (i=0;i<PAGE_SIZE/4;++i)
        {
            *(int*)(page+i*4)=(int)0;
        }
        bm->markDirty(index);
        return spaceLeft=8188;
    }

    int insertData(MyData *data);

    int searchData(Constraints* con,std::vector<MyData*> &res);

    int deleteData(Constraints* con);

    int updateData(Constraints* con,Updates* upd,std::vector<MyData*> &updated);

    int findData(std::vector<std::pair<int,int>> &res);
};


#endif //DBPROJECT_MYPAGE_H