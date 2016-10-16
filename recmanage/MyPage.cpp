//
// Created by luogan on 16-10-15.
//

#include "MyPage.h"

int MyPage::insertData(MyData &data)
{
    int* eleNum=(int*)(page+8188);
    int last=*(int*)(page+8184-4**eleNum);
    memcpy(page+last,data.data,data.len);
    *eleNum+=1;
    *(int*)(page+8184-4*(*eleNum))=last+data.len;
    spaceLeft=8184-last-data.len-4**eleNum;
    bm->markDirty(index);
    return spaceLeft;
}

int MyPage::searchData(Constraints* con,std::vector<MyData> &res)
{
    int* eleNum=(int*)(page+8188);
    int k=1;
    int* next=(int*)(page+8184),*ele;
    while (k<=*eleNum)
    {
        ele=next;++k;next-=4;
        MyData myData(page,*ele,*next-*ele);
        if (con->checkData(myData))
            res.push_back(myData);
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
        ele=next;++k;next-=4;
        MyData myData(page,*ele,*next-*ele);
        if (!con->checkData(myData))
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
    for (i=0;i<reserves.size();++i)
    {
        if (i<reserves[i]-1)
        {
            pos=*(int*)(page+8188-4*reserves[i]);
            len=*(int*)(page+8184-reserves[i])-pos;
            if (len>0)
            {
                memmove(page+last,page+pos,len);
                last+=len;
            }
        }else
        {
            last=*(int*)(page+8184-4*reserves[i]);
        }
    }
    for (i=0;i<reserves.size();++i)
    {
        *(int*)(page+8184-4*i)=*(int*)(page+8188-4*reserves[i]);
    }
    *(int*)(page+8184-4*reserves.size())=*(int*)(page+8184-4**eleNum);
    *eleNum=reserves.size();
    spaceLeft=8184-*(int*)(page+8184-4**eleNum)-4**eleNum;
    return spaceLeft;
}

int MyPage::updateData(Constraints* con,Updates* upd,std::vector<MyData> &updated)
{
    int* eleNum=(int*)(page+8188);
    int k=0;
    int* next=(int*)(page+8184),*ele;
    reserves.clear();
    while (k<*eleNum)
    {
        ele=next;++k;next-=4;
        MyData myData(page,*ele,*next-*ele);
        if (!con->checkData(myData))
            reserves.push_back(k);
        else
        {
            bm->markDirty(index);
            int oldLen=myData.len;
            upd->update(myData);
            if (oldLen==myData.len)
            {
                memmove(ele,myData.data,myData.len);
                reserves.push_back(k);
            }
            else
            {
                updated.push_back(myData);
            }
        }
    }
    return _deleteData();
}