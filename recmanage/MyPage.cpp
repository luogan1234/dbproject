//
// Created by luogan on 16-10-15.
//

#include "MyPage.h"

int MyPage::insertData(MyData *data)
{
    int* eleNum=(int*)(page+8188);
    int last=*(int*)(page+8184-4**eleNum);
    memcpy(page+last,data->data,data->len);
    *eleNum+=1;
    *(int*)(page+8184-4*(*eleNum))=last+data->len;
    spaceLeft=8184-last-data->len-4**eleNum;
    bm->markDirty(index);
    return spaceLeft;
}

int MyPage::searchData(Constraints* con,std::vector<MyData*> &res)
{
    int* eleNum=(int*)(page+8188);
    int k=1;
    int* next=(int*)(page+8184),*ele;
    while (k<=*eleNum)
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
    int k=0;
    int* next=(int*)(page+8184),*ele;
    reserves.clear();
    while (k<*eleNum)
    {
        ele=next;++k;next-=1;
        MyData myData=MyData(page,*ele,*next-*ele);
        if (!con->checkData(&myData))
            reserves.push_back(k);
        else
            bm->markDirty(index);
    }
    return _deleteData();
}

int MyPage::_deleteData()
{
    int* eleNum=(int*)(page+8188);
    int i,last=0,len,pos;
    std::vector<int> position;
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

int MyPage::updateData(Constraints* con,Updates* upd,std::vector<MyData*> &updated)
{
    int* eleNum=(int*)(page+8188);
    int k=0;
    int* next=(int*)(page+8184),*ele;
    reserves.clear();
    while (k<*eleNum)
    {
        ele=next;++k;next-=1;
        MyData *myData=new MyData(page,*ele,*next-*ele);
        if (!con->checkData(myData))
        {
            reserves.push_back(k);
            delete myData;
        }
        else
        {
            int oldLen=myData->len;
            if (!upd->update(myData))
            {
                reserves.push_back(k);
                delete myData;
            }
            else
            if (oldLen==myData->len)
            {
                bm->markDirty(index);
                memmove(page+*ele,myData->data,myData->len);
                reserves.push_back(k);
                delete myData;
            }
            else
            {
                updated.push_back(myData);
            }
        }
    }
    return _deleteData();
}