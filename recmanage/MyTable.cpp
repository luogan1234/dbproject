//
// Created by luogan on 16-10-15.
//

#include <algorithm>
#include "MyTable.h"
#include "../StaticMethod.h"
#include "MyPage.h"
#include "MyIndex.h"
#include "MyFileIO.h"
#include "MyIndex.h"

using namespace std;

bool MyTable::cmp(const pair<MyData*,MyValue*> &x,const pair<MyData*,MyValue*> &y)
{
    if (x.second->compare(y.second)==COMPARE_SMALLER)
        return true;
    else
        return false;
}

bool MyTable::cmp2(const pair<MyValue*,int> &x,const pair<MyValue*,int> &y)
{
    int comRes=x.first->compare(y.first);
    if (comRes==COMPARE_SMALLER||comRes==COMPARE_EQUAL&&x.second<y.second)
        return true;
    else
        return false;
}

bool MyTable::cmp3(const pair<int,int> &x,const pair<int,int> &y)
{
    if (x.first<y.first||x.first==y.first&&x.second<y.second)
        return true;
    return false;
}

void MyTable::deal()
{
    indexingCol.clear();
    indexingType.clear();
    indexCanNull.clear();
    indexCanDel.clear();
    int index0;
    char* page0=bm->getPage(fileID,0,index0);
    totalUsed=*(int*)page0;
    indexingTot=*(int*)(page0+4);
    for (int i=0;i<indexingTot;++i)
    {
        indexingCol.push_back(*(short*)(page0+i*5+8));
        indexingType.push_back(*(page0+i*5+10));
        char p=*(page0+i*5+11);
        if (p=='0')
            indexCanNull.push_back(false);
        else
            indexCanNull.push_back(true);
        p=*(page0+i*5+12);
        if (p=='0')
            indexCanDel.push_back(false);
        else
            indexCanDel.push_back(true);
    }
    infos.clear();
    infoClusters.clear();
}

bool MyTable::hasUniqueIndex()
{
    int i;
    for (i=0;i<indexingTot;++i)
        if (indexingType[i]!=INDEX_UNCLUSTERED)
            return true;
    return false;
}

bool MyTable::isUnique(MyData *data)
{
    if (!cols.checkData(data,myFileIO))
        return false;
    int i,num,offset,colID;
    MyValue value;
    vector<pair<int,int>> res;
    res.clear();
    for (i=0;i<indexingTot;++i)
        if (indexingType[i]==INDEX_UNCLUSTERED_UNIQUE)
        {
            colID=indexingCol[i];
            cols.getByOrder(colID,num,offset);
            data->getValue(num,offset,&cols.cols[colID],value);
            myIndex=myFileIO->getIndex(name,colID,this);
            myIndex->findData(&value,COMPARE_SMALLER_EQUAL,&value,COMPARE_LARGER_EQUAL,res);
            if (res.size()>0)
                return false;
        }
    return true;
}

bool MyTable::isUnique(vector<MyData*> &datas)
{
    int i,num,offset,colID,j,m;
    bool p=true;
    MyValue value;
    vector<pair<int,int>> res;
    res.clear();
    for (i=0;i<indexingTot;++i)
        if (indexingType[i]==INDEX_UNCLUSTERED_UNIQUE)
            indexes[i]=myFileIO->getIndex(name,indexingCol[i],this);
    for (i=0;i<indexingTot;++i)
        if (indexingType[i]==INDEX_UNCLUSTERED_UNIQUE)
        {
            colID=indexingCol[i];
            cols.getByOrder(colID,num,offset);
            m=datas.size();
            for (j=m-1;j>=0;--j)
            {
                datas[j]->getValue(num,offset,&cols.cols[colID],value);
                indexes[i]->findData(&value,COMPARE_SMALLER_EQUAL,&value,COMPARE_LARGER_EQUAL,res);
                if (res.size()>0||!cols.checkData(datas[j],myFileIO))
                {
                    p=false;
                    res.clear();
                    datas.erase(datas.begin()+j);
                    --m;
                }
            }
        }
    return p;
}

int MyTable::getColID(std::string colName)
{
    return cols.getColID(colName);
}

int MyTable::getColNum()
{
    return cols.n;
}

std::string MyTable::getColName(int colID)
{
    if (colID<cols.n)
        return cols.cols[colID].name;
    return "";
}

int MyTable::getColType(int colID)
{
    if (colID>=indexingTot)
        return COL_ERROR;
    if (cols.cols[colID].isPrimary)
        return COL_PRI;
    for (int i=0;i<indexingTot;++i)
        if (indexingCol[i]==colID)
        {
            if (indexingType[i]==INDEX_UNCLUSTERED||indexCanNull[i])
                return COL_MUL;
            else
                return COL_UNI;
        }
    return COL_NULL;
}

bool MyTable::createIndex(short colID, char type,bool canNull,bool canDel)
{
    for (int i=0;i<indexingTot;++i)
        if (colID==indexingCol[i]||type==INDEX_CLUSTERED&&indexingType[i]==INDEX_CLUSTERED)
        {
            return false;
        }
    if (!myFileIO->createIndex(name,colID,type,canNull,canDel,cols.cols[colID].type,cols.cols[colID].len))
        return false;
    indexingCol.push_back(colID);
    indexingType.push_back(type);
    indexCanNull.push_back(canNull);
    indexCanDel.push_back(canDel);
    ++indexingTot;
    int index0;
    char* page0=bm->getPage(fileID,0,index0);
    int *tot=(int*)(page0+4);
    *(short*)(page0+*tot*5+8)=colID;
    *(page0+*tot*5+10)=type;
    if (!canNull)
        *(page0+*tot*5+11)='0';
    else
        *(page0+*tot*5+11)='1';
    if (!canDel)
        *(page0+*tot*5+12)='0';
    else
        *(page0+*tot*5+12)='1';
    *tot+=1;
    bm->markDirty(index0);
    int num,offset;
    cols.getByOrder(colID,num,offset);
    myIndex=myFileIO->getIndex(name,colID,this);
    if (myIndex==0)
    {
        dropIndex(colID);
        return false;
    }
    int pageNum=1;
    vector<MyData*> res;
    vector<int> pages,slots;
    res.clear();pages.clear();slots.clear();
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int* used=(int*)page;
        for (int i=0;i<*used;++i)
        {
            int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
            MyPage page(fileID,*dataPage,bm,this);
            page.findAllData(res,pages,slots);
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
            break;
    }
    int i,m=res.size();
    if (type==INDEX_CLUSTERED)
    {
        vector<pair<MyData*,MyValue*>> sorts;
        sorts.clear();
        for (i=0;i<m;++i)
        {
            MyValue* value=new MyValue;
            res[i]->getValue(num,offset,&cols.cols[colID],*value);
            sorts.push_back(make_pair(res[i],value));
        }
        sort(sorts.begin(),sorts.end(),cmp);
        for (i=0;i<m-1;++i)
            if (MyValue::compare(sorts[i].second,sorts[i+1].second)==COMPARE_EQUAL||!canNull&&sorts[i].second->isNull)
            {
                dropIndex(colID);
                return false;
            }
        pageNum=1;
        while (true)
        {
            char* page=bm->getPage(fileID,pageNum,index);
            int* used=(int*)page;
            for (int i=0;i<*used;++i)
            {
                int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
                MyPage page(fileID,*dataPage,bm,this);
                page.deleteAllData();
                bm->markDirty(index);
            }
            pageNum=*(int*)(page+8188);
            if (pageNum==-1)
                break;
        }
        char* page0=bm->getPage(fileID,0,index);
        int *totalUsed=(int*)page0;
        *totalUsed=2;
        bm->markDirty(index);
        page0=bm->getPage(fileID,1,index);
        memset(page0,0,PAGE_SIZE);
        *(int*)(page0+8188)=-1;
        bm->markDirty(index);
        insertData(res);
        for (i=0;i<m;++i)
            delete sorts[i].first,sorts[i].second;
    } else
    {
        for (i=0;i<m;++i)
        {
            MyValue value;
            res[i]->getValue(num,offset,&cols.cols[colID],value);
            if (!myIndex->insertData(&value,pages[i],slots[i]))
            {
                dropIndex(colID);
                return false;
            }
        }
    }
    return true;
}

bool MyTable::dropIndex(short colID)
{
    for (int i=0;i<indexingTot;++i)
        if (colID==indexingCol[i]&&indexCanDel[i])
        {
            if (!myFileIO->dropIndex(name,colID))
                return false;
            --indexingTot;
            int index0;
            char* page0=bm->getPage(fileID,0,index0);
            int *tot=(int*)(page0+4);
            *tot-=1;
            *(short*)(page0+i*5+8)=*(short*)(page0+*tot*5+8);
            *(page0+i*5+10)=*(page0+*tot*5+10);
            *(page0+i*5+11)=*(page0+*tot*5+11);
            *(page0+i*5+12)=*(page0+*tot*5+12);
            indexingCol[i]=indexingCol[indexingTot];
            indexingType[i]=indexingType[indexingTot];
            indexCanNull[i]=indexCanNull[indexingTot];
            indexCanDel[i]=indexCanDel[indexingTot];
            indexingCol.pop_back();
            indexingType.pop_back();
            indexCanNull.pop_back();
            indexCanDel.pop_back();
            bm->markDirty(index0);
            return true;
        }
    return false;
}

bool MyTable::dropAllIndex()
{
    for (int i=0;i<indexingTot;++i)
        myFileIO->dropIndex(name,indexingCol[i]);
    return true;
}

MyIndex* MyTable::getClusteredIndex()
{
    for (int i=0;i<indexingTot;++i)
        if (indexingType[i]==INDEX_CLUSTERED)
        {
            return myFileIO->getIndex(name,indexingCol[i],this);
        }
    return 0;
}

MyIndex* MyTable::getIndex(int colID)
{
    for (int i=0;i<indexingTot;++i)
        if (indexingCol[i]==colID)
        {
            return myFileIO->getIndex(name,indexingCol[i],this);
        }
    return 0;
}

int MyTable::getClusteredID()
{
    for (int i=0;i<indexingTot;++i)
        if (indexingType[i]==INDEX_CLUSTERED)
        {
            return indexingCol[i];
        }
    return -1;
}

bool MyTable::getAllForeignKey(vector<pair<int,string> > &res)
{
    res.clear();
    if (!cols.hasPrimaryKey())
        return false;
    myFileIO->getAllForeignKey(name,res);
    return true;
}

void MyTable::init()
{
    char* page0=bm->getPage(fileID,0,index);        //0号页记录int totalUsedPage, int indexingTot, short indexingID0, char indexingType0,int indexingRootPage0...
    int *totalUsed=(int*)page0;
    memset(page0,0,PAGE_SIZE);
    *totalUsed=2;
    int *indexingTot=(int*)page0+1;
    *indexingTot=0;
    bm->markDirty(index);

    page0=bm->getPage(fileID,1,index);      //1号页记录int dataUsedPage, int dataPageID0, int spaceLeft0...,int nextRootDataPage
    memset(page0,0,PAGE_SIZE);
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
    data->print();
    if (!isUnique(data))
        return false;
    for (int i=0;i<indexingTot;++i)
        if (indexingType[i]==INDEX_CLUSTERED)
        {
            bool p;
            MyIndex* myIndex=myFileIO->getIndex(name,indexingCol[i],this);
            if (myIndex==0)
                break;
            int num,offset,colID=indexingCol[i],sl,page2,sl2;
            cols.getByOrder(colID,num,offset);
            MyValue value;
            data->getValue(num,offset,&cols.cols[colID],value);
            int resPage=myIndex->insertDataClustered(value);
            _totalUsed=totalUsed;
            if (resPage==-1)
            {
                resPage=totalUsed;
                totalUsed+=1;
                char* page0=bm->getPage(fileID,resPage,index);
                memset(page0,0,PAGE_SIZE);
                bm->markDirty(index);
            }
            MyPage myPage(fileID,resPage,bm,this);
            page2=-1;
            p=myPage.insertDataClustered(data,num,offset,value,&cols.cols[colID],myIndex,sl,page2,sl2);
            if (p)
            {
                int pageNum=1;
                while (true)
                {
                    char* page=bm->getPage(fileID,pageNum,index);
                    int* used=(int*)page;
                    for (int i=0;i<*used;++i)
                    {
                        int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
                        if (*dataPage==resPage)
                            *spaceLeft=sl,resPage=-1;
                        if (*dataPage==page2)
                            *spaceLeft=sl2,page2=-1;
                    }
                    if (resPage==-1&&page2==-1)
                        break;
                    if (*used<1000&&(resPage>-1||page2>-1))
                    {
                        int *dataPage=(int*)(page+*used*8+4),*spaceLeft=(int*)(page+*used*8+8);
                        *used+=1;
                        if (resPage>-1)
                        {
                            *dataPage=resPage;
                            *spaceLeft=sl;
                        } else
                        {
                            *dataPage=page2;
                            *spaceLeft=sl2;
                        }
                        bm->markDirty(index);
                        break;
                    }
                    pageNum=*(int*)(page+8188);
                    if (pageNum==-1)
                    {
                        pageNum=*(int*)(page+8188)=totalUsed;
                        totalUsed+=1;
                        int index1;
                        char* page0=bm->getPage(fileID,pageNum,index1);
                        memset(page0,0,PAGE_SIZE);
                        *(int*)(page0+8188)=-1;
                        bm->markDirty(index1);
                        bm->markDirty(index);
                    }
                }
            }
            pageUsedUpdate();
            indexInfoUpdate();
            return p;
        }
    return _insertData(data);
}

bool MyTable::_insertData(MyData *data)
{
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
                MyPage page(fileID,*dataPage,bm,this);
                *spaceLeft=page.insertData(data);
                bm->markDirty(index);
                pageUsedUpdate();
                indexInfoUpdate();
                return true;
            }
        }
        if (*used<1000)
        {
            int *dataPage=(int*)(page+*used*8+4),*spaceLeft=(int*)(page+*used*8+8);
            *used+=1;
            *dataPage=totalUsed;
            totalUsed+=1;
            MyPage page(fileID,*dataPage,bm,this);
            page.init();
            *spaceLeft=page.insertData(data);
            bm->markDirty(index);
            pageUsedUpdate();
            indexInfoUpdate();
            return true;
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            pageNum=*(int*)(page+8188)=totalUsed;
            totalUsed+=1;
            int index1;
            char* page0=bm->getPage(fileID,pageNum,index1);
            memset(page0,0,PAGE_SIZE);
            *(int*)(page0+8188)=-1;
            bm->markDirty(index1);
            bm->markDirty(index);
        }
    }
}

bool MyTable::insertData(vector<MyData*> &datas)
{
    bool p=isUnique(datas);
    for (int i=0;i<indexingTot;++i)
        if (indexingType[i]==INDEX_CLUSTERED)
        {
            MyIndex* myIndex=myFileIO->getIndex(name,indexingCol[i],this);
            if (myIndex==0)
                break;
            int m=datas.size();
            for (size_t j=0;j<m;++j)
            {
                p&=insertData(datas[j]);
            }
            return p;
        }
    return _insertData(datas)&&p;
}

bool MyTable::_insertData(vector<MyData*> &data)
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
                MyPage page(fileID,*dataPage,bm,this);
                *spaceLeft=page.insertData(data[k]);
                bm->markDirty(index);++k;
            }
            if (k>=m)
            {
                pageUsedUpdate();
                indexInfoUpdate();
                return true;
            }
        }
        while (*used<1000)
        {
            int *dataPage=(int*)(page+*used*8+4),*spaceLeft=(int*)(page+*used*8+8);
            *used+=1;
            *dataPage=totalUsed;
            totalUsed+=1;
            MyPage page(fileID,*dataPage,bm,this);
            *spaceLeft=page.init();
            while (k<m&&*spaceLeft>=data[k]->len+4)
            {
                *spaceLeft=page.insertData(data[k]);++k;
            }
            bm->markDirty(index);
            if (k>=m)
            {
                pageUsedUpdate();
                indexInfoUpdate();
                return true;
            }
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            pageNum=*(int*)(page+8188)=totalUsed;
            totalUsed+=1;
            int index1;
            char* page0=bm->getPage(fileID,pageNum,index1);
            memset(page0,0,PAGE_SIZE);
            *(int*)(page0+8188)=-1;
            bm->markDirty(index1);
            bm->markDirty(index);
        }
    }
}

bool MyTable::searchData(Constraints* con,vector<MyData*> &res)
{
    int pageNum=1;
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page;
        for (int i=0;i<used;++i)
        {
            int *dataPage=(int*)(page+i*8+4);
            MyPage page(fileID,*dataPage,bm,this);
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
            MyPage page(fileID,*dataPage,bm,this);
            *spaceLeft=page.deleteData(con);
            bm->markDirty(index);
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            pageUsedUpdate();
            indexInfoUpdate();
            return true;
        }
    }
}

bool MyTable::updateData(Constraints* con,Updates* upd)
{
    int pageNum=1;
    vector<MyData*> updated;
    updated.clear();
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page;
        for (int i=0;i<used;++i)
        {
            int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
            MyPage page(fileID,*dataPage,bm,this);
            *spaceLeft=page.updateData(con,upd,updated);
            bm->markDirty(index);
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            pageUsedUpdate();
            indexInfoUpdate();
            insertData(updated);
            return true;
        }
    }
}

bool MyTable::updateDataSafe(Constraints* con,Updates* upd)
{
    if (!hasUniqueIndex())
        return updateData(con,upd);
    int pageNum=1;
    vector<MyData*> updates;
    updates.clear();
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page;
        for (int i=0;i<used;++i)
        {
            int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
            MyPage page(fileID,*dataPage,bm,this);
            page.searchData(con,updates);
            *spaceLeft=page.deleteData(con);
            bm->markDirty(index);
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            pageUsedUpdate();
            indexInfoUpdate();
            int i,m=updates.size();
            for (i=0;i<m;++i)
            {
                upd->update(updates[i]);
                insertData(updates[i]);
            }
            return true;
        }
    }
}

bool MyTable::indexInfoUpdate()
{
    int i,k,m=infos.size(),n=infoClusters.size();
    for (k=0;k<indexingTot;++k)
    {
        myIndex=myFileIO->getIndex(name,indexingCol[k],this);
        if (myIndex==0)
            continue;
        if (indexingType[k]==INDEX_CLUSTERED)
        {
            for (i=0;i<n;++i)
            {
                ModifyInfoForCluster* mi=infoClusters[i];
                if (mi->oldValue!=0)
                    myIndex->deleteData(mi->oldValue,mi->page,-1);
                if (mi->newValue!=0)
                    myIndex->insertData(mi->newValue,mi->page,-1);
            }
        } else
        {
            int num,offset;
            cols.getByOrder(indexingCol[k],num,offset);
            ModifyInfo* mi;
            for (i=0;i<m;++i)
            {
                mi=infos[i];
                MyValue value;
                mi->data->getValue(num,offset,&cols.cols[k],value);
                if (mi->oldPage!=-1)
                    myIndex->deleteData(&value,mi->oldPage,mi->oldSlot);
                if (mi->newPage!=-1)
                    myIndex->insertData(&value,mi->newPage,mi->newSlot);
            }

        }
    }
    for (i=0;i<m;++i)
        delete infos[i];
    for (i=0;i<n;++i)
        delete infoClusters[i];
    infos.clear();infoClusters.clear();
}

bool MyTable::getData(vector<pair<int,int>> &datas,vector<MyData*> &res)
{
    sort(datas.begin(),datas.end(),cmp3);
    vector<int> slots;
    int i,j,m=datas.size(),nowPage;
    for (i=0;i<m;++i)
        if (i==0||datas[i].first>datas[i-1].first)
        {
            nowPage=datas[i].first;
            if (nowPage>=totalUsed)
                return false;
            slots.clear();
            slots.push_back(datas[i].second);
            if (slots[0]>-1)
                for (j=i+1;j<m;++j)
                    if (datas[j].first==datas[i].first&&datas[j].second>datas[j-1].second)
                        slots.push_back(datas[j].second);
                    else
                        break;
            MyPage myPage(fileID,nowPage,bm,this);
            myPage.findData(slots,res);
        }
    return true;
}

bool MyTable::deleteData(std::vector<std::pair<int,int>> &datas,Constraints* con)
{
    sort(datas.begin(),datas.end(),cmp3);
    int n=datas.size(),i,m;
    bool *p=new bool[totalUsed];
    for (i=0;i<totalUsed;++i)
        p[i]=false;
    for (i=0;i<n;++i)
        if (datas[i].first<totalUsed)
            p[datas[i].first]=true;
    int pageNum=1;
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page;
        for (int i=0;i<used;++i)
        {
            int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
            if (p[*dataPage])
            {
                MyPage page(fileID,*dataPage,bm,this);
                *spaceLeft=page.deleteData(con);
                bm->markDirty(index);
            }
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            delete []p;
            pageUsedUpdate();
            indexInfoUpdate();
            return true;
        }
    }
}

bool MyTable::updateData(std::vector<std::pair<int,int>> &datas,Constraints* con,Updates* upd)
{
    sort(datas.begin(),datas.end(),cmp3);
    int n=datas.size(),i;
    bool *p=new bool[totalUsed];
    for (i=0;i<totalUsed;++i)
        p[i]=false;
    for (i=0;i<n;++i)
        if (datas[i].first<totalUsed)
            p[datas[i].first]=true;
    int pageNum=1;
    vector<MyData*> updated;
    updated.clear();
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page;
        for (int i=0;i<used;++i)
        {
            int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
            if (p[*dataPage])
            {
                MyPage page(fileID,*dataPage,bm,this);
                *spaceLeft=page.updateData(con,upd,updated);
                bm->markDirty(index);
            }
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            pageUsedUpdate();
            indexInfoUpdate();
            insertData(updated);
            delete []p;
            return true;
        }
    }
}

bool MyTable::updateDataSafe(std::vector<std::pair<int,int>> &datas,Constraints* con,Updates* upd)
{
    if (!hasUniqueIndex())
        return updateData(datas,con,upd);
    sort(datas.begin(),datas.end(),cmp3);
    int n=datas.size(),i;
    bool *p=new bool[totalUsed];
    for (i=0;i<totalUsed;++i)
        p[i]=false;
    for (i=0;i<n;++i)
        if (datas[i].first<totalUsed)
            p[datas[i].first]=true;
    int pageNum=1;
    vector<MyData*> updates;
    updates.clear();
    while (true)
    {
        char* page=bm->getPage(fileID,pageNum,index);
        int used=*(int*)page;
        for (int i=0;i<used;++i)
        {
            int *dataPage=(int*)(page+i*8+4),*spaceLeft=(int*)(page+i*8+8);
            if (p[*dataPage])
            {
                MyPage page(fileID,*dataPage,bm,this);
                page.searchData(con,updates);
                *spaceLeft=page.deleteData(con);
                bm->markDirty(index);
            }
        }
        pageNum=*(int*)(page+8188);
        if (pageNum==-1)
        {
            pageUsedUpdate();
            indexInfoUpdate();
            int i,m=updates.size();
            for (i=0;i<m;++i)
            {
                upd->update(updates[i]);
                insertData(updates[i]);
            }
            delete []p;
            return true;
        }
    }
}