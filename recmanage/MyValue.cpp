//
// Created by luogan on 16-10-29.
//

#include "MyValue.h"
#include "../consts.h"
#include <iostream>
using namespace std;

void MyValue::get(int valueType,int valueLen,bool canNull,char *pos,int len)
{
    type=valueType;
    if (canNull)
    {
        isNull=(*pos!='0');
        res=pos+1;
    }else
    {
        isNull=false;
        res=pos;
    }
    switch (valueType)
    {
        case TYPE_INT:
            dataLen=4;
            break;
        case TYPE_CHAR:
            dataLen=valueLen;
            break;
        case TYPE_VARCHAR:
            dataLen=len;
            if (canNull)
                --dataLen;
            break;
        default:
            ;
    }
}

void MyValue::print()
{
    int i;
    switch (type)
    {
        case TYPE_INT:
            cout<<*(int*)res<<endl;
            break;
        case TYPE_CHAR:
            for (i=0;i<dataLen;++i)
            {
                cout<<res[i];
            }
            cout<<endl;
            break;
        case TYPE_VARCHAR:
            for (i=0;i<dataLen;++i)
            {
                cout<<res[i];
            }
            cout<<endl;
            break;
        default:
            ;
    }
}

int MyValue::compare(MyValue* v)
{
    if (type!=v->type)
        return COMPARE_UNDEFINED;
    if (isNull||v->isNull)
    {
        if (isNull&&v->isNull)
            return COMPARE_EQUAL;
        if (isNull)
            return COMPARE_SMALLER;
        return COMPARE_LARGER;
    }
    int i;
    switch (type)
    {
        case TYPE_INT:
            int p1,p2;
            p1=*(int*)res;
            p2=*(int*)v->res;
            if (p1==p2)
                return COMPARE_EQUAL;
            if (p1>p2)
                return COMPARE_LARGER;
            if (p1<p2)
                return COMPARE_SMALLER;
            break;
        case TYPE_CHAR:
            if (dataLen!=v->dataLen)
                return COMPARE_UNDEFINED;
            for (i=0;i<dataLen;++i)
            {
                if (res[i]>v->res[i])
                    return COMPARE_LARGER;
                if (res[i]<v->res[i])
                    return COMPARE_SMALLER;
            }
            return COMPARE_EQUAL;
        case TYPE_VARCHAR:
            int n=dataLen;
            if (v->dataLen<n)
                n=v->dataLen;
            for (i=0;i<n;++i)
            {
                if (res[i]>v->res[i])
                    return COMPARE_LARGER;
                if (res[i]<v->res[i])
                    return COMPARE_SMALLER;
            }
            if (dataLen>n)
                return COMPARE_LARGER;
            if (v->dataLen>n)
                return COMPARE_SMALLER;
            return COMPARE_EQUAL;
    }
    return COMPARE_UNDEFINED;
}

int MyValue::compareNoNull(MyValue *v)
{
    if (isNull||v->isNull)
    {
        return COMPARE_UNDEFINED;
    }
    return compare(v);
}

int MyValue::compare(MyValue* v1,MyValue* v2)
{
    if (v1->type!=v2->type||v1->isNull||v2->isNull)
        return COMPARE_UNDEFINED;
    int i;
    switch (v1->type)
    {
        case TYPE_INT:
            int p1,p2;
            p1=*(int*)v1->res;
            p2=*(int*)v2->res;
            if (p1==p2)
                return COMPARE_EQUAL;
            if (p1>p2)
                return COMPARE_LARGER;
            if (p1<p2)
                return COMPARE_SMALLER;
            break;
        case TYPE_CHAR:
            if (v1->dataLen!=v2->dataLen)
                return COMPARE_UNDEFINED;
            for (i=0;i<v1->dataLen;++i)
            {
                if (v1->res[i]>v2->res[i])
                    return COMPARE_LARGER;
                if (v1->res[i]<v2->res[i])
                    return COMPARE_SMALLER;
            }
            return COMPARE_EQUAL;
        case TYPE_VARCHAR:
            int n=v1->dataLen;
            if (v2->dataLen<n)
                n=v2->dataLen;
            for (i=0;i<n;++i)
            {
                if (v1->res[i]>v2->res[i])
                    return COMPARE_LARGER;
                if (v1->res[i]<v2->res[i])
                    return COMPARE_SMALLER;
            }
            if (v1->dataLen>n)
                return COMPARE_LARGER;
            if (v2->dataLen>n)
                return COMPARE_SMALLER;
            return COMPARE_EQUAL;
    }
    return COMPARE_UNDEFINED;
}

int MyValue::compareNoNull(MyValue *v1,MyValue *v2)
{
    if (v1->isNull||v2->isNull)
    {
        return COMPARE_UNDEFINED;
    }
    return compare(v1,v2);
}