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
#include "../StaticMethod.h"
#include "MyValue.h"

class MyData
{
public:
    char* data;
    int len;

    MyData(char* d,int offset,int l)
    {
        len=l;data=new char[l];
        memmove(data,d+offset,l);
    }

    MyData(std::string d)
    {
        setData(d);
    }

    void setData(std::string d)
    {
        len=d.size();
        data=new char[len];
        memmove(data,(char*)d.c_str(),len);
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

    static bool format(int p,MyCol* myCol,MyValue &v);

    static bool format(std::string word,MyCol* myCol,MyValue &v);

    //num是第几个varchar
    bool getValue(int num,int offset,MyCol* myCol,MyValue &v);

    bool setValue(int num,int offset,MyCol* myCol,MyValue &v);
};

#endif //DBPROJECT_MYDATA_H