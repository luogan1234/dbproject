//
// Created by luogan on 16-10-29.
//

#ifndef DBPROJECT_MYVALUE_H
#define DBPROJECT_MYVALUE_H


#include "../consts.h"

class MyValue {
public:
    bool isNull;
    char* res;
    int dataLen;
    int type;

    MyValue()
    {
    }

    int compare(MyValue* v);

    static int compare(MyValue* v1,MyValue* v2);

    void print();

    void get(int valueType,int valueLen,bool canNull,char *pos,int len);
};


#endif //DBPROJECT_MYVALUE_H
