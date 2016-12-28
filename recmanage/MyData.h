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
#include "TableCols.h"

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

    MyData(TableCols cols)
    {
        int i,j=0;len=0;
        for (i=0;i<cols.n;++i)
            switch (cols.cols[i].type)
            {
                case TYPE_INT:
                    len+=5;
                    j+=5;
                    break;
                case TYPE_CHAR:
                    len+=cols.cols[i].len+1;
                    j+=cols.cols[i].len+1;
                    break;
                case TYPE_VARCHAR:
                    len+=2;
                    break;
            }
        data=new char[len];
        while (j+1<len)
        {
            data[j+1]=StaticMethod::p3;
            j+=2;
        }
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
    //格式化数据成存储时的形式，int对应char[4]，char是补全空格，varchar是给定的长度
    static bool format(int p,MyCol* myCol,MyValue &v);

    static bool format(std::string word,MyCol* myCol,MyValue &v,bool isNull=false);

    //num是第几个varchar，offset是偏移量
    bool getValue(int num,int offset,MyCol* myCol,MyValue &v);

    bool setValue(int num,int offset,MyCol* myCol,MyValue &v);
};

#endif //DBPROJECT_MYDATA_H