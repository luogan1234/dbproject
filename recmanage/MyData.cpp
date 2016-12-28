//
// Created by luogan on 16-10-15.
//

#include "MyData.h"

bool MyData::format(int p, MyCol *myCol, MyValue &v)
{
    if (myCol==0)
        return false;
    if (myCol->type==TYPE_INT)
    {
        v.type=TYPE_INT;
        v.isNull=false;
        v.res=new char[4];
        memmove(v.res,(char*)&p,4);
        v.dataLen=4;
        return true;
    }
    return false;
}

bool MyData::format(std::string word, MyCol *myCol, MyValue &v,bool isNull)
{
    if (myCol==0)
        return false;
    if (myCol->type==TYPE_CHAR)
    {
        StaticMethod::addBlank(word,myCol->len);
        v.type=TYPE_CHAR;
        v.isNull=isNull;
        v.dataLen=myCol->len;
        v.res=new char[v.dataLen];
        memmove(v.res,(char*)word.c_str(),v.dataLen);
        return true;
    }
    if (myCol->type==TYPE_VARCHAR)
    {
        v.type=TYPE_VARCHAR;
        v.isNull=isNull;
        v.dataLen=word.size();
        if (v.dataLen>myCol->len)
            v.dataLen=myCol->len;
        v.res=new char[v.dataLen];
        memmove(v.res,(char*)word.c_str(),v.dataLen);
        return true;
    }
    return false;
}

//num是第几个varchar
bool MyData::getValue(int num,int offset,MyCol* myCol,MyValue &v)
{
    if (myCol==0)
        return false;
    v.type=myCol->type;
    char* d=data+offset;
    switch (myCol->type)
    {
        case TYPE_VARCHAR:
        {
            while (num>0)
            {
                while (d[0]!=StaticMethod::p3)
                    d+=1;
                d+=1;--num;
            }
            if (d[0]=='1')
                v.isNull=true;
            else
                v.isNull=false;
            d+=1;v.dataLen=0;v.res=d;
            while (d[0]!=StaticMethod::p3)
                d+=1,++v.dataLen;
            break;
        }
        case TYPE_INT:
            if (d[0]=='1')
                v.isNull=true;
            else
                v.isNull=false;
            v.res=d+1;
            v.dataLen=4;
            break;
        case TYPE_CHAR:
            if (d[0]=='1')
                v.isNull=true;
            else
                v.isNull=false;
            v.res=d+1;
            v.dataLen=myCol->len;
            break;
    }
    return true;
}

bool MyData::setValue(int num,int offset,MyCol* myCol,MyValue &v)
{
    if (myCol==0||v.type!=myCol->type)
        return false;
    char* d=data+offset;int pos=offset;
    switch (myCol->type)
    {
        case TYPE_VARCHAR:
        {
            while (num>0)
            {
                while (d[0]!=StaticMethod::p3)
                    d+=1,++pos;
                d+=1;--num;++pos;
            }
            if (v.isNull)
                d[0]='1';
            else
                d[0]='0';
            d+=1;++pos;
            int l=pos;
            int delta=v.dataLen;
            char *dd=d;
            while (dd[0]!=StaticMethod::p3)
                dd+=1,++pos,--delta;
            char* tmp=new char[len+delta];
            memmove(tmp,data,l);
            memmove(tmp+l,v.res,v.dataLen);
            memmove(tmp+l+v.dataLen,data+pos,len-pos);
            len+=delta;
            delete data;
            data=tmp;
            break;
        }
        case TYPE_INT:
            if (v.isNull)
                d[0]='1';
            else
                d[0]='0';
            memmove(d+1,v.res,4);
            break;
        case TYPE_CHAR:
            if (v.dataLen!=myCol->len)
                return false;
            if (v.isNull)
                d[0]='1';
            else
                d[0]='0';
            memmove(d+1,v.res,myCol->len);
            break;
    }
    return true;
}