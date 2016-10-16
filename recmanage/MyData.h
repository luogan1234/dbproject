//
// Created by luogan on 16-10-14.
//

#ifndef DBPROJECT_MYDATA_H
#define DBPROJECT_MYDATA_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include "../consts.h"
#include "MyCol.h"

class MyData
{
public:
    char* data;
    int len;

    MyData(char* d,int offset,int l)
    {
        len=l;data=new char[2000];
        memcpy(data,d+offset,l);
    }

    void setData(std::string d)
    {
        data=new char[2000];
        len=d.size();
        memcpy(data,(char*)d.c_str(),len);
    }

    void print()
    {
        int i;
        for (i=0;i<len;++i)
            printf("%c",data[i]);
        printf("\n");
    }

    ~MyData()
    {
        delete []data;
    }

    bool format(int p,MyCol* myCol,char* &res,int &dataLen);

    bool format(std::string word,MyCol* myCol,char* &res,int &dataLen);
    //num是第几个varchar
    bool getValue(int num,int offset,MyCol* myCol,bool &isNull,char* &res,int &dataLen);

    bool setValue(int num,int offset,MyCol* myCol,bool isNull,char* res,int dataLen);
};

#endif //DBPROJECT_MYDATA_H