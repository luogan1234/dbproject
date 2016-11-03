//
// Created by luogan on 16-10-15.
//

#include "MyPage.h"

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
    int* eleNum=(int*)(page+8188);
    int k=0,i=0;
    int* next=(int*)(page+8184),*ele;
    reserves.clear();
    while (k<*eleNum)
    {
        ele=next;++k;next-=1;
        MyData* myData=new MyData(page,*ele,*next-*ele);
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
    for (i=0;i<m;++i)
    {
        if (i<reserves[i]-1)
        {
            pos=*(int*)(page+8188-4*reserves[i]);
            len=*(int*)(page+8184-4*reserves[i])-pos;
            if (len>0)
            {
                memmove(page+last,page+pos,len);
                last+=len;
            }
            position.push_back(last);
        }else
        {
            last=*(int*)(page+8184-4*reserves[i]);
            position.push_back(last);
        }
    }
    for (i=0;i<=m;++i)
    {
        *(int*)(page+8184-4*i)=position[i];
    }
    *eleNum=reserves.size();
    spaceLeft=8184-*(int*)(page+8184-4**eleNum)-4**eleNum;
    return spaceLeft;
}

int MyPage::updateData(Constraints* con,Updates* upd,vector<MyData*> &updated)
{
    int* eleNum=(int*)(page+8188);
    int k=0,i=0;
    int* next=(int*)(page+8184),*ele;
    reserves.clear();
    while (k<*eleNum)
    {
        ele=next;++k;next-=1;
        MyData *myData=new MyData(page,*ele,*next-*ele);
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
                ModifyInfo* mi=new ModifyInfo;
                mi->data=myData;
                mi->newPage=pageID;mi->newSlot=i;
                mi->oldPage=-1;mi->oldSlot=-1;
                myTable->infos.push_back(mi);
                ModifyInfo* mi2=new ModifyInfo;
                mi2->data=myData2;
                mi2->newPage=-1;mi2->newSlot=-1;
                mi2->oldPage=pageID;mi2->oldSlot=k;
                myTable->infos.push_back(mi);
            }
            else
            {
                updated.push_back(myData);
            }
        }
    }
    return _deleteData();
}

bool MyPage::findData(vector<int> &slots,vector<MyData*> &res)
{
    int eleNum=*(int*)(page+8188);
    int* next,*ele,i,m=slots.size();
    for (i=0;i<m;++i)
        if (slots[i]<=eleNum&&slots[i]>0)
        {
            ele=(int*)(page+8188-slots[i]*4);
            next=(int*)(page+8184-slots[i]*4);
            MyData *myData=new MyData(page,*ele,*next-*ele);
            res.push_back(myData);
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