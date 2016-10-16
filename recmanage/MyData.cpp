//
// Created by luogan on 16-10-15.
//

#include "MyData.h"
#include "../StaticMethod.h"

bool MyData::format(int p,MyCol* myCol,char* &res,int &dataLen)
{
    if (myCol==0)
        return false;
    if (myCol->type==TYPE_INT)
    {
        res=(char*) &p;
        dataLen=4;
        return true;
    }
    return false;
}

bool MyData::format(std::string word,MyCol* myCol,char* &res,int &dataLen)
{
    if (myCol==0)
        return false;
    if (myCol->type==TYPE_CHAR)
    {
        StaticMethod::addBlank(word,myCol->len);
        res=(char*)word.c_str();
        dataLen=myCol->len;
        return true;
    }
    if (myCol->type==TYPE_VARCHAR)
    {
        res=(char*)word.c_str();
        dataLen=word.size();
        if (dataLen>myCol->len)
            dataLen=myCol->len;
        return true;
    }
    return false;
}
//num是第几个varchar
bool MyData::getValue(int num,int offset,MyCol* myCol,bool &isNull,char* &res,int &dataLen)
{
    if (myCol==0)
        return false;
    char* d=data+offset;
    switch (myCol->type)
    {
        case TYPE_VARCHAR:
        {
            while (num>0)
            {
                while (d[0]!='$')
                    d+=1;
                d+=1;--num;
            }
            if (d[0]=='1')
                isNull=true;
            else
                isNull=false;
            d+=1;dataLen=0;res=d;
            while (d[0]!='$')
                d+=1,++dataLen;
            break;
        }
        case TYPE_INT:
            if (d[0]=='1')
                isNull=true;
            else
                isNull=false;
            res=d+1;
            dataLen=4;
            break;
        case TYPE_CHAR:
            if (d[0]=='1')
                isNull=true;
            else
                isNull=false;
            res=d+1;
            dataLen=myCol->len;
            break;
    }
    return true;
}

bool MyData::setValue(int num,int offset,MyCol* myCol,bool isNull,char* res,int dataLen)
{
    if (myCol==0)
        return false;
    char* d=data+offset;int pos=offset;
    switch (myCol->type)
    {
        case TYPE_VARCHAR:
        {
            while (num>0)
            {
                while (d[0]!='$')
                    d+=1,++pos;
                d+=1;--num;++pos;
            }
            if (isNull)
                d[0]='1';
            else
                d[0]='0';
            d+=1;++pos;
            char* tmp=new char[1000],*dd=d;
            int delta=dataLen;
            while (dd[0]!='$')
                dd+=1,++pos,--delta;
            memcpy(tmp,dd,len-pos);
            memcpy(d,res,dataLen);
            memcpy(d+dataLen,tmp,len-pos);
            len+=delta;
            break;
        }
        case TYPE_INT:
            if (isNull)
                d[0]='1';
            else
                d[0]='0';
            memcpy(d+1,res,4);
            break;
        case TYPE_CHAR:
            if (isNull)
                d[0]='1';
            else
                d[0]='0';
            memcpy(d+1,res,myCol->len);
            break;
    }
    return true;
}