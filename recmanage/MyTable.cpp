//
// Created by luogan on 16-10-15.
//

#include "MyTable.h"
#include "../StaticMethod.h"
#include "MyPage.h"

bool MyTable::insertData(MyData &data)
{
    int pageNum=0;
    while (true)
    {
        char* page0=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page0;
        for (int i=1;i<PAGE_SIZE/4;++i)
        {
            int *spaceLeft=(int*)(page0+i*4);
            if (used<i||*spaceLeft>=data.len+4)
            {
                MyPage page(fileID,pageNum+i,bm);
                if (used<i)
                {
                    *spaceLeft=page.init();
                    bm->markDirty(index);
                }
                if (*spaceLeft>=data.len+4)
                {
                    *spaceLeft=page.insertData(data);
                    bm->markDirty(index);
                    return true;
                }
            }
        }
        pageNum+=PAGE_SIZE/4;
    }
}

bool MyTable::insertData(std::vector<MyData> &data)
{
    int pageNum=0,k=0,m=data.size();
    while (k<m)
    {
        char* page0=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page0;
        for (int i=1;i<PAGE_SIZE/4;++i)
        {
            int *spaceLeft=(int*)(page0+i*4);
            if (used<i||*spaceLeft>=data[k].len+4)
            {
                MyPage page(fileID,pageNum+i,bm);
                if (used<i)
                {
                    *spaceLeft=page.init();
                    bm->markDirty(index);
                }
                while (k<m&&*spaceLeft>=data[k].len+4)
                {
                    *spaceLeft=page.insertData(data[k]);
                    bm->markDirty(index);
                    ++k;
                }
                if (k>=m)
                    return true;
            }
        }
        pageNum+=PAGE_SIZE/4;
    }
    return true;
}

bool MyTable::searchData(Constraints* con,std::vector<MyData> &res)
{
    int pageNum=0;
    while (true)
    {
        char* page0=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page0;
        for (int i=1;i<PAGE_SIZE/4;++i)
        {
            if (used<i)
                return true;
            MyPage page(fileID,pageNum+i,bm);
            page.searchData(con,res);
        }
        pageNum+=PAGE_SIZE/4;
    }
}

bool MyTable::deleteData(Constraints* con)
{
    int pageNum=0;
    while (true)
    {
        char* page0=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page0;
        for (int i=1;i<PAGE_SIZE/4;++i)
        {
            int *spaceLeft=(int*)(page0+i*4);
            if (used<i)
                return true;
            MyPage page(fileID,pageNum+i,bm);
            *spaceLeft=page.deleteData(con);
            bm->markDirty(index);
        }
        pageNum+=PAGE_SIZE/4;
    }
}

bool MyTable::updateData(Constraints* con,Updates* upd)
{
    int pageNum=0;
    std::vector<MyData> updated;
    updated.clear();
    while (true)
    {
        char* page0=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page0;
        for (int i=1;i<PAGE_SIZE/4;++i)
        {
            int *spaceLeft=(int*)(page0+i*4);
            if (used<i)
            {
                insertData(updated);
                return true;
            }
            MyPage page(fileID,pageNum+i,bm);
            *spaceLeft=page.updateData(con,upd,updated);
            bm->markDirty(index);
        }
        pageNum+=PAGE_SIZE/4;
    }
}