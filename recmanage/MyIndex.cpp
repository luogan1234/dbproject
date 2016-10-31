//
// Created by luogan on 16-10-29.
//

#include "MyIndex.h"
#include "MyTable.h"
#include "MyPage.h"

using namespace std;

void MyIndex::init()
{
    int index0;
    char *page0=bm->getPage(fileID,0,index0);
    *(short*)page0=colID;
    *(page0+2)=type;
    *(int*)(page0+4)=valueType;
    *(int*)(page0+8)=valueLen;
    totalUsed=2;
    rootPage=1;
    *(int*)(page0+12)=totalUsed;
    *(int*)(page0+16)=rootPage;
    bm->markDirty(index0);
    char *page1=bm->getPage(fileID,1,index0);
    int i;
    for (i=0;i<PAGE_SIZE/4;++i)
        *(int*)(page1+i*4)=0;
    *(int*)page1=PAGE_LEAF;
    *(int*)(page1+8188)=0;
    *(int*)(page1+8184)=4;
}

void MyIndex::getInfo()
{
    int index0;
    char *page0=bm->getPage(fileID,0,index0);
    colID=*(short*)page0;
    type=*(page0+2);
    valueType=*(int*)(page0+4);
    valueLen=*(int*)(page0+8);
    totalUsed=*(int*)(page0+12);
    rootPage=*(int*)(page0+16);
}

bool MyIndex::insertDataClustered(MyData* myData)
{
    if (type!=INDEX_CLUSTERED)
        return false;
    int num,offset;
    myTable->cols.getByOrder(colID,num,offset);
    MyValue value;
    myData->getValue(num,offset,&myTable->cols.cols[colID],value);
    int pageNow=rootPage,comRes,resPage=-1;
    while (true)
    {
        char *page=bm->getPage(fileID,pageNow,index);
        int pageType=*(int*)page,eleNum;
        int head=0;
        if (pageType==PAGE_NORMAL)
        {
            head=4;
            if (type==INDEX_UNCLUSTERED)
                head+=8;
        }else
        {
            if (type==INDEX_CLUSTERED)
                head=4;
            else
                head=8;
        }
        eleNum=*(int*)(page+8188);
        int k=1;
        int* next=(int*)(page+8184),*ele;
        while (k<=eleNum)
        {
            ele=next;++k;next-=1;
            MyValue v;
            v.isNull=false;
            v.type=valueType;
            v.res=page+*ele+head;
            switch (valueType)
            {
                case TYPE_INT:
                    v.dataLen=4;
                    break;
                case TYPE_CHAR:
                    v.dataLen=valueLen;
                    break;
                case TYPE_VARCHAR:
                    v.dataLen=*next-*ele-head;
                    break;
                default:
                    ;
            }
            comRes=value.compare(&v);
            if (comRes==COMPARE_SMALLER||comRes==COMPARE_EQUAL||pageType==PAGE_LEAF&&k>eleNum)
            {
                if (pageType==PAGE_NORMAL)
                {
                    pageNow=*(int*)(page+*ele);
                    break;
                }else
                {
                    resPage=*(int*)(page+*ele);
                    break;
                }
            }
        }
        if (resPage!=-1)
            break;
    }

}

bool MyIndex::findData(MyValue* value1,int type1,MyValue* value2,int type2,vector<pair<int,int>> &res)
{
    res.clear();
    if (totalUsed==0)
        return true;
    if (type1!=COMPARE_UNDEFINED&&type1!=COMPARE_SMALLER&&type1!=COMPARE_SMALLER_EQUAL)
        return true;
    if (type2!=COMPARE_UNDEFINED&&type2!=COMPARE_LARGER&&type2!=COMPARE_LARGER_EQUAL)
        return true;
    int comRes=MyValue::compare(value1,value2);
    if (comRes==COMPARE_LARGER||comRes==COMPARE_EQUAL&&(type1==COMPARE_SMALLER||type2==COMPARE_LARGER))
        return true;
    int pageNow=rootPage,leftPage,leftSlot=-1,rightPage,rightSlot=-1;
    while (true)
    {
        char *page=bm->getPage(fileID,pageNow,index);
        int pageType=*(int*)page,eleNum;
        int head=0;
        if (pageType==PAGE_NORMAL)
        {
            head=4;
            if (type==INDEX_UNCLUSTERED)
                head+=8;
        }else
        {
            if (type==INDEX_CLUSTERED)
                head=4;
            else
                head=8;
        }
        eleNum=*(int*)(page+8188);
        int k=1;
        int* next=(int*)(page+8184),*ele;
        while (k<=eleNum)
        {
            ele=next;++k;next-=1;
            if (type1!=COMPARE_UNDEFINED)
            {
                MyValue v;
                v.isNull=false;
                v.type=valueType;
                v.res=page+*ele+head;
                switch (valueType)
                {
                    case TYPE_INT:
                        v.dataLen=4;
                        break;
                    case TYPE_CHAR:
                        v.dataLen=valueLen;
                        break;
                    case TYPE_VARCHAR:
                        v.dataLen=*next-*ele-head;
                        break;
                    default:
                        ;
                }
                comRes=value1->compare(&v);
            }
            if (type1==COMPARE_UNDEFINED||comRes==COMPARE_SMALLER&&(type1==COMPARE_SMALLER_EQUAL||type1==COMPARE_SMALLER)||comRes==COMPARE_EQUAL&&type1==COMPARE_SMALLER_EQUAL)
            {
                if (pageType==PAGE_NORMAL)
                {
                    pageNow=*(int*)(page+*ele);--k;
                    break;
                }else
                {
                    leftPage=pageNow;--k;
                    leftSlot=k;
                    break;
                }
            }
        }
        if (k>eleNum)
            return true;
        if (leftSlot!=-1)
            break;
    }
    pageNow=rootPage;
    while (true)
    {
        char *page=bm->getPage(fileID,pageNow,index);
        int pageType=*(int*)page,eleNum;
        int head=0;
        if (pageType==PAGE_NORMAL)
        {
            head=4;
            if (type==INDEX_UNCLUSTERED)
                head+=8;
        }else
        {
            if (type==INDEX_CLUSTERED)
                head=4;
            else
                head=8;
        }
        eleNum=*(int*)(page+8188);
        int k=1;
        bool p=false;
        int* next=(int*)(page+8184),*ele;
        while (k<=eleNum)
        {
            ele=next;++k;next-=1;
            if (type2!=COMPARE_UNDEFINED)
            {
                MyValue v;
                v.isNull=false;
                v.type=valueType;
                v.res=page+*ele+head;
                switch (valueType)
                {
                    case TYPE_INT:
                        v.dataLen=4;
                        break;
                    case TYPE_CHAR:
                        v.dataLen=valueLen;
                        break;
                    case TYPE_VARCHAR:
                        v.dataLen=*next-*ele-head;
                        break;
                    default:
                        ;
                }
                comRes=value2->compare(&v);
            }
            if (type2==COMPARE_UNDEFINED||comRes==COMPARE_LARGER&&(type2==COMPARE_LARGER_EQUAL||type2==COMPARE_LARGER)||comRes==COMPARE_EQUAL&&type2==COMPARE_LARGER_EQUAL)
            {
                p=true;
                if (pageType==PAGE_NORMAL)
                {
                    pageNow=*(int*)(page+*ele);
                }else
                {
                    rightPage=pageNow;
                    rightSlot=k-1;
                }
                if (comRes==COMPARE_EQUAL&&type2==COMPARE_LARGER_EQUAL&&type!=INDEX_UNCLUSTERED)
                    break;
            }
            else
            {
                if (type==INDEX_CLUSTERED)
                {
                    p=true;
                    if (pageType==PAGE_NORMAL)
                    {
                        pageNow=*(int*)(page+*ele);
                    }else
                    {
                        rightPage=pageNow;
                        rightSlot=k-1;
                    }
                }
                break;
            }
        }
        if (!p)
            return true;
        if (rightSlot!=-1)
            break;
    }
    while (true)
    {
        char *page=bm->getPage(fileID,leftPage,index);
        int eleNum=*(int*)(page+8188),n,i;
        if (leftPage!=rightPage)
            n=eleNum;
        else
            n=rightSlot;
        for (i=leftSlot;i<=n;++i)
        {
            int *ele=(int*)(page+8188-4*i);
            if (type==INDEX_CLUSTERED)
            {
                res.push_back(make_pair(*(int*)(page+*ele),-1));
            } else
            {
                res.push_back(make_pair(*(int*)(page+*ele),*(int*)(page+*ele+4)));
            }
        }
        if (leftPage==rightPage)
            break;
        int ele=*(int*)(page+8188-4*eleNum);
        int tar=*(int*)(page+ele);
        leftPage=tar;leftSlot=1;
    }
}

bool MyIndex::searchData(MyValue* value,int page,int slot,int pp)
{
    if (type==INDEX_CLUSTERED&&slot>=0)
        return false;
    if (type!=INDEX_CLUSTERED&&slot==-1)
        return false;
    int pageNow=rootPage,comRes;
    pages.clear();nows.clear();slots.clear();indexs.clear();
    while (true)
    {
        char* page0=bm->getPage(fileID,pageNow,index);
        int pageType=*(int*)page0,eleNum;
        int head=0,head0=0;
        if (pageType==PAGE_NORMAL)
        {
            head=head0=4;
            if (type==INDEX_UNCLUSTERED)
                head+=8;
        }else
        if (type==INDEX_CLUSTERED)
            head=4;
        else
            head=8;
        eleNum=*(int*)(page0+8188);
        int k=1;
        int* next=(int*)(page0+8184),*ele;
        while (k<=eleNum)
        {
            ele=next;++k;next-=1;
            MyValue v;
            v.isNull=false;
            v.type=valueType;
            v.res=page0+*ele+head;
            switch (valueType)
            {
                case TYPE_INT:
                    v.dataLen=4;
                    break;
                case TYPE_CHAR:
                    v.dataLen=valueLen;
                    break;
                case TYPE_VARCHAR:
                    v.dataLen=*next-*ele-head;
                    break;
                default:
                    ;
            }
            comRes=value->compare(&v);
            if (comRes==COMPARE_SMALLER||comRes==COMPARE_EQUAL||k>eleNum)
            {
                if (k<=eleNum&&comRes==COMPARE_EQUAL)
                {
                    if (type==INDEX_UNCLUSTERED)
                    {
                        int _page=*(int*)(page0+*ele+head0),_slot=*(int*)(page0+*ele+head0+4);
                        if (page>_page||page==_page&&slot>_slot)
                            continue;
                    }
                }
                if (pageType==PAGE_NORMAL)
                {
                    pages.push_back(page0);
                    nows.push_back(pageNow);
                    indexs.push_back(index);
                    slots.push_back(k-1);
                    pageNow=*(int*)(page0+*ele);
                    break;
                } else
                {
                    pages.push_back(page0);
                    nows.push_back(pageNow);
                    indexs.push_back(index);
                    int _page=-1,_slot=-1;
                    if (comRes==COMPARE_LARGER)
                        slots.push_back(k);
                    else
                    {
                        slots.push_back(k-1);
                        _page=*(int*)page0+*ele;
                        if (type!=INDEX_CLUSTERED)
                            _slot=*(int*)page0+*ele+4;
                    }
                    if (pp==1&&type!=INDEX_UNCLUSTERED&&comRes==COMPARE_EQUAL)
                        return false;
                    if (pp==2&&(comRes!=COMPARE_EQUAL||page!=_page||slot!=_slot))
                        return false;
                    return true;
                }
            }
        }
    }
}

bool MyIndex::insertData(MyValue* value,int page,int slot)
{
    if (searchData(value,page,slot,1))
    {
        char *page0;
        int k,eleNum;
        MyValue vl,vn,vr;
        MyValue* values=new MyValue[2000];
        vl.res=new char[2000];vn.res=new char[2000];vr.res=new char[2000];
        *(int*)vl.res=page;
        if (type==INDEX_CLUSTERED)
        {
            vl.dataLen=value->dataLen+4;
            memmove(vl.res+4,value->res,value->dataLen);
        }else
        {
            vl.dataLen=value->dataLen+8;
            *(int*)(vl.res+4)=slot;
            memmove(vl.res+8,value->res,value->dataLen);
        }
        vn.dataLen=vr.dataLen=0;
        int m=pages.size()-1,o;
        for (o=m;o>=0;--o)
        {
            if (vl.dataLen==0&&vn.dataLen==0&&vr.dataLen==0)
                break;
            page0=pages[o];k=slots[o];
            int i,j=0,tot=0;eleNum=*(int*)page0+8188;
            for (i=1;i<=eleNum+1;++i)
            {
                if (i==k&&vl.dataLen>0)
                {
                    ++j;
                    values[j].res=vl.res;
                    values[j].dataLen=vl.dataLen;
                    tot+=vl.dataLen+4;
                }
                if (i==k&&vn.dataLen>0)
                {
                    ++j;
                    values[j].res=vn.res;
                    values[j].dataLen=vn.dataLen;
                    tot+=vn.dataLen+4;
                }
                if (i<=eleNum&&(i!=k||vn.dataLen==0))
                {
                    ++j;
                    int t1=*(int*)(page0+8188-i*4),t2=*(int*)(page0+8184-i*4);
                    values[j].dataLen=t2-t1;
                    values[j].res=page0+t1;
                    tot+=t2-t1+4;
                }
                if (i==k&&vr.dataLen>0)
                {
                    ++j;
                    values[j].res=vr.res;
                    values[j].dataLen=vr.dataLen;
                    tot+=vr.dataLen+4;
                }
            }
            int ii=j+1,offset,p,nextPage=*(int*)(page0+*(int*)(page0+8184-eleNum*4)),prevPage=*(&nextPage+1);
            if (tot>8000)
            {
                int index1;
                char *page1=bm->getPage(fileID,totalUsed,index1);
                for (i=0;i<PAGE_SIZE/4;++i)
                    *(int*)(page1+i*4)=0;
                if (o==m)
                    *(int*)page1=PAGE_LEAF;
                else
                    *(int*)page1=PAGE_NORMAL;
                bm->markDirty(index1);
                int tot2=0;
                for (i=1;i<=j;++i)
                {
                    tot2+=values[i].dataLen;
                    if (tot2>tot/2)
                    {
                        ii=i+1;
                        break;
                    }
                }
                offset=4,p=0;
                for (i=ii;i<=j;++i)
                {
                    ++p;
                    memmove(page1+offset,values[i].res,values[i].dataLen);
                    *(int*)(page1+8188-p*4)=offset;
                    offset+=values[i].dataLen;
                }
                *(int*)(page1+8188)=p;
                *(int*)(page1+8184-p*4)=offset;
                if (o==m)
                {
                    *(int*)(page1+offset)=nextPage;
                    *(int*)(page1+offset+4)=nows[o];
                }
                if (o==m)
                {
                    switch (type)
                    {
                        case INDEX_CLUSTERED:
                            memmove(vr.res+4,values[i].res+4,values[i].dataLen+4);
                            vr.dataLen=values[i].dataLen;
                            break;
                        case INDEX_UNCLUSTERED:
                            memmove(vr.res+4,values[i].res,values[i].dataLen);
                            vr.dataLen=values[i].dataLen+4;
                            break;
                        case INDEX_UNCLUSTERED_UNIQUE:
                            memmove(vr.res+4,values[i].res+8,values[i].dataLen-8);
                            vr.dataLen=values[i].dataLen-4;
                            break;
                        default:
                            break;
                    }
                    *(int*)vr.res=totalUsed;
                } else
                {
                    memmove(vr.res+4,values[i].res+4,values[i].dataLen-4);
                    vr.dataLen=values[i].dataLen;
                    *(int*)vr.res=totalUsed;
                }
            }
            offset=4;
            for (i=1;i<ii;++i)
            {
                offset+=values[i].dataLen;
            }
            if (o==m)
            {
                if (tot>8000)
                {
                    *(int*)(page0+offset)=totalUsed;
                    *(int*)(page0+offset+4)=prevPage;
                } else
                {
                    *(int*)(page0+offset)=nextPage;
                    *(int*)(page0+offset+4)=prevPage;
                }
            }
            *(int*)(page0+8188-ii*4)=offset;
            for (i=ii-1;i>=k;--i)
            {
                offset-=values[i].dataLen;
                memmove(page0+offset,values[i].res,values[i].dataLen);
                *(int*)(page0+8188-i*4)=offset;
            }
            bm->markDirty(indexs[o]);
            vl.dataLen=0;
            if (tot>8000||k==eleNum&&(vn.dataLen>0||vr.dataLen>0)||k>eleNum)
            {
                --ii;
                if (o==m)
                {
                    memmove(vn.res+4,values[ii].res+8,values[ii].dataLen-8);
                    vn.dataLen=values[ii].dataLen-4;
                    *(int*)vn.res=nows[o];
                } else
                {
                    memmove(vn.res+4,values[ii].res+4,values[ii].dataLen-4);
                    vn.dataLen=values[ii].dataLen;
                    *(int*)vn.res=nows[o];
                }
            }
            if (tot>8000)
            {
                int index0;
                char *page00=bm->getPage(fileID,0,index0);
                ++totalUsed;
                *(int*)(page00+12)=totalUsed;
                bm->markDirty(index0);
            }
        }
        if (o<0&&vn.dataLen>0&&vr.dataLen>0)
        {
            int index0;
            char *page0=bm->getPage(fileID,totalUsed,index0);
            *(int*)page0=PAGE_NORMAL;
            *(int*)(page0+8188)=2;
            *(int*)(page0+8184)=4;
            memmove(page0+4,vn.res,vn.dataLen);
            *(int*)(page0+8180)=vn.dataLen+4;
            memmove(page0+vn.dataLen+4,vr.res,vr.dataLen);
            *(int*)(page0+8176)=vn.dataLen+vr.dataLen+4;
            bm->markDirty(index0);
            char *page00=bm->getPage(fileID,0,index0);
            rootPage=totalUsed;
            ++totalUsed;
            *(int*)(page00+12)=totalUsed;
            *(int*)(page00+16)=rootPage;
            bm->markDirty(index0);
        }
        delete []values;
        delete vl.res;
        delete vn.res;
        delete vr.res;
        return true;
    }
    return false;
}

bool MyIndex::deleteData(MyValue* value,int page,int slot)
{
    if (searchData(value,page,slot,2))
    {
        char *page0;
        int k,eleNum;
        int m=pages.size()-1,o;
        for (o=m;o>=0;--o)
        {
            page0=pages[o];k=slots[o];
            bm->markDirty(indexs[o]);
            int i,j=0,tot=0;eleNum=*(int*)(page0+8188);
            int *ele,*next=(int*)(page0+8184-k*4);
            for (i=k;i<eleNum;++i)
            {
                ele=next;next-=1;
                int now=*(int*)(page0+8188-i*4),len=*next-*ele;
                memmove(page0+now,page0+*ele,len);
                *ele=now+len;
            }
            if (o==m)
            {
                int now=*(int*)(page0+8188-eleNum*4);ele=(int*)(page0+8184-eleNum*4);
                memmove(page0+now,page0+*ele,8);
            }
            --eleNum;
            *(int*)(page0+8188)=eleNum;
            if (o==m&&eleNum==0||o<m&&eleNum==1)
            {
                if (o==m)
                {
                    int prevPage=*(int*)(page0+4),nextPage=*(int*)(page0+8);
                    if (prevPage>0)
                    {
                        int index1;
                        char* page1=bm->getPage(fileID,prevPage,index1);
                        int *next=(int*)(page1+*(int*)(page1+8184-*(int*)(page1+8188)*4));
                        *next=nextPage;
                        bm->markDirty(index1);
                    }
                    if (nextPage>0)
                    {
                        int index1;
                        char* page1=bm->getPage(fileID,prevPage,index1);
                        int *prev=(int*)(page1+4+*(int*)(page1+8184-*(int*)(page1+8188)*4));
                        *prev=prevPage;
                        bm->markDirty(index1);
                    }
                }
                if (o<m)
                {
                    int pointPage=*(int*)(page0+4);
                    if (o==0)
                    {
                        rootPage=pointPage;
                        char* page00=bm->getPage(fileID,0,index);
                        *(int*)(page00+16)=rootPage;
                        bm->markDirty(index);
                    }else
                    {
                        char* page00=pages[o-1];
                        k=slots[o-1];
                        *(int*)(page00+*(int*)(page00+8188-k*4))=pointPage;
                        bm->markDirty(indexs[o-1]);
                    }
                    return true;
                }
            }
            else
                return true;
        }
    }
    return false;
}