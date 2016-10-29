//
// Created by luogan on 16-10-15.
//

#include "MyTable.h"
#include "../StaticMethod.h"
#include "MyPage.h"
#include "MyIndex.h"

void MyTable::deal()
{
    indexingCol.clear();
    indexingType.clear();
    int index0;
    char* page0=bm->getPage(fileID,0,index0);
    totalUsed=*(int*)page0;
    indexingTot=*(int*)(page0+4);
    for (int i=0;i<indexingTot;++i)
    {
        indexingCol.push_back(*(short*)(page0+i*3+8));
        indexingType.push_back(*(page0+i*3+10));
    }
}

bool MyTable::createIndex(short colID, char type)
{
    for (int i=0;i<indexingTot;++i)
        if (colID==indexingCol[i]||type==INDEX_CLUSTERED&&indexingType[i]==INDEX_CLUSTERED)
        {
            return false;
        }
    if (!myFileIO->createIndex(name,colID,type,cols.cols[colID].type,cols.cols[colID].len))
        return false;
    indexingCol.push_back(colID);
    indexingType.push_back(type);
    ++indexingTot;
    int index0;
    char* page0=bm->getPage(fileID,0,index0);
    int *tot=(int*)(page0+4);
    *tot+=1;
    *(short*)(page0+*tot*3+8)=colID;
    *(page0+*tot*3+10)=type;
    bm->markDirty(index0);
}

bool MyTable::dropIndex(short colID)
{
    for (int i=0;i<indexingTot;++i)
        if (colID==indexingCol[i])
        {
            if (!myFileIO->dropIndex(name,colID))
                return false;
            --indexingTot;
            int index0;
            char* page0=bm->getPage(fileID,0,index0);
            int *tot=(int*)(page0+4);
            *tot-=1;
            *(short*)(page0+i*3+8)=*(short*)(page0+*tot*3+8);
            *(page0+i*3+10)=*(page0+*tot*3+10);
            indexingCol[i]=indexingCol[indexingTot];
            indexingType[i]=indexingType[indexingTot];
            indexingCol.pop_back();
            indexingType.pop_back();
            bm->markDirty(index0);
            return true;
        }
    return false;
}

void MyTable::init()
{
    char* page0=bm->getPage(fileID,0,index);        //0号页记录int totalUsedPage, int indexingTot, short indexingID0, char indexingType0,int indexingRootPage0...
    int *totalUsed=(int*)page0;
    *totalUsed=2;
    int *indexingTot=(int*)page0+1;
    *indexingTot=0;
    int i;
    for (i=2;i<PAGE_SIZE/4;++i)
    {
        *(int*)(page0+i*4)=0;
    }
    bm->markDirty(index);

    page0=bm->getPage(fileID,1,index);      //1号页记录int dataUsedPage, int dataPageID0, int spaceLeft0...,int nextRootDataPage
    for (i=0;i<PAGE_SIZE/4;++i)
    {
        *(int*)(page0+i*4)=0;
    }
    *(int*)(page0+8188)=-1;
    bm->markDirty(index);
}

void MyTable::pageUsedUpdate()
{
    if (totalUsed>_totalUsed)
    {
        int index0;
        char* page0=bm->getPage(fileID,0,index0);
        *(int*)page0=totalUsed;
        bm->markDirty(index0);
    }
}

bool MyTable::insertData(MyData *data)
{
    for (int i=0;i<indexingTot;++i)
        if (indexingType[i]==INDEX_CLUSTERED)
        {
            MyIndex* myIndex=myFileIO.getIndex(name,indexingCol[i]);
            if (myIndex==0)
                break;
            myIndex->insertData(data);
            return true;
        }
    _totalUsed=totalUsed;
    int pageNum=1;
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int* used=(int*)page;
        for (int i=0;i<*used;++i)
        {
            int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
            if (*spaceLeft>=data->len+4)
            {
                MyPage page(fileID,*dataPage,bm);
                *spaceLeft=page.insertData(data);
                bm->markDirty(index);
                pageUsedUpdate();
                return true;
            }
        }
        if (*used<1000)
        {
            int *dataPage=(int*)(page+*used*8+4),*spaceLeft=(int*)(page+*used*8+8);
            *used+=1;
            *dataPage=totalUsed;
            totalUsed+=1;
            MyPage page(fileID,*dataPage,bm);
            page.init();
            *spaceLeft=page.insertData(data);
            bm->markDirty(index);
            pageUsedUpdate();
            return true;
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            pageNum=*(int*)(page+8188)=totalUsed;
            totalUsed+=1;
            int index1,i;
            char* page0=bm->getPage(fileID,pageNum,index1);
            for (i=0;i<PAGE_SIZE/4;++i)
            {
                *(int*)(page0+i*4)=0;
            }
            *(int*)(page0+8188)=-1;
            bm->markDirty(index1);
            bm->markDirty(index);
        }
    }
}

bool MyTable::insertData(std::vector<MyData*> &data)
{
    _totalUsed=totalUsed;
    int pageNum=1,k=0,m=data.size();
    while (k<m)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int* used=(int*)page;
        for (int i=0;i<*used;++i)
        {
            int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
            while (k<m&&*spaceLeft>=data[k]->len+4)
            {
                MyPage page(fileID,*dataPage,bm);
                *spaceLeft=page.insertData(data[k]);
                bm->markDirty(index);++k;
            }
            if (k>=m)
            {
                pageUsedUpdate();
                return true;
            }
        }
        while (*used<1000)
        {
            int *dataPage=(int*)(page+*used*8+4),*spaceLeft=(int*)(page+*used*8+8);
            *used+=1;
            *dataPage=totalUsed;
            totalUsed+=1;
            MyPage page(fileID,*dataPage,bm);
            *spaceLeft=page.init();
            while (k<m&&*spaceLeft>=data[k]->len+4)
            {
                *spaceLeft=page.insertData(data[k]);++k;
            }
            bm->markDirty(index);
            if (k>=m)
            {
                pageUsedUpdate();
                return true;
            }
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            pageNum=*(int*)(page+8188)=totalUsed;
            totalUsed+=1;
            int index1,i;
            char* page0=bm->getPage(fileID,pageNum,index1);
            for (i=0;i<PAGE_SIZE/4;++i)
            {
                *(int*)(page0+i*4)=0;
            }
            *(int*)(page0+8188)=-1;
            bm->markDirty(index1);
            bm->markDirty(index);
        }
    }
}

bool MyTable::searchData(Constraints* con,std::vector<MyData*> &res)
{
    int pageNum=1;
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page;
        for (int i=0;i<used;++i)
        {
            int *dataPage=(int*)(page+i*8+4);
            MyPage page(fileID,*dataPage,bm);
            page.searchData(con,res);
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
            return true;
    }
}

bool MyTable::deleteData(Constraints* con)
{
    int pageNum=1;
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page;
        for (int i=0;i<used;++i)
        {
            int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
            MyPage page(fileID,*dataPage,bm);
            *spaceLeft=page.deleteData(con);
            bm->markDirty(index);
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
            return true;
    }
}

bool MyTable::updateData(Constraints* con,Updates* upd)
{
    int pageNum=1;
    std::vector<MyData*> updated;
    updated.clear();
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page;
        for (int i=0;i<used;++i)
        {
            int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
            MyPage page(fileID,*dataPage,bm);
            *spaceLeft=page.updateData(con,upd,updated);
            bm->markDirty(index);
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            insertData(updated);
            size_t j,m=updated.size();
            for (j=0;j<m;++j)
                delete updated[j];
            return true;
        }
    }
}