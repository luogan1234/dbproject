//
// Created by luogan on 16-10-15.
//

#include "MyPage.h"
#include "MyIndex.h"

using namespace std;

int MyPage::insertData(MyData *data)
{
    int* eleNum=(int*)(page+8188);
    int last=*(int*)(page+8184-4**eleNum);
    memmove(page+last,data->data,data->len);
    *eleNum+=1;
    *(int*)(page+8184-4*(*eleNum))=last+data->len;
    spaceLeft=8184-last-data->len-4**eleNum;
    bm->markDirty(index);
    ModifyInfo* mi=new ModifyInfo;
    mi->data=data;
    mi->newPage=pageID;mi->newSlot=*eleNum;
    mi->oldPage=-1;mi->oldSlot=-1;
    myTable->infos.push_back(mi);
    return spaceLeft;
}

bool MyPage::insertDataClustered(MyData *data,int num,int offset,MyValue &value,MyCol* myCol,MyIndex* myIndex)
{
    int* eleNum=(int*)(page+8188);
    int k=0,p=-1,len=8;
    int* next=(int*)(page+8184),*ele;
    vector<MyData*> datas;
    vector<MyValue*> values;
    datas.clear();
    while (k<*eleNum)
    {
        ele=next;++k;next-=1;
        MyData *myData=new MyData(page,*ele,*next-*ele);
        MyValue* myValue=new MyValue;
        myData->getValue(num,offset,myCol,*myValue);
        int comRes=value.compare(myValue);
        if (comRes==COMPARE_EQUAL)
        {
            int i,m=datas.size();
            for (i=0;i<m;++i)
                delete datas[i];
            return false;
        }
        if (comRes==COMPARE_SMALLER&&p==-1)
        {
            datas.push_back(data);p=k-1;
            values.push_back(&value);
            len+=data->len+4;
        }
        datas.push_back(myData);
        values.push_back(myValue);
        len+=myData->len+4;
    }
    if (p==-1)
    {
        datas.push_back(data);p=k;
        len+=data->len+4;
    }
    int i,ii=datas.size(),j,pos,index0,m=datas.size();
    if (len>8100)
    {
        int len2=8;
        for (i=0;i<m;++i)
        {
            len2+=datas[i]->len+4;
            if (len2>len/2)
            {
                ii=i;
                break;
            }
        }
        int newPage=myTable->totalUsed;j=pos=0;
        char* page0=bm->getPage(fileID,newPage,index0);
        for (i=ii;i<m;++i)
        {
            ++j;
            *(int*)(page0+8188-j*4)=pos;
            memmove(page0+pos,datas[i]->data,datas[i]->len);
            pos+=datas[i]->len;
            ModifyInfo* mi=new ModifyInfo;
            mi->data=datas[i];
            mi->newPage=newPage;mi->newSlot=j;
            if (i==p)
            {
                mi->oldPage=mi->oldSlot=-1;
            }else
            {
                mi->oldPage=pageID;mi->oldSlot=i+1;
                if (i>p)
                    mi->oldSlot=i;
            }
            myTable->infos.push_back(mi);
        }
        *(int*)(page0+8188)=j;
        myIndex->insertData(values[m-1],newPage,-1);
        bm->markDirty(index0);
        ++myTable->totalUsed;
        page0=bm->getPage(fileID,0,index0);
        *(int*)page0=myTable->totalUsed;
        bm->markDirty(index0);
    }
    j=pos=0;
    for (i=0;i<ii;++i)
    {
        ++j;
        if (i<p)
        {
            pos+=datas[i]->len;
            continue;
        }
        *(int*)(page+8188-j*4)=pos;
        memmove(page+pos,datas[i]->data,datas[i]->len);
        pos+=datas[i]->len;
        ModifyInfo* mi=new ModifyInfo;
        mi->data=datas[i];
        mi->newPage=pageID;mi->newSlot=j;
        if (i==p)
        {
            mi->oldPage=mi->oldSlot=-1;
        }else
        {
            mi->oldPage=pageID;mi->oldSlot=i;
        }
        myTable->infos.push_back(mi);
    }
    *(int*)(page+8188)=j;
    bm->markDirty(index);
    if (ii<m||p==m-1)
    {
        if (p==m-1)
            myIndex->deleteData(values[p-1],pageID,-1);
        else
            myIndex->deleteData(values[m-1],pageID,-1);
        myIndex->insertData(values[ii-1],pageID,-1);
    }
    return true;
}

int MyPage::searchData(Constraints* con,vector<MyData*> &res)
{
    int* eleNum=(int*)(page+8188);
    int k=0;
    int* next=(int*)(page+8184),*ele;
    while (k<*eleNum)
    {
        ele=next;++k;next-=1;
        MyData *myData=new MyData(page,*ele,*next-*ele);
        if (con->checkData(myData))
            res.push_back(myData);
        else
            delete myData;
    }
    spaceLeft=8184-*(int*)(page+8184-4**eleNum)-4**eleNum;
    return spaceLeft;
}

int MyPage::deleteData(Constraints* con)
{
    int eleNum=*(int*)(page+8188);
    int k=0,i=0;
    int* next=(int*)(page+8184),*ele;
    reserves.clear();
    MyData* myData,*lastData;
    while (k<eleNum)
    {
        ele=next;++k;next-=1;
        myData=new MyData(page,*ele,*next-*ele);
        if (k==eleNum)
            lastData=new MyData(page,*ele,*next-*ele);
        if (!con->checkData(myData))
        {
            reserves.push_back(k);
            ++i;
            if (k>i)
            {
                ModifyInfo* mi=new ModifyInfo;
                mi->data=myData;
                mi->newPage=pageID;mi->newSlot=i;
                mi->oldPage=pageID;mi->oldSlot=k;
                myTable->infos.push_back(mi);
            }else
                delete myData;
        }
        else
        {
            ModifyInfo* mi=new ModifyInfo;
            mi->data=myData;
            mi->newPage=mi->newSlot=-1;
            mi->oldPage=pageID;mi->oldSlot=k;
            myTable->infos.push_back(mi);
            bm->markDirty(index);
        }
    }
    myIndex=myTable->getClusteredIndex();
    int m=reserves.size();
    needChange=false;
    if ((m==0||eleNum>reserves[m-1])&&myIndex!=0)
    {
        needChange=true;
        int num,offset,colID=myTable->getClusteredID();
        myTable->cols.getByOrder(colID,num,offset);
        lastData->getValue(num,offset,&myTable->cols.cols[colID],myValue);
        myIndex->deleteData(&myValue,pageID,-1);
    }
    delete lastData;
    return _deleteData();
}

int MyPage::_deleteData()
{
    int* eleNum=(int*)(page+8188);
    int i,last=0,len,pos;
    vector<int> position;
    position.clear();
    position.push_back(0);
    size_t m=reserves.size();
    MyData* lastData;
    for (i=0;i<m;++i)
    {
        pos=*(int*)(page+8188-4*reserves[i]);
        len=*(int*)(page+8184-4*reserves[i])-pos;
        if (i==m-1)
        {
            lastData=new MyData(page,pos,len);
        }
        if (i<reserves[i]-1&&len>0)
        {
            memmove(page+last,page+pos,len);
        }
        last+=len;
        position.push_back(last);
    }
    for (i=0;i<=m;++i)
    {
        *(int*)(page+8184-4*i)=position[i];
    }
    *eleNum=reserves.size();
    spaceLeft=8184-*(int*)(page+8184-4**eleNum)-4**eleNum;
    if (needChange&&*eleNum>0)
    {
        int num,offset,colID=myTable->getClusteredID();
        myTable->cols.getByOrder(colID,num,offset);
        lastData->getValue(num,offset,&myTable->cols.cols[colID],myValue);
        myIndex->insertData(&myValue,pageID,-1);
    }
    if (m>0)
        delete lastData;
    return spaceLeft;
}

int MyPage::updateData(Constraints* con,Updates* upd,vector<MyData*> &updated)
{
    int eleNum=*(int*)(page+8188);
    int k=0,i=0;
    int* next=(int*)(page+8184),*ele;
    reserves.clear();
    MyData *lastData;
    while (k<eleNum)
    {
        ele=next;++k;next-=1;
        MyData *myData=new MyData(page,*ele,*next-*ele);
        if (k==eleNum)
        {
            lastData=new MyData(page,*ele,*next-*ele);
        }
        if (!con->checkData(myData))
        {
            reserves.push_back(k);
            ++i;
            if (k>i)
            {
                ModifyInfo* mi=new ModifyInfo;
                mi->data=myData;
                mi->newPage=pageID;mi->newSlot=i;
                mi->oldPage=pageID;mi->oldSlot=k;
                myTable->infos.push_back(mi);
            }else
                delete myData;
        }
        else
        {
            int oldLen=myData->len;
            MyData *myData2=new MyData(page,*ele,*next-*ele);
            if (!upd->update(myData))
            {
                reserves.push_back(k);
                ++i;
                if (k>i)
                {
                    ModifyInfo* mi=new ModifyInfo;
                    mi->data=myData;
                    mi->newPage=pageID;mi->newSlot=i;
                    mi->oldPage=pageID;mi->oldSlot=k;
                    myTable->infos.push_back(mi);
                    delete myData2;
                }else
                    delete myData,myData2;
            }
            else
            if (oldLen==myData->len)
            {
                bm->markDirty(index);
                memmove(page+*ele,myData->data,myData->len);
                reserves.push_back(k);
                ++i;
                ModifyInfo* mi2=new ModifyInfo;
                mi2->data=myData2;
                mi2->newPage=-1;mi2->newSlot=-1;
                mi2->oldPage=pageID;mi2->oldSlot=k;
                myTable->infos.push_back(mi2);
                ModifyInfo* mi=new ModifyInfo;
                mi->data=myData;
                mi->newPage=pageID;mi->newSlot=i;
                mi->oldPage=-1;mi->oldSlot=-1;
                myTable->infos.push_back(mi);
            }
            else
            {
                updated.push_back(myData);
                ModifyInfo* mi2=new ModifyInfo;
                mi2->data=myData2;
                mi2->newPage=-1;mi2->newSlot=-1;
                mi2->oldPage=pageID;mi2->oldSlot=k;
                myTable->infos.push_back(mi2);
            }
        }
    }
    myIndex=myTable->getClusteredIndex();
    int m=reserves.size();
    needChange=false;
    if ((m==0||eleNum>reserves[m-1])&&myIndex!=0)
    {
        needChange=true;
        int num,offset,colID=myTable->getClusteredID();
        myTable->cols.getByOrder(colID,num,offset);
        lastData->getValue(num,offset,&myTable->cols.cols[colID],myValue);
        myIndex->deleteData(&myValue,pageID,-1);
    }
    delete lastData;
    return _deleteData();
}

bool MyPage::findData(vector<int> &slots,vector<MyData*> &res)
{
    int eleNum=*(int*)(page+8188);
    int* next,*ele,i,m=slots.size();
    if (slots[0]>-1)
    {
        for (i=0;i<m;++i)
            if (slots[i]<=eleNum&&slots[i]>0)
            {
                ele=(int*)(page+8188-slots[i]*4);
                next=(int*)(page+8184-slots[i]*4);
                MyData *myData=new MyData(page,*ele,*next-*ele);
                res.push_back(myData);
            }
    }else
    {
        int k=0;
        while (k<eleNum)
        {
            ele=next;++k;next-=1;
            MyData *myData=new MyData(page,*ele,*next-*ele);
            res.push_back(myData);
        }
    }
    return true;
}

bool MyPage::findAllData(vector<MyData*> &res,vector<int> &pages,vector<int> &slots)
{
    int eleNum=*(int*)(page+8188);
    int k=0;
    int* next=(int*)(page+8184),*ele;
    while (k<eleNum)
    {
        ele=next;++k;next-=1;
        MyData *myData=new MyData(page,*ele,*next-*ele);
        res.push_back(myData);
        pages.push_back(pageID);
        slots.push_back(k);
    }
    return true;
}

int MyPage::deleteAllData()
{
    spaceLeft=8184;
    memset(page,0,PAGE_SIZE);
    bm->markDirty(index);
    return spaceLeft;
}